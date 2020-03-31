#include "CDevice.h"


// !A \fn.
/*!
  function to return the instance of the singelton if first is not instance before.
*/
CDevice * CDevice::getInstance()
{
	if (DeviceInstance == NULL)
		DeviceInstance = new CDevice();


	return DeviceInstance;
}

CDevice::CDevice(CDevice const &)
{
}

//! An \fn.
	/*!
	  init for class CDevice, init m_DeviceDesc with _C_DEVICE_DESC only in D3D11
	  \param _C_DEVICE_DESC an C_DEVICE_DESC.
	*/
int CDevice::init(C_DEVICE_DESC  _C_DEVICE_DESC)
{
#if defined(D3D11)	
	m_DeviceDesc = _C_DEVICE_DESC;
	

#else 

#endif
	return 0;
}

//! An \fn.
	/*!
	  update for the class CDevice
	*/
void CDevice::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CDevice
	*/
void CDevice::detroy()
{
}

//! An \fn.
	/*!
	  render for the class CDevice
	*/
void CDevice::render()
{
}

//! A \fn.
	/*!
	  function return pointer for use g_pd3dDevice pointer.
	*/
void * CDevice::GetDev()
{
#if defined(D3D11)
	return  g_pd3dDevice;
#endif
	return nullptr;
}
