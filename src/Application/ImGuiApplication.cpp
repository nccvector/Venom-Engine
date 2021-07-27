#include "Application/ImGuiApplication.h"
#include <Magnum/GL/Renderer.h>

#include <imgui_internal.h>
#include "DrawableObjects/PickableObject.h"

/****************************************************************************************************/
ImGuiApplication::ImGuiApplication(const std::string &title,
                                   const Arguments &arguments,
                                   const Vector2i &defaultWindowSize)
    : GLApplication{title, arguments, defaultWindowSize} {

  /* Setup ImGui and ImGuizmo */
  m_ImGuiContext = ImGuiIntegration::Context(
      Vector2{windowSize()} / dpiScaling(), windowSize(), framebufferSize());

  ImGuiIO &io = ImGui::GetIO();
  // ImGui::StyleColorsDark(); // Being set by a function below

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones.
  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // SETTING DARK THEME
  SetDarkThemeColors();

  /* Setup proper blending to be used by ImGui. There's a great chance
     you'll need this exact behavior for the rest of your scene. If not, set
     this only for the drawFrame() call. */
  GL::Renderer::setBlendFunction(
      GL::Renderer::BlendFunction::SourceAlpha,
      GL::Renderer::BlendFunction::OneMinusSourceAlpha);
}

void ImGuiApplication::SetDarkThemeColors() {
  auto &colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};

  // Headers
  colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
  colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
  colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

  // Buttons
  colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
  colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
  colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

  // Frame BG
  colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
  colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
  colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

  // Tabs
  colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
  colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
  colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
  colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

  // Title
  colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
  colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
}

/****************************************************************************************************/
void ImGuiApplication::viewportEvent(ViewportEvent &event) {
  GLApplication::viewportEvent(event);

  /* Relayout ImGui */
  m_ImGuiContext.relayout(Vector2{event.windowSize()} / event.dpiScaling(),
                          event.windowSize(), event.framebufferSize());
}

/****************************************************************************************************/
void ImGuiApplication::keyPressEvent(KeyEvent &event) {
  if (m_ImGuiContext.handleKeyPressEvent(event)) {
    event.setAccepted(true);
  } else {
    GLApplication::keyPressEvent(event);
    if (!event.isAccepted()) {
      if (event.key() == KeyEvent::Key::H) {
        m_bShowMenu ^= true;
        event.setAccepted(true);
      }
    }
  }
}

void ImGuiApplication::keyReleaseEvent(KeyEvent &event) {
  if (m_ImGuiContext.handleKeyReleaseEvent(event)) {
    event.setAccepted(true);
  }
}

/****************************************************************************************************/
void ImGuiApplication::mousePressEvent(MouseEvent &event) {
  if (m_ImGuiContext.handleMousePressEvent(event)) {
    event.setAccepted(true);
  } else {
    GLApplication::mousePressEvent(event);
  }
}

/****************************************************************************************************/
void ImGuiApplication::mouseReleaseEvent(MouseEvent &event) {
  if (m_ImGuiContext.handleMouseReleaseEvent(event)) {
    event.setAccepted(true);
  }
}

/****************************************************************************************************/
void ImGuiApplication::mouseMoveEvent(MouseMoveEvent &event) {
  if (m_ImGuiContext.handleMouseMoveEvent(event)) {
    event.setAccepted(true);
  } else {
    GLApplication::mouseMoveEvent(event);
  }
}

/****************************************************************************************************/
void ImGuiApplication::mouseScrollEvent(MouseScrollEvent &event) {
  if (m_ImGuiContext.handleMouseScrollEvent(event)) {
    /* Prevent scrolling the page */
    event.setAccepted(true);
  } else {
    GLApplication::mouseScrollEvent(event);
  }
}

/****************************************************************************************************/
void ImGuiApplication::textInputEvent(TextInputEvent &event) {
  if (m_ImGuiContext.handleTextInputEvent(event)) {
    event.setAccepted(true);
  }
}

/****************************************************************************************************/
void ImGuiApplication::beginFrame() {
  m_ImGuiContext.newFrame();
  /* Enable text input, if needed */
  if (ImGui::GetIO().WantTextInput && !isTextInputActive()) {
    startTextInput();
  } else if (!ImGui::GetIO().WantTextInput && isTextInputActive()) {
    stopTextInput();
  }
}

/****************************************************************************************************/
void ImGuiApplication::endFrame() {
  /* Update application cursor */
  m_ImGuiContext.updateApplicationCursor(*this);

  /* Set appropriate states. If you only draw imgui UI, it is sufficient to do
   * this once in the constructor. */
  GL::Renderer::enable(GL::Renderer::Feature::Blending);
  GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
  GL::Renderer::disable(GL::Renderer::Feature::DepthTest);
  GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);

  m_ImGuiContext.drawFrame();

  /* Reset state. Only needed if you want to draw something else with different
   * state next frame. */
  GL::Renderer::disable(GL::Renderer::Feature::ScissorTest);
  GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
  GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
  GL::Renderer::disable(GL::Renderer::Feature::Blending);
}

