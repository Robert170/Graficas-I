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


struct C_DepthStencilView_DESC
{
	UINT Flags;
	UINT MipSlice;
#if defined(D3D11)
	DXGI_FORMAT Format;
	D3D11_DSV_DIMENSION ViewDimension;
	D3D11_TEX2D_DSV Texture2D;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ID3D11DepthStencilView*  g_pDepthStencilView = NULL;
#endif
};
class CDepthStencilView
{
public:
	// abstraer
	int init(C_DepthStencilView_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_DepthStencilView_DESC  m_DepthStencilView;
};

