#include "CInputLayer.h"


//! An \fn.
	/*!
	  init for class CInputLayer, init m_InputLayer with _C_DEVICE_DESC only in D3D11
	  \param _C_DEVICE_DESC an C_DEVICE_CONTEXT_DESC.
	*/
int CInputLayer::init(C_InputLayer_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_InputLayer = _C_DEVICE_DESC;
	//ZeroMemory(&m_InputLayer.layout, sizeof(m_InputLayer.layout));
	

#else 

#endif
	return 0;
}

//! An \fn.
	/*!
	  update for the class CInputLayer
	*/
void CInputLayer::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CInputLayer
	*/
void CInputLayer::detroy()
{
}


//! An \fn.
	/*!
	  render for the class CInputLayer
	*/
void CInputLayer::render()
{
}
