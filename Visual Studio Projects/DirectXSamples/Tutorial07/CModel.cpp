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
		CurrentMesh.m_VVertex.push_back(Ver);
	}

	for (unsigned int i = 0; i < Mesh->mNumFaces; i++)
	{
		aiFace Face = Mesh->mFaces[i];
		for (unsigned int j = 0; j < Face.mNumIndices; j++)
		{
			CurrentMesh.m_VIndex.push_back(Face.mIndices[2 - j]);
		}
	}

	if (mat->GetTextureCount(aiTextureType_DIFFUSE))
	{
		aiString FPath;
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &FPath, NULL, NULL, NULL, NULL, NULL);
		std::string FilePath = FPath.data;
		//CurrentMesh.TextureM.init(FilePath);
	}

	

	return CurrentMesh;
}

void CModel::ProcessNod(aiNode * node, const aiScene * scene)
{
}

void CModel::LoadModel(const std::string & path)
{
}

CModel::~CModel()
{
}
