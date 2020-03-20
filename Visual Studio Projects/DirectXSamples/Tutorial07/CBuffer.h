

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
#include "CDevice.h"
#pragma once

struct C_Buffer_DESC
{
	unsigned int ByteWidth;
	
	unsigned int  BindFlags;
	unsigned int  CPUAccessFlags;
	unsigned int  MiscFlags;
	unsigned int  StructureByteStride;

#if defined(D3D11)
	C_USAGE		Usage;
#endif

};

class CBuffer
{
public:
	int init(C_Buffer_DESC& _C_DEVICE_DESC);
	
	void update();
	void detroy();
	void render();
	C_Buffer_DESC  m_Buffer;
	

#if defined(D3D11)
	static void createVertexBuffer(int _numvertex, const aiScene* _model, SimpleVertex* _vertex, ID3D11Buffer*& _buffer, void* _dev);
	static void createIndexBuffer(int numindices, const aiScene* _model, WORD* _index, ID3D11Buffer*& _buffer, void* _dev);
	D3D11_BUFFER_DESC bd;
	ID3D11Buffer*   P_Buffer = NULL;
	
#endif
	
};


