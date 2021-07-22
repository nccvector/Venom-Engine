#include "MyApplication.h"

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/PixelFormat.h>
#include <Magnum/Image.h>

#include <ImGuizmo.h>

#include <Corrade/Containers/GrowableArray.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Primitives/Icosphere.h>

#include <imgui_internal.h>

using namespace Magnum::Math::Literals;

void BeginDockspace();
void EndDockspace();

/****************************************************************************************************/
MyApplication::MyApplication(const Arguments& arguments,
                                size_t indexDataSize,
                                const Vector2i& defaultWindowSize) :
    ImGuiApplication{"My Application", arguments, defaultWindowSize} {

    /* Relayout ImGuizmo */
    ImGuiIO& io = ImGui::GetIO();
    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

    /* Setup buffers */
    m_RBColor = GL::Renderbuffer{};
    m_RBColor.setStorage(GL::RenderbufferFormat::RGBA8, GL::defaultFramebuffer.viewport().size());

    CORRADE_INTERNAL_ASSERT(indexDataSize == 8
                            || indexDataSize == 16
                            || indexDataSize == 32);
    if(indexDataSize == 8) {
        m_IndexFormat = GL::RenderbufferFormat::R8UI;
        m_PixelFormat = PixelFormat::R8UI;
    } else if(indexDataSize == 16) {
        m_IndexFormat = GL::RenderbufferFormat::R16UI;
        m_PixelFormat = PixelFormat::R16UI;
    } else if(indexDataSize == 32) {
        m_IndexFormat = GL::RenderbufferFormat::R32UI;
        m_PixelFormat = PixelFormat::R32UI;
    } else {
        Fatal{} << "Invalid index data size type";
    }

    m_RBObjectIdx = GL::Renderbuffer{};
    m_RBObjectIdx.setStorage(m_IndexFormat, GL::defaultFramebuffer.viewport().size());

    m_RBDepth = GL::Renderbuffer{};
    m_RBDepth.setStorage(GL::RenderbufferFormat::DepthComponent24, GL::defaultFramebuffer.viewport().size());

    m_FrameBuffer = GL::Framebuffer{ GL::defaultFramebuffer.viewport() };
    m_FrameBuffer.attachRenderbuffer(GL::Framebuffer::ColorAttachment{ 0 }, m_RBColor)
        .attachRenderbuffer(GL::Framebuffer::ColorAttachment{ 1 }, m_RBObjectIdx)
        .attachRenderbuffer(GL::Framebuffer::BufferAttachment::Depth,  m_RBDepth)
        .mapForDraw({ { Shaders::Phong::ColorOutput, GL::Framebuffer::ColorAttachment{ 0 } },
                        { Shaders::Phong::ObjectIdOutput, GL::Framebuffer::ColorAttachment{ 1 } } });
    CORRADE_INTERNAL_ASSERT(m_FrameBuffer.checkStatus(GL::FramebufferTarget::Draw) == GL::Framebuffer::Status::Complete);

    // CONFIGURING IMGUI ===============================================================
    // SETTING CONFIG FLAGS FOR DOCKING ### ADDED LATER
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // SETTING DEFAULT FONT
    io.Fonts->AddFontFromFileTTF("../assets/fonts/OpenSans-Regular.ttf", 18.0f);
    io.FontDefault = io.Fonts->Fonts[1];
    m_ImGuiContext.relayout(Vector2{ windowSize() } / dpiScaling(),
                                               windowSize(), framebufferSize());

    m_MeshSphere = MeshTools::compile(Primitives::icosphereSolid(3));

    for(size_t i = 0; i < 8; ++i) {
        const Vector3 tmpPos = Vector3(std::rand(), std::rand(), std::rand()) /
                               Float(RAND_MAX);
        arrayAppend(m_Points,         Containers::InPlaceInit, tmpPos * 2.0f - Vector3{ 1.0f });

        arrayAppend(m_DrawablePoints, Containers::InPlaceInit,
                    new PickableObject{ m_SphereShader,
                                        Color3{ tmpPos },
                                        m_MeshSphere,
                                        &m_Scene,
                                        &m_Drawables });

        m_Points[i].y() += 1.0f;
        m_DrawablePoints[i]->setTransformation(Matrix4::translation(m_Points[i]) *
                                               Matrix4::scaling(Vector3(0.05f)));
        m_mDrawableIdxToPointIdx[m_DrawablePoints[i]->idx()] = i;
    }
}

