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

#ifdef D3D11
void CBuffer::createVertexBuffer(int _numvertex, const aiScene * _model, SimpleVertex * _vertex, ID3D11Buffer *& _buffer, void * _dev)
{
	ID3D11Device* dev = static_cast<ID3D11Device*>(_dev);
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * _numvertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _vertex;
	dev->CreateBuffer(&bd, &InitData, &_buffer);
}

void CBuffer::createIndexBuffer(int numindices, const aiScene * _model, WORD * _index, ID3D11Buffer *& _buffer, void * _dev)
{
	ID3D11Device* dev = static_cast<ID3D11Device*>(_dev);
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * numindices;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr = dev->CreateBuffer(&bd, &InitData, &_buffer);
	if (FAILED(hr))
		return;
}

#endif // D3D11

