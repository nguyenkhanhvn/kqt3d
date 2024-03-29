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
    OpenGLBasicFrameRenderCallback();

    virtual void init() override;
    virtual void beforeRender() override;

    QSharedPointer<kqtcore3d::ShaderProgram> program();

public:
    QColor clearColor = "white";

protected:
    QSharedPointer<kqtcore3d::ShaderProgram> m_program = nullptr;
};

}

#endif // OPENGLBASICFRAMERENDERCALLBACK_H
