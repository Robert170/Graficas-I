#include "CTexture2D.h"


//! An \fn.
	/*!
	  init for class CTexture2D, init Tex_Des with m_TexDesc only in D3D11
	  \param _C_DEVICE_DESC an C_Texture2D_DESC.
	*/
int CTexture2D::init(C_Texture2D_DESC& _C_DEVICE_DESC)
{
	m_TexDesc = _C_DEVICE_DESC;
#ifdef D3D11
	ZeroMemory(&Tex_Des, sizeof(Tex_Des));

	Tex_Des.Width = m_TexDesc.Width;
	Tex_Des.Height = m_TexDesc.Height;
	Tex_Des.MipLevels = m_TexDesc.MipLevels;
	Tex_Des.ArraySize = m_TexDesc.ArraySize;
	Tex_Des.Format = (DXGI_FORMAT)m_TexDesc.Format;
	Tex_Des.SampleDesc.Count = m_TexDesc.SampleDesc.Count;
	Tex_Des.SampleDesc.Quality = m_TexDesc.SampleDesc.Quality;
	Tex_Des.Usage = (D3D11_USAGE)m_TexDesc.Usage;
	Tex_Des.BindFlags = m_TexDesc.BindFlags;
	Tex_Des.CPUAccessFlags = m_TexDesc.CPUAccessFlags;
	Tex_Des.MiscFlags = m_TexDesc.MiscFlags;
#endif
	return 0;
}

//! An \fn.
	/*!
	  init for class CTexture2D
	  \param Nam an string.
	*/
void CTexture2D::init(std::string Nam)
{
	
}

//! An \fn.
	/*!
	  update for the class CTexture2D
	*/
void CTexture2D::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CTexture2D
	*/
void CTexture2D::detroy()
{
}

//! An \fn.
	/*!
	  render for the class CTexture2D
	*/
void CTexture2D::render()
{
}
