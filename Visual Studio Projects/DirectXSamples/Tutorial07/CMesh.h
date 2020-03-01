#pragma once
#include "Define.h"
#include "CTexture2D.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include <vector>
class CMesh
{
public:

	std::vector<unsigned int>m_VIndex;
	std::vector<SimpleVertex>m_VVertex;
	CTexture2D TextureM;
	CVertexBuffer VertexBufferM;
	CIndexBuffer IndexBufferM;

	CMesh();
	~CMesh();
};

