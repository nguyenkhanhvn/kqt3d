#ifndef BASICPERSPECTIVECAMERA_H
#define BASICPERSPECTIVECAMERA_H

#include "kqtcore3d/kqtcore3d.h"

namespace kqt3d {

class BasicPerspectiveCamera : public kqtcore3d::PerspectiveCamera
{
public:
    BasicPerspectiveCamera(QVector3D position = {0.0, 0.0, 1.0}, QVector3D orientation = {0.0, 0.0, -1.0}, QVector3D up = {0.0, 1.0, 0.0},
                           float verticalAngle = 45, float aspectRatio = 1.0, float nearPlane = 0.01, float farPlane = 1000, QMatrix4x4 projection = QMatrix4x4());


    void resize(QRectF newSize);
    void inputControl(int key);
    void zoom(float delta);
};

}

#endif // BASICPERSPECTIVECAMERA_H
