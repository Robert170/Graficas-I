/*****************************************************************************/
/**
* @File CSceneManager.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el device context en singelton
* @Bug No kown bug
**/
/****************************************************************************/

#pragma once
#include <vector>
#include "CMesh.h"
#include "CDeviceContext.h"
#include "CDevice.h"
#include "CBuffer.h"
class CSceneManager
{
public:
	//! A constructor.
	/*!
	  function for use the constructor of the class CSceneManager.
	*/
	CSceneManager();

	//! A destroyer.
	/*!
	  function for use the destroyer of the class CSceneManager.
	*/
	~CSceneManager();

	//! A public function.
	/*!
	  function for add mesh.
	  \param newMesh an CMesh.
	*/
	void
		AddMesh(CMesh* newMesh);

	//! A public function.
	/*!
	  function return mesh.
	  \param c an int.
	*/
	CMesh*& GetMesh(int c);

	//! A Update.
	/*!
	  function for update.
	*/
	void Update();

	//! A public function.
	/*!
	  function for render.
	  \param _deviceCon an CDeviceContext.
	  \param _buff an CBuffer.
	  \param _dev an CDevice.
	*/
	void Render(CDeviceContext *_deviceCon, CBuffer* _buff, CDevice* _dev);

	//! A public function.
	/*!
	  function for Shutdown.
	*/
	void Shutdown();

	//Variables
	//! A public variable.
	/*!
	  variable pointer CBuffer for use meshData.
	*/
	CBuffer* meshData;

	//! A public variable.
	/*!
	  variable vector of CMesh use for m_MeshInScene.
	*/
	std::vector<CMesh*> m_MeshInScene;
private:
	//Variables

	//! A private variable.
	/*!
	  variable  int for ID.
	*/
	int m_ID = 0;
};

