
//*****************************************************************************/
/**
* @File CTargetView.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief abstraccion de target view
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
/*! struc for class CTargetView. */
struct C_TargetView_DESC
{
#if defined(D3D11)
	/**< struct FORMAT Format. */
	FORMAT Format;
	/**< struct RTV_DIMENSION ViewDimension. */
	RTV_DIMENSION ViewDimension;
	union
	{
		/**< struct BUFFER_RTV buffer. */
		BUFFER_RTV buffer;

		/**< struct TEX1D_DSV texture1D. */
		TEX1D_DSV texture1D;

		/**< struct TEX1D_ARRAY_DSV texture1DArray. */
		TEX1D_ARRAY_DSV texture1DArray;

		/**< struct TEX2D_DSV Texture2D. */
		TEX2D_DSV Texture2D;

		/**< struct TEX2D_ARRAY_DSV texture2DArray. */
		TEX2D_ARRAY_DSV texture2DArray;

		/**< struct TEX2DMS_DSV texture2DMS. */
		TEX2DMS_DSV texture2DMS;

		/**< struct TEX2DMS_ARRAY_DSV texture2DMSArray. */
		TEX2DMS_ARRAY_DSV texture2DMSArray;

		/**< struct TEX3D_RTV texture3D. */
		TEX3D_RTV texture3D;
	};
	
#endif
};
class CTargetView
{
public:
	//! An init.
	/*!
	  init for class CTargetView.
	  \param _C_DEVICE_DESC an C_TargetView_DESC.
	*/
	int init(C_TargetView_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CTargetView.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CTargetView.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CTargetView.
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_TargetView_DESC for use the member of struc with the variable m_TargetView.
	*/
	C_TargetView_DESC  m_TargetView;
#if defined(D3D11)

	//! A public variable.
	/*!
	  variable pointer ID3D11RenderTargetView for the pointer g_pRenderTargetView, only whit D3D11.
	*/
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;

	//! A public variable.
	/*!
	  variable  D3D11_RENDER_TARGET_VIEW_DESC , only whit D3D11.
	*/
	D3D11_RENDER_TARGET_VIEW_DESC m_Desc;
#endif
};

