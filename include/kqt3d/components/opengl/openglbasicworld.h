#ifndef OPENGLBASICWORLD_H
#define OPENGLBASICWORLD_H

#include <QList>

#include "openglbasicmodel.h"

namespace kqt3d {

class OpenGLBasicWorld : kqtcore3d::IRenderable
{
public:
    OpenGLBasicWorld(QList<QSharedPointer<OpenGLBasicModel>> listStaticModel = {}, QMatrix4x4 transformationMatrix = QMatrix4x4());

    // IRenderable interface
    virtual bool init(kqtcore3d::RenderCallback callback = {}) override;
    virtual void translate(const QVector3D &vector) override;
    virtual void translate(float x, float y) override;
    virtual void translate(float x, float y, float z) override;
    virtual void rotate(float angle, float x, float y, float z = 0) override;
    virtual void rotate(const QQuaternion &quaternion) override;
    virtual void rotate(const QVector3D &rotateAxis,float angle) override;
    virtual void rotateGlobal(const QVector3D &rotateAxis, float angle, const QVector3D &rotatePoint = {0,0,0}) override;
    virtual void scale(const QVector3D &vector) override;
    virtual void scale(float x, float y) override;
    virtual void scale(float x, float y, float z) override;
    virtual void scale(float factor) override;


    virtual void destroy();

    virtual void addModel(QSharedPointer<OpenGLBasicModel> model);
    virtual int removeModel(QSharedPointer<OpenGLBasicModel> model);

    virtual void setAttribLayout(QSharedPointer<kqtcore3d::ShaderProgram> program);
    virtual void render(QSharedPointer<kqtcore3d::ShaderProgram> program, const char *worldUniform, const char *modelUniform, kqtcore3d::RenderCallback callback = {});

protected:
    QMatrix4x4 m_transformationMatrix;
    QList<QSharedPointer<OpenGLBasicModel>> m_staticModels;
    QList<QSharedPointer<OpenGLBasicModel>> m_models;
};

}

#endif // OPENGLBASICWORLD_H
