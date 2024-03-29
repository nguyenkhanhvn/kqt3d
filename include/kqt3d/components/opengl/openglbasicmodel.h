#ifndef OPENGLBASICMODEL_H
#define OPENGLBASICMODEL_H

#include "kqtcore3d/components/opengl/openglmodel.h"
#include "kqtcore3d/kqtcore3d.h"

#include "openglbasicmesh.h"

namespace kqt3d {

class OpenGLBasicModel : public kqtcore3d::OpenGLModel
{
public:
    // accept BasicMesh, otherwise, other function will not work
    OpenGLBasicModel(const QVector<QSharedPointer<kqtcore3d::BaseMesh>> &meshes = QVector<QSharedPointer<kqtcore3d::BaseMesh>>());

    virtual void render(QSharedPointer<kqtcore3d::ShaderProgram> program, const char *modelUniform, kqtcore3d::RenderCallback callback = {});

    virtual void setAttribLayout(QSharedPointer<kqtcore3d::ShaderProgram> program);

    virtual void setPosition(const QVector3D &newPosition);

    virtual void setScale(float newScale);

    virtual QMatrix4x4 getTranformMatrix() const;

};

}

#endif // OPENGLBASICMODEL_H
