#pragma once

#include "Application/PickableApplication.h"
#include "DrawableObjects/PickableObject.h"

#include <Corrade/Containers/Array.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Shaders/Phong.h>

/****************************************************************************************************/
class VenomApplication final : public PickableApplication  {
public:
    explicit VenomApplication(const Arguments& arguments);

protected:
    void drawEvent() override;

    /* Draw pickable spheres */
    Containers::Array<Vector3>         m_Points;
    Containers::Array<PickableObject*> m_DrawablePoints;
    Shaders::Phong                     m_SphereShader { Shaders::Phong::Flag::ObjectId };
    GL::Mesh m_MeshSphere{ NoCreate };
};

/****************************************************************************************************/
MAGNUM_APPLICATION_MAIN(VenomApplication)
