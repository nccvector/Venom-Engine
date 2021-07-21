/**
 * Copyright 2020 Nghia Truong <nghiatruong.vn@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "DrawableObjects/PickableObject.h"
#include "MyApplication.h"

#include <Corrade/Containers/GrowableArray.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Primitives/Icosphere.h>

using namespace Magnum::Math::Literals;

/****************************************************************************************************/
MyApplication::MyApplication(const Arguments& arguments) :
    PickableApplication{"Graphics Template Application ", arguments} {

    // CONFIGURING IMGUI
    // SETTING CONFIG FLAGS FOR DOCKING ### ADDED LATER
    ImGuiIO& io = ImGui::GetIO();
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




    // ImGui::Begin("Hello Tab");
    // ImGui::Text("Hello World");
    // ImGui::End();
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
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            if (ImGui::MenuItem("Flag: NoSplit",                "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
            if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            
            ImGui::Separator();

            if (ImGui::MenuItem("Close", NULL, false))
                dockspaceOpen = false;
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::Begin("Hello Window");
    ImGui::Text("HELLOW WORLD");
    ImGui::End();

    /* Manipulate nodes' transformation */
    PickableObject* selectedPoint = PickableObject::selectedObj();
    if(selectedPoint) {
        if(selectedPoint->isSelectable()
           && selectedPoint->isMovable()) {
            ImGui::Begin("Transform");
            std::string str = "Point: #" + std::to_string(selectedPoint->idx());
            ImGui::Text("%s", str.c_str());
            ImGui::Separator();
            ImGui::Spacing();

            Matrix4 objMat = selectedPoint->transformation();
            if(editPointTransformation(objMat)) {
                selectedPoint->setTransformation(objMat);                       /* Update drawable transformation */
                setPointTransformation(selectedPoint->idx(), objMat, m_Points); /* Update real data point */
            }
            ImGui::End();
        }
    }

    ImGui::End();

    ImGuiApplication::endFrame();
    swapBuffers();
    redraw();
}
