#include "CDeviceContext.h"



CDeviceContext * CDeviceContext::getInstance()
{
	if (DeviceInstanceCo == NULL)
		DeviceInstanceCo = new CDeviceContext();


	return DeviceInstanceCo;
}

CDeviceContext::CDeviceContext(CDeviceContext const &)
{
}

int CDeviceContext::init(C_DEVICE_CONTEXT_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)
	C_DEVICE_CONTEXT_DESC DC;
	ZeroMemory(&DC, sizeof(DC));

	m_DeviceContDesc = _C_DEVICE_DESC;



#else 

#endif
	return 0;
}

void CDeviceContext::update()
{
}

void CDeviceContext::detroy()
{
}

void CDeviceContext::render()
{
}

void * CDeviceContext::GetDevCont()
{
#if defined(D3D11)
	return  g_pImmediateContext;
#endif
	return nullptr;
}
