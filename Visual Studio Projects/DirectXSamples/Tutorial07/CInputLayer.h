//*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el Input layer
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


struct C_InputLayer_DESC
{
	
	UINT SemanticIndex;
	UINT InputSlot;
	UINT AlignedByteOffset;
	UINT InstanceDataStepRate;
	
#if defined(D3D11)
	LPCSTR SemanticName;
	DXGI_FORMAT Format;
	D3D11_INPUT_CLASSIFICATION InputSlotClass;
	ID3D11InputLayout*  g_pVertexLayout = NULL;
	D3D11_INPUT_ELEMENT_DESC layout[];
#endif
};

class CInputLayer
{
public:
	//abstraer
	int init(C_InputLayer_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_InputLayer_DESC  m_InputLayer;
};

