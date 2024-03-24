#include "frame3d.h"

#include <QOpenGLFramebufferObjectFormat>

namespace render3d {

Frame3d::Frame3d(QSharedPointer<RenderCallback> renderCallback, QQuickItem *parent) :
    QQuickFramebufferObject(parent),
    m_rendererCallback(renderCallback)
{
    Q_ASSERT(!m_rendererCallback.isNull());
}

QQuickFramebufferObject::Renderer *Frame3d::createRenderer() const
{
    return new Frame3dRenderer(m_rendererCallback);
}



Frame3dRenderer::Frame3dRenderer(QSharedPointer<RenderCallback> rendererCallback) :
    m_rendererCallback(rendererCallback)
{
    initializeOpenGLFunctions();

    m_rendererCallback->init();
}

void Frame3dRenderer::render()
{
    m_rendererCallback->beforeRender();
    m_rendererCallback->render();
    m_rendererCallback->afterRender();

    update();
}

QOpenGLFramebufferObject *Frame3dRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

}
