#include "CDepthStencil.h"

int CDepthStencil::init(C_DepthStencil_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_DepthStencil = _C_DEVICE_DESC;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = m_DepthStencil.Width;
	descDepth.Height = m_DepthStencil.Height;
	descDepth.MipLevels = m_DepthStencil.MipLevels;
	descDepth.ArraySize = m_DepthStencil.ArraySize;
	descDepth.BindFlags = m_DepthStencil.BindFlags;
	descDepth.CPUAccessFlags = m_DepthStencil.CPUAccessFlags;
	descDepth.MiscFlags = m_DepthStencil.MiscFlags;
	descDepth.Format =(DXGI_FORMAT) m_DepthStencil.Format;
	descDepth.SampleDesc.Count = m_DepthStencil.SampleDesc.Count;
	descDepth.SampleDesc.Quality = m_DepthStencil.SampleDesc.Quality;
	descDepth.Usage =(D3D11_USAGE) m_DepthStencil.Usage;
#else 

#endif
	return 0;
}

void CDepthStencil::update()
{
}

void CDepthStencil::detroy()
{
}

void CDepthStencil::render()
{
}

void * CDepthStencil::GetDepth()
{
#if defined(D3D11)
	return  g_pDepthStencil;
#endif
	return nullptr;
}
