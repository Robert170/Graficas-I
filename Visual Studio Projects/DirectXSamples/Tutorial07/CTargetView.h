
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
	union
	{
		BUFFER_RTV buffer;
		TEX1D_DSV texture1D;
		TEX1D_ARRAY_DSV texture1DArray;
		TEX2D_DSV Texture2D;
		TEX2D_ARRAY_DSV texture2DArray;
		TEX2DMS_DSV texture2DMS;
		TEX2DMS_ARRAY_DSV texture2DMSArray;
		TEX3D_RTV texture3D;
	};
	
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
	D3D11_RENDER_TARGET_VIEW_DESC m_Desc;
#endif
};

