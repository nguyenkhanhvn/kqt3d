#include "openglbasicmodel.h"
#include "openglbasicmesh.h"

namespace kqt3d {

OpenGLBasicModel::OpenGLBasicModel(const QVector<QSharedPointer<kqtcore3d::BaseMesh> > &meshes, QSharedPointer<kqtcore3d::IModelImporter> importer) :
    kqtcore3d::OpenGLModel(meshes, importer)
{
}

OpenGLBasicModel::OpenGLBasicModel(QSharedPointer<kqtcore3d::IModelImporter> importer) :
    kqtcore3d::OpenGLModel(QVector<QSharedPointer<kqtcore3d::BaseMesh>>(), importer)
{
}

void OpenGLBasicModel::render(QSharedPointer<kqtcore3d::ShaderProgram> program, const char *modelUniform, kqtcore3d::RenderCallback callback)
{
    if(program.isNull() || !program->bind()) return;
    for (const QSharedPointer<kqtcore3d::BaseMesh>& mesh : m_meshes)
    {
        QSharedPointer<OpenGLBasicMesh> tmp = qSharedPointerCast<OpenGLBasicMesh>(mesh);
        if(!tmp.isNull()) tmp->render(program, modelUniform, callback);
    }
}

void OpenGLBasicModel::setAttribLayout(QSharedPointer<kqtcore3d::ShaderProgram> program)
{
    if(program.isNull() || !program->bind()) return;
    for (const QSharedPointer<kqtcore3d::BaseMesh>& mesh : m_meshes)
    {
        QSharedPointer<OpenGLBasicMesh> tmp = qSharedPointerCast<OpenGLBasicMesh>(mesh);
        if(!tmp.isNull()) tmp->setAttribLayout(program);
    }
}

void OpenGLBasicModel::setPosition(const QVector3D &newPosition)
{
    for (const QSharedPointer<kqtcore3d::BaseMesh>& mesh : m_meshes)
    {
        QSharedPointer<OpenGLBasicMesh> tmp = qSharedPointerCast<OpenGLBasicMesh>(mesh);
        if(!tmp.isNull()) tmp->setPosition(newPosition);
    }
}

void OpenGLBasicModel::setScale(float newScale)
{
    for (const QSharedPointer<kqtcore3d::BaseMesh>& mesh : m_meshes)
    {
        QSharedPointer<OpenGLBasicMesh> tmp = qSharedPointerCast<OpenGLBasicMesh>(mesh);
        if(!tmp.isNull()) tmp->setScale(newScale);
    }
}

QMatrix4x4 OpenGLBasicModel::getTranformMatrix() const
{
    if(m_meshes.isEmpty()) return QMatrix4x4();
    return m_meshes.at(0)->getTransformationMatrix();
}

}
