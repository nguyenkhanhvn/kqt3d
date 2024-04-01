#ifndef FRAMEBUFFEROBJECT_H
#define FRAMEBUFFEROBJECT_H

#include <QQuickFramebufferObject>

#include "kqt3d/interfaces/iframerendercallback.h"

namespace kqt3d {

class FramebufferObject : public QQuickFramebufferObject
{
public:
    // RendererCallback must not be null
    explicit FramebufferObject(QSharedPointer<IFrameRenderCallback> frameRendererCallback, QQuickItem *parent = nullptr);

    virtual Renderer *createRenderer() const override;

protected:
    QSharedPointer<IFrameRenderCallback> const m_frameRendererCallback;

};

namespace {
class FramebufferObjectRenderer : public QQuickFramebufferObject::Renderer
{

public:
    FramebufferObjectRenderer(QSharedPointer<IFrameRenderCallback> frameRendererCallback);
    ~FramebufferObjectRenderer();

    virtual void render() override;
    virtual QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

protected:
    const QSharedPointer<IFrameRenderCallback> m_frameRendererCallback;

};
}


}

#endif // FRAMEBUFFEROBJECT_H
