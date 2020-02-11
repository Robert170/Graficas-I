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
	ID3D11Texture2D* pBackBuffer = NULL;
#endif

};

class CRenderTarget
{
};

