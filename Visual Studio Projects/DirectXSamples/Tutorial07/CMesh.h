#pragma once
#include "Define.h"
#include "CTexture2D.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include <vector>
class CMesh
{

public:

	
	std::vector<unsigned int> IndexM;
	std::vector<SimpleVertex> VertexM;
	CTexture2D Texture;
	CVertexBuffer VerBUF;
	CIndexBuffer IndBUF;

	CMesh();
	
	~CMesh();
};

