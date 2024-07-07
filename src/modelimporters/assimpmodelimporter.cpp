#include "assimpmodelimporter.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "kqtcore3d/kqtcore3d.h"

#include "kqt3dutils.h"
#include "components/opengl/openglbasicmesh.h"

namespace kqt3d {

QMatrix4x4 aiMatrixToQMatrix(const aiMatrix4x4& aiMat) {
    QMatrix4x4 qtMat;

    // Copy each element from aiMatrix to QMatrix4x4
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qtMat(i, j) = aiMat[j][i]; // Transpose elements for the conversion
        }
    }

    return qtMat;
}

AssimpModelImporter::AssimpModelImporter(QColor defaultColor, const char* hint, uint flags) :
    m_defaultColor(defaultColor.redF(), defaultColor.greenF(), defaultColor.blueF(), defaultColor.alphaF()),
    m_flags(flags), m_hint(hint)
{
}

AssimpModelImporter::AssimpModelImporter(QVector4D defaultColor, const char* hint, uint flags) :
    m_defaultColor(defaultColor), m_flags(flags), m_hint(hint)
{
}

kqtcore3d::ModelImporterData AssimpModelImporter::loadModel(const QString &filename, QMatrix4x4 matrix)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename.toUtf8().constData(), m_flags);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG_KQT3D << "ERROR::ASSIMP::Load model error: " << importer.GetErrorString();
    }
    else
    {
        processScene(scene, matrix);
    }

    return m_lastData;
}

kqtcore3d::ModelImporterData AssimpModelImporter::loadModelFromMemory(const QByteArray &data, QMatrix4x4 matrix)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(data, data.size(), m_flags);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG_KQT3D << "ERROR::ASSIMP::Load model error: " << importer.GetErrorString();
    }
    else
    {
        processScene(scene, matrix);
    }

    return m_lastData;
}

uint AssimpModelImporter::getFlags() const
{
    return m_flags;
}

void AssimpModelImporter::setFlags(uint flags)
{
    if(m_flags != flags)
    {
        m_flags = flags;
    }
}

const char *AssimpModelImporter::getHint() const
{
    return m_hint;
}

void AssimpModelImporter::setHint(const char *hint)
{
    if(m_hint != hint)
    {
        m_hint = hint;
    }
}

QVector4D AssimpModelImporter::getDefaultColor() const
{
    return m_defaultColor;
}

void AssimpModelImporter::setDefaultColor(QVector4D defaultColor)
{
    if(m_defaultColor != defaultColor)
    {
        m_defaultColor = defaultColor;
    }
}

kqtcore3d::ModelImporterData AssimpModelImporter::getLastData() const
{
    return m_lastData;
}

void AssimpModelImporter::processScene(const aiScene *scene, QMatrix4x4 matrix)
{
    m_lastData = kqtcore3d::ModelImporterData();

    /**** Experiment: Move model to center of viewport ****/
    //    if(scene->mMeshes && scene->mMeshes[0]->mVertices)
    //    {
    //        matrix.translate({-scene->mMeshes[0]->mVertices[0].x, -scene->mMeshes[0]->mVertices[0].y, -scene->mMeshes[0]->mVertices[0].z});
    //    }
    processNode(scene->mRootNode, scene, matrix);
    if (m_lastData.meshes.size() > 0)
    {
        m_lastData.isLoaded = true;
    }
}

void AssimpModelImporter::processNode(aiNode *node, const aiScene *scene, QMatrix4x4 matrix)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene, aiMatrixToQMatrix(node->mTransformation) * matrix);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, aiMatrixToQMatrix(node->mTransformation) * matrix);
    }
}

void AssimpModelImporter::processMesh(aiMesh *mesh, const aiScene *scene, QMatrix4x4 matrix)
{
    QSharedPointer<BasicVertices> vertices = QSharedPointer<BasicVertices>::create();
    QSharedPointer<BasicIndices> indices = QSharedPointer<BasicIndices>::create();

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        BasicVertex vertex;
        if (mesh->mVertices) {
            vertex.position = QVector3D(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        }

        if (mesh->mNormals) {
            vertex.normal = QVector3D(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        }

        if (mesh->mColors && mesh->mColors[0]) {
            vertex.color = QVector4D(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a);
        } else vertex.color = m_defaultColor;

        vertices->push(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        if(face.mNumIndices < 3) continue;
        for (unsigned int j = 1; j < face.mNumIndices - 1; j++) {
            indices->push(face.mIndices[0]);
            indices->push(face.mIndices[j]);
            indices->push(face.mIndices[j + 1]);
        }
    }

    m_lastData.meshes.append(QSharedPointer<OpenGLBasicMesh>::create(vertices, indices, matrix));
}

}
