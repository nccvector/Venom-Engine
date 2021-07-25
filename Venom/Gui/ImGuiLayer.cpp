#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include <glad/glad.h> 

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Venom
{
  ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
  {
  }

  ImGuiLayer::~ImGuiLayer()
  {
  }

  void ImGuiLayer::OnAttach() 
  {

  }

  void ImGuiLayer::OnDetach()
  {

  }

  void ImGuiLayer::OnUpdate()
  {

  }

  void ImGuiLayer::OnEvent(Event& event)
  {

  }
}