#pragma once
#include "Define.h"
#include "CMesh.h"
#include <vector>

class CModel
{
	std::vector<CMesh> m_VMesh;
	glm::mat4x4 m_Tranform;

	CMesh ProcessMesh(aiMesh * Mesh, const aiScene * Scene, aiMaterial * mat);
	void ProcessNod(aiNode *node, const aiScene* scene);
	void LoadModel(const std::string& path);
	CModel();
	~CModel();
};

