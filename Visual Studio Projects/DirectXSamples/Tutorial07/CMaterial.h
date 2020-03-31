//*****************************************************************************/
/**
* @File CMaterial.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief clase para el material
* @Bug No kown bug
**/
//****************************************************************************/

#pragma once

/*! \file Define.h
	\brief A Documented file.

	.h where include eneum, struc an other things for class use.
*/
#include "Define.h"
#include <string>


/*! \def D3D11

	definition for use D3D11.
*/
#ifdef D3D11
#include <d3d11.h>
#elif defined (OGL) 

#endif

class CMaterial
{
public:

	//! A constructor.
	/*!
	  function for use the constructor of the class CMaterial.
	*/
	CMaterial();

	//! A destroyer.
	/*!
	  function for use the destroyer of the class CMaterial.
	*/
	~CMaterial();

	//! A public function.
	/*!
	  function shutdown the texture.
	*/
	void Shutdown();

	//Variables

	//! A public variable.
	/*!
	  variable string for name of normal.
	*/
	std::string					m_NormalName;

	//! A public variable.
	/*!
	  variable bool for know if has normal.
	*/
	bool						m_HasNormals;

	//! A public variable.
	/*!
	  variable bool for know if has difuse.
	*/
	bool						m_HasDifuse;

	//! A public variable.
	/*!
	  variable string for direccion of textures.
	*/
	std::string					m_Diroftextures;

	//! A public variable.
	/*!
	  variable string for name of difuse.
	*/
	std::string					m_DifuseName;


#if defined(D3D11)
	//! A public variable.
	/*!
	  variable ID3D11ShaderResourceView pointer for texture difuse, only for D3D11.
	*/
	ID3D11ShaderResourceView*	m_TexDif = NULL;

	//! A public variable.
	/*!
	  variable ID3D11ShaderResourceView pointer for texture normal, only for D3D11.
	*/
	ID3D11ShaderResourceView*	m_TexNorm = NULL;
#endif // D3D11


};

