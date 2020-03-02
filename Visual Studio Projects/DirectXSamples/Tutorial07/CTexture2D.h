/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear texture
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
#include <vector>
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
public:
	int init(C_Texture2D_DESC& _C_DEVICE_DESC);
	void init(std::string Nam);
	void update();
	void detroy();
	void render();

	C_Texture2D_DESC m_TexDesc;
#if defined(D3D11)
	ID3D11Texture2D* m_pTexture;
	ID3D11ShaderResourceView *G_PTextureRV;
	ID3D11ShaderResourceView   *G_PInactiveRV = NULL;
	D3D11_TEXTURE2D_DESC Tex_Des;
#endif
};

