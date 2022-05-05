#pragma once

#include "Widget.h"
#include "raylib.h"

class Viewport : public Widget
{
public:
    RenderTexture ViewTexture;
};