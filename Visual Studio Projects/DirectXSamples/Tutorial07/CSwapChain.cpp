#include "CSwapChain.h"



CSwapChain * CSwapChain::getInstance()
{
	if (SwapChainInstance == NULL)
		SwapChainInstance = new CSwapChain();


	return SwapChainInstance;
}

CSwapChain::CSwapChain(CSwapChain const &)
{
}

int CSwapChain::init(C_SWAP_CHAIN_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_SwapChain = _C_DEVICE_DESC;
	ZeroMemory(&m_SwapChain.sd, sizeof(m_SwapChain.sd));
	m_SwapChain.sd.BufferCount = m_SwapChain.BufferCount;
	m_SwapChain.sd.BufferDesc.Width = m_SwapChain.Width;
	m_SwapChain.sd.BufferDesc.Height = m_SwapChain.Height;
	m_SwapChain.sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_SwapChain.sd.BufferDesc.RefreshRate.Numerator = m_SwapChain.Numerator;
	m_SwapChain.sd.BufferDesc.RefreshRate.Denominator = m_SwapChain.Denominator;
	m_SwapChain.sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_SwapChain.sd.OutputWindow = m_SwapChain.OutputWindow;
	m_SwapChain.sd.SampleDesc.Count = m_SwapChain.Count;
	m_SwapChain.sd.SampleDesc.Quality = m_SwapChain.Quality;
	m_SwapChain.sd.Windowed = m_SwapChain.Windowed;

#else 

#endif
	return 0;
}

void CSwapChain::update()
{
}

void CSwapChain::detroy()
{
}

void CSwapChain::render()
{
}

const DXGI_SWAP_CHAIN_DESC CSwapChain::GetSD()
{
	return m_SwapChain.sd;
}