#ifndef ASSIMPMODELIMPORTER_H
#define ASSIMPMODELIMPORTER_H

#include <QColor>

#include "kqtcore3d/kqtcore3d.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace kqt3d {

class AssimpModelImporter : public kqtcore3d::IModelImporter
{
public:
    AssimpModelImporter(QColor defaultColor = "white", const char* hint = "", uint flags = aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
    AssimpModelImporter(QVector4D defaultColor, const char* hint = "", uint flags = aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    virtual kqtcore3d::ModelImporterData loadModel(const QString &filename, QMatrix4x4 matrix = QMatrix4x4()) override;
    virtual kqtcore3d::ModelImporterData loadModelFromMemory(const QByteArray &data, QMatrix4x4 matrix = QMatrix4x4()) override;

    uint getFlags() const;
    void setFlags(uint flags);

    const char* getHint() const;
    void setHint(const char* hint);

    QVector4D getDefaultColor() const;
    void setDefaultColor(QVector4D defaultColor);

    kqtcore3d::ModelImporterData getLastData() const;

private:
    void processScene(const aiScene *scene, QMatrix4x4 matrix);
    void processNode(aiNode *node, const aiScene *scene, QMatrix4x4 matrix = QMatrix4x4());
    void processMesh(aiMesh *mesh, const aiScene *scene, QMatrix4x4 matrix = QMatrix4x4());

private:
    uint m_flags;
    const char* m_hint;
    kqtcore3d::ModelImporterData m_lastData;
    QVector4D m_defaultColor;
};

}

#endif // ASSIMPMODELIMPORTER_H
