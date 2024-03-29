#include "openglbasicmesh.h"

namespace kqt3d {

OpenGLBasicMesh::OpenGLBasicMesh(const QSharedPointer<kqtcore3d::IVertices> &vertices, const QSharedPointer<kqtcore3d::IIndices> &indices, QMatrix4x4 meshMatrix) :
    kqtcore3d::OpenGLMesh(vertices, indices, meshMatrix), m_position(0,0,0), m_scale(1)
{}

QMatrix4x4 OpenGLBasicMesh::getTransformationMatrix() const
{
    QMatrix4x4 modelMatrix = m_transformationMatrix;
    modelMatrix.translate(m_position);
    modelMatrix.scale(m_scale);
    return modelMatrix;
}

void OpenGLBasicMesh::render(QSharedPointer<kqtcore3d::ShaderProgram> program, const char* modelUniform, kqtcore3d::RenderCallback callback)
{
    program->setUniformValue(modelUniform, getTransformationMatrix());
    kqtcore3d::OpenGLMesh::render(callback);
}

void OpenGLBasicMesh::setAttribLayout(QSharedPointer<kqtcore3d::ShaderProgram> program)
{
    m_vao->bind();
    m_vbo->bind();
    program->setAttributeBuffer();
    m_vao->release();
    m_vbo->release();
}

QVector3D OpenGLBasicMesh::getPosition() const
{
    return m_position;
}

void OpenGLBasicMesh::setPosition(const QVector3D &newPosition)
{
    if(m_position == newPosition) return;
    m_position = newPosition;
}

float OpenGLBasicMesh::getScale() const
{
    return m_scale;
}

void OpenGLBasicMesh::setScale(float newScale)
{
    m_scale = newScale;
}

}
