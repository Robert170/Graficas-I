

//*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief abstraccion de buffer
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

struct C_Buffer_DESC
{
	unsigned int ByteWidth;
	C_USAGE		Usage;
	unsigned int  BindFlags;
	unsigned int  CPUAccessFlags;
	unsigned int  MiscFlags;
	unsigned int  StructureByteStride;
};

class CBuffer
{
public:
	int init(C_Buffer_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_Buffer_DESC  m_Buffer;
	D3D11_BUFFER_DESC bd;
};

