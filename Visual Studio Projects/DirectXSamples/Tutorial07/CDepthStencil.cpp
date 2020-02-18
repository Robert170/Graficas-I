#include "CDepthStencil.h"

int CDepthStencil::init(C_DepthStencil_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_DepthStencil = _C_DEVICE_DESC;
	ZeroMemory(&m_DepthStencil.descDepth, sizeof(m_DepthStencil.descDepth));
	m_DepthStencil.descDepth.Width = m_DepthStencil.Width;
	m_DepthStencil.descDepth.Height = m_DepthStencil.Height;
	m_DepthStencil.descDepth.MipLevels = m_DepthStencil.MipLevels;
	m_DepthStencil.descDepth.ArraySize = m_DepthStencil.ArraySize;
	m_DepthStencil.descDepth.BindFlags = m_DepthStencil.BindFlags;
	m_DepthStencil.descDepth.CPUAccessFlags = m_DepthStencil.CPUAccessFlags;
	m_DepthStencil.descDepth.MiscFlags = m_DepthStencil.MiscFlags;
	m_DepthStencil.descDepth.Format = m_DepthStencil.Format;
	m_DepthStencil.descDepth.SampleDesc = m_DepthStencil.SampleDesc;
	m_DepthStencil.descDepth.Usage = m_DepthStencil.Usage;
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
