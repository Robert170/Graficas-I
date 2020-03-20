#pragma once
#include "Define.h"
#include <string>

#ifdef D3D11
#include <d3d11.h>
#elif defined (OGL) 

#endif

class CMaterial
{
public:

	CMaterial();
	~CMaterial();

	void Shutdown();

	//Variables
	std::string					m_NormalName;
	bool						m_HasNormals;
	bool						m_HasDifuse;
	std::string					m_Diroftextures;
	std::string					m_DifuseName;
#if defined(D3D11)
	ID3D11ShaderResourceView*	m_TexDif = NULL;
	ID3D11ShaderResourceView*	m_TexNorm = NULL;
#endif // D3D11


};

