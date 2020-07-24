/*****************************************************************************/
/**
* @File CGraphicApi.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief crear el graphic api
* @Bug No kown bug
**/
/****************************************************************************/

/*! \file Define.h
	\brief A Documented file.

	.h where include eneum, struc an other things for class use.
*/
#pragma once
#include "Define.h"

#include "CDeviceContext.h"
#include "CDevice.h"
#include <string>
#include "CMesh.h"
#include "CSceneManager.h"
#include <map>

#include "gtc/quaternion.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/quaternion.hpp"

//struct MatrixForBone
//{
//	aiMatrix4x4 m_BoneOfften;
//	aiMatrix4x4 m_FinalBoneMatrix;
//};


class CGraphicApi
{
public:
	//! A constructor.
	/*!
	  function for use the constructor of the class CGraphicApi.
	*/
	CGraphicApi();

	//! A destroyer.
	/*!
	  function for use the destroyer of the class CGraphicApi.
	*/
	~CGraphicApi();

	//! A public variable.
	/*!
	  variable pointer aiScene for the model.
	*/
	const aiScene* m_Model = new const aiScene();

	//! A public variable.
	/*!
	  variable pointer Importer for assimp.
	*/
	//Assimp::Importer* m_Importer = new Assimp::Importer();

	//unsigned int m_NumBones;
	//! A public function.
	/*!
	  function return bool if the mesh was charge.
	  \param _meshPath an const char.
	  \param _sceneManager an CSceneManager.
	  \param _model an const aiScene.
	  \param _devCont an CDeviceContext.
	  \param _importer an Assimp::Importer.
	  \param _dev an void.
	*/
	const aiScene*
		ChargeMesh(const char* _meshPath, CSceneManager* _sceneManager, const aiScene* _model, CDeviceContext* _devCont, void* _dev, Assimp::Importer* Imp);

	//std::vector<MatrixForBone> MatrixBone;


	void BonesTrasnformation(float Time, std::vector<glm::mat4>& Transform, const aiScene * _model, CSceneManager * _sceneManager);

private:

	//! A private function.
	/*!
	  function for read mesh.
	  \param _model an const aiScene.
	  \param _mesh an CMesh.
	  \param _meshIndex an int.
	  \param _dev an void.
	*/
	void
		MeshRead(const aiScene* _model, CMesh* _mesh, int _meshIndex, void* _dev);

	//! A private function.
	/*!
	  function for read texture.
	  \param _model an const aiScene.
	  \param _mesh an CMesh.
	  \param _meshIndex an int.
	  \param _dev an void.
	*/
	void
		ReadTextureMesh(const aiScene* _model, CMesh* _mesh, int _meshIndex, void* _dev);

	const aiNodeAnim * AnimatinFindNode(const std::string NameNod, const aiAnimation * Anim);

	void JerarquiaDeNodo(float TimeAnim, const aiNode * Node, const glm::mat4 Transform, const aiScene* Model, CMesh * _mesh);

	int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
};

