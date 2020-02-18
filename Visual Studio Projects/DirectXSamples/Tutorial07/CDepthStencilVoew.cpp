#include "CDepthStencilVoew.h"

int CDepthStencilView::init(C_DepthStencilView_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_DepthStencilView = _C_DEVICE_DESC;
	ZeroMemory(&m_DepthStencilView.descDSV, sizeof(m_DepthStencilView.descDSV));
	//m_DepthStencilView.descDSV.Flags = m_DepthStencilView.Flags;
	m_DepthStencilView.descDSV.Format = m_DepthStencilView.Format;
	m_DepthStencilView.descDSV.ViewDimension = m_DepthStencilView.ViewDimension;
	m_DepthStencilView.Texture2D.MipSlice = m_DepthStencilView.MipSlice;
#else 

#endif
	return 0;
}

void CDepthStencilView::update()
{
}

void CDepthStencilView::detroy()
{
}

void CDepthStencilView::render()
{
}
