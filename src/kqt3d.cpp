#include "kqt3d.h"

#include <QQuickWindow>

#include "kqtcore3d/kqtcore3d.h"


namespace kqt3d {

void kqt3dInit()
{
    LOG << "init core 3d";
    kqtcore3d::kqtcore3dInit(kqtcore3d::RendererApi::OpenGL);

    LOG << "init graphic api";
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    QSurfaceFormat fmt;
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);
}

}
