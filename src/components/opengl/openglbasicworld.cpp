#include "openglbasicworld.h"

namespace kqt3d {

#define ALL_MODELS_DO_FUNCTION(functionName, ...)                                   \
for (const QSharedPointer<kqt3d::OpenGLBasicModel>& staticModel : m_staticModels) { \
    if(!staticModel.isNull()) staticModel->functionName(__VA_ARGS__);               \
}                                                                                   \
for (const QSharedPointer<kqt3d::OpenGLBasicModel>& model : m_models) {             \
    if(!model.isNull()) model->functionName(__VA_ARGS__);                           \
}

OpenGLBasicWorld::OpenGLBasicWorld(QList<QSharedPointer<OpenGLBasicModel> > listStaticModel, QMatrix4x4 transformationMatrix) :
    m_staticModels(listStaticModel), m_transformationMatrix(transformationMatrix)
{
}

bool OpenGLBasicWorld::init(kqtcore3d::RenderCallback callback)
{
    bool result = true;
    for (const QSharedPointer<kqt3d::OpenGLBasicModel>& staticModel : m_staticModels)
    {
        if(!staticModel.isNull()) result &= staticModel->init(callback);
    }
    for (const QSharedPointer<kqt3d::OpenGLBasicModel>& model : m_models)
    {
        if(!model.isNull()) result &= model->init(callback);
    }
    return result;
}

void OpenGLBasicWorld::translate(const QVector3D &vector)
{
    m_transformationMatrix.translate(vector);
}

void OpenGLBasicWorld::translate(float x, float y)
{
    m_transformationMatrix.translate(x, y);
}

void OpenGLBasicWorld::translate(float x, float y, float z)
{
    m_transformationMatrix.translate(x, y, z);
}

void OpenGLBasicWorld::rotate(float angle, float x, float y, float z)
{
    m_transformationMatrix.rotate(angle, x, y, z);
}

void OpenGLBasicWorld::rotate(const QQuaternion &quaternion)
{
    m_transformationMatrix.rotate(quaternion);
}

void OpenGLBasicWorld::rotate(const QVector3D &rotateAxis, float angle)
{
    m_transformationMatrix.rotate(angle, rotateAxis);
}

void OpenGLBasicWorld::rotateGlobal(const QVector3D &rotateAxis, float angle, const QVector3D &rotatePoint)
{
    QMatrix4x4 beforeRotation;
    beforeRotation.translate(-rotatePoint);
    QMatrix4x4 globalRotation;
    globalRotation.rotate(angle, rotateAxis);
    QMatrix4x4 afterRotation;
    afterRotation.translate(rotatePoint);
    m_transformationMatrix = beforeRotation * globalRotation * afterRotation * m_transformationMatrix;
}

void OpenGLBasicWorld::scale(const QVector3D &vector)
{
    m_transformationMatrix.scale(vector);
}

void OpenGLBasicWorld::scale(float x, float y)
{
    m_transformationMatrix.scale(x, y);
}

void OpenGLBasicWorld::scale(float x, float y, float z)
{
    m_transformationMatrix.scale(x, y, z);
}

void OpenGLBasicWorld::scale(float factor)
{
    m_transformationMatrix.scale(factor);
}

void OpenGLBasicWorld::addModel(QSharedPointer<OpenGLBasicModel> model)
{
    m_models.append(model);
}

int OpenGLBasicWorld::removeModel(QSharedPointer<OpenGLBasicModel> model)
{
    return m_models.removeAll(model);
}

void OpenGLBasicWorld::setAttribLayout(QSharedPointer<kqtcore3d::ShaderProgram> program)
{
    ALL_MODELS_DO_FUNCTION(setAttribLayout, program);
}

void OpenGLBasicWorld::render(QSharedPointer<kqtcore3d::ShaderProgram> program, const char *worldUniform, const char *modelUniform, kqtcore3d::RenderCallback callback)
{
    if(program.isNull() || !program->bind()) return;
    program->setUniformValue(worldUniform, m_transformationMatrix);
    ALL_MODELS_DO_FUNCTION(render, program, modelUniform, callback);
}

}
