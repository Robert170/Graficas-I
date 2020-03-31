
//*****************************************************************************/
/**
* @File CVertexBuffer.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief abstraccion de vertex buffer
* @Bug No kown bug
**/
//****************************************************************************/

/*! \file Define.h
	\brief A Documented file.

	.h where include eneum, struc an other things for class use.
*/
#include "Define.h"


/*! \def D3D11

	definition for use D3D11.
*/
#ifdef D3D11
#include <d3d11.h>
#elif defined (OGL) 

#endif

#include <iostream>
#include <windows.h>
#include "CBuffer.h"
#pragma once

// !An struct.
/*! struc for class CVertexBuffer. */
struct C_Vertex_Buffer_DESC
{
	/**< struct const void* pSystem. */
	const void* pSystem;

	/**< struct unsigned int SystemMemoryPitch. */
	unsigned int  SystemMemoryPitch;

	/**< struct unsigned int SysMemSlicePitch. */
	unsigned int SysMemSlicePitch;

#if defined(D3D11)
	
	
#endif
};

class CVertexBuffer
{
public:

	//! An init.
	/*!
	  init for class CVertexBuffer.
	  \param _C_DEVICE_DESC an C_Vertex_Buffer_DESC.
	*/
	int init(C_Vertex_Buffer_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CVertexBuffer.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CVertexBuffer.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CVertexBuffer.
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_Vertex_Buffer_DESC for use the member of struc with the variable m_VertexBuffer.
	*/
	C_Vertex_Buffer_DESC  m_VertexBuffer;
	
	//! A public variable.
	/*!
	  variable CBuffer for use buffer with the variable BVertex.
	*/
	CBuffer BVertex;

	//! A public variable.
	/*!
	  variable for know the number of elements.
	*/
	unsigned int NumElements;
#if defined(D3D11)
	//ID3D11Buffer*    g_pVertexBuffer = NULL;

	//! A public variable.
	/*!
	  variable  D3D11_SUBRESOURCE_DATA , only whit D3D11.
	*/
	D3D11_SUBRESOURCE_DATA InitData;
#endif
};

