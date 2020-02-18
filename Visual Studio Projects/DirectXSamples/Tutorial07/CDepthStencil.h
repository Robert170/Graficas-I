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


struct C_DepthStencil_DESC
{
	
	UINT Width;
	UINT Height;
	UINT MipLevels;
	UINT ArraySize;
	UINT BindFlags;
	UINT CPUAccessFlags;
	UINT MiscFlags;
#if defined(D3D11)
	DXGI_FORMAT Format;
	DXGI_SAMPLE_DESC SampleDesc;
	D3D11_USAGE Usage;
	D3D11_TEXTURE2D_DESC descDepth;
	ID3D11Texture2D* g_pDepthStencil = NULL;
#endif
};

class CDepthStencil
{
public:
	// abstraer
	int init(C_DepthStencil_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_DepthStencil_DESC  m_DepthStencil;
};

