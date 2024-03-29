#ifndef OPENGLBASICMESH_H
#define OPENGLBASICMESH_H

#include "kqtcore3d/kqtcore3d.h"
#include "kqtcore3d/components/opengl/openglmesh.h"

namespace kqt3d {

class OpenGLBasicMesh : public kqtcore3d::OpenGLMesh
{
public:
    OpenGLBasicMesh(const QSharedPointer<kqtcore3d::IVertices>& vertices = nullptr, const QSharedPointer<kqtcore3d::IIndices>& indices = nullptr, QMatrix4x4 meshMatrix = QMatrix4x4());
    
    virtual QMatrix4x4 getTransformationMatrix() const override;

    virtual void render(QSharedPointer<kqtcore3d::ShaderProgram> program, const char *modelUniform, kqtcore3d::RenderCallback callback = {});

    virtual void setAttribLayout(QSharedPointer<kqtcore3d::ShaderProgram> program);

    virtual QVector3D getPosition() const;
    virtual void setPosition(const QVector3D &newPosition);

    virtual float getScale() const;
    virtual void setScale(float newScale);

protected:
    QVector3D m_position;
    float m_scale;
    GLenum m_mode;
};

}

#endif // OPENGLBASICMESH_H
