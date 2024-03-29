#include "basicperspectivecamera.h"

namespace kqt3d {

BasicPerspectiveCamera::BasicPerspectiveCamera(QVector3D position, QVector3D orientation, QVector3D up, float verticalAngle, float aspectRatio, float nearPlane, float farPlane, QMatrix4x4 projection) :
    kqtcore3d::PerspectiveCamera(position, orientation, up, verticalAngle, aspectRatio, nearPlane, farPlane, projection)
{
    m_orientation = orientation - position;
    m_orientation.normalize();
}

void BasicPerspectiveCamera::resize(QRectF newSize)
{
    setupPerspective(m_verticalAngle, newSize.width() / newSize.height(), m_nearPlane, m_farPlane);
}

void BasicPerspectiveCamera::inputControl(int key)
{
    if (key == Qt::Key_A) {
        cameraControl(kqtcore3d::CameraControl::Move_Left);
    } else if (key == Qt::Key_D) {
        cameraControl(kqtcore3d::CameraControl::Move_Right);
    } else if (key == Qt::Key_W) {
        cameraControl(kqtcore3d::CameraControl::Move_Up);
    } else if (key == Qt::Key_S) {
        cameraControl(kqtcore3d::CameraControl::Move_Down);
    }
}

void BasicPerspectiveCamera::zoom(float delta)
{
    cameraControl(kqtcore3d::CameraControl::Move_Forward, delta * 0.05);
}

}
