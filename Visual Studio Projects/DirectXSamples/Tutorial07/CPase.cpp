#include "CPase.h"

int CPase::initDX(PASSE_DIRECTX_STRUCT & _C_Pase_DESC)
{
#if defined(D3D11)

	m_PaseDirectx.IntLay= _C_Pase_DESC.IntLay;
	m_PaseDirectx.VertShader= _C_Pase_DESC.VertShader;
	m_PaseDirectx.PixShader= _C_Pase_DESC.PixShader;
	m_PaseDirectx.ViewPort = _C_Pase_DESC.ViewPort;
	m_PaseDirectx.p_BoneBuffer = _C_Pase_DESC.p_BoneBuffer;
	
#else 

#endif
	return 0;
}


void CPase::detroy()
{
}

void CPase::render()
{
}

void CPase::PaseDirectX(PASSE_DIRECTX_STRUCT& Struc, ID3D11DeviceContext& DevCon)
{
	//// shaders
	//{
	//	// vertex
	//	DevCon.IASetInputLayout(Struc.IntLay->g_pVertexLayout);
	//	//g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
	//	//g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
	//	DevCon.VSSetShader(Struc.VertShader.g_pVertexShader, NULL, 0);

	//	// fragment
	//	DevCon.PSSetShader(Struc.PixShader.g_pPixelShader, NULL, 0);
	//	//g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
	//}

	//// render target
	//{
	//	//render target 2
	//	DevCon.OMSetRenderTargets(1, &Struc.RenTarget2.g_pRenderTargetView, Struc.DepStenView.g_pDepthStencilView);

	//	//render target 1
	//	DevCon.OMSetRenderTargets(1, &Struc.RenTarget.g_pRenderTargetView, Struc.DepStenView.g_pDepthStencilView);
	//	//g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);
	//}

	//// constant buffers
	//{
	//	//segunda camara
	//	DevCon.VSSetConstantBuffers(0, 1, &Struc.PaseSecondCamera->g_pCBNeverChanges.P_Buffer);
	//	DevCon.VSSetConstantBuffers(1, 1, &Struc.PaseSecondCamera->g_pCBChangeOnResize.P_Buffer);
	//	DevCon.VSSetConstantBuffers(2, 1, &Struc.PaseSecondCamera->g_pCBChangesEveryFrame.P_Buffer);

	//	DevCon.PSSetConstantBuffers(2, 1, &Struc.PaseSecondCamera->g_pCBChangesEveryFrame.P_Buffer);
	//	DevCon.PSSetConstantBuffers(3, 1, &Struc.PasseLightDir.P_Buffer);

	//	//first camera
	//	DevCon.VSSetConstantBuffers(0, 1, &Struc.PaseMainCamera->g_pCBNeverChanges.P_Buffer);
	//	DevCon.VSSetConstantBuffers(1, 1, &Struc.PaseMainCamera->g_pCBChangeOnResize.P_Buffer);
	//	DevCon.VSSetConstantBuffers(2, 1, &Struc.PaseMainCamera->g_pCBChangesEveryFrame.P_Buffer);

	//	DevCon.PSSetConstantBuffers(2, 1, &Struc.PaseMainCamera->g_pCBChangesEveryFrame.P_Buffer);
	//	DevCon.PSSetConstantBuffers(3, 1, &Struc.PasseLightDir.P_Buffer);

	//	/*g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	//	g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	//	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
	//	g_pImmediateContext->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);*/
	//}

	//// misc config
	//{
	//	// viewport
	//	DevCon.RSSetViewports(1, &Struc.PasseViewPort.data);
	//	//g_pImmediateContext->RSSetViewports(1, &g_vp);

	//	// clear RT2
	//	DevCon.ClearRenderTargetView(Struc.RenTarget2.g_pRenderTargetView, Struc.ClearColor);
	//	DevCon.ClearDepthStencilView(Struc.DepStenView.g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//
	//	// clear RT1
	//	DevCon.ClearRenderTargetView(Struc.RenTarget.g_pRenderTargetView, Struc.ClearColor);
	//	DevCon.ClearDepthStencilView(Struc.DepStenView.g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//	/*g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
	//	g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);*/// si lleva o no depth

	//	// sampler
	//	DevCon.PSSetSamplers(0, 1, &Struc.PasseSampleState.g_pSamplerLinear);// que sampler usas desde desc
	//}

	//// al final de render en el pase!!!!!
	////for (int i = 0; i < mesh.lenhgt; i++)
	//{
	//	// mesh
	//	{
	//		// Set vertex buffer
	//		UINT stride = sizeof(SimpleVertex);
	//		UINT offset = 0;
	//		DevCon.IASetVertexBuffers(0, 1, &Struc.PasseVertexBuffer->BVertex.P_Buffer, &stride, &offset);
	//		//g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	//		// index buffer
	//		DevCon.IASetIndexBuffer(Struc.PasseIndexBuffer.BIndex.P_Buffer, DXGI_FORMAT_R16_UINT, 0);
	//		//g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//		// Set primitive topology
	//		DevCon.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//		//g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//		// material
	//		DevCon.PSSetShaderResources(0, 1, &Struc.PasseShaderResource.G_PTextureRV);
	//		//g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);

	//		DevCon.DrawIndexed(36, 0, 0);
	//		//g_pImmediateContext->DrawIndexed(36, 0, 0);// ESTO HACE QUE TODO FUNCIONE A COMO LO SETEASTE!!!!!

	//	}
	//}
}

