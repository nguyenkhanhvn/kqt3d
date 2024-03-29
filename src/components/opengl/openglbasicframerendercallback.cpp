#include "openglbasicframerendercallback.h"

namespace kqt3d {

OpenGLBasicFrameRenderCallback::OpenGLBasicFrameRenderCallback()
{
}

void OpenGLBasicFrameRenderCallback::init()
{
    initializeOpenGLFunctions();
    m_program = kqtcore3d::ShaderProgram::create();
}

void OpenGLBasicFrameRenderCallback::beforeRender()
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

QSharedPointer<kqtcore3d::ShaderProgram> OpenGLBasicFrameRenderCallback::program()
{
    return m_program;
}

}
