//*****************************************************************************/
/**
* @File CIndexBuffer.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief abstraccion de index buffer
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
/*! struc for class CIndexBuffer. */
struct C_Index_Buffer_DESC
{
	/**< struct const void* pSystem. */
	const void* pSystem;

	/**< struct unsigned int  SystemMemoryPitch. */
	unsigned int  SystemMemoryPitch;

	/**< struct unsigned int  SysMemSlicePitch. */
	unsigned int SysMemSlicePitch;

#if defined(D3D11)


#endif
};

class CIndexBuffer
{
public:

	//! An init.
	/*!
	  init for class CIndexBuffer
	  \param _C_DEVICE_DESC an C_Index_Buffer_DESC.
	*/
	int init(C_Index_Buffer_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CIndexBuffer
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CIndexBuffer
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CIndexBuffer
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_Index_Buffer_DESC for use the member of struc with the variable m_IndexBuffer.
	*/
	C_Index_Buffer_DESC  m_IndexBuffer;

	//! A public variable.
	/*!
	  variable CBuffer for use the buffer object.
	*/
	CBuffer BIndex;

	//! A public variable.
	/*!
	  variable unsigned int for save the num of elements.
	*/
	unsigned int NumElements;

#if defined(D3D11)
	//! A public variable.
	/*!
	  variable D3D11_SUBRESOURCE_DATA for  use InitD, only whit D3D11.
	*/
	D3D11_SUBRESOURCE_DATA InitD;
#endif
};

