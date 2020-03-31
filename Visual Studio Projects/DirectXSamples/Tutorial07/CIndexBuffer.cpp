#include "CIndexBuffer.h"


//! An \fn.
	/*!
	  init for class CDeviceContext, init index buffer only in D3D11
	  \param _C_DEVICE_DESC an C_Index_Buffer_DESC.
	*/
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


//! An \fn.
	/*!
	  update for the class CIndexBuffer
	*/
void CIndexBuffer::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CIndexBuffer
	*/
void CIndexBuffer::detroy()
{
}

//! An \fn.
	/*!
	  render for the class CIndexBuffer
	*/
void CIndexBuffer::render()
{
}
