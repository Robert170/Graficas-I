#include "CDepthStencilVoew.h"

int CDepthStencilView::init(C_DepthStencilView_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_DepthStencilView = _C_DEVICE_DESC;
	ZeroMemory(&descDSV, sizeof(descDSV));
	//m_DepthStencilView.descDSV.Flags = m_DepthStencilView.Flags;
	descDSV.Format =(DXGI_FORMAT) m_DepthStencilView.Format;
	descDSV.ViewDimension =(D3D11_DSV_DIMENSION) m_DepthStencilView.ViewDimension;
	m_DepthStencilView.Texture2D.mipSlice = m_DepthStencilView.MipSlice;
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