void MyApplication::viewportEvent(ViewportEvent& event) {
    ImGuiApplication::viewportEvent(event);

    /* Relayout ImGuizmo */
    ImGuiIO& io = ImGui::GetIO();
    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

    /* Resize buffers */
    const auto viewport = GL::defaultFramebuffer.viewport();
    m_RBColor.setStorage(GL::RenderbufferFormat::RGBA8, viewport.size());
    m_RBObjectIdx.setStorage(GL::RenderbufferFormat::R16UI, viewport.size());
    m_RBDepth.setStorage(GL::RenderbufferFormat::DepthComponent24, viewport.size());
    m_FrameBuffer.setViewport(viewport);
}

void MyApplication::mousePressEvent(MouseEvent& event) {
    ImGuiApplication::mousePressEvent(event);
    if(event.isAccepted()) {
        return;
    }

    /* Update picking object
     * Read object ID at given click position (framebuffer has Y up while windowing system Y down)
     * If is there any active text edit, then just deselect object
     */
    m_FrameBuffer.mapForRead(GL::Framebuffer::ColorAttachment{ 1 });
    Image2D data = m_FrameBuffer.read(
        Range2Di::fromSize({ event.position().x(),
                             m_FrameBuffer.viewport().sizeY() - event.position().y() - 1 },
                           { 1, 1 }),
        { m_PixelFormat });

    uint32_t idx = 0;
    if(m_PixelFormat == PixelFormat::R8UI) {
        idx = static_cast<uint32_t>(data.data()[0]);
    } else if(m_PixelFormat == PixelFormat::R16UI) {
        idx = static_cast<uint32_t>(Containers::arrayCast<uint16_t>(data.data())[0]);
    } else if(m_PixelFormat == PixelFormat::R32UI) {
        idx = Containers::arrayCast<uint32_t>(data.data())[0];
    } else {
        Fatal{} << "Invalid pixel format";
    }

    PickableObject::updateSelectedObject(idx);
    event.setAccepted();
}

bool MyApplication::editPointTransformation(PickableObject* object) {
    const auto camMat = m_Camera->viewMatrix();
    const auto prjMat = m_Camera->camera().projectionMatrix();
    ImGuizmo::BeginFrame();

    // APPLYING GUI TRANSFORMS
    Vector3 translation = object->translation();
    Vector3 scale = object->scaling();
    Vector3 eulerAngles = Vector3(object->rotation().toEuler());
    eulerAngles *= 180.0f / M_PI;

    bool bEdited = ImGui::InputFloat3("Position", translation.data(), "%.4f", 3);
    bEdited |= ImGui::InputFloat3("Rotation", eulerAngles.data(), "%.4f", 3);
    bEdited |= ImGui::InputFloat3("Scale", scale.data(), "%.4f", 3);

    object->setTranslation(translation);
    object->setScaling(scale);
    Rad ax{eulerAngles.data()[0] * (float)M_PI / 180.0f};
    Rad ay{eulerAngles.data()[1] * (float)M_PI / 180.0f};
    Rad az{eulerAngles.data()[2] * (float)M_PI / 180.0f};
    Matrix4 frot = Matrix4::rotationZ(az) * Matrix4::rotationY(ay) * Matrix4::rotationX(ax);
    object->setRotation(Quaternion::fromMatrix(Matrix3(frot)));

    // APPLYING GIZMO TRANSFORMS

    Matrix4 tempTrans = object->transformation();

    // ImGuizmo::Manipulate(camMat.data(), prjMat.data(),
    //                      ImGuizmo::SCALE, ImGuizmo::LOCAL,
    //                      tempTrans.data(),
    //                      nullptr, nullptr, nullptr, nullptr);

    // ImGuizmo::Manipulate(camMat.data(), prjMat.data(),
    //                      ImGuizmo::ROTATE, ImGuizmo::LOCAL,
    //                      tempTrans.data(),
    //                      nullptr, nullptr, nullptr, nullptr);

    ImGuizmo::Manipulate(camMat.data(), prjMat.data(),
                         ImGuizmo::TRANSLATE, ImGuizmo::LOCAL,
                         tempTrans.data(),
                         nullptr, nullptr, nullptr, nullptr);

    object->setTranslation(tempTrans.translation());
    object->setRotation(Quaternion::fromMatrix(tempTrans.rotation()));
    object->setScaling(tempTrans.scaling());

    return bEdited || ImGuizmo::IsUsing();
}

