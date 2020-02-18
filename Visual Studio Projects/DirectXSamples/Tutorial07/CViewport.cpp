#include "CViewport.h"

int CViewport::init(C_Viewport_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_Viewport = _C_DEVICE_DESC;
	ZeroMemory(&m_Viewport.vp, sizeof(m_Viewport.vp));
	/*m_Viewport.vp.Width = m_Viewport.Width;
	m_Viewport.vp.Height = m_Viewport.Height;
	m_Viewport.vp.MinDepth = m_Viewport.MinDepth;
	m_Viewport.vp.MaxDepth = m_Viewport.MaxDepth;
	m_Viewport.vp.TopLeftX = m_Viewport.TopLeftX;
	m_Viewport.vp.TopLeftY = m_Viewport.TopLeftY;*/
	data.Height = m_Viewport.Height;
	data.Width = m_Viewport.Width;
	data.MinDepth = m_Viewport.MinDepth;
	data.MaxDepth = m_Viewport.MaxDepth;
	data.TopLeftX = m_Viewport.TopLeftX;
	data.TopLeftY = m_Viewport.TopLeftY;
	
#else 

#endif
	return 0;
}

void CViewport::update()
{
}

void CViewport::detroy()
{
}

void CViewport::render()
{
}
