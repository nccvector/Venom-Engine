#pragma once

#include "Viewport.h"

class ImageViewport : public Viewport
{
public:

	void setup() override;
    void shutdown() override;
	void show() override;
	void update() override;
    void updateRenderTexture();

    Texture ImageTexture;
    Camera2D Camera = { 0 };

    Vector2 LastMousePos = { 0 };
    Vector2 LastTarget = { 0 };
    bool Dragging = false;
    bool DirtyScene = false;

    enum class ToolMode
    {
        None,
        Move,
    };

    ToolMode CurrentToolMode = ToolMode::None;

};