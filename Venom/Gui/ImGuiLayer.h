#pragma once

#include "Core/Layer.h"
#include "Events/Event.h"

namespace Venom
{
  class ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnEvent(Event& event) override;
  private:

  };
}