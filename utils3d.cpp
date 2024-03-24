#include "utils3d.h"

#include <QQuickWindow>

#include "utils.h"


namespace render3d {

void render3dInit()
{
    LOGD << "init graphic api";
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    QSurfaceFormat fmt;
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);
}

}
