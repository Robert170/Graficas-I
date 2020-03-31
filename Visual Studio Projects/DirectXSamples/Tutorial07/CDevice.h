/*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el device en singelton
* @Bug No kown bug
**/
/****************************************************************************/

/*! \file Define.h
	\brief A Documented file.

	.h where include eneum, struc an other things for class use.
*/
#include "Define.h"


/*! \def D3D11

	definition for use D3D11.
*/
#ifdef D3D11
#include <d3d11.h>
#elif defined (OGL) 

#endif

#include <iostream>
#include <windows.h>



#pragma once

// !An struct.
/*! struc for class CDevice. */
struct C_DEVICE_DESC
{
	/**< struct unsigned int createDeviceFlags. */
	unsigned int createDeviceFlags;

	/**< struct unsigned int numFeatureLevels. */
	unsigned int numFeatureLevels;
	
#if defined(D3D11)

	/**< struct DRIVER_TYPE DriverTypeDe only with D3D11. */
	DRIVER_TYPE DriverTypeDe;
	
#endif
};


class CDevice
{
public:
	
	//singelton

	//! A public static pointer function.
	/*!
	  function to obtain the instance of the singelton.
	*/
	static CDevice* getInstance();

	//! A constructor.
	/*!
	  function for use the constructor of the class CDevice.
	  \param const an CDevice.
	*/
	CDevice(CDevice const&);
	


	//! An init.
	/*!
	  init for class CDevice
	  \param _C_DEVICE_DESC an C_DEVICE_DESC.
	*/
	int init(C_DEVICE_DESC _C_DEVICE_DESC);


	//! An update.
	/*!
	  update for class CDevice.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CDevice.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CDevice.
	*/
	void render();

	//! A public function.
	/*!
	  function return void punter for use device pointer.
	*/
	void*GetDev();

	//! A public variable.
	/*!
	  variable C_DEVICE_DESC for use the member of struc with the variable m_DeviceDesc.
	*/
	C_DEVICE_DESC  m_DeviceDesc;

#if defined(D3D11)

	//! A public variable.
	/*!
	  variable pointer ID3D11Device for the pointer g_pd3dDevice, only whit D3D11.
	*/
	ID3D11Device*   g_pd3dDevice = NULL;
#endif


private:

	//! A private variable.
	/*!
	  variable static pointer CDevice for the pointer DeviceInstance.
	*/
	static CDevice *DeviceInstance;

protected:

	//! A protected function.
	/*!
	  for know if the singelton was create.
	*/
	CDevice()
	{
		std::cout << "Creating singleton" << std::endl;
	}

	//! A protected function.
	/*!
	  for use the destroy for the singelton.
	*/
	~CDevice()
	{
	}

};


