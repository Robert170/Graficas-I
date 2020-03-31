/**
* @File CTexture2D.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear texture
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
#include <vector>
#pragma once


// !An struct.
/*! struc for class CTexture2D. */
struct C_Texture2D_DESC
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

	/**< struct SAMPLE_DESC SampleDesc. */
	SAMPLE_DESC SampleDesc;

	/**< struct C_USAGE Usage. */
	C_USAGE Usage;
	
#endif
};
class CTexture2D
{
public:
	//! An init.
	/*!
	  init for class CTexture2D.
	  \param _C_DEVICE_DESC an C_InputLayer_DESC.
	*/
	int init(C_Texture2D_DESC& _C_DEVICE_DESC);

	//! An init.
	/*!
	  init for class CTexture2D but this is void.
	  \param Nam an string.
	*/
	void init(std::string Nam);

	//! An update.
	/*!
	  update for class CTexture2D.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CTexture2D.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CTexture2D.
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_Texture2D_DESC for use the member of struc with the variable m_TexDesc.
	*/
	C_Texture2D_DESC m_TexDesc;
#if defined(D3D11)
	//! A public variable.
	/*!
	  variable pointer ID3D11Texture2D for the pointer m_pTexture, only whit D3D11.
	*/
	ID3D11Texture2D* m_pTexture;

	//! A public variable.
	/*!
	  variable pointer ID3D11ShaderResourceView for the pointer G_PTextureRV, only whit D3D11.
	*/
	ID3D11ShaderResourceView *G_PTextureRV;

	//! A public variable.
	/*!
	  variable pointer ID3D11ShaderResourceView for the pointer G_PInactiveRV, only whit D3D11.
	*/
	ID3D11ShaderResourceView   *G_PInactiveRV = NULL;

	//! A public variable.
	/*!
	  variable  D3D11_TEXTURE2D_DESC , only whit D3D11.
	*/
	D3D11_TEXTURE2D_DESC Tex_Des;
#endif
};

