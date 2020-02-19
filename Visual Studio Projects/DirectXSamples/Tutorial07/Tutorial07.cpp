//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#include "CCamera.h"
#include "CCamFirst.h"
#include <fstream>
#include <iostream>
#include "CDevice.h"
#include "CDeviceContext.h"
#include "CSwapChain.h"
#include "CVertexBuffer.h"
#include "CBuffer.h"
#include "CTargetView.h"
#include "CRenderTarget.h"
#include "CDepthStencil.h"
#include "CDepthStencilVoew.h"
#include "CSampleState.h"
#include "CViewport.h"
#include "CVertexShader.h"
#include "CInputLayer.h"
#include "CPixelShader.h"
CDevice *CDevice::DeviceInstance = NULL;
CDeviceContext* CDeviceContext::DeviceInstanceCo = NULL;
CSwapChain* CSwapChain::SwapChainInstance = NULL;
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

struct CBNeverChanges
{
	glm::mat4x4 mView;
    //XMMATRIX mView;
};

struct CBChangeOnResize
{
	glm::mat4x4 mProjection;
   // XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
	glm::mat4x4 mWorld;
    XMFLOAT4 vMeshColor;
};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
//ID3D11Device*                       g_pd3dDevice = NULL;
CDevice*							DeviceChido = CDevice::getInstance();
//ID3D11DeviceContext*                g_pImmediateContext = NULL;
CDeviceContext*						DeviceContextChido = CDeviceContext::getInstance();
//IDXGISwapChain*                     g_pSwapChain = NULL;
CSwapChain*							SwapChainChido = CSwapChain::getInstance();
//ID3D11RenderTargetView*             g_pRenderTargetView = NULL;
CTargetView							G_PRenderTargetView;
CDepthStencil						G_PDepthStencil;
//ID3D11Texture2D*                    g_pDepthStencil = NULL;
CDepthStencilView					G_PDepthStencilView;

//ID3D11DepthStencilView*             g_pDepthStencilView = NULL;
CVertexShader						G_PVertexShader;
//ID3D11VertexShader*                 g_pVertexShader = NULL;
CPixelShader						G_PPixelShader;
//ID3D11PixelShader*                  g_pPixelShader = NULL;
CInputLayer*						G_PInputLayer = new CInputLayer();
//ID3D11InputLayout*                  g_pVertexLayout = NULL;
CVertexBuffer*						g_VertexBuffer = new CVertexBuffer();
//ID3D11Buffer*                       g_pVertexBuffer = NULL;
ID3D11Buffer*                       g_pIndexBuffer = NULL;
ID3D11Buffer*                       g_pCBNeverChanges = NULL;
ID3D11Buffer*                       g_pCBChangeOnResize = NULL;
ID3D11Buffer*                       g_pCBNeverChangesGOD = NULL;
ID3D11Buffer*                       g_pCBChangeOnResizeGOD = NULL;
ID3D11Buffer*                       CURRENTNEVERCHANGE = NULL;
ID3D11Buffer*                       CURRENTCHANGEONRESIZE = NULL;
ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
//ID3D11SamplerState*                 g_pSamplerLinear = NULL;
glm::mat4x4                            g_World;
glm::mat4x4                            g_View;
glm::mat4x4                            g_Projection;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );
CCamera CAM;
CCamera * other = new CCamFirst();
CCamera GODCAM;
CBuffer Buf;
CRenderTarget BackBuffer;
CSampleState SampleState;
CViewport ViewPort;

int WholeLevel[10][10] = { 0 };
int Rows = 0;
int Columns = 0;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();


enum VariablesParaElMapa
{
	Paredes = 1,
	Vacio = 2,
	Enemigos = 3,
	Pilares = 4,
	NotColideWalls = 5

};

