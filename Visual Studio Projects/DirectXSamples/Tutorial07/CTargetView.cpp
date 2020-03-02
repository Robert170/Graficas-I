#include "CTargetView.h"

int CTargetView::init(C_TargetView_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)
	ZeroMemory(&m_Desc, sizeof(m_Desc));
	m_Desc.Format = (DXGI_FORMAT)_C_DEVICE_DESC.Format;
	m_Desc.ViewDimension = (D3D11_RTV_DIMENSION)_C_DEVICE_DESC.ViewDimension;
	m_Desc.Texture2D.MipSlice = _C_DEVICE_DESC.Texture2D.mipSlice;
#endif
	return 0;

}

void CTargetView::update()
{
}

void CTargetView::detroy()
{
}

void CTargetView::render()
{
}
