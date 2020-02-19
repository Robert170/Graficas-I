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
	
	unsigned int SemanticIndex;
	unsigned int InputSlot;
	unsigned int AlignedByteOffset;
	unsigned int InstanceDataStepRate;
	
#if defined(D3D11)
	LPCSTR SemanticName;
	FORMAT Format;
	INPUT_CLASSIFICATION InputSlotClass;

	
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
#if defined(D3D11)
	LPCSTR SemanticName;
	FORMAT Format;
	D3D11_INPUT_CLASSIFICATION InputSlotClass;
	ID3D11InputLayout*  g_pVertexLayout = NULL;
	D3D11_INPUT_ELEMENT_DESC layout[];
#endif
};

