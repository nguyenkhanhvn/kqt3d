#ifndef FRAME3D_H
#define FRAME3D_H

#include <QQuickFramebufferObject>
#include <QOpenGLFunctions>

#include "modules/3d/interfaces/RenderCallback.h"

namespace render3d {

class Frame3d : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    // RendererCallback must not be null
    explicit Frame3d(QSharedPointer<RenderCallback> renderCallback, QQuickItem *parent = nullptr);

    virtual Renderer *createRenderer() const override;

private:
    QSharedPointer<RenderCallback> const m_rendererCallback;

};

class Frame3dRenderer : public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions
{

public:
    Frame3dRenderer(QSharedPointer<RenderCallback> rendererCallback);

    virtual void render() override;
    virtual QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    const QSharedPointer<RenderCallback> m_rendererCallback;
};


}

#endif // FRAME3D_H
