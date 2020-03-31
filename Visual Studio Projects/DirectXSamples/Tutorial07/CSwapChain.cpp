#include "CSwapChain.h"


// !A \fn.
/*!
  function to return the instance of the singelton if first is not instance before.
*/
CSwapChain * CSwapChain::getInstance()
{
	if (SwapChainInstance == NULL)
		SwapChainInstance = new CSwapChain();


	return SwapChainInstance;
}

CSwapChain::CSwapChain(CSwapChain const &)
{
}

//! An \fn.
	/*!
	  init for class CSwapChain, init SCD with m_SwapChain only in D3D11
	  \param _C_DEVICE_DESC an C_DEVICE_DESC.
	*/
int CSwapChain::init(C_SWAP_CHAIN_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_SwapChain = _C_DEVICE_DESC;
	ZeroMemory(&SCD, sizeof(SCD));
	//m_SwapChain.sd.BufferCount = m_SwapChain.BufferCount;
	//m_SwapChain.sd.BufferDesc.Width = m_SwapChain.Width;
	//m_SwapChain.sd.BufferDesc.Height = m_SwapChain.Height;
	//m_SwapChain.sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//m_SwapChain.sd.BufferDesc.RefreshRate.Numerator = m_SwapChain.Numerator;
	//m_SwapChain.sd.BufferDesc.RefreshRate.Denominator = m_SwapChain.Denominator;
	//m_SwapChain.sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//m_SwapChain.sd.OutputWindow = m_SwapChain.OutputWindow;
	//m_SwapChain.sd.SampleDesc.Count = m_SwapChain.Count;
	//m_SwapChain.sd.SampleDesc.Quality = m_SwapChain.Quality;
	//m_SwapChain.sd.Windowed = m_SwapChain.Windowed;
	
	SCD.BufferCount = m_SwapChain.BufferCount;
	SCD.BufferDesc.Width = m_SwapChain.Width;
	SCD.BufferDesc.Height = m_SwapChain.Height;
	SCD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SCD.BufferDesc.RefreshRate.Numerator = m_SwapChain.Numerator;
	SCD.BufferDesc.RefreshRate.Denominator = m_SwapChain.Denominator;
	SCD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SCD.OutputWindow = m_SwapChain.OutputWindow;
	SCD.SampleDesc.Count = m_SwapChain.Count;
	SCD.SampleDesc.Quality = m_SwapChain.Quality;
	SCD.Windowed = m_SwapChain.Windowed;

#else 

#endif
	return 0;
}

//! An \fn.
	/*!
	  update for the class CSwapChain
	*/
void CSwapChain::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CSwapChain
	*/
void CSwapChain::detroy()
{
}

//! An \fn.
	/*!
	  v for the class CSwapChain
	*/
void CSwapChain::render()
{
}

//! A \fn.
	/*!
	  function return pointer for use g_pd3dDevice pointer or SCD.
	*/
void * CSwapChain::GetSwap()
{
#if defined(D3D11)
	return  g_pSwapChain;
#endif
	return nullptr;
}
#if defined(D3D11)
const DXGI_SWAP_CHAIN_DESC CSwapChain::GetSD()
{
	return SCD;
}
#endif