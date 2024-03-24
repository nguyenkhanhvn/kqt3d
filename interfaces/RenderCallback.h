#ifndef RENDERCALLBACK_H
#define RENDERCALLBACK_H

namespace render3d {

class RenderCallback {
public:
    virtual void init() = 0;

    virtual void beforeRender() = 0;
    virtual void render() = 0;
    virtual void afterRender() = 0;
};

}

#endif // RENDERCALLBACK_H
