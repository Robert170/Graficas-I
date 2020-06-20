#include "CManager.h"

CManager::CManager()
{
	lightPos.x= 1.0f;
	lightPos.y = 1.0f;
	lightPos.z = 1.0f;

	g_World= glm::mat4(1.0f);

}

CManager::~CManager()
{
}

void CManager::Init()
{
}

void CManager::Update(CDevice *Device, Manager_desc Desc)
{
	
}
