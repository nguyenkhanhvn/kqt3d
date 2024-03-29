#ifndef KQT3DUTILS_H
#define KQT3DUTILS_H

#include <QString>
#include <QThread>
#include "kqtcore3d/kqtcore3d.h"

namespace kqt3d {

#define LOG_KQT3D qDebug() << "[kqt3d]" << "[Thread:" << QThread::currentThread() << "]" << "[" << __FILE__ << "][" << __FUNCTION__ << "][" << __LINE__ << "] "

typedef kqtcore3d::Indices<GLuint, GL_UNSIGNED_INT> BasicIndices;

struct BasicVertex {
    QVector3D position;
    QVector3D normal;
    QVector4D color = {0.0, 0.0, 0.0, 1.0};
    QVector2D texUV;
};
typedef kqtcore3d::Vertices<BasicVertex> BasicVertices;

QByteArray readFile(QString filename);

}

#endif // KQT3DUTILS_H
