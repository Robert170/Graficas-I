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


struct C_SampleState_DESC
{
	FLOAT MinLOD;
	FLOAT MaxLOD;
#if defined(D3D11)
	D3D11_FILTER Filter;
	D3D11_TEXTURE_ADDRESS_MODE AddressU;
	D3D11_TEXTURE_ADDRESS_MODE AddressV;
	D3D11_TEXTURE_ADDRESS_MODE AddressW;
	D3D11_COMPARISON_FUNC ComparisonFunc;
	D3D11_SAMPLER_DESC sampDesc;
	ID3D11SamplerState*                 g_pSamplerLinear = NULL;
#endif
};

class CSampleState
{
public:
	// abstraer
	int init(C_SampleState_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_SampleState_DESC  m_SampleSate;
};

