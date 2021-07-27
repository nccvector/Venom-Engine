#pragma once

#include "DrawableObjects/FlatShadeObject.h"

#include <Corrade/Containers/Pointer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Shaders/Flat.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/TranslationRotationScalingTransformation3D.h>

/****************************************************************************************************/
using namespace Corrade;
using namespace Magnum;
using Object3D = SceneGraph::Object<SceneGraph::TranslationRotationScalingTransformation3D>;
using Scene3D  = SceneGraph::Scene<SceneGraph::TranslationRotationScalingTransformation3D>;

/****************************************************************************************************/
class Grid {
public:
    explicit Grid(Scene3D* const scene, SceneGraph::DrawableGroup3D* const drawableGroup);

    Grid& setColor(const Color3& color) { m_DrawableObj->color() = color; return *this; }
    Grid& setEnable(bool bStatus) { m_DrawableObj->setEnable(bStatus); return *this; }
    Grid& transform(const Matrix4& transMatrix) { m_Obj3D->setTransformation(transMatrix); return *this; }

    Color3& color() { return m_DrawableObj->color(); }
    bool& enabled() { return m_DrawableObj->enabled(); }

private:
    GL::Mesh                             m_Mesh { NoCreate };
    Shaders::Flat3D                      m_FlatShader { NoCreate };
    Containers::Pointer<Object3D>        m_Obj3D;
    Containers::Pointer<FlatShadeObject> m_DrawableObj;
};
