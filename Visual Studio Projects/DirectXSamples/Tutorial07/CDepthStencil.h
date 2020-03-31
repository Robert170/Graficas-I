/*****************************************************************************/
/**
* @File CDepthStencil.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief clase para recrear el depthstencil y hacer su abstraccion
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
/*! struc for class CDepthstencil. */
struct C_DepthStencil_DESC
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

	/**< struct unsigned int MiscFlags. */
	unsigned int MiscFlags;
#if defined(D3D11)


	/**< struct FORMAT Format. */
	FORMAT Format;

	/**< struct C_USAGE Usaget. */
	C_USAGE Usage;

	/**< struct SAMPLE_DESC SampleDesc. */
	SAMPLE_DESC SampleDesc;
	
#endif
};

class CDepthStencil
{
public:
	//! An init.
	/*!
	  init for class CDepthstencil.
	  \param _C_DEVICE_DESC an C_DepthStencil_DESC.
	*/
	int init(C_DepthStencil_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CDepthstencil
	*/
	void update();

	//! An destroyer.
	/*!
	  destroyer for class CDepthstencil
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CDepthstencil
	*/
	void render();

	//! A public function.
	/*!
	  function return void punter for use depthstencil pointer.
	*/
	void* GetDepth();

	//! A public variable.
	/*!
	  variable C_DepthStencil_DESC for use the member of struc with the variable m_DepthStencil.
	*/
	C_DepthStencil_DESC  m_DepthStencil;

#if defined(D3D11)
	//! A public variable.
	/*!
	  variable D3D11_TEXTURE2D_DESC for use the member of struc with the variable descDepth, only whit D3D11.
	*/
	D3D11_TEXTURE2D_DESC descDepth;

	//! A public variable.
	/*!
	  variable pointer ID3D11Texture2D for the pointer g_pDepthStencil, only whit D3D11.
	*/
	ID3D11Texture2D* g_pDepthStencil = NULL;
#endif
};

