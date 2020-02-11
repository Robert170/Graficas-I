
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
	DXGI_FORMAT Format;
	D3D11_RTV_DIMENSION ViewDimension;
	union
	{
		D3D11_BUFFER_RTV Buffer;
		D3D11_TEX1D_RTV Texture1D;
		D3D11_TEX1D_ARRAY_RTV Texture1DArray;
		D3D11_TEX2D_RTV Texture2D;
		D3D11_TEX2D_ARRAY_RTV Texture2DArray;
		D3D11_TEX2DMS_RTV Texture2DMS;
		D3D11_TEX2DMS_ARRAY_RTV Texture2DMSArray;
		D3D11_TEX3D_RTV Texture3D;
	};
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;
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
};

