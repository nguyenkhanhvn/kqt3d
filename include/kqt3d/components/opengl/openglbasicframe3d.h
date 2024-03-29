#ifndef OPENGLBASICFRAME3D_H
#define OPENGLBASICFRAME3D_H

#include "kqt3d/components/framebufferobject.h"
#include "openglbasicframerendercallback.h"

namespace kqt3d {

class OpenGLBasicFrame3d : public FramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(QColor clearColor READ clearColor WRITE setClearColor NOTIFY clearColorChanged FINAL)


public:
    OpenGLBasicFrame3d(QSharedPointer<OpenGLBasicFrameRenderCallback> callback);
    QColor clearColor() const;
    void setClearColor(const QColor &newClearColor);

signals:
    void clearColorChanged();

protected:
    QSharedPointer<kqt3d::BasicPerspectiveCamera> m_camera = nullptr;
    QSharedPointer<OpenGLBasicFrameRenderCallback> m_basicFrameRenderCallback;

};

}

#endif // OPENGLBASICFRAME3D_H
