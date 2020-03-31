#include "CDeviceContext.h"


// !A \fn.
/*!
  function to return the instance of the singelton if first is not instance before.
*/
CDeviceContext * CDeviceContext::getInstance()
{
	if (DeviceInstanceCo == NULL)
		DeviceInstanceCo = new CDeviceContext();


	return DeviceInstanceCo;
}

// !A \fn.
/*!
  function for construc the class.
*/
CDeviceContext::CDeviceContext(CDeviceContext const &)
{
}

//! An \fn.
	/*!
	  init for class CDeviceContext, init m_DeviceContDesc with _C_DEVICE_DESC only in D3D11
	  \param _C_DEVICE_DESC an C_DEVICE_CONTEXT_DESC.
	*/
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

//! An \fn.
	/*!
	  update for the class CDeviceContext
	*/
void CDeviceContext::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CDeviceContext
	*/
void CDeviceContext::detroy()
{
}

//! An \fn.
	/*!
	  render for the class CDeviceContext
	*/
void CDeviceContext::render()
{
}

//! A \fn.
	/*!
	  function return pointer for use g_pImmediateContext pointer.
	*/
void * CDeviceContext::GetDevCont()
{
#if defined(D3D11)
	return  g_pImmediateContext;
#endif
	return nullptr;
}
