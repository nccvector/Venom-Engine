#pragma once

#include "Application/ImGuiApplication.h"
#include "DrawableObjects/PickableObject.h"

#include <Magnum/Magnum.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/GL/Renderbuffer.h>
#include <Magnum/GL/RenderbufferFormat.h>
#include <Corrade/Containers/Array.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Shaders/Phong.h>

#include <unordered_map>

/****************************************************************************************************/
class MyApplication final : public ImGuiApplication  {
public:
    explicit MyApplication(const Arguments& arguments, 
                            size_t indexDataSize = 16, 
                            const Vector2i& defaultWindowSize = Vector2i{ 1920, 1080 });

protected:
    void viewportEvent(ViewportEvent& event) override;
    void mousePressEvent(MouseEvent& event) override;

    bool editPointTransformation(PickableObject* object);
    void setPointTransformation(size_t selectedObjID, const Matrix4& objMat,
                                Containers::Array<Vector3>& points);
                                
    void drawEvent() override;

    /* Object index format */
    GL::RenderbufferFormat               m_IndexFormat { GL::RenderbufferFormat::R16UI };
    PixelFormat                          m_PixelFormat { PixelFormat::R16UI };
    std::unordered_map<uint32_t, size_t> m_mDrawableIdxToPointIdx;

    /* Framebuffer and render bufers */
    GL::Framebuffer  m_FrameBuffer { NoCreate };
    GL::Renderbuffer m_RBColor{ NoCreate };
    GL::Renderbuffer m_RBObjectIdx{ NoCreate };
    GL::Renderbuffer m_RBDepth{ NoCreate };

    /* Draw pickable spheres */
    Containers::Array<Vector3>         m_Points;
    Containers::Array<PickableObject*> m_DrawablePoints;
    Shaders::Phong                     m_SphereShader { Shaders::Phong::Flag::ObjectId };
    GL::Mesh m_MeshSphere{ NoCreate };
};

/****************************************************************************************************/
MAGNUM_APPLICATION_MAIN(MyApplication)