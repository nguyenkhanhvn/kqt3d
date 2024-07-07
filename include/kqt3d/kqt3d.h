#ifndef KQT3D_H
#define KQT3D_H

#include "kqt3dutils.h"
#include "interfaces/iframerendercallback.h"
#include "modelimporters/assimpmodelimporter.h"
#include "components/framebufferobject.h"
#include "components/basicperspectivecamera.h"
#include "components/opengl/openglbasicframe3d.h"
#include "components/opengl/openglbasicframerendercallback.h"
#include "components/opengl/openglbasicmesh.h"
#include "components/opengl/openglbasicmodel.h"
#include "components/opengl/openglbasicworld.h"

namespace kqt3d {

void kqt3dInit();

}

#endif // KQT3D_H
