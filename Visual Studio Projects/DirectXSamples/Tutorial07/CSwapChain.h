/*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  05/02/2020
* @brief recrear el device context en singelton
* @Bug No kown bug
**/
/****************************************************************************/
#include "Define.h"

#ifdef D3D11
#include <d3d11.h>
#elif defined (OGL) 

#endif

#include <iostream>
#include <windows.h>
#pragma once


struct C_SWAP_CHAIN_DESC
{
	unsigned int BufferCount;
	unsigned int Width;
	unsigned int Height;
	unsigned int Numerator;
	unsigned int Denominator;
	HWND OutputWindow;
	unsigned int Count;
	unsigned int Quality ;
	bool Windowed;

#if defined(D3D11)
	DXGI_SWAP_CHAIN_DESC BufferUsage;
	DXGI_SWAP_CHAIN_DESC BufferDes;
	IDXGISwapChain*      g_pSwapChain = NULL;
	DXGI_SWAP_CHAIN_DESC sd;
#endif
};


class CSwapChain
{
public:

	//singelton
	static CSwapChain* getInstance();
	CSwapChain(CSwapChain const&);
	

	//abstraer
	int init(C_SWAP_CHAIN_DESC& _C_DEVICE_DESC);
	void update();
	void detroy();
	void render();
	C_SWAP_CHAIN_DESC  m_SwapChain;
	const DXGI_SWAP_CHAIN_DESC GetSD();

private:
	static CSwapChain *SwapChainInstance;

protected:
	CSwapChain()
	{
		std::cout << "Creating singleton" << std::endl;
	}

	virtual ~CSwapChain()
	{
	}
};



