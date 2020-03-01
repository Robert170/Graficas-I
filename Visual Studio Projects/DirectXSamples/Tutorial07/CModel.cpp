#include "CModel.h"

CMesh CModel::ProcessMesh(aiMesh * Mesh, const aiScene * Scene, aiMaterial * mat)
{
	CMesh CurrentMesh;
	for (unsigned int i = 0; i < Mesh->mNumVertices; i++)
	{
		SimpleVertex Ver;
		
		Ver.Pos.x = Mesh->mVertices[i].x;
		Ver.Pos.y = Mesh->mVertices[i].y;
		Ver.Pos.z = Mesh->mVertices[i].z;

		if (Mesh->mTextureCoords[0])
		{
			Ver.Tex.x = (float)Mesh->mTextureCoords[0][i].x;
			Ver.Tex.y = (float)Mesh->mTextureCoords[0][i].y;
		}
		CurrentMesh.VertexM.push_back(Ver);
	}

	for (unsigned int i = 0; i < Mesh->mNumFaces; i++)
	{
		aiFace Face = Mesh->mFaces[i];
		for (unsigned int j = 0; j < Face.mNumIndices; j++)
		{
			CurrentMesh.IndexM.push_back(Face.mIndices[2 - j]);
		}
	}

	if (mat->GetTextureCount(aiTextureType_DIFFUSE))
	{
		aiString FPath;
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &FPath, NULL, NULL, NULL, NULL, NULL);
		std::string FilePath = FPath.data;
		CurrentMesh.Texture.init(FilePath);
	}
	CurrentMesh.VerBUF.NumElements = CurrentMesh.VertexM.size();
	CurrentMesh.IndBUF.NumElements = CurrentMesh.IndexM.size();

	return CurrentMesh;
}

void CModel::ProcessNod(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* Mesh = scene->mMeshes[node->mMeshes[i]];
		aiMaterial* Material = scene->mMaterials[Mesh->mMaterialIndex];
		m_VMesh.push_back(ProcessMesh(Mesh, scene, Material));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNod(node->mChildren[i], scene);
	}
}

void CModel::LoadModel(const std::string & path)
{
Assimp::Importer IMP;
const aiScene* Model = aiImportFile("Smart Bomb.obj",aiProcess_ConvertToLeftHanded);
if (Model == nullptr)
{
	//error
}
else
{
	ProcessNod(Model->mRootNode, Model);
}
	std::vector<SimpleVertex> vertices;
	Assimp::Importer importer;



}

CModel::CModel()
{
}



CModel::~CModel()
{
}
