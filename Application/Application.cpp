#include "Application.h"

// CUSTOM INCLUDES
#include "UIMain.h"
#include "ApplicationStateMachine.h"
#include "PickState.h"

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

    // get a pointer to the already created root
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

    // Creating a scene manager
    sceneManager = root->createSceneManager(DefaultSceneManagerFactory::FACTORY_TYPE_NAME, "Main");

    // Initializing state machine
    ApplicationStateMachine::Singleton().ChangeState(&PickState::Singleton());

    ////////////////////////////////
    sceneManager->addRenderQueueListener(&OverlaySystem::getSingleton());

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneManager);

    // CREATING A MAIN CAMERA
    SceneNode* camNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    Camera* cam = sceneManager->createCamera("Main Camera");
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

    // Assigning callbacks to toolbar
    Toolbar& tb = Toolbar::getSingleton();
    tb.SetPickCallback     (&Application::PickCallback);
    tb.SetMoveCallback     (&Application::MoveCallback);
    tb.SetRotateCallback   (&Application::RotateCallback);
    tb.SetScaleCallback    (&Application::ScaleCallback);
    tb.SetObjectCallback   (&Application::ObjectCallback);
    tb.SetCubeCallback     (&Application::CubeCallback);
    tb.SetConeCallback     (&Application::ConeCallback);
}

// Toolbar Callbacks
void Application::PickCallback()
{
    // Switching state
    ApplicationStateMachine::Singleton().ChangeState(&PickState::Singleton());

    Console::getSingleton().AddLog("PICK TOOL EVENT");
}

void Application::MoveCallback()
{
    // Switching state
    ApplicationStateMachine::Singleton().ChangeState(&MoveState::Singleton());

    Console::getSingleton().AddLog("MOVE TOOL EVENT");
}

void Application::RotateCallback()
{
    // Switching state
    ApplicationStateMachine::Singleton().ChangeState(&RotateState::Singleton());

    Console::getSingleton().AddLog("ROTATE TOOL EVENT");
}

void Application::ScaleCallback()
{
    // Switching state
    ApplicationStateMachine::Singleton().ChangeState(&ScaleState::Singleton());

    Console::getSingleton().AddLog("SCALE TOOL EVENT");
}

void Application::ObjectCallback()
{
    // Console::getSingleton().AddLog("OBJECT TOOL EVENT");

    // // Creating an ogre entity and attaching to scene
    // Ogre::Entity* ogreEntity = app->sceneManager->createEntity("ogrehead.mesh");
    // Ogre::SceneNode* ogreNode = app->sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 50, 0));
    // ogreNode->attachObject(ogreEntity);

}

void Application::CubeCallback()
{
    Console::getSingleton().AddLog("CUBE TOOL EVENT");
}

void Application::ConeCallback()
{
    Console::getSingleton().AddLog("CONE TOOL EVENT");
}

}