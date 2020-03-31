//*****************************************************************************/
/**
* @File CRenderTarget.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief abstraccion de render target
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
#pragma once

// !An struct.
/*! struc for class CRenderTarget. */
struct MyStruC_Render_Target_DESCct
{
	/**< struct unsigned int Width. */
	unsigned int Width;

	/**< struct unsigned int Height. */
	unsigned int Height;

	/**< struct unsigned int MipLevels. */
	unsigned int MipLevels;

	/**< struct unsigned int ArraySize. */
	unsigned int ArraySize;

	/**< struct unsigned int BindFlags. */
	unsigned int BindFlags;

	/**< struct unsigned int CPUAccessFlags. */
	unsigned int CPUAccessFlags;

	/**< struct unsigned int v. */
	unsigned int MiscFlags;
#if defined(D3D11)

	/**< struct unsigned int Format. */
	FORMAT Format;
	
	/**< struct unsigned int Usage. */
	C_USAGE Usage;
	
#endif

};

class CRenderTarget
{
public:
	//! An init.
	/*!
	  init for class v.
	  \param _C_DEVICE_DESC an MyStruC_Render_Target_DESCct.
	*/
	int init(MyStruC_Render_Target_DESCct& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CRenderTarget.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CRenderTarget.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CRenderTarget.
	*/
	void render();

	//! A public variable.
	/*!
	  variable MyStruC_Render_Target_DESCct for use the member of struc with the variable m_RenderTarget.
	*/
	MyStruC_Render_Target_DESCct  m_RenderTarget;
#if defined(D3D11)

	//! A public variable.
	/*!
	  variable  DXGI_SAMPLE_DESC for SampleDesc, only whit D3D11.
	*/
	DXGI_SAMPLE_DESC SampleDesc;

	//! A public variable.
	/*!
	  variable pointer ID3D11Texture2D for the pointer pBackBuffer, only whit D3D11.
	*/
	ID3D11Texture2D* pBackBuffer = NULL;
#endif
};

