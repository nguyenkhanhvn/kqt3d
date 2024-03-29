#include "modelvector.h"

#include <QVector4D>

#include "kqt3dutils.h"

namespace kqt3d {

ModelVector::ModelVector(QVector3D tail, QVector3D head, QColor color, float scale) :
    OpenGLBasicModel(), m_tail(tail), m_head(head)
{
    createMesh(color, scale);
    calculateTransformationMatrix();
}

ModelVector::ModelVector(int length, QVector3D direction, QVector3D startPoint, QColor color, float scale) :
    OpenGLBasicModel()
{
    m_tail = startPoint;
    m_head = m_tail + direction;
    createMesh(color, scale);
    calculateTransformationMatrix();
}

bool ModelVector::init(kqtcore3d::RenderCallback callback)
{
    bool result = OpenGLBasicModel::init();
    return result & m_lineMesh->init();
}

void ModelVector::render(QSharedPointer<kqtcore3d::ShaderProgram> program, const char *modelUniform, kqtcore3d::RenderCallback callback)
{
    OpenGLBasicModel::render(program, modelUniform, callback);

    program->setUniformValue(modelUniform, m_lineMesh->getTransformationMatrix());
//    m_lineMesh->drawArrays(GL_LINES, 0, 2);
    m_lineMesh->drawElements(GL_LINES, m_lineMesh->indices()->getSize(), 0, callback);
}

void ModelVector::setAttribLayout(QSharedPointer<kqtcore3d::ShaderProgram> program)
{
    OpenGLBasicModel::setAttribLayout(program);
    m_lineMesh->setAttribLayout(program);
}

void ModelVector::setTail(QVector3D tail)
{
    m_tail = tail;
    calculateTransformationMatrix();
}

void ModelVector::setHead(QVector3D head)
{
    m_head = head;
    calculateTransformationMatrix();
}

void ModelVector::setDirection(QVector3D direction)
{
    m_head = m_tail + direction;
    calculateTransformationMatrix();
}

void ModelVector::calculateTransformationMatrix()
{
    QMatrix4x4 transformation;
    transformation.translate(m_head);
    QVector3D direction = m_head - m_tail;
    transformation.rotate(QQuaternion::rotationTo({0, 0, 1}, direction));
    m_headMesh->setTransformationMatrix(transformation);
    m_lineMesh->setTransformationMatrix(transformation);
    m_lineMesh->setScale(m_head.distanceToPoint(m_tail));
}

void ModelVector::createMesh(QColor color, float scale)
{
    QVector4D arrowColor = {color.redF(), color.greenF(), color.blueF(), color.alphaF()};
    m_headMesh = QSharedPointer<OpenGLBasicMesh>::create(
        QSharedPointer<BasicVertices>::create(QVector<BasicVertex>{
//            {{-0.1f, -1.0f,  0.1f},     { 0.0f, -1.0f,  0.0f},      arrowColor,     {0.0f, 0.0f}},		// Bottom side
//            {{-0.1f, -1.0f, -0.1f},     { 0.0f, -1.0f,  0.0f},      arrowColor,     {0.0f, 2.0f}},		// Bottom side
//            {{ 0.1f, -1.0f, -0.1f},     { 0.0f, -1.0f,  0.0f},      arrowColor,     {2.0f, 2.0f}},		// Bottom side
//            {{ 0.1f, -1.0f,  0.1f},     { 0.0f, -1.0f,  0.0f},      arrowColor,     {2.0f, 0.0f}},		// Bottom side

//            {{-0.1f, -1.0f,  0.1f},		{-1.0f,  0.1f,  0.0f},		arrowColor, 	{0.0f, 0.0f}},		// Left Side
//            {{-0.1f, -1.0f, -0.1f},		{-1.0f,  0.1f,  0.0f},		arrowColor,		{2.0f, 0.0f}},		// Left Side
//            {{ 0.0f,  0.0f,  0.0f},		{-1.0f,  0.1f,  0.0f},		arrowColor,		{1.0f, 2.0f}},		// Left Side

//            {{-0.1f, -1.0f, -0.1f},		{ 0.0f,  0.1f, -1.0f},		arrowColor,		{2.0f, 0.0f}},		// Non-facing side
//            {{ 0.1f, -1.0f, -0.1f},		{ 0.0f,  0.1f, -1.0f},		arrowColor,		{0.0f, 0.0f}},		// Non-facing side
//            {{ 0.0f,  0.0f,  0.0f},		{ 0.0f,  0.1f, -1.0f},		arrowColor,		{1.0f, 2.0f}},		// Non-facing side

//            {{ 0.1f, -1.0f, -0.1f},		{ 1.0f,  0.1f,  0.0f},		arrowColor,		{0.0f, 0.0f}},		// Right side
//            {{ 0.1f, -1.0f,  0.1f},		{ 1.0f,  0.1f,  0.0f},		arrowColor,		{2.0f, 0.0f}},		// Right side
//            {{ 0.0f,  0.0f,  0.0f},		{ 1.0f,  0.1f,  0.0f},		arrowColor,		{1.0f, 2.0f}},		// Right side

//            {{ 0.1f, -1.0f,  0.1f},		{ 0.0f,  0.1f,  1.0f},		arrowColor,		{2.0f, 0.0f}},		// Facing side
//            {{-0.1f, -1.0f,  0.1f},		{ 0.0f,  0.1f,  1.0f},		arrowColor, 	{0.0f, 0.0f}},		// Facing side
//            {{ 0.0f,  0.0f,  0.0f},		{ 0.0f,  0.1f,  1.0f},		arrowColor,		{1.0f, 2.0f}},		// Facing side

            {{ 0.0000f,  0.0000f,  0.0f},        {0.0f, 0.0f, 0.0f},     arrowColor,     {0.0f, 0.0f}},
            {{ 0.0000f,  0.0000f, -1.0f},        {0.0f, 0.0f, 0.0f},     arrowColor,     {0.0f, 0.0f}},
            {{-0.1000f,  0.0000f, -1.0f},        {0.0f, 0.0f, 0.0f},     arrowColor,     {0.0f, 0.0f}},
            {{-0.0500f,  0.0866f, -1.0f},        {0.0f, 0.0f, 0.0f},     arrowColor,     {0.0f, 0.0f}},
            {{ 0.0500f,  0.0866f, -1.0f},        {0.0f, 0.0f, 0.0f},     arrowColor,     {0.0f, 0.0f}},
            {{ 0.1000f,  0.0000f, -1.0f},        {0.0f, 0.0f, 0.0f},     arrowColor,     {0.0f, 0.0f}},
            {{ 0.0500f, -0.0866f, -1.0f},        {0.0f, 0.0f, 0.0f},     arrowColor,     {0.0f, 0.0f}},
            {{-0.0500f, -0.0866f, -1.0f},        {0.0f, 0.0f, 0.0f},     arrowColor,     {0.0f, 0.0f}},
        }),
        QSharedPointer<BasicIndices>::create(QVector<GLuint>{
//            0, 1, 2,    // Bottom side
//            0, 2, 3,    // Bottom side
//            4, 6, 5,    // Left side
//            7, 9, 8,    // Non-facing side
//            10, 12, 11, // Right side
//            13, 15, 14  // Facing side

            0, 2, 3,
            0, 3, 4,
            0, 4, 5,
            0, 5, 6,
            0, 6, 7,
            0, 7, 2,

            1, 2, 3,
            1, 3, 4,
            1, 4, 5,
            1, 5, 6,
            1, 6, 7,
            1, 7, 2,
        }));
    m_headMesh->setScale(scale);


    m_lineMesh = QSharedPointer<OpenGLBasicMesh>::create(
        QSharedPointer<BasicVertices>::create(QVector<BasicVertex>{
            {{0.0f, 0.0f, -1.0f},     { 0.0f, 0.0f, 0.0f},      arrowColor,     {0.0f, 0.0f}},		// tail
            {{0.0f, 0.0f,  0.0f},     { 0.0f, 0.0f, 0.0f},      arrowColor,     {0.0f, 0.0f}},		// head
        }),
        QSharedPointer<BasicIndices>::create(QVector<GLuint>{
            0, 1,
        }));


    m_meshes.push_back(m_headMesh);
}

}
