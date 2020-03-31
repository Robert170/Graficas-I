/*****************************************************************************/
/**
* @File C_SampleState_DESC.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief abstraccion de sample state
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
/*! struc for class CSampleState. */
struct C_SampleState_DESC
{
	/**< struct float MinLOD. */
	float MinLOD;

	/**< struct float MaxLOD. */
	float MaxLOD;
#if defined(D3D11)

	/**< struct FILTER Filter. */
	FILTER Filter;

	/**< struct TEXTURE_ADDRESS_MODE AddressU. */
	TEXTURE_ADDRESS_MODE AddressU;

	/**< struct TEXTURE_ADDRESS_MODE AddressV. */
	TEXTURE_ADDRESS_MODE AddressV;

	/**< struct TEXTURE_ADDRESS_MODE AddressW. */
	TEXTURE_ADDRESS_MODE AddressW;

	/**< struct COMPARISON_FUNC ComparisonFunc. */
	COMPARISON_FUNC ComparisonFunc;
#endif
};

class CSampleState
{
public:
	
	//! An init.
	/*!
	  init for class CSampleState.
	  \param _C_DEVICE_DESC an C_SampleState_DESC.
	*/
	int init(C_SampleState_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CSampleState.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CSampleState.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CSampleState.
	*/
	void render();

	//! A public variable.
	/*!
	  variable C_SampleState_DESC for use the member of struc with the variable m_SampleSate.
	*/
	C_SampleState_DESC  m_SampleSate;
#if defined(D3D11)

	//! A public variable.
	/*!
	  variable  D3D11_SAMPLER_DESC , only whit D3D11.
	*/
	D3D11_SAMPLER_DESC sampDesc;

	//! A public variable.
	/*!
	  variable pointer v for the pointer g_pSamplerLinear, only whit D3D11.
	*/
	ID3D11SamplerState*                 g_pSamplerLinear = NULL;
#endif
};

