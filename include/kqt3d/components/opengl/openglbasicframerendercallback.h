#ifndef OPENGLBASICFRAMERENDERCALLBACK_H
#define OPENGLBASICFRAMERENDERCALLBACK_H

#include <QColor>
#include <QOpenGLFunctions>

#include "kqt3d/components/basicperspectivecamera.h"
#include "kqt3d/interfaces/iframerendercallback.h"

namespace kqt3d {

class OpenGLBasicFrameRenderCallback: public IFrameRenderCallback, public QOpenGLFunctions
{
public:
    explicit OpenGLBasicFrameRenderCallback();

    virtual void init() override;
    virtual void destroy() override;
    virtual void beforeRender() override;

    QSharedPointer<kqt3d::BasicPerspectiveCamera> camera() const;
    QSharedPointer<kqtcore3d::ShaderProgram> program() const;

public:
    QColor clearColor = "white";

protected:
    QSharedPointer<kqt3d::BasicPerspectiveCamera> m_camera = nullptr;
    QSharedPointer<kqtcore3d::ShaderProgram> m_program = nullptr;
};

}

#endif // OPENGLBASICFRAMERENDERCALLBACK_H
