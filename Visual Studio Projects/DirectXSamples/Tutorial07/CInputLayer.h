//*****************************************************************************/
/**
* @File CInputLayer.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el Input layer
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
/*! struc for class CInputLayer. */
struct C_InputLayer_DESC
{
	/**< struct unsigned int SemanticIndex. */
	unsigned int SemanticIndex;

	/**< struct unsigned int InputSlot. */
	unsigned int InputSlot;

	/**< struct unsigned int AlignedByteOffset. */
	unsigned int AlignedByteOffset;

	/**< struct unsigned int InstanceDataStepRate. */
	unsigned int InstanceDataStepRate;
	
#if defined(D3D11)

	/**< struct LPCSTR SemanticName. */
	LPCSTR SemanticName;

	/**< struct FORMAT Format. */
	FORMAT Format;

	/**< struct INPUT_CLASSIFICATION InputSlotClass. */
	INPUT_CLASSIFICATION InputSlotClass;

	
#endif
};

class CInputLayer
{
public:
	//! An init.
	/*!
	  init for class CInputLayer.
	  \param _C_DEVICE_DESC an C_InputLayer_DESC.
	*/
	int init(C_InputLayer_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CInputLayer.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CInputLayer.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CInputLayer.
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_InputLayer_DESC for use the member of struc with the variable m_InputLayer.
	*/
	C_InputLayer_DESC  m_InputLayer;


#if defined(D3D11)

	//! A public variable.
	/*!
	  variable  SemanticName , only whit D3D11.
	*/
	LPCSTR SemanticName;

	//! A public variable.
	/*!
	  variable  FORMAT , only whit D3D11.
	*/
	FORMAT Format;

	//! A public variable.
	/*!
	  variable  D3D11_INPUT_CLASSIFICATION , only whit D3D11.
	*/
	D3D11_INPUT_CLASSIFICATION InputSlotClass;

	//! A public variable.
	/*!
	  variable pointer ID3D11InputLayout for the pointer g_pVertexLayout, only whit D3D11.
	*/
	ID3D11InputLayout*  g_pVertexLayout = NULL;

	//! A public variable.
	/*!
	  variable  D3D11_INPUT_ELEMENT_DESC , only whit D3D11.
	*/
	D3D11_INPUT_ELEMENT_DESC layout[];
#endif
};

