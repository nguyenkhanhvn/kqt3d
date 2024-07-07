#include "openglbasicframerendercallback.h"

namespace kqt3d {

OpenGLBasicFrameRenderCallback::OpenGLBasicFrameRenderCallback()
{
    m_camera = QSharedPointer<kqt3d::BasicPerspectiveCamera>::create();
}

void OpenGLBasicFrameRenderCallback::init()
{
    initializeOpenGLFunctions();
    m_program = kqtcore3d::ShaderProgram::create();
}

void OpenGLBasicFrameRenderCallback::destroy()
{
    m_program = nullptr;
}

void OpenGLBasicFrameRenderCallback::beforeRender()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

QSharedPointer<kqt3d::BasicPerspectiveCamera> OpenGLBasicFrameRenderCallback::camera() const
{
    return m_camera;
}

QSharedPointer<kqtcore3d::ShaderProgram> OpenGLBasicFrameRenderCallback::program() const
{
    return m_program;
}

}
