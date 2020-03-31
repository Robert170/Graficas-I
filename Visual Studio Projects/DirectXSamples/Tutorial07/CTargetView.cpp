#include "CTargetView.h"

//! An \fn.
	/*!
	  init for class CTargetView, init m_Desc with _C_DEVICE_DESC only in D3D11
	  \param _C_DEVICE_DESC an C_TargetView_DESC.
	*/
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

//! An \fn.
	/*!
	  update for the class CTargetView
	*/
void CTargetView::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CTargetView
	*/
void CTargetView::detroy()
{
}

//! An \fn.
	/*!
	  render for the class CTargetView
	*/
void CTargetView::render()
{
}
