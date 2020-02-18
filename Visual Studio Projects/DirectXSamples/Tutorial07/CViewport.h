/*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el viewport
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


struct C_Viewport_DESC
{
	
	FLOAT TopLeftX;
	FLOAT TopLeftY;
	FLOAT Width;
	FLOAT Height;
	FLOAT MinDepth;
	FLOAT MaxDepth;
#if defined(D3D11)
	VIEWPORT vp;
#endif
};

class CViewport
{
public:
	//abstraer
	int init(C_Viewport_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_Viewport_DESC  m_Viewport;
#if defined(D3D11)
	D3D11_VIEWPORT data;
#endif
	
};

