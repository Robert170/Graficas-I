#include "CSceneManager.h"

//! An \fn.
	/*!
	  constructor of the class CSceneManager
	*/
CSceneManager::CSceneManager()
{
}

//! An \fn.
	/*!
	  v of the class CSceneManager
	*/
CSceneManager::~CSceneManager()
{
}

//! An \fn.
	/*!
	  function for add mesh, and push back in the vector.
	  \param newMesh an CMesh.
	*/
void CSceneManager::AddMesh(CMesh * newMesh)
{
	newMesh->SetSceneID(m_ID);
	m_ID++;
	m_MeshInScene.push_back(newMesh);
}

//! An \fn.
	/*!
	  function return mesh if is equal to meshID.
	  \param c an int.
	*/
CMesh *& CSceneManager::GetMesh(int meshID)
{
	for (size_t i = 0; i < m_MeshInScene.size(); i++) {

		if (m_MeshInScene[i]->GetSceneID() == meshID)
			return m_MeshInScene[i];
	}
}

//! An \fn.
	/*!
	  update for the class CSceneManager
	*/
void CSceneManager::Update()
{
	for (size_t i = 0; i < m_MeshInScene.size(); i++) {

		m_MeshInScene[i]->Update();
	}
}

//! A An \fn.
	/*!
	  function for render the model in the scene.
	  \param _deviceCon an CDeviceContext.
	  \param _buff an CBuffer.
	  \param _dev an CDevice.
	*/
void CSceneManager::Render(CDeviceContext * _deviceCon, CBuffer * _buff, CDevice * _dev)
{
	for (size_t i = 0; i < m_MeshInScene.size(); i++) {

		m_MeshInScene[i]->Render(_deviceCon, _buff, _dev);
	}
}

//! An \fn.
	/*!
	  Shutdown for the class CSceneManager
	*/
void CSceneManager::Shutdown()
{
	for (size_t i = 0; i < m_MeshInScene.size(); i++) {

		m_MeshInScene[i]->Delete();
	}
}
