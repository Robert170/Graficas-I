#include "CSampleState.h"

//! An \fn.
	/*!
	  init for class CSampleState, init sampDesc with m_SampleSate only in D3D11
	  \param _C_DEVICE_DESC an C_SampleState_DESC.
	*/
int CSampleState::init(C_SampleState_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_SampleSate = _C_DEVICE_DESC;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = (D3D11_FILTER)m_SampleSate.Filter;
	sampDesc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)m_SampleSate.AddressU;
	sampDesc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)m_SampleSate.AddressV;
	sampDesc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)m_SampleSate.AddressW;
	sampDesc.ComparisonFunc = (D3D11_COMPARISON_FUNC)m_SampleSate.ComparisonFunc;
	sampDesc.MaxLOD = m_SampleSate.MaxLOD;
	sampDesc.MinLOD = m_SampleSate.MinLOD;
	
#else 

#endif
	return 0;
}

//! An \fn.
	/*!
	  update for the class CSampleState
	*/
void CSampleState::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CSampleState
	*/
void CSampleState::detroy()
{
}

//! An \fn.
	/*!
	  render for the class CSampleState
	*/
void CSampleState::render()
{
}
