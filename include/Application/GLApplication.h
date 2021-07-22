#pragma once

#include "Camera/ArcBallCamera.h"
#include "DrawableObjects/Grid.h"

#include <Corrade/Containers/Pointer.h>
#include <Magnum/Magnum.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Platform/GlfwApplication.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/TranslationRotationScalingTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/Drawable.h>

/****************************************************************************************************/
using namespace Corrade;
using namespace Magnum;
using namespace Magnum::Math::Literals;

using Object3D = SceneGraph::Object<SceneGraph::TranslationRotationScalingTransformation3D>;
using Scene3D  = SceneGraph::Scene<SceneGraph::TranslationRotationScalingTransformation3D>;

/****************************************************************************************************/
class GLApplication : public Platform::Application {
public:
    explicit GLApplication(const std::string& title, const Arguments& arguments,
                           const Vector2i& defaultWindowSize = Vector2i{ 1920, 1080 });
    virtual ~GLApplication() {}

protected:
    void viewportEvent(ViewportEvent& event) override;
    void keyPressEvent(KeyEvent& event) override;
    void mousePressEvent(MouseEvent& event) override;
    void mouseMoveEvent(MouseMoveEvent& event) override;
    void mouseScrollEvent(MouseScrollEvent& event) override;

    void setupCamera();

    /* Window control */
    bool   m_bVsync { true };
    Color3 m_BkgColor { 0.35f };

    /* Scene and drawable group */
    Scene3D                     m_Scene;
    SceneGraph::DrawableGroup3D m_Drawables;

    /* Ground grid */
    Containers::Pointer<Grid> m_Grid;

    /* Camera helpers */
    Vector3 m_DefaultCamPosition { 0.0f, 1.5f, 8.0f };
    Vector3 m_DefaultCamTarget { 0.0f, 1.0f, 0.0f };
    Containers::Pointer<ArcBallCamera> m_Camera;
};
