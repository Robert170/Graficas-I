#include "CBuffer.h"

int CBuffer::init(C_Buffer_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_Buffer = _C_DEVICE_DESC;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = (D3D11_USAGE)m_Buffer.Usage;
	bd.ByteWidth = m_Buffer.ByteWidth;
	bd.BindFlags = m_Buffer.BindFlags;
	bd.CPUAccessFlags = m_Buffer.CPUAccessFlags;

#else 

#endif
	return 0;
}

void CBuffer::update()
{
}

void CBuffer::detroy()
{
}

void CBuffer::render()
{
}
