#pragma once
#include "Define.h"
#include "CMesh.h"
//*****************************************************************************/
/**
* @File CModel.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief clase para hacer cargas de modelos
* @Bug No kown bug
**/
//****************************************************************************/


#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CDevice.h"
#include <vector>


class CModel
{
public:
	//! A constructor.
	/*!
	  function for use the constructor of the class CModel.
	*/
	CModel();

	//! A destroyer.
	/*!
	  function for use the destroyer of the class CModel.
	*/
	~CModel();


};

//{
//public:
//
//	std::vector<CMesh> m_VMesh;
//	glm::mat4x4 m_Tranform;
//
//	CMesh ProcessMesh(aiMesh * Mesh, const aiScene * Scene, aiMaterial * mat);
//	void ProcessNod(aiNode *node, const aiScene* scene);
//	void LoadModel(const std::string& path);
//	CModel();
//	~CModel();
//};

