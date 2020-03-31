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
	Assimp::Importer* m_Importer = new Assimp::Importer();


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
	bool
		ChargeMesh(const char* _meshPath, CSceneManager* _sceneManager, const aiScene* _model, CDeviceContext* _devCont, Assimp::Importer* _importer, void* _dev);

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
};

