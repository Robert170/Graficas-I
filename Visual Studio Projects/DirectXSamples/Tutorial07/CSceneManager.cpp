#include "CSceneManager.h"

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::AddMesh(CMesh * newMesh)
{
	newMesh->SetSceneID(m_ID);
	m_ID++;
	m_MeshInScene.push_back(newMesh);
}

CMesh *& CSceneManager::GetMesh(int meshID)
{
	for (size_t i = 0; i < m_MeshInScene.size(); i++) {

		if (m_MeshInScene[i]->GetSceneID() == meshID)
			return m_MeshInScene[i];
	}
}

void CSceneManager::Update()
{
	for (size_t i = 0; i < m_MeshInScene.size(); i++) {

		m_MeshInScene[i]->Update();
	}
}

void CSceneManager::Render(CDeviceContext * _deviceCon, CBuffer * _buff, CDevice * _dev)
{
	for (size_t i = 0; i < m_MeshInScene.size(); i++) {

		m_MeshInScene[i]->Render(_deviceCon, _buff, _dev);
	}
}

void CSceneManager::Shutdown()
{
	for (size_t i = 0; i < m_MeshInScene.size(); i++) {

		m_MeshInScene[i]->Delete();
	}
}
