/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el pixel shader
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


struct C_PIXELSHADER_DESC
{

	

#if defined(D3D11)
	


#endif
};
class CPixelShader
{
public:
	//abstraer
	int init(C_PIXELSHADER_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_PIXELSHADER_DESC  m_InputLayer;
#if defined(D3D11)
	ID3D11PixelShader*                  g_pPixelShader = NULL;
	ID3DBlob* pPSBlob = NULL;
#endif
};

