/*****************************************************************************/
/**
* @File CDeviceContext.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el device context en singelton
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
/*! struc for class CDeviceContext. */
struct C_DEVICE_CONTEXT_DESC
{
	
#if defined(D3D11)
	

#endif
};

class CDeviceContext
{
public:
	//singelton

	//! A public static pointer function.
	/*!
	  function to obtain the instance of the singelton.
	*/
	static CDeviceContext* getInstance();

	//! A constructor.
	/*!
	  function for use the constructor of the class CDeviceContext.
	  \param const an CDeviceContext.
	*/
	CDeviceContext(CDeviceContext const&);

	//abstraer

	//! An init.
	/*!
	  init for class CDeviceContext
	  \param _C_DEVICE_DESC an C_DEVICE_CONTEXT_DESC.
	*/
	int init(C_DEVICE_CONTEXT_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CDeviceContext
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CDeviceContext
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CDeviceContext
	*/
	void render();

	//! A public function.
	/*!
	  function return void punter for use device context pointer.
	*/
	void*GetDevCont();

	//! A public variable.
	/*!
	  variable C_DEVICE_CONTEXT_DESC for use the member of struc with the variable m_DeviceContDesc.
	*/
	C_DEVICE_CONTEXT_DESC  m_DeviceContDesc;


#if defined(D3D11)

	//! A public variable.
	/*!
	  variable pointer ID3D11DeviceContext for the pointer g_pImmediateContext, only whit D3D11.
	*/
	ID3D11DeviceContext*   g_pImmediateContext = NULL;

#endif

private:

	//! A private variable.
	/*!
	  variable static pointer CDevice Contextfor the pointer 	static CDeviceContext *DeviceInstanceCo.
	*/
	static CDeviceContext *DeviceInstanceCo;

protected:

	//! A protected function.
	/*!
	  for know if the singelton was create.
	*/
	CDeviceContext()
	{
		std::cout << "Creating singleton" << std::endl;
	}

	//! A protected function.
	/*!
	  for use the destroy for the singelton.
	*/
	virtual ~CDeviceContext()
	{
	}
};