void CPase::Render(CTargetView& _pRenderTargetView, CDepthStencilView& _pDepthStencilView, CDeviceContext * DevCont, CSceneManager& ScMana, CCamera * CAM, CBuffer * Light)
{
	// render target
	{
		DevCont->g_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView.g_pRenderTargetView, _pDepthStencilView.g_pDepthStencilView);
	}

	// shaders
	{
		// vertex
		DevCont->g_pImmediateContext->IASetInputLayout(m_PaseDirectx.IntLay->g_pVertexLayout);
		DevCont->g_pImmediateContext->VSSetShader(m_PaseDirectx.VertShader->g_pVertexShader, NULL, 0);

		// fragment
		DevCont->g_pImmediateContext->PSSetShader(m_PaseDirectx.PixShader->g_pPixelShader, NULL, 0);
		
	}

	// misc config
	{
		// viewport
		DevCont->g_pImmediateContext->RSSetViewports(1, &m_PaseDirectx.ViewPort->data);
	}

	DevCont->g_pImmediateContext->VSSetConstantBuffers(0, 1, &CAM->g_pCBNeverChanges.P_Buffer);
	DevCont->g_pImmediateContext->VSSetConstantBuffers(1, 1, &CAM->g_pCBChangeOnResize.P_Buffer);
	DevCont->g_pImmediateContext->VSSetConstantBuffers(4, 1, &m_PaseDirectx.p_BoneBuffer->P_Buffer);


	// al final de render en el pase!!!!!
	for (int i = 0; i < ScMana.m_MeshInScene.size(); i++)
	{

		// constant buffers
		{
			DevCont->g_pImmediateContext->VSSetConstantBuffers(2, 1, &CAM->g_pCBChangesEveryFrame.P_Buffer);

			DevCont->g_pImmediateContext->PSSetConstantBuffers(2, 1, &CAM->g_pCBChangesEveryFrame.P_Buffer);

			DevCont->g_pImmediateContext->PSSetConstantBuffers(3, 1, &Light->P_Buffer);

			
		}

		// mesh
		{
			// Set vertex buffer
			UINT stride = sizeof(SimpleVertex);
			UINT offset = 0;
			DevCont->g_pImmediateContext->IASetVertexBuffers(0, 1, &ScMana.m_MeshInScene[i]->m_VertexBuffer->P_Buffer, &stride, &offset);

			// index buffer
			DevCont->g_pImmediateContext->IASetIndexBuffer(ScMana.m_MeshInScene[i]->m_Index->P_Buffer, DXGI_FORMAT_R16_UINT, 0);

			// Set primitive topology
			DevCont->g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// material

			DevCont->g_pImmediateContext->PSSetShaderResources(0, 1, &ScMana.m_MeshInScene[i]->m_Materials->m_TexDif);

			DevCont->g_pImmediateContext->DrawIndexed(ScMana.m_MeshInScene[i]->GetIndexNum(), 0, 0);
		}
	}
}


