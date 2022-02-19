#include "Application.h"

// CUSTOM INCLUDES
#include "UIMain.h"
#include "Dockspace.h"
#include "Toolbar.h"
#include "Console.h"

#include "ApplicationStateMachine.h"
#include "PickState.h"
#include "MoveState.h"
#include "RotateState.h"
#include "ScaleState.h"

using namespace Ogre;
using namespace OgreBites;

using namespace Venom::UI;
using namespace Venom::States;

namespace Venom::App
{

// Imgui event capture
bool Application::keyPressed(const KeyboardEvent& evt) 
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }

    return mListenerChain.keyPressed(evt);
}

bool Application::keyReleased(const KeyboardEvent& evt) 
{ 
    return mListenerChain.keyReleased(evt); 
}

bool Application::mouseMoved(const MouseMotionEvent& evt) 
{ 
    return mListenerChain.mouseMoved(evt); 
}

bool Application::mouseWheelRolled(const MouseWheelEvent& evt) 
{ 
    return mListenerChain.mouseWheelRolled(evt); 
}

bool Application::mousePressed(const MouseButtonEvent& evt) 
{ 
    return mListenerChain.mousePressed(evt); 
}

bool Application::mouseReleased(const MouseButtonEvent& evt) 
{ 
    return mListenerChain.mouseReleased(evt); 
}

bool Application::textInput (const TextInputEvent& evt) 
{ 
    return mListenerChain.textInput (evt); 
}


bool Application::frameStarted(const Ogre::FrameEvent& evt)
{
    ApplicationContext::frameStarted(evt);

    // DRAWING UI
    UIMain::Singleton().Draw();

    // manually call sample callback to ensure correct order
    return true;
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    // Call update of current state
    ApplicationStateMachine::Singleton().GetCurrentState()->HandleInput();
    ApplicationStateMachine::Singleton().GetCurrentState()->Update();
    ApplicationStateMachine::Singleton().GetCurrentState()->LogicalUpdate();

    return true;
}

void Application::windowResized(Ogre::RenderWindow* rw)
{
    Console::getSingleton().AddLog("RESIZED");

    unsigned int width, height;
    int left, top;
    rw->getMetrics(width, height, left, top);

    // Create some random ogre object at origin
    sceneManager->getCamera("Main Camera")->setAspectRatio(Real(width) / Real(height));
}

void Application::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();

    // Initializing root pointer
    root = getRoot();

    // Setting startup resolution (can also set fullscreen here)
    root->getRenderSystem()->setConfigOption("Video Mode", "1280 x 720 @ 32-bit colour");
    root->getRenderSystem()->_initialise();

    // // Setting start window size
    // getRenderWindow()->resize(1280, 720);
    // getRenderWindow()->setVSyncEnabled(true);
    // getRenderWindow()->initialize();

    // Adding input listener
    addInputListener(this);

    // ADDING RESOURCE LOCATIONS
    ResourceGroupManager::getSingleton().addResourceLocation("../Media", "FileSystem");
    ResourceGroupManager::getSingleton().addResourceLocation("../Media/fonts", "FileSystem");

    // Initializing UIMain
    UIMain::Singleton();

    // Creating and Initializing sceneManager pointer
    sceneManager = root->createSceneManager(DefaultSceneManagerFactory::FACTORY_TYPE_NAME, "Main");

    // Initializing raySceneQuery
    raySceneQuery = sceneManager->createRayQuery(Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
    raySceneQuery->setSortByDistance(true);

    // Initializing state machine
    ApplicationStateMachine::Singleton().ChangeState(&PickState::Singleton());

    ////////////////////////////////
    sceneManager->addRenderQueueListener(&OverlaySystem::getSingleton());

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneManager);

    // Initializing the camera node
    SceneNode* cameraNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    
    // CREATING A MAIN CAMERA and assigning to cameraNode
    camera = sceneManager->createCamera("Main Camera");
    camera->setNearClipDistance(5);
    cameraNode->attachObject(camera);

    // CAMERA CONTROLLER
    mCameraMan.reset(new CameraMan(cameraNode));
    mCameraMan->setStyle(OgreBites::CS_ORBIT);

    // Setting initial transform
    cameraNode->setPosition(500, 500, 500);
    cameraNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);

    // ADDING INPUT LISTENERS
    mImguiListener.reset(new ImGuiInputListener());
    mListenerChain = InputListenerChain({ 
        mImguiListener.get(),
        mCameraMan.get()
    });
    

    //! [addviewport]
    Viewport* vp = getRenderWindow()->addViewport(camera);
    //! [addviewport]

    //! [viewportback]
    vp->setBackgroundColour(ColourValue(0, 0, 0));
    //! [viewportback]

    //! [cameraratio]
    camera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
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
    Entity* groundEntity = sceneManager->createEntity("ground");
    sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    //! [planecreate]

    //! [planenoshadow]
    groundEntity->setCastShadows(false);
    //! [planenoshadow]

    //! [planesetmat]
    // groundEntity->setMaterialName("Examples/Rockwall");
    //! [planesetmat]


    //! [directlight]
    Light* directionalLight = sceneManager->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    //! [directlight]

    //! [directlightcolor]
    directionalLight->setDiffuseColour(ColourValue(0.8, 0.8, 0.8));
    directionalLight->setSpecularColour(ColourValue(0.8, 0.8, 0.8));
    //! [directlightcolor]

    //! [directlightdir]
    SceneNode* directionalLightNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    directionalLightNode->attachObject(directionalLight);
    directionalLightNode->setDirection(Vector3(-2, -1, -1));
    //! [directlightdir]

    sceneManager->setAmbientLight(ColourValue(0.1, 0.1, 0.1));
    sceneManager->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
}

// void ScreenToWorldRa

}