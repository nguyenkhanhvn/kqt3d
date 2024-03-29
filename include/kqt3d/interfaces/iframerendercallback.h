#ifndef IFRAMERENDERCALLBACK_H
#define IFRAMERENDERCALLBACK_H

namespace kqt3d {

class IFrameRenderCallback {
public:
    virtual void init() {}

    virtual void beforeRender() {}
    virtual void render() {}
    virtual void afterRender() {}
};

}

#endif // IFRAMERENDERCALLBACK_H
