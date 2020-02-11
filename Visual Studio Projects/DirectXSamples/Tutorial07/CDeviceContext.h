/*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el device context en singelton
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

struct C_DEVICE_CONTEXT_DESC
{
	
#if defined(D3D11)
	ID3D11DeviceContext*   g_pImmediateContext = NULL;

#endif
};

class CDeviceContext
{
public:
	//singelton
	static CDeviceContext* getInstance();
	CDeviceContext(CDeviceContext const&);

	//abstraer
	int init(C_DEVICE_CONTEXT_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_DEVICE_CONTEXT_DESC  m_DeviceContDesc;

private:
	static CDeviceContext *DeviceInstanceCo;

protected:
	CDeviceContext()
	{
		std::cout << "Creating singleton" << std::endl;
	}

	virtual ~CDeviceContext()
	{
	}
};


