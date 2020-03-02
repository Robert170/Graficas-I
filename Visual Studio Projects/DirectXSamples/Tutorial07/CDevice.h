/*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el device en singelton
* @Bug No kown bug
**/
/****************************************************************************/
#include "Define.h"

#ifdef D3D11
#include <d3d11.h>
#elif defined (OGL) 

#endif

#include <iostream>
#include <windows.h>



#pragma once

struct C_DEVICE_DESC
{
	//UINT g_driverType;
	unsigned int createDeviceFlags;
	unsigned int numFeatureLevels;
	
#if defined(D3D11)
	DRIVER_TYPE DriverTypeDe;
	
#endif
};


class CDevice
{
public:
	
	//singelton
	static CDevice* getInstance();
	CDevice(CDevice const&);
	//CDevice& operator=(CDevice const&);

	//abstraer
	int init(C_DEVICE_DESC _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	void*GetDev();
	C_DEVICE_DESC  m_DeviceDesc;
#if defined(D3D11)
	ID3D11Device*   g_pd3dDevice = NULL;
#endif


private:
	static CDevice *DeviceInstance;

protected:
	CDevice()
	{
		std::cout << "Creating singleton" << std::endl;
	}

	~CDevice()
	{
	}

};


