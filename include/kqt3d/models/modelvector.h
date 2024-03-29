#ifndef MODELVECTOR_H
#define MODELVECTOR_H

#include <QColor>

#include "kqt3d/components/opengl/openglbasicmodel.h"

namespace kqt3d {

class ModelVector : public OpenGLBasicModel
{
public:
    ModelVector(QVector3D tail = {0, -1, 0}, QVector3D head = {0, 0, 0}, QColor color = "white", float scale = 1);
    ModelVector(int length = 1, QVector3D direction = {0, 1, 0}, QVector3D startPoint = {0, 0, 0}, QColor color = "white", float scale = 1);

    // OpenGLBasicModel interface
    virtual bool init(kqtcore3d::RenderCallback callback = {}) override;
    virtual void render(QSharedPointer<kqtcore3d::ShaderProgram> program, const char *modelUniform, kqtcore3d::RenderCallback callback = {}) override;
    virtual void setAttribLayout(QSharedPointer<kqtcore3d::ShaderProgram> program) override;

    void setTail(QVector3D tail);
    void setHead(QVector3D head);

    // keep tail, move head to (tail+vector)
    void setDirection(QVector3D direction);

protected:
    void calculateTransformationMatrix();

    // IRenderable interface, not allow transformation
    virtual void translate(const QVector3D &vector) override {OpenGLBasicModel::translate(vector);}
    virtual void translate(float x, float y) override {OpenGLBasicModel::translate(x, y);}
    virtual void translate(float x, float y, float z) override {OpenGLBasicModel::translate(x, y, z);}
    virtual void rotate(float angle, float x, float y, float z) override {OpenGLBasicModel::rotate(angle, x, y, z);}
    virtual void rotate(const QQuaternion &quaternion) override {OpenGLBasicModel::rotate(quaternion);}
    virtual void rotate(const QVector3D &rotateAxis, float angle) override {OpenGLBasicModel::rotate(rotateAxis, angle);}
    virtual void rotateGlobal(const QVector3D &rotateAxis, float angle, const QVector3D &rotatePoint) override {OpenGLBasicModel::rotateGlobal(rotateAxis, angle, rotatePoint);}
    virtual void scale(const QVector3D &vector) override {OpenGLBasicModel::scale(vector);}
    virtual void scale(float x, float y) override {OpenGLBasicModel::scale(x, y);}
    virtual void scale(float x, float y, float z) override {OpenGLBasicModel::scale(x, y, z);}
    virtual void scale(float factor) override {OpenGLBasicModel::scale(factor);}

private:
    void createMesh(QColor color, float scale);

private:
    QVector3D m_tail;
    QVector3D m_head;
    QSharedPointer<OpenGLBasicMesh> m_headMesh = nullptr;
    QSharedPointer<OpenGLBasicMesh> m_lineMesh = nullptr;


};

}

#endif // MODELVECTOR_H
