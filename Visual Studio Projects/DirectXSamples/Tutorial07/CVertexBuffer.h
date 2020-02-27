
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
#include "CBuffer.h"
#pragma once
struct C_Vertex_Buffer_DESC
{
	const void* pSystem;
	unsigned int  SystemMemoryPitch;
	unsigned int SysMemSlicePitch;

#if defined(D3D11)
	
	
#endif
};

class CVertexBuffer
{
public:
	int init(C_Vertex_Buffer_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_Vertex_Buffer_DESC  m_VertexBuffer;
	
	CBuffer BVertex;
#if defined(D3D11)
	//ID3D11Buffer*    g_pVertexBuffer = NULL;
	D3D11_SUBRESOURCE_DATA InitData;
#endif
};

