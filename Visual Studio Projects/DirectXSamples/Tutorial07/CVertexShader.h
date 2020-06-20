/*****************************************************************************/
/**
* @File CVertexShader.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief abstraer el vertex shader
* @Bug No kown bug
**/
/****************************************************************************/

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
#include "CInputLayer.h"
#pragma once

// !An struct.
/*! struc for class CVertexShader. */
struct C_VertexShader_DESC
{

	
#if defined(D3D11)
	
#endif
};




class CVertexShader
{
public:
	//abstraer

	//! An init.
	/*!
	  init for class CVertexShader.
	  \param _C_DEVICE_DESC an C_VertexShader_DESC.
	*/
	int init(C_VertexShader_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CVertexShader.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CVertexShader.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CVertexShader.
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_VertexShader_DESC for use the member of struc with the variable v.
	*/
	C_VertexShader_DESC  m_VertexShader;

	
#if defined(D3D11)

	//! A public variable.
	/*!
	  variable pointer ID3D11VertexShader for the pointer g_pVertexShader, only whit D3D11.
	*/
	ID3D11VertexShader*   g_pVertexShader = NULL;

	//! A public variable.
	/*!
	  variable pointer ID3DBlob for the pointer pVSBlob, only whit D3D11.
	*/
	ID3DBlob* pVSBlob = NULL;
#endif
	
};

