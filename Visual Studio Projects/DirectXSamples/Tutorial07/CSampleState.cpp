#include "CSampleState.h"

int CSampleState::init(C_SampleState_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_SampleSate = _C_DEVICE_DESC;
	ZeroMemory(&m_SampleSate.sampDesc, sizeof(m_SampleSate.sampDesc));
	m_SampleSate.sampDesc.Filter = m_SampleSate.Filter;
	m_SampleSate.sampDesc.AddressU = m_SampleSate.AddressU;
	m_SampleSate.sampDesc.AddressV = m_SampleSate.AddressV;
	m_SampleSate.sampDesc.AddressW = m_SampleSate.AddressW;
	m_SampleSate.sampDesc.ComparisonFunc = m_SampleSate.ComparisonFunc;
	m_SampleSate.sampDesc.MaxLOD = m_SampleSate.MaxLOD;
	m_SampleSate.sampDesc.MinLOD = m_SampleSate.MinLOD;
	
#else 

#endif
	return 0;
}

void CSampleState::update()
{
}

void CSampleState::detroy()
{
}

void CSampleState::render()
{
}
