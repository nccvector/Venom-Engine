#pragma once

/*-------------------------------------------------------------------------
This source file is a part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/


Copyright (c) 2000-2013 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:


The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE
-------------------------------------------------------------------------*/

// SYSTEM INCLUDES
#include <exception>
#include <iostream>

// OVERLAY INCLUDES
#include "OgreOverlaySystem.h"
#include "OgreOverlayManager.h"

// OGRE APPLICATION INCLUDES
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"
#include "OgreResourceManager.h"
#include "OgreResourceGroupManager.h"

// IMGUI INCLUDES
#include <OgreImGuiInputListener.h>

// CUSTOM INCLUDES

using namespace Ogre;
using namespace OgreBites;

namespace Venom::App
{

class Application
        : public ApplicationContext
        , public InputListener
{
    // CREATING INPUT LISTENERS
    std::unique_ptr<ImGuiInputListener> mImguiListener;
    std::unique_ptr<CameraMan> mCameraMan;           // basic camera controller

    // LISTENER CHAIN (can be trays, ui or camera/viewport)
    InputListenerChain mListenerChain;

    // Private constructor
    Application() : ApplicationContext("Venom Engine") {};

public:
    // Application Vars
    Ogre::Root* root;
    Ogre::SceneManager* sceneManager;
    Ogre::Camera* camera;
    Ogre::RaySceneQuery* raySceneQuery;
    Ogre::RaySceneQueryResult* raySceneQueryResult;

    static Application& Singleton()
    {
        static Application instance;
        return instance;
    }

    ~Application() {};

    // Imgui event capture
    bool keyPressed(const KeyboardEvent& evt)               override;

    bool keyReleased(const KeyboardEvent& evt)              override;

    bool mouseMoved(const MouseMotionEvent& evt)            override;

    bool mouseWheelRolled(const MouseWheelEvent& evt)       override;

    bool mousePressed(const MouseButtonEvent& evt)          override;

    bool mouseReleased(const MouseButtonEvent& evt)         override;

    bool textInput (const TextInputEvent& evt)              override;

    bool frameStarted(const Ogre::FrameEvent& evt)          override;

    bool frameRenderingQueued(const Ogre::FrameEvent& evt)  override;

    void windowResized(Ogre::RenderWindow* rw)              override;

    void setup()                                            override;
};

}