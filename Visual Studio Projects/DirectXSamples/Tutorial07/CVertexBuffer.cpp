#include "CVertexBuffer.h"

int CVertexBuffer::init(C_Vertex_Buffer_DESC & _C_DEVICE_DESC)
{

#if defined(D3D11)

	m_VertexBuffer = _C_DEVICE_DESC;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = m_VertexBuffer.pSystem;

#else 

#endif
	return 0;
}

void CVertexBuffer::update()
{
}

void CVertexBuffer::detroy()
{
}

void CVertexBuffer::render()
{
}
