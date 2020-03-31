/*****************************************************************************/
/**
* @File CViewport.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el viewport
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
#pragma once

// !An struct.
/*! struc for class CViewport. */
struct C_Viewport_DESC
{
	/**< struct FLOAT TopLeftX. */
	FLOAT TopLeftX;

	/**< struct FLOAT TopLeftY. */
	FLOAT TopLeftY;

	/**< struct FLOAT Width. */
	FLOAT Width;

	/**< struct FLOAT Height. */
	FLOAT Height;

	/**< struct FLOAT MinDepth. */
	FLOAT MinDepth;

	/**< struct FLOAT MaxDepth. */
	FLOAT MaxDepth;
};

class CViewport
{
public:
	//abstraer

	//! An init.
	/*!
	  init for class CViewport.
	  \param _C_DEVICE_DESC an C_Viewport_DESC.
	*/
	int init(C_Viewport_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CViewport.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CViewport.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CViewport.
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_Viewport_DESC for use the member of struc with the variable m_Viewport.
	*/
	C_Viewport_DESC  m_Viewport;
#if defined(D3D11)

	//! A public variable.
	/*!
	  variable  D3D11_VIEWPORT , only whit D3D11.
	*/
	D3D11_VIEWPORT data;
#endif
	
};

