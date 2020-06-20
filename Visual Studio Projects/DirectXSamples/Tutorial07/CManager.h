#pragma once

#include "Define.h";
#include "CDevice.h"


struct Manager_desc
{
	
};

class CManager
{
public:
	CManager();
	~CManager();
	void Init();
	void Update(CDevice *Device, Manager_desc Desc);
	//void RenderManagerRender();

	glm::mat4x4 g_World;
	glm::vec4   g_vMeshColor;
	glm::vec4 lightPos;
};

