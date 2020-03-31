#include "CDepthStencilVoew.h"


//! An fn.
	/*!
	  init for class CDepthStencilView, init all members of the struc 
	  \param _C_DEVICE_DESC an C_DepthStencilView_DESC.
	  \param FORMAT an DXGI_FORMAT.
	*/
#if defined(D3D11)
int CDepthStencilView::init(C_DepthStencilView_DESC & _C_DEVICE_DESC, DXGI_FORMAT FORMAT)
{
#if defined(D3D11)

	m_DepthStencilView = _C_DEVICE_DESC;
	ZeroMemory(&descDSV, sizeof(descDSV));
	//m_DepthStencilView.descDSV.Flags = m_DepthStencilView.Flags;
	descDSV.Format =FORMAT;
	descDSV.ViewDimension =(D3D11_DSV_DIMENSION) m_DepthStencilView.ViewDimension;
	m_DepthStencilView.Texture2D.mipSlice = m_DepthStencilView.MipSlice;
#else 

#endif
	return 0;
}
#endif

//! An fn.
	/*!
	  update for the class Depth Stencil
	*/
void CDepthStencilView::update()
{
}

//! An fn.
	/*!
	  destroyer for the class Depth Stencil
	*/
void CDepthStencilView::detroy()
{
}

//! An fn.
	/*!
	  render for the class Depth Stencil
	*/
void CDepthStencilView::render()
{
}
