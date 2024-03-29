#include "openglbasicframe3d.h"

namespace kqt3d {

OpenGLBasicFrame3d::OpenGLBasicFrame3d(QSharedPointer<OpenGLBasicFrameRenderCallback> callback) :
    FramebufferObject(callback), m_basicFrameRenderCallback(callback)
{
    m_camera = QSharedPointer<kqt3d::BasicPerspectiveCamera>::create();
}

QColor OpenGLBasicFrame3d::clearColor() const
{
    return m_basicFrameRenderCallback->clearColor;
}

void OpenGLBasicFrame3d::setClearColor(const QColor &newClearColor)
{
    if (m_basicFrameRenderCallback->clearColor == newClearColor)
        return;
    m_basicFrameRenderCallback->clearColor = newClearColor;
    emit clearColorChanged();
}

}
