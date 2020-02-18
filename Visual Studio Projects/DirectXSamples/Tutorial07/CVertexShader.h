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


struct C_VertexShader_DESC
{

	
#if defined(D3D11)
	
#endif
};

class CVertexShader
{
public:
	//abstraer
	int init(C_VertexShader_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_VertexShader_DESC  m_VertexShader;
#if defined(D3D11)
	ID3D11VertexShader*   g_pVertexShader = NULL;
	ID3DBlob* pVSBlob = NULL;
#endif
	
};

