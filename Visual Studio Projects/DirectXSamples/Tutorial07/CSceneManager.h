#pragma once
#include <vector>
#include "CMesh.h"
#include "CDeviceContext.h"
#include "CDevice.h"
#include "CBuffer.h"
class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	void
		AddMesh(CMesh* newMesh);

	CMesh*& GetMesh(int meshID);

	void Update();

	void Render(CDeviceContext *_deviceCon, CBuffer* _buff, CDevice* _dev);

	void Shutdown();

	//Variables
	CBuffer* meshData;

	std::vector<CMesh*> m_MeshInScene;
private:
	//Variables

	int m_ID = 0;
};

