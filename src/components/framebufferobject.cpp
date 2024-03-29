#include "framebufferobject.h"

#include <QOpenGLFramebufferObjectFormat>

#include "kqt3dutils.h"

namespace kqt3d {

FramebufferObject::FramebufferObject(QSharedPointer<IFrameRenderCallback> frameRendererCallback, QQuickItem *parent) :
    QQuickFramebufferObject(parent),
    m_frameRendererCallback(frameRendererCallback)
{
    Q_ASSERT(!m_frameRendererCallback.isNull());
    LOG_KQT3D;
}

QQuickFramebufferObject::Renderer *FramebufferObject::createRenderer() const
{
    LOG_KQT3D;
    return new FramebufferObjectRenderer(m_frameRendererCallback);
}



FramebufferObjectRenderer::FramebufferObjectRenderer(QSharedPointer<IFrameRenderCallback> frameRendererCallback) :
    m_frameRendererCallback(frameRendererCallback)
{
    LOG_KQT3D;
    m_frameRendererCallback->init();
}

void FramebufferObjectRenderer::render()
{
    m_frameRendererCallback->beforeRender();
    m_frameRendererCallback->render();
    m_frameRendererCallback->afterRender();

    update();
}

QOpenGLFramebufferObject *FramebufferObjectRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

}
