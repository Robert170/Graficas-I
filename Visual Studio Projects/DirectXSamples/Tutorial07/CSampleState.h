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
	float MinLOD;
	float MaxLOD;
#if defined(D3D11)
	FILTER Filter;
	TEXTURE_ADDRESS_MODE AddressU;
	TEXTURE_ADDRESS_MODE AddressV;
	TEXTURE_ADDRESS_MODE AddressW;
	COMPARISON_FUNC ComparisonFunc;
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
#if defined(D3D11)
	D3D11_SAMPLER_DESC sampDesc;
	ID3D11SamplerState*                 g_pSamplerLinear = NULL;
#endif
};

