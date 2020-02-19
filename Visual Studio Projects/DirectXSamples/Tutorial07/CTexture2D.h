/**
* @File CDevice.h
* @Author Roberto Ram�rez Ontiveros (xc1700@hotmail.com)
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


struct C_Texture2D_DESC
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
	SAMPLE_DESC SampleDesc;
	C_USAGE Usage;
	
#endif
};
class CTexture2D
{
};

