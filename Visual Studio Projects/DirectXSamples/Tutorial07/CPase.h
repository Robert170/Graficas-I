#pragma once

#include "Define.h"
#include "CDeviceContext.h"
#include "CInputLayer.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CTargetView.h"
#include "CDepthStencilVoew.h"
#include "CBuffer.h"
#include "CCamera.h"
#include "CViewport.h"
#include "CSampleState.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CTexture2D.h"
#include "CRenderTarget.h"
#include "CDepthStencilVoew.h"
#include "CSceneManager.h"
#include "CViewport.h"



struct PASSE_DIRECTX_STRUCT
{
	CInputLayer* IntLay;

	CVertexShader* VertShader;
	CPixelShader* PixShader;

	CViewport* ViewPort;

	CBuffer * p_BoneBuffer;

};


class CPase
{
public:
	CPase() {};
	PASSE_DIRECTX_STRUCT m_PaseDirectx;
	//PASSE_OPENGL_STRUCT m_PaseOpenGL;

	//CBuffer * m_pCBB;

	int initDX(PASSE_DIRECTX_STRUCT& _C_Pase_DESC);


	void detroy();
	void render();

	void PaseDirectX(PASSE_DIRECTX_STRUCT& Struc, ID3D11DeviceContext& DevCon);

	void Render(CTargetView& _pRenderTargetView, CDepthStencilView& _pDepthStencilView, CDeviceContext * DevCont, CSceneManager& ScMana, CCamera * CAM, CBuffer * Light);
};

