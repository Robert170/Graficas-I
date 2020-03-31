#include "CVertexBuffer.h"

//! An \fn.
	/*!
	  init for class CInputLayer, init InitData with m_VertexBuffer only in D3D11
	  \param _C_DEVICE_DESC an C_Vertex_Buffer_DESC.
	*/
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

//! An \fn.
	/*!
	  update for the class CVertexBuffer
	*/
void CVertexBuffer::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CVertexBuffer
	*/
void CVertexBuffer::detroy()
{
}

//! An \fn.
	/*!
	  render for the class CVertexBuffer
	*/
void CVertexBuffer::render()
{
}