void MyApplication::setPointTransformation(size_t selectedObjID, const Matrix4& objMat,
                                                 Containers::Array<Vector3>& points) {
    const auto it = m_mDrawableIdxToPointIdx.find(selectedObjID);
    CORRADE_INTERNAL_ASSERT(it != m_mDrawableIdxToPointIdx.end());

    const Vector3& translation = objMat[3].xyz();
    points[it->second] = translation;
}

/****************************************************************************************************/
void MyApplication::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth);
    ImGuiApplication::beginFrame();

    /* Update camera */
    m_Camera->update();

    /* Draw to custom framebuffer */
    m_FrameBuffer
        .clearColor(0, m_BkgColor)
        .clearColor(1, Vector4ui{})
        .clearDepth(1.0f)
        .bind();

    /* Draw other objects (grid) */
    m_Camera->draw(m_Drawables);

    /* Bind the default framebuffer back, as only the clickable objects need to be render to custom framebuffer */
    GL::defaultFramebuffer.bind();

    /* Blit color to window framebuffer */
    m_FrameBuffer.mapForRead(GL::Framebuffer::ColorAttachment{ 0 });
    GL::AbstractFramebuffer::blit(m_FrameBuffer, GL::defaultFramebuffer,
                                  { {}, m_FrameBuffer.viewport().size() }, GL::FramebufferBlit::Color);
    
    BeginDockspace();

    // Menu Bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::Separator();

            if (ImGui::MenuItem("Quit", NULL, false))
            {
                // Exit the application
                exit();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    // Heirarchy
    {
        ImGui::Begin("Heirarchy");

        ImGui::End();
    }

    // INSPECTOR
    {
        ImGui::Begin("Inspector");

        PickableObject* selectedPoint = PickableObject::selectedObj();
        if(selectedPoint && ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
            if(selectedPoint->isSelectable()
            && selectedPoint->isMovable()) {
                std::string str = "Point: #" + std::to_string(selectedPoint->idx());
                ImGui::Text("%s", str.c_str());
                ImGui::Separator();
                ImGui::Spacing();

                Matrix4 objMat = selectedPoint->transformation();
                if(editPointTransformation(selectedPoint)) {
                    setPointTransformation(selectedPoint->idx(), objMat, m_Points); /* Update real data point */
                }
            }
        }

        ImGui::End();
    }

    EndDockspace();

    ImGuiApplication::endFrame();
    swapBuffers();
    redraw();
}

void BeginDockspace()
{
    static bool dockspaceOpen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Venom Engine Dockspace", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("Venom Engine Dockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        static auto first_time = true;
        if (first_time)
        {
            first_time = false;

            ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
            ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

            // split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the following args in the following order
            //   window ID to split, direction, fraction (between 0 and 1), the final two setting let's us choose which id we want (which ever one we DON'T set as NULL, will be returned by the function)
            //                                                              out_id_at_dir is the id of the node in the direction we specified earlier, out_id_at_opposite_dir is in the opposite direction
            auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
            auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.25f, nullptr, &dockspace_id);

            // we now dock our windows into the docking node we made above
            ImGui::DockBuilderDockWindow("Heirarchy", dock_id_left);
            ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
            ImGui::DockBuilderFinish(dockspace_id);
        }
    }
}

void EndDockspace()
{
    ImGui::End();
}