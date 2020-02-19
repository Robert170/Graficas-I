//*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief abstraccion de render target
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

struct MyStruC_Render_Target_DESCct
{
	unsigned int Width;
	unsigned int Height;
	unsigned int MipLevels;
	unsigned int ArraySize;
	unsigned int BindFlags;
	unsigned int CPUAccessFlags;
	unsigned int MiscFlags;
#if defined(D3D11)
	FORMAT Format;
	
	C_USAGE Usage;
	
#endif

};

class CRenderTarget
{
public:
	int init(MyStruC_Render_Target_DESCct& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	MyStruC_Render_Target_DESCct  m_RenderTarget;
#if defined(D3D11)

	DXGI_SAMPLE_DESC SampleDesc;
	ID3D11Texture2D* pBackBuffer = NULL;
#endif
};

