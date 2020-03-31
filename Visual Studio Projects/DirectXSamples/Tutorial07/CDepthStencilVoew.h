/*****************************************************************************/
/**
* @File CDepthStencilVoew.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear depth stencil view y abstraer
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
/*! struc for class CDepthStencilView. */
struct C_DepthStencilView_DESC
{
	/**< struct unsigned int Flags. */
	unsigned int Flags;

	/**< struct unsigned int MipSlice. */
	unsigned int MipSlice;

#if defined(D3D11)

	/**< struct FORMAT Format. */
	FORMAT Format;

	/**< struct DSV_DIMENSION ViewDimension. */
	DSV_DIMENSION ViewDimension;

	/**< struct TEX2D_DSV Texture2D. */
	TEX2D_DSV Texture2D;
	
#endif
};

class CDepthStencilView
{
public:
	// abstraer
#if defined(D3D11)

	//! An init.
	/*!
	  init for class CDepthStencilView only whit D3D11.
	  \param _C_DEVICE_DESC an C_DepthStencilView_DESC.
	  \param FORMAT an DXGI_FORMAT.
	*/
	int init(C_DepthStencilView_DESC& _C_DEVICE_DESC, DXGI_FORMAT FORMAT);
#endif

	//! An update.
	/*!
	  update for class CDepthStencilView.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CDepthStencilView.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CDepthStencilView.
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_DepthStencilView_DESC for use the member of struc with the variable m_DepthStencilView.
	*/
	C_DepthStencilView_DESC  m_DepthStencilView;
#if defined(D3D11)

	//! A public variable.
	/*!
	  variable D3D11_DEPTH_STENCIL_VIEW_DESC for use the member of struc with the variable descDSV, only whit D3D11.
	*/
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

	//! A public variable.
	/*!
	  variable pointer ID3D11DepthStencilView for the pointer g_pDepthStencilView, only whit D3D11.
	*/
	ID3D11DepthStencilView*  g_pDepthStencilView = NULL;
#endif
};

