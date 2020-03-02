#include "CDevice.h"



CDevice * CDevice::getInstance()
{
	if (DeviceInstance == NULL)
		DeviceInstance = new CDevice();


	return DeviceInstance;
}

CDevice::CDevice(CDevice const &)
{
}

int CDevice::init(C_DEVICE_DESC  _C_DEVICE_DESC)
{
#if defined(D3D11)	
	m_DeviceDesc = _C_DEVICE_DESC;
	

#else 

#endif
	return 0;
}

void CDevice::update()
{
}

void CDevice::detroy()
{
}

void CDevice::render()
{
}

void * CDevice::GetDev()
{
#if defined(D3D11)
	return  g_pd3dDevice;
#endif
	return nullptr;
}
