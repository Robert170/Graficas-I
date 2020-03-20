#include "CMaterial.h"

CMaterial::CMaterial()
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::Shutdown()
{
#if defined(D3D11)
	if (m_TexDif) {

		m_TexDif->Release();
}
#endif // D3D11
	
}