void Laberinto(std::string FileLevelName)
{
	std::ifstream MapFile;
	MapFile.open(FileLevelName);

	MapFile >> Columns >> Rows;

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			MapFile >> WholeLevel[i][j];
		}
	}

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			std::cout << WholeLevel[i][j] << " ";
		}
		std::cout << std::endl;
	}
	MapFile.close();
}


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            Render();
        }
    }

    CleanupDevice();
	Laberinto("Laberinto.txt");
    return ( int )msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( L"TutorialWindowClass", L"Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );
    if( !g_hWnd )
        return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );
	Laberinto("Laberinto.txt");
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( g_hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	C_DEVICE_DESC DC;
	DC.createDeviceFlags = 2;
	DC.DriverTypeDe =(DRIVER_TYPE) D3D_DRIVER_TYPE_NULL;
	DC.numFeatureLevels = 3;
	DeviceChido->init(DC);
	
	C_SWAP_CHAIN_DESC SD;
	SD.BufferCount = 1;
	SD.Width = width;
	SD.Height = height;
	SD.Numerator = 60;
	SD.Denominator = 1;
	SD.OutputWindow = g_hWnd;
	SD.Count = 1;
	SD.Quality = 0;
	SD.Windowed = TRUE;
	
	SwapChainChido->init(SD);

    /*DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;*/

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        DeviceChido->m_DeviceDesc.DriverTypeDe = (DRIVER_TYPE)driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE) DeviceChido->m_DeviceDesc.DriverTypeDe, NULL, DeviceChido->m_DeviceDesc.createDeviceFlags, featureLevels, DeviceChido->m_DeviceDesc.numFeatureLevels,
			D3D11_SDK_VERSION, &SwapChainChido->GetSD(), &SwapChainChido->g_pSwapChain, &DeviceChido->g_pd3dDevice, &g_featureLevel, &DeviceContextChido->g_pImmediateContext);
        /*hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext );*/
        if( SUCCEEDED( hr ) )
            break;
    }
    if( FAILED( hr ) )
        return hr;

    // Create a render target view
	
    //ID3D11Texture2D* pBackBuffer = NULL;
	hr = SwapChainChido->g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer.pBackBuffer);
   /* hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );*/
    if( FAILED( hr ) )
        return hr;

	hr = DeviceChido->g_pd3dDevice->CreateRenderTargetView(BackBuffer.pBackBuffer, NULL, &G_PRenderTargetView.g_pRenderTargetView);
	
    /*hr = g_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );*/
	BackBuffer.pBackBuffer->Release();
   /* pBackBuffer->Release();*/
    if( FAILED( hr ) )
        return hr;

    // Create depth stencil texture
	C_DepthStencil_DESC  DSD;
	DSD.Width = width;
	DSD.Height = height;
	DSD.MipLevels = 1;
	DSD.ArraySize = 1;
	DSD.Format =(FORMAT) DXGI_FORMAT_D24_UNORM_S8_UINT;
	DSD.SampleDesc.Count = 1;
	DSD.SampleDesc.Quality = 0;
	DSD.Usage =(C_USAGE) D3D11_USAGE_DEFAULT;
	DSD.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DSD.CPUAccessFlags = 0;
	DSD.MiscFlags = 0;

	G_PDepthStencil.init(DSD);
 /*   D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory( &descDepth, sizeof(descDepth) );
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;*/
	hr = DeviceChido->g_pd3dDevice->CreateTexture2D(&G_PDepthStencil.descDepth, NULL, &G_PDepthStencil.g_pDepthStencil);
    /*hr = g_pd3dDevice->CreateTexture2D( &descDepth, NULL, &g_pDepthStencil );*/
    if( FAILED( hr ) )
        return hr;

    // Create the depth stencil view
	C_DepthStencilView_DESC DSVD;
	DSVD.Format = (FORMAT)G_PDepthStencil.descDepth.Format;
	DSVD.ViewDimension =(DSV_DIMENSION) D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVD.MipSlice = 0;

	G_PDepthStencilView.init(DSVD);

    /*D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory( &descDSV, sizeof(descDSV) );
    descDSV.Format = G_PDepthStencil->m_DepthStencil.descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;*/

	hr = DeviceChido->g_pd3dDevice->CreateDepthStencilView(G_PDepthStencil.g_pDepthStencil, &G_PDepthStencilView.descDSV, &G_PDepthStencilView.g_pDepthStencilView);
   /* hr = g_pd3dDevice->CreateDepthStencilView( g_pDepthStencil, &descDSV, &g_pDepthStencilView );*/
    if( FAILED( hr ) )
        return hr;
	DeviceContextChido->g_pImmediateContext->OMSetRenderTargets(1, &G_PRenderTargetView.g_pRenderTargetView, G_PDepthStencilView.g_pDepthStencilView);
	
   /* g_pImmediateContext->OMSetRenderTargets( 1, &g_pRenderTargetView, g_pDepthStencilView );*/

    // Setup the viewport
	C_Viewport_DESC VPD;
	VPD.Width = (FLOAT)width;
	VPD.Height = (FLOAT)height;
	VPD.MinDepth = 0.0f;
	VPD.MaxDepth = 1.0f;
	VPD.TopLeftX = 0;
	VPD.TopLeftY = 0;

	ViewPort.init(VPD);

  /*  D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;*/
	DeviceContextChido->g_pImmediateContext->RSSetViewports(1, &ViewPort.data);
    /*g_pImmediateContext->RSSetViewports( 1, &vp );*/

    // Compile the vertex shader
	
    //ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile( L"Tutorial07.fx", "VS", "vs_4_0", &G_PVertexShader.pVSBlob);
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

    // Create the vertex shader
	hr = DeviceChido->g_pd3dDevice->CreateVertexShader(G_PVertexShader.pVSBlob->GetBufferPointer(), G_PVertexShader.pVSBlob->GetBufferSize(), NULL, &G_PVertexShader.g_pVertexShader);
    /*hr = g_pd3dDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );*/
    if( FAILED( hr ) )
    {    
		G_PVertexShader.pVSBlob->Release();
        return hr;
    }

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	
    UINT numElements = ARRAYSIZE( layout );

	

    // Create the input layout
	hr = DeviceChido->g_pd3dDevice->CreateInputLayout(layout, numElements, G_PVertexShader.pVSBlob->GetBufferPointer(),
		G_PVertexShader.pVSBlob->GetBufferSize(), &G_PInputLayer->g_pVertexLayout);
  /*  hr = g_pd3dDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
                                          pVSBlob->GetBufferSize(), &g_pVertexLayout );*/
	G_PVertexShader.pVSBlob->Release();
    if( FAILED( hr ) )
        return hr;

    // Set the input layout
	DeviceContextChido->g_pImmediateContext->IASetInputLayout(G_PInputLayer->g_pVertexLayout);
   /* g_pImmediateContext->IASetInputLayout( g_pVertexLayout );*/

    // Compile the pixel shader
    //ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile( L"Tutorial07.fx", "PS", "ps_4_0", &G_PPixelShader.pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

    // Create the pixel shader
	hr = DeviceChido->g_pd3dDevice->CreatePixelShader(G_PPixelShader.pPSBlob->GetBufferPointer(), G_PPixelShader.pPSBlob->GetBufferSize(), NULL, &G_PPixelShader.g_pPixelShader);
    /*hr = g_pd3dDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );*/
	G_PPixelShader.pPSBlob->Release();
    if( FAILED( hr ) )
        return hr;

    // Create vertex buffer
    SimpleVertex vertices[] =
    {
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
    };

	C_Buffer_DESC BD;
	BD.Usage = C_USAGE::C_USAGE_DEFAULT;
	BD.ByteWidth = sizeof(SimpleVertex) * 24;
	BD.BindFlags= D3D11_BIND_VERTEX_BUFFER;
	BD.CPUAccessFlags = 0;

	Buf.init(BD);

    /*D3D11_BUFFER_DESC bd;
    ZeroMemory( &bd, sizeof(bd) );
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( SimpleVertex ) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;*/

	C_Vertex_Buffer_DESC INITDATA;
	INITDATA.pSystem = vertices;
	g_VertexBuffer->init(INITDATA);

   /* D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory( &InitData, sizeof(InitData) );
    InitData.pSysMem = vertices;*/

	hr = DeviceChido->g_pd3dDevice->CreateBuffer(&Buf.bd, &g_VertexBuffer->InitData, &g_VertexBuffer->g_pVertexBuffer);
   /* hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pVertexBuffer );*/
    if( FAILED( hr ) )
        return hr;

    // Set vertex buffer
    UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;
	DeviceContextChido->g_pImmediateContext->IASetVertexBuffers(0, 1, &g_VertexBuffer->g_pVertexBuffer, &stride, &offset);
   /* g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );*/

    // Create index buffer
    // Create vertex buffer
    WORD indices[] =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };

	BD.Usage = C_USAGE::C_USAGE_DEFAULT;
	BD.ByteWidth = sizeof(WORD) * 36;
	BD.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BD.CPUAccessFlags = 0;

	Buf.init(BD);
    /*bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( WORD ) * 36;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;*/
	INITDATA.pSystem = indices;
	g_VertexBuffer->init(INITDATA);
    //InitData.pSysMem = indices;
	hr = DeviceChido->g_pd3dDevice->CreateBuffer(&Buf.bd, &g_VertexBuffer->InitData, &g_pIndexBuffer);
  /*  hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pIndexBuffer );*/
    if( FAILED( hr ) )
        return hr;

    // Set index buffer
	DeviceContextChido->g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
   /* g_pImmediateContext->IASetIndexBuffer( g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );*/

    // Set primitive topology
	DeviceContextChido->g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    /*g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );*/

    // Create the constant buffers
	BD.Usage = C_USAGE::C_USAGE_DEFAULT;
	BD.ByteWidth = sizeof(CBNeverChanges);
	BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BD.CPUAccessFlags = 0;

	Buf.init(BD);
    /*bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(CBNeverChanges);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;*/
	hr = DeviceChido->g_pd3dDevice->CreateBuffer(&Buf.bd, NULL, &g_pCBNeverChanges);
   /* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBNeverChanges );*/
    if( FAILED( hr ) )
        return hr;
	hr = DeviceChido->g_pd3dDevice->CreateBuffer(&Buf.bd, NULL, &g_pCBNeverChangesGOD);
    /*hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBNeverChangesGOD );*/
    if( FAILED( hr ) )
        return hr;
    BD.Usage = C_USAGE::C_USAGE_DEFAULT;
	BD.ByteWidth = sizeof(CBChangeOnResize);
	BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BD.CPUAccessFlags = 0;

	Buf.init(BD);
    //bd.ByteWidth = sizeof(CBChangeOnResize);
	hr = DeviceChido->g_pd3dDevice->CreateBuffer(&Buf.bd, NULL, &g_pCBChangeOnResize);
   /* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangeOnResize );*/
    if( FAILED( hr ) )
        return hr;
	hr = DeviceChido->g_pd3dDevice->CreateBuffer(&Buf.bd, NULL, &g_pCBChangeOnResizeGOD);
   /* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangeOnResizeGOD );*/
    if( FAILED( hr ) )
        return hr;
	BD.Usage = C_USAGE::C_USAGE_DEFAULT;
	BD.ByteWidth = sizeof(CBChangesEveryFrame);
	BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BD.CPUAccessFlags = 0;

	Buf.init(BD);
    //bd.ByteWidth = sizeof(CBChangesEveryFrame);
	hr = DeviceChido->g_pd3dDevice->CreateBuffer(&Buf.bd, NULL, &g_pCBChangesEveryFrame);
   /* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangesEveryFrame );*/
    if( FAILED( hr ) )
        return hr;

    // Load the Texture
	hr = D3DX11CreateShaderResourceViewFromFile(DeviceChido->g_pd3dDevice, L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL);
    /*hr = D3DX11CreateShaderResourceViewFromFile( g_pd3dDevice, L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL );*/
    if( FAILED( hr ) )
        return hr;

    // Create the sample state
	C_SampleState_DESC STD;
	STD.Filter =(FILTER)D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	STD.AddressU =(TEXTURE_ADDRESS_MODE) D3D11_TEXTURE_ADDRESS_WRAP;
	STD.AddressV = (TEXTURE_ADDRESS_MODE)D3D11_TEXTURE_ADDRESS_WRAP;
	STD.AddressW = (TEXTURE_ADDRESS_MODE)D3D11_TEXTURE_ADDRESS_WRAP;
	STD.ComparisonFunc =(COMPARISON_FUNC) D3D11_COMPARISON_NEVER;
	STD.MinLOD = 0;
	STD.MaxLOD = D3D11_FLOAT32_MAX;

	SampleState.init(STD);
    /*D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;*/

	hr = DeviceChido->g_pd3dDevice->CreateSamplerState(&SampleState.sampDesc, &SampleState.g_pSamplerLinear);
    /*hr = g_pd3dDevice->CreateSamplerState( &sampDesc, &g_pSamplerLinear );*/
    if( FAILED( hr ) )
        return hr;

    // Initialize the world matrices
	g_World = glm::mat4(1.0f);
		//XMMatrixIdentity();

    // Initialize the view matrix
	glm::vec3 Eye = { 0.0f, 1.0f, -6.0f };
	glm::vec3 At = { 0.0f, 1.0f, 0.0f };
	glm::vec3 Up = { 0.0f, 1.0f, 0.0f };
   /* XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );*/

	CCameraDatas D;
	
	D.Posicion=Eye;
	D.At=At;
	D.Up=Up; //referencia al mundo
	D.W=width;
	D.H=height;
	D.Near=0.1f;
	D.Far=1000;
	D.Fov= XM_PIDIV4;
	
	CAM.Init(D);

	Eye = { 0.0f, 20.0f, -6.0f };
	At = { 0.0f, -1.0f, 0.0f };
	Up = { 0.0f, 0.0f, 1.0f };
	D.Posicion = Eye;
	D.At = At;
	D.Up = Up;

	GODCAM.Init(D);

    //g_View = XMMatrixLookAtLH( Eye, At, Up );

    CBNeverChanges cbNeverChanges;
	cbNeverChanges.mView = CAM.GetView();//XMMatrixTranspose( g_View );
	DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);
    /*g_pImmediateContext->UpdateSubresource( g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );*/
	CURRENTNEVERCHANGE = g_pCBNeverChanges;
    // Initialize the projection matrix
	g_Projection = CAM.GetProyeccion(); //XMMatrixPerspectiveFovLH( XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f );
    
    CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = CAM.GetProyeccion();//XMMatrixTranspose( g_Projection );
	DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);
    /*g_pImmediateContext->UpdateSubresource( g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );*/

	CURRENTCHANGEONRESIZE = g_pCBChangeOnResize;
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (DeviceContextChido->g_pImmediateContext) DeviceContextChido->g_pImmediateContext->ClearState();
   /* if( g_pImmediateContext ) g_pImmediateContext->ClearState();*/

	if (SampleState.g_pSamplerLinear) SampleState.g_pSamplerLinear->Release();
    /*if( g_pSamplerLinear ) g_pSamplerLinear->Release();*/
    if( g_pTextureRV ) g_pTextureRV->Release();
    if( g_pCBNeverChanges ) g_pCBNeverChanges->Release();
    if( g_pCBChangeOnResize ) g_pCBChangeOnResize->Release();
    if( g_pCBChangesEveryFrame ) g_pCBChangesEveryFrame->Release();
	
	if (g_VertexBuffer->g_pVertexBuffer) g_VertexBuffer->g_pVertexBuffer->Release();
   /* if( g_pVertexBuffer ) g_pVertexBuffer->Release();*/
    if( g_pIndexBuffer ) g_pIndexBuffer->Release();
	
		if (G_PInputLayer->g_pVertexLayout) G_PInputLayer->g_pVertexLayout->Release();
  /*  if( g_pVertexLayout ) g_pVertexLayout->Release();*/
	if (G_PVertexShader.g_pVertexShader) G_PVertexShader.g_pVertexShader->Release();
    /*if( g_pVertexShader ) g_pVertexShader->Release();*/
	if (G_PPixelShader.g_pPixelShader) G_PPixelShader.g_pPixelShader->Release();
   /* if( g_pPixelShader ) g_pPixelShader->Release();*/
	
	if (G_PDepthStencil.g_pDepthStencil) G_PDepthStencil.g_pDepthStencil->Release();
   /* if( g_pDepthStencil ) g_pDepthStencil->Release();*/
	
	if (G_PDepthStencilView.g_pDepthStencilView) G_PDepthStencilView.g_pDepthStencilView->Release();
   /* if( g_pDepthStencilView ) g_pDepthStencilView->Release();*/
	
	if (G_PRenderTargetView.g_pRenderTargetView) G_PRenderTargetView.g_pRenderTargetView->Release();
    /*if( g_pRenderTargetView ) g_pRenderTargetView->Release();*/
	
	
	if (SwapChainChido->g_pSwapChain) SwapChainChido->g_pSwapChain->Release();
   /* if( g_pSwapChain ) g_pSwapChain->Release();*/
	
	if (DeviceContextChido->g_pImmediateContext) DeviceContextChido->g_pImmediateContext->Release();
    /*if( g_pImmediateContext ) g_pImmediateContext->Release();*/
	if (DeviceChido->g_pd3dDevice) DeviceChido->g_pd3dDevice->Release();
    /*if( g_pd3dDevice ) g_pd3dDevice->Release();*/
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;
		case WM_SIZING:
		{
			RECT rc;
			GetClientRect(g_hWnd, &rc);
			UINT width = rc.right - rc.left;
			UINT height = rc.bottom - rc.top;
			g_World = glm::mat4(1.0f);
			CAM.setHeight(height);
			CAM.setWeight(width);
			CAM.UpdateProyeccion();
			CBChangeOnResize cbChangesOnResize;
			cbChangesOnResize.mProjection = CAM.GetProyeccion();//XMMatrixTranspose( g_Projection );
			DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);
			/*g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);*/
			if (SwapChainChido->g_pSwapChain)
			{
				DeviceContextChido->g_pImmediateContext->OMSetRenderTargets(0, 0, 0);
				//g_pd3dDeviceContext->OMSetRenderTargets(0, 0, 0);

				// Release all outstanding references to the swap chain's buffers.
				G_PRenderTargetView.g_pRenderTargetView->Release();
				//g_pRenderTargetView->Release();

				HRESULT hr;
				// Preserve the existing buffer count and format.
				// Automatically choose the width and height to match the client rect for HWNDs.
				hr = SwapChainChido->g_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
				//hr = g_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

				// Perform error handling here!

				// Get buffer and create a render-target-view.
				ID3D11Texture2D* pBuffer;
				hr=SwapChainChido->g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
					(void**)&pBuffer);
				/*hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
					(void**)&pBuffer);*/
				// Perform error handling here!
				hr= DeviceChido->g_pd3dDevice->CreateRenderTargetView(pBuffer, NULL,
					&G_PRenderTargetView.g_pRenderTargetView);
				/*hr = g_pd3dDevice->CreateRenderTargetView(pBuffer, NULL,
					&g_pRenderTargetView);*/
				// Perform error handling here!
				pBuffer->Release();
				DeviceContextChido->g_pImmediateContext->OMSetRenderTargets(1, &G_PRenderTargetView.g_pRenderTargetView, NULL);
				//g_pd3dDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

				// Set up the viewport.
				C_Viewport_DESC VPD;
				VPD.Width = (FLOAT)width;
				VPD.Height = (FLOAT)height;
				VPD.MinDepth = 0.0f;
				VPD.MaxDepth = 1.0f;
				VPD.TopLeftX = 0;
				VPD.TopLeftY = 0;

				ViewPort.init(VPD);
				/*D3D11_VIEWPORT vp;
				vp.Width = width;
				vp.Height = height;
				vp.MinDepth = 0.0f;
				vp.MaxDepth = 1.0f;
				vp.TopLeftX = 0;
				vp.TopLeftY = 0;*/
				DeviceContextChido->g_pImmediateContext->RSSetViewports(1, &ViewPort.data);
				//g_pd3dDeviceContext->RSSetViewports(1, &vp);
			}
		}

		case WM_KEYDOWN:
		{
			if ((wParam == 'g' || wParam == 'G') && GODCAM.GodC == false)
			{
				//if ()
				//{
				
					GODCAM.GodC = true;
					CBNeverChanges cbNeverChanges;
					cbNeverChanges.mView = GODCAM.GetView();//XMMatrixTranspose( g_View );
					DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBNeverChangesGOD, 0, NULL, &cbNeverChanges, 0, 0);
					/*g_pImmediateContext->UpdateSubresource(g_pCBNeverChangesGOD, 0, NULL, &cbNeverChanges, 0, 0);*/
					CURRENTNEVERCHANGE = g_pCBNeverChangesGOD;

					// Initialize the projection matrix
					g_Projection = GODCAM.GetProyeccion(); //XMMatrixPerspectiveFovLH( XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f );

					CBChangeOnResize cbChangesOnResize;
					cbChangesOnResize.mProjection = GODCAM.GetProyeccion();//XMMatrixTranspose( g_Projection );
					DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResizeGOD, 0, NULL, &cbChangesOnResize, 0, 0);
					/*g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResizeGOD, 0, NULL, &cbChangesOnResize, 0, 0);*/

					CURRENTCHANGEONRESIZE = g_pCBChangeOnResizeGOD;
				//}
				
				/*else if (GODCAM.GodC == true)
				{
					GODCAM.GodC = false;
				}*/

			}
			else if ((wParam == 'g' || wParam == 'G') && GODCAM.GodC == true)
			//else //if (GODCAM.GodC == false)
			{
				GODCAM.GodC = false;
				CAM.Input(wParam);
				CBNeverChanges cbNeverChanges;
				cbNeverChanges.mView = CAM.GetView(); //XMMatrixTranspose( g_View );
				DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);
				/*g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/
				CURRENTNEVERCHANGE = g_pCBNeverChanges;
				CURRENTCHANGEONRESIZE = g_pCBChangeOnResize;

			}
			if (GODCAM.GodC == true)
			{

				GODCAM.Input(wParam);
				CBNeverChanges cbNeverChanges;
				cbNeverChanges.mView = GODCAM.GetView();//XMMatrixTranspose( g_View );
				DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);
				/*g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/
				CURRENTNEVERCHANGE = g_pCBNeverChanges;
				CURRENTCHANGEONRESIZE = g_pCBChangeOnResize;
			}
			if (GODCAM.GodC == false)
			{
				CAM.Input(wParam);
				CBNeverChanges cbNeverChanges;
				cbNeverChanges.mView = CAM.GetView(); //XMMatrixTranspose( g_View );
				DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);
				/*g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/
				CURRENTNEVERCHANGE = g_pCBNeverChanges;
				CURRENTCHANGEONRESIZE = g_pCBChangeOnResize;
			}
		
			break;
		}
		case WM_LBUTTONDOWN:
		{
			if (GODCAM.GodC == false)
			{
				POINT Mouse;
				GetCursorPos(&Mouse);
				CAM.PosIn = { float(Mouse.x),float(Mouse.y),0 };
				CAM.Fpres = true;
			}
			else if (GODCAM.GodC == true)
			{
				POINT Mouse;
				GetCursorPos(&Mouse);
				GODCAM.PosIn = { float(Mouse.x),float(Mouse.y),0 };
				GODCAM.Fpres = true;
			}
			
			break;
		}
		case WM_MOUSEMOVE:
		{
			if (GODCAM.GodC == false)
			{
				if (CAM.Fpres == true)
				{
					POINT MOUSE;
					GetCursorPos(&MOUSE);
					CAM.PosFn = { float(MOUSE.x),float(MOUSE.y),0 };
					SetCursorPos(CAM.PosIn.x, CAM.PosIn.y);

					CAM.Dir = CAM.PosIn - CAM.PosFn;
					/*float cosine = cosf(CAM.Dir.x);
					float sine = sinf(CAM.Dir.x);*/
					CAM.MoveMouse(CAM.Dir);
					CBNeverChanges cbNeverChanges;
					cbNeverChanges.mView = CAM.GetView();//XMMatrixTranspose( g_View );
					DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);
					/*g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/

				}
			}
			else if (GODCAM.GodC == true)
			{
				if (GODCAM.Fpres == true)
				{
					POINT MOUSE;
					GetCursorPos(&MOUSE);
					GODCAM.PosFn = { float(MOUSE.x),float(MOUSE.y),0 };
					SetCursorPos(GODCAM.PosIn.x, GODCAM.PosIn.y);

					GODCAM.Dir = GODCAM.PosIn - GODCAM.PosFn;
					/*float cosine = cosf(CAM.Dir.x);
					float sine = sinf(CAM.Dir.x);*/
					GODCAM.MoveMouse(GODCAM.Dir);
					CBNeverChanges cbNeverChanges;
					cbNeverChanges.mView = GODCAM.GetView();//XMMatrixTranspose( g_View );
					DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);
					/*g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/
				}
			}
			
			break;
		}
		case WM_LBUTTONUP:
		{
			if (GODCAM.GodC == false)
			{
				CAM.Fpres = false;
			}
			else if (GODCAM.GodC == true)
			{
				GODCAM.Fpres = false;
			}
		}

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Update our time
    static float t = 0.0f;
    if( DeviceChido->m_DeviceDesc.DriverTypeDe == D3D_DRIVER_TYPE_REFERENCE )
    {
        t += ( float )XM_PI * 0.0125f;
    }
    else
    {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();
        if( dwTimeStart == 0 )
            dwTimeStart = dwTimeCur;
        t = ( dwTimeCur - dwTimeStart ) / 1000.0f;
    }

    // Rotate cube around the origin
    //g_World = XMMatrixRotationY( t );
	glm::vec3 T = { 3, 0, 0 };
	g_World = glm::translate(T);

    // Modify the color
    g_vMeshColor.x = ( sinf( t * 1.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.y = ( cosf( t * 3.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.z = ( sinf( t * 5.0f ) + 1.0f ) * 0.5f;

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	DeviceContextChido->g_pImmediateContext->ClearRenderTargetView(G_PRenderTargetView.g_pRenderTargetView, ClearColor);
	
   /* g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );*/

    //
    // Clear the depth buffer to 1.0 (max depth)
    //
	DeviceContextChido->g_pImmediateContext->ClearDepthStencilView(G_PDepthStencilView.g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    /*g_pImmediateContext->ClearDepthStencilView( g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );*/

    //
    // Update variables that change once per frame
    //
    CBChangesEveryFrame cb;
    cb.mWorld = glm::transpose( g_World );
    cb.vMeshColor = g_vMeshColor;
	DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);
    /*g_pImmediateContext->UpdateSubresource( g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0 );*/

	
    //
    // Render the cube
    //
	DeviceContextChido->g_pImmediateContext->VSSetShader(G_PVertexShader.g_pVertexShader, NULL, 0);
	DeviceContextChido->g_pImmediateContext->VSSetConstantBuffers(0, 1, &CURRENTNEVERCHANGE);
	DeviceContextChido->g_pImmediateContext->VSSetConstantBuffers(1, 1, &CURRENTCHANGEONRESIZE);
	DeviceContextChido->g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	DeviceContextChido->g_pImmediateContext->PSSetShader(G_PPixelShader.g_pPixelShader, NULL, 0);
	DeviceContextChido->g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	DeviceContextChido->g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
	DeviceContextChido->g_pImmediateContext->PSSetSamplers(0, 1, &SampleState.g_pSamplerLinear);
	DeviceContextChido->g_pImmediateContext->DrawIndexed(36, 0, 0);
  /*  g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
    g_pImmediateContext->VSSetConstantBuffers( 0, 1, &CURRENTNEVERCHANGE);
    g_pImmediateContext->VSSetConstantBuffers( 1, 1, &CURRENTCHANGEONRESIZE);
    g_pImmediateContext->VSSetConstantBuffers( 2, 1, &g_pCBChangesEveryFrame );
    g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );
    g_pImmediateContext->PSSetConstantBuffers( 2, 1, &g_pCBChangesEveryFrame );
    g_pImmediateContext->PSSetShaderResources( 0, 1, &g_pTextureRV );
    g_pImmediateContext->PSSetSamplers( 0, 1, &g_pSamplerLinear );
    g_pImmediateContext->DrawIndexed( 36, 0, 0 );*/

	int DistanceX = 0;
	int DistanceY = 0;
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			if (WholeLevel[i][j])
			{

				DistanceX += 2.5;
			}

			else if (WholeLevel[i][j] == Pilares)
			{
				DistanceX += 2.5;
			}
			else
			{
				DistanceX += 2.5;
			}
			if (WholeLevel[i][j] != 0)
			{
				DeviceContextChido->g_pImmediateContext->VSSetShader(G_PVertexShader.g_pVertexShader, NULL, 0);
				DeviceContextChido->g_pImmediateContext->VSSetConstantBuffers(0, 1, &CURRENTNEVERCHANGE);
				DeviceContextChido->g_pImmediateContext->VSSetConstantBuffers(1, 1, &CURRENTCHANGEONRESIZE);
				DeviceContextChido->g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
				DeviceContextChido->g_pImmediateContext->PSSetShader(G_PPixelShader.g_pPixelShader, NULL, 0);
				DeviceContextChido->g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
				DeviceContextChido->g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
				DeviceContextChido->g_pImmediateContext->PSSetSamplers(0, 1, &SampleState.g_pSamplerLinear);
				DeviceContextChido->g_pImmediateContext->DrawIndexed(36, 0, 0);
				/*g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
				g_pImmediateContext->VSSetConstantBuffers(0, 1, &CURRENTNEVERCHANGE);
				g_pImmediateContext->VSSetConstantBuffers(1, 1, &CURRENTCHANGEONRESIZE);
				g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
				g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
				g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
				g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
				g_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
				g_pImmediateContext->DrawIndexed(36, 0, 0);*/
			}
			T = { DistanceX, 0, DistanceY };
			g_World = glm::translate(T);
			cb.mWorld = glm::transpose(g_World);
			cb.vMeshColor = g_vMeshColor;
			DeviceContextChido->g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);
			/*g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);*/
		}
		DistanceY += 2.5;
		DistanceX = 0;
	}
    //
    // Present our back buffer to our front buffer
    //
	
	SwapChainChido->g_pSwapChain->Present(0, 0);
  /*  g_pSwapChain->Present( 0, 0 );*/
}