/****************************************************************************************************/
void ImGuiApplication::showMenuHeader() {
  ImGui::SetNextWindowBgAlpha(0.5f);
  ImGui::Begin("Options", nullptr);
  ImGui::Text("Hide/show menu: H | Exit: ESC");
  ImGui::Text("%3.2f FPS", static_cast<double>(ImGui::GetIO().Framerate));
  ImGui::SameLine(100);
  if (ImGui::Checkbox("VSync", &m_bVsync)) {
    setSwapInterval(m_bVsync);
  }
  ImGui::Spacing();
  ImGui::Checkbox("Render grid", &m_Grid->enabled());
  if (ImGui::ColorEdit3("Background color", m_BkgColor.data())) {
    GL::Renderer::setClearColor(m_BkgColor);
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();
}

void ImGuiApplication::showMenuFooter(bool bButtonResetCamera) {
  if (bButtonResetCamera) {
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    if (ImGui::Button("Reset camera")) {
      m_Camera->reset();
    }
  }
  ImGui::End();
}

void ImGuiApplication::BeginDockspace() {
  static bool dockspaceOpen = true;
  static ImGuiDockNodeFlags dockspace_flags =
      ImGuiDockNodeFlags_PassthruCentralNode;

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window
  // not dockable into,
  // because it would be confusing to have two docking targets within each
  // others.
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |=
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  window_flags |= ImGuiWindowFlags_NoBackground;

  // Important: note that we proceed even if Begin() returns false (aka window
  // is collapsed).
  // This is because we want to keep our DockSpace() active. If a DockSpace() is
  // inactive,
  // all active windows docked into it will lose their parent and become
  // undocked.
  // We cannot preserve the docking relationship between an active window and an
  // inactive docking, otherwise
  // any change of dockspace/settings would lead to windows being stuck in limbo
  // and never being visible.
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("Venom Engine Dockspace", &dockspaceOpen, window_flags);
  ImGui::PopStyleVar();
  ImGui::PopStyleVar(2);

  // Submit the DockSpace
  ImGuiIO &io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockspace_id = ImGui::GetID("Venom Engine Dockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    static auto first_time = true;
    if (first_time) {
      first_time = false;

      ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
      ImGui::DockBuilderAddNode(dockspace_id,
                                dockspace_flags | ImGuiDockNodeFlags_DockSpace);
      ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

      // split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the
      // following args in the following order
      //   window ID to split, direction, fraction (between 0 and 1), the final
      //   two setting let's us choose which id we want (which ever one we DON'T
      //   set as NULL, will be returned by the function)
      //                                                              out_id_at_dir
      //                                                              is the id
      //                                                              of the
      //                                                              node in
      //                                                              the
      //                                                              direction
      //                                                              we
      //                                                              specified
      //                                                              earlier,
      //                                                              out_id_at_opposite_dir
      //                                                              is in the
      //                                                              opposite
      //                                                              direction
      auto dock_id_left = ImGui::DockBuilderSplitNode(
          dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
      auto dock_id_right = ImGui::DockBuilderSplitNode(
          dockspace_id, ImGuiDir_Right, 0.25f, nullptr, &dockspace_id);

      // we now dock our windows into the docking node we made above
      ImGui::DockBuilderDockWindow("Heirarchy", dock_id_left);
      ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
      ImGui::DockBuilderFinish(dockspace_id);
    }
  }
}

void ImGuiApplication::EndDockspace() 
{
  ImGui::End();
}

void ImGuiApplication::OnDraw() 
{
  BeginDockspace();

  // Menu Bar
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      ImGui::Separator();

      if (ImGui::MenuItem("Quit", NULL, false)) {
        // Exit the application
        exit();
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit")) {
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View")) {
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

    // PickableObject *selectedPoint = PickableObject::selectedObj();
    // if (selectedPoint &&
    //     ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
    //   if (selectedPoint->isSelectable() && selectedPoint->isMovable()) {
    //     std::string str = "Point: #" + std::to_string(selectedPoint->idx());
    //     ImGui::Text("%s", str.c_str());
    //     ImGui::Separator();
    //     ImGui::Spacing();

    //     Matrix4 objMat = selectedPoint->transformation();
    //     if (editPointTransformation(selectedPoint)) {
    //       setPointTransformation(selectedPoint->idx(), objMat,
    //                              m_Points); /* Update real data point */
    //     }
    //   }
    // }

    ImGui::End();
  }

  EndDockspace();
}