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

#include "Application/ImGuiApplication.h"
#include <Magnum/GL/Renderer.h>

/****************************************************************************************************/
ImGuiApplication::ImGuiApplication(const std::string& title, const Arguments& arguments,
                                   const Vector2i& defaultWindowSize) :
    GLApplication{title, arguments, defaultWindowSize} {

    /* Setup ImGui and ImGuizmo */
    m_ImGuiContext = ImGuiIntegration::Context(Vector2{ windowSize() } / dpiScaling(),
                                               windowSize(), framebufferSize());
    
    // SETTING CONFIG FLAGS FOR DOCKING ### ADDED LATER
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // SETTING DEFAULT FONT
    io.Fonts->AddFontFromFileTTF("/home/vector/cpp-projects/Venom-Engine/assets/fonts/OpenSans-Regular.ttf", 18.0f);
    io.FontDefault = io.Fonts->Fonts[1];
    m_ImGuiContext.relayout(Vector2{ windowSize() } / dpiScaling(),
                                               windowSize(), framebufferSize());

    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    SetDarkThemeColors();

    /* Setup proper blending to be used by ImGui. There's a great chance
       you'll need this exact behavior for the rest of your scene. If not, set
       this only for the drawFrame() call. */
    GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::SourceAlpha,
                                   GL::Renderer::BlendFunction::OneMinusSourceAlpha);
}

void ImGuiApplication::SetDarkThemeColors()
{
    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    
    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}

/****************************************************************************************************/
void ImGuiApplication::viewportEvent(ViewportEvent& event) {
    GLApplication::viewportEvent(event);

    /* Relayout ImGui */
    m_ImGuiContext.relayout(Vector2{ event.windowSize() } / event.dpiScaling(),
                            event.windowSize(), event.framebufferSize());
}

/****************************************************************************************************/
void ImGuiApplication::keyPressEvent(KeyEvent& event) {
    if(m_ImGuiContext.handleKeyPressEvent(event)) {
        event.setAccepted(true);
    } else {
        GLApplication::keyPressEvent(event);
        if(!event.isAccepted()) {
            if(event.key() == KeyEvent::Key::H) {
                m_bShowMenu ^= true;
                event.setAccepted(true);
            }
        }
    }
}

void ImGuiApplication::keyReleaseEvent(KeyEvent& event) {
    if(m_ImGuiContext.handleKeyReleaseEvent(event)) {
        event.setAccepted(true);
    }
}

/****************************************************************************************************/
void ImGuiApplication::mousePressEvent(MouseEvent& event) {
    if(m_ImGuiContext.handleMousePressEvent(event)) {
        event.setAccepted(true);
    } else {
        GLApplication::mousePressEvent(event);
    }
}

/****************************************************************************************************/
void ImGuiApplication::mouseReleaseEvent(MouseEvent& event) {
    if(m_ImGuiContext.handleMouseReleaseEvent(event)) {
        event.setAccepted(true);
    }
}

/****************************************************************************************************/
void ImGuiApplication::mouseMoveEvent(MouseMoveEvent& event) {
    if(m_ImGuiContext.handleMouseMoveEvent(event)) {
        event.setAccepted(true);
    } else {
        GLApplication::mouseMoveEvent(event);
    }
}

/****************************************************************************************************/
void ImGuiApplication::mouseScrollEvent(MouseScrollEvent& event) {
    if(m_ImGuiContext.handleMouseScrollEvent(event)) {
        /* Prevent scrolling the page */
        event.setAccepted(true);
    } else {
        GLApplication::mouseScrollEvent(event);
    }
}

/****************************************************************************************************/
void ImGuiApplication::textInputEvent(TextInputEvent& event) {
    if(m_ImGuiContext.handleTextInputEvent(event)) {
        event.setAccepted(true);
    }
}

/****************************************************************************************************/
void ImGuiApplication::beginFrame() {
    m_ImGuiContext.newFrame();
    /* Enable text input, if needed */
    if(ImGui::GetIO().WantTextInput && !isTextInputActive()) {
        startTextInput();
    } else if(!ImGui::GetIO().WantTextInput && isTextInputActive()) {
        stopTextInput();
    }
}

/****************************************************************************************************/
void ImGuiApplication::endFrame() {
    /* Update application cursor */
    m_ImGuiContext.updateApplicationCursor(*this);

    /* Set appropriate states. If you only draw imgui UI, it is sufficient to do this once in the constructor. */
    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::disable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);

    m_ImGuiContext.drawFrame();

    /* Reset state. Only needed if you want to draw something else with different state next frame. */
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
    if(ImGui::Checkbox("VSync", &m_bVsync)) {
        setSwapInterval(m_bVsync);
    }
    ImGui::Spacing();
    ImGui::Checkbox("Render grid", &m_Grid->enabled());
    if(ImGui::ColorEdit3("Background color", m_BkgColor.data())) {
        GL::Renderer::setClearColor(m_BkgColor);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
}

void ImGuiApplication::showMenuFooter(bool bButtonResetCamera) {
    if(bButtonResetCamera) {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        if(ImGui::Button("Reset camera")) {
            m_Camera->reset();
        }
    }
    ImGui::End();
}
