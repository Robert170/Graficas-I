/*****************************************************************************/
/**
* @File CSwapChain.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el SwapChain  en singelton
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
/*! struc for class CSwapChain. */
struct C_SWAP_CHAIN_DESC
{
	/**< struct unsigned int BufferCount. */
	unsigned int BufferCount;

	/**< struct unsigned int Width. */
	unsigned int Width;

	/**< struct unsigned int Height. */
	unsigned int Height;

	/**< struct unsigned int Numerator. */
	unsigned int Numerator;

	/**< struct unsigned int Denominator. */
	unsigned int Denominator;

	/**< struct HWND OutputWindow. */
	HWND OutputWindow;

	/**< struct unsigned int Count. */
	unsigned int Count;

	/**< struct unsigned int Quality. */
	unsigned int Quality ;

	/**< struct bool Windowed. */
	bool Windowed;

#if defined(D3D11)

	/**< struct SWAP_CHAIN_DESC BufferUsage. */
	SWAP_CHAIN_DESC BufferUsage;

	/**< struct SWAP_CHAIN_DESC BufferDes. */
	SWAP_CHAIN_DESC BufferDes;

	/**< struct SWAP_CHAIN_DESC sd. */
	SWAP_CHAIN_DESC sd;
#endif
};


class CSwapChain
{
public:

	//singelton

	//! A public static pointer function.
	/*!
	  function to obtain the instance of the singelton.
	*/
	static CSwapChain* getInstance();

	//! A constructor.
	/*!
	  function for use the constructor of the class CSwapChain.
	  \param const an CDevice.
	*/
	CSwapChain(CSwapChain const&);
	

	//abstraer

	//! An init.
	/*!
	  init for class CSwapChain.
	  \param _C_DEVICE_DESC an C_SWAP_CHAIN_DESC.
	*/
	int init(C_SWAP_CHAIN_DESC& _C_DEVICE_DESC);

	//! An update.
	/*!
	  update for class CSwapChain.
	*/
	void update();

	//! An detroy.
	/*!
	  detroy for class CSwapChain.
	*/
	void detroy();

	//! An render.
	/*!
	  render for class CSwapChain.
	*/
	void render();

	//! An public function.
	/*!
	  GetSwap for class CSwapChain.
	*/
	void*GetSwap();

	//! A public variable.
	/*!
	  variable C_SWAP_CHAIN_DESC for use the member of struc with the variable m_SwapChain.
	*/
	C_SWAP_CHAIN_DESC  m_SwapChain;
	

#if defined(D3D11)

	//! An public function.
	/*!
	  GetSD for class CSwapChain, only whit D3D11.
	*/
	const DXGI_SWAP_CHAIN_DESC GetSD();

	//! A public variable.
	/*!
	  variable pointer IDXGISwapChain for the pointer g_pSwapChain, only whit D3D11.
	*/
	IDXGISwapChain*      g_pSwapChain = NULL;

	//! A public variable.
	/*!
	  variable  DXGI_SWAP_CHAIN_DESC for the SCD, only whit D3D11.
	*/
	DXGI_SWAP_CHAIN_DESC SCD;
	
#endif

private:
	//! A private variable.
	/*!
	  variable static pointer CSwapChain for the pointer SwapChainInstance.
	*/
	static CSwapChain *SwapChainInstance;

protected:

	//! A protected function.
	/*!
	  for know if the singelton was create.
	*/
	CSwapChain()
	{
		std::cout << "Creating singleton" << std::endl;
	}
	//! A protected virtual function.
	/*!
	  for use the destroy for the singelton.
	*/
	virtual ~CSwapChain()
	{
	}
};



