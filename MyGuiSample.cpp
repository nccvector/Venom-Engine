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
#include "UIMain.h"

using namespace Ogre;
using namespace OgreBites;

class TutorialApplication
        : public ApplicationContext
        , public InputListener
{
    // CREATING UIMAIN OBJECT
    UIMain* uimain;

    // CREATING INPUT LISTENERS
    std::unique_ptr<ImGuiInputListener> mImguiListener;
    std::unique_ptr<CameraMan> mCameraMan;           // basic camera controller

    // LISTENER CHAIN (can be trays, ui or camera/viewport)
    InputListenerChain mListenerChain;

public:
    TutorialApplication(): ApplicationContext("OgreTutorialApp") {};

    ~TutorialApplication() {};

    // Imgui event capture
    bool keyPressed(const KeyboardEvent& evt) 
    {
        if (evt.keysym.sym == SDLK_ESCAPE)
        {
            getRoot()->queueEndRendering();
        }

        return mListenerChain.keyPressed(evt);
    }

    bool keyReleased(const KeyboardEvent& evt) 
    { 
        return mListenerChain.keyReleased(evt); 
    }

    bool mouseMoved(const MouseMotionEvent& evt) 
    { 
        return mListenerChain.mouseMoved(evt); 
    }

    bool mouseWheelRolled(const MouseWheelEvent& evt) 
    { 
        return mListenerChain.mouseWheelRolled(evt); 
    }

    bool mousePressed(const MouseButtonEvent& evt) 
    { 
        return mListenerChain.mousePressed(evt); 
    }

    bool mouseReleased(const MouseButtonEvent& evt) 
    { 
        return mListenerChain.mouseReleased(evt); 
    }

    bool textInput (const TextInputEvent& evt) 
    { 
        return mListenerChain.textInput (evt); 
    }

    //
    void setup();


    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        ApplicationContext::frameStarted(evt);

        // DRAWING UI
        uimain->Draw();

        // manually call sample callback to ensure correct order
        return true;
    }

    void windowResized(Ogre::RenderWindow* rw)
    {
        Console::getSingleton()->AddLog("RESIZED");

        unsigned int width, height;
        int left, top;
        rw->getMetrics(width, height, left, top);

        // Create some random ogre object at origin
        SceneManager* scnMgr = getRoot()->getSceneManager("Main");
        scnMgr->getCamera("Main Camera")->setAspectRatio(Real(width) / Real(height));
    }
};

void TutorialApplication::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();

    // // Setting start window size
    // getRenderWindow()->resize(1280, 720);
    // getRenderWindow()->setVSyncEnabled(true);

    // Adding input listener
    addInputListener(this);

    // ADDING RESOURCE LOCATIONS
    ResourceGroupManager::getSingleton().addResourceLocation("../Media", "FileSystem");
    ResourceGroupManager::getSingleton().addResourceLocation("../Media/fonts", "FileSystem");

    // get a pointer to the already created root
    Root* root = getRoot();

    // root->getRenderSystem()->setConfigOption("Video Mode", "1280 x 720 @ 32-bit colour");
    // root->initialise(true);

    SceneManager* scnMgr = root->createSceneManager(DefaultSceneManagerFactory::FACTORY_TYPE_NAME, "Main");

    // Initializing UI
    uimain = new UIMain(root);

    ////////////////////////////////
    scnMgr->addRenderQueueListener(&OverlaySystem::getSingleton());

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // CREATING A MAIN CAMERA
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    Camera* cam = scnMgr->createCamera("Main Camera");
    cam->setNearClipDistance(5);
    camNode->attachObject(cam);

    // CAMERA CONTROLLER
    mCameraMan.reset(new CameraMan(camNode));
    mCameraMan->setStyle(OgreBites::CS_ORBIT);

    // Setting initial transform
    camNode->setPosition(500, 500, 500);
    camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);

    // ADDING INPUT LISTENERS
    mImguiListener.reset(new ImGuiInputListener());
    mListenerChain = InputListenerChain({ 
        mImguiListener.get(),
        mCameraMan.get()
    });
    

    //! [addviewport]
    Viewport* vp = getRenderWindow()->addViewport(cam);
    //! [addviewport]

    //! [viewportback]
    vp->setBackgroundColour(ColourValue(0, 0, 0));
    //! [viewportback]

    //! [cameraratio]
    cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    //! [cameraratio]

    //! [plane]
    Plane plane(Vector3::UNIT_Y, 0);
    //! [plane]

    //! [planedefine]
    MeshManager::getSingleton().createPlane(
            "ground", RGN_DEFAULT,
            plane,
            1500, 1500, 20, 20,
            true,
            1, 5, 5,
            Vector3::UNIT_Z);
    //! [planedefine]

    //! [planecreate]
    Entity* groundEntity = scnMgr->createEntity("ground");
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    //! [planecreate]

    //! [planenoshadow]
    groundEntity->setCastShadows(false);
    //! [planenoshadow]

    //! [planesetmat]
    // groundEntity->setMaterialName("Examples/Rockwall");
    //! [planesetmat]


    //! [directlight]
    Light* directionalLight = scnMgr->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    //! [directlight]

    //! [directlightcolor]
    directionalLight->setDiffuseColour(ColourValue(0.8, 0.8, 0.8));
    directionalLight->setSpecularColour(ColourValue(0.8, 0.8, 0.8));
    //! [directlightcolor]

    //! [directlightdir]
    SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    directionalLightNode->attachObject(directionalLight);
    directionalLightNode->setDirection(Vector3(-2, -1, -1));
    //! [directlightdir]

    scnMgr->setAmbientLight(ColourValue(0.1, 0.1, 0.1));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
}


int main(int argc, char **argv)
{
    try
    {
        TutorialApplication app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [starter]
