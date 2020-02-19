
//*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief abstraccion de buffer
* @Bug No kown bug
**/
//****************************************************************************/

#include "Define.h"

#ifdef D3D11
#include <d3d11.h>
#elif defined (OGL) 

#endif

#include <iostream>
#include <windows.h>
#pragma once

struct C_TargetView_DESC
{
#if defined(D3D11)
	FORMAT Format;
	RTV_DIMENSION ViewDimension;
	
#endif
};
class CTargetView
{
public:
	int init(C_TargetView_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_TargetView_DESC  m_TargetView;
#if defined(D3D11)
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;
#endif
};

