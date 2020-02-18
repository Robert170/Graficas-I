#include "CInputLayer.h"

int CInputLayer::init(C_InputLayer_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_InputLayer = _C_DEVICE_DESC;
	//ZeroMemory(&m_InputLayer.layout, sizeof(m_InputLayer.layout));
	

#else 

#endif
	return 0;
}

void CInputLayer::update()
{
}

void CInputLayer::detroy()
{
}

void CInputLayer::render()
{
}
