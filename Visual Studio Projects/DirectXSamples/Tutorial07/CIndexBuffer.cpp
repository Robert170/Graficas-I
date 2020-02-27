#include "CIndexBuffer.h"

int CIndexBuffer::init(C_Index_Buffer_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_IndexBuffer = _C_DEVICE_DESC;
	ZeroMemory(&InitD, sizeof(InitD));
	InitD.pSysMem = m_IndexBuffer.pSystem;

#else 

#endif
	return 0;
}

void CIndexBuffer::update()
{
}

void CIndexBuffer::detroy()
{
}

void CIndexBuffer::render()
{
}
