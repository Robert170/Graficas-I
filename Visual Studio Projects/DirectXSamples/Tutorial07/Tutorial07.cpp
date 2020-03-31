//*****************************************************************************/
/**
* @File Tutorial07.cpp
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/03/2020
* @brief cuerpo de todo el proyecto
* @Bug No kown bug
**/
//****************************************************************************/

//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#define STB_IMAGE_IMPLEMENTATION

/*! \file includes of .h
	\brief A Documented file.

	this is where include all class who use for the proyect like, device, Camera, Buffer, etc
*/
#include <windows.h>
#include "Define.h"
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
#include "CIndexBuffer.h"
#include "CTexture2D.h"
#include <vector>
#include "CModel.h"
#include "CGraphicApi.h"
#include "CSceneManager.h"
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "ShaderOGL.h"
//#include "stb_image.h"
#include "CameraOGL.h"
#include "ModelOGL.h"
CDevice *CDevice::DeviceInstance = NULL;
CDeviceContext* CDeviceContext::DeviceInstanceCo = NULL;
CSwapChain* CSwapChain::SwapChainInstance = NULL;

//assimp
//#include "assimp/scene.h"
//#include "assimp/cimport.h"
//#include "assimp/postprocess.h"
//#include "assimp/Importer.hpp"
//#include "assimp/material.h"

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------

// !An struct.
/*! struc CBNeverChanges. */
struct CBNeverChanges
{
	/**< struct glm::mat4x4 mView. */
	glm::mat4x4 mView;
    //XMMATRIX mView;
};

// !An struct.
/*! struc CBChangeOnResize. */
struct CBChangeOnResize
{
	/**< struct glm::mat4x4 mProjection. */
	glm::mat4x4 mProjection;

};

//struct CBChangesEveryFrame
//{
//	glm::mat4x4 mWorld;
//	glm::vec4 vMeshColor;
//    //XMFLOAT4 vMeshColor;
//};



//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------

//! A  Global Variables.
	/*!
	  variable, i use this variables in all proyects, someones are for directx and others are for OpenGL.
	*/
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
GLFWwindow*							window;
#if defined(D3D11)
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
#endif
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
CVertexBuffer*						g_VertexBufferMOD = new CVertexBuffer();
//ID3D11Buffer*                       g_pVertexBuffer = NULL;
CIndexBuffer                       g_pIndexBuffer;
CIndexBuffer                       g_pIndexBufferMOD;
//CBuffer							g_pCBNeverChanges;
//CBuffer							g_pCBChangeOnResize;
//CBuffer							 g_pCBNeverChangesGOD;
//CBuffer							g_pCBChangeOnResizeGOD;
//CBuffer							CURRENTNEVERCHANGE;
//CBuffer							CURRENTCHANGEONRESIZE;
//CBuffer							 g_pCBChangesEveryFrame;
CTexture2D                       g_ShaderResource;
//ID3D11ShaderResourceView*           g_pTextureRV = NULL;
//ID3D11SamplerState*                 g_pSamplerLinear = NULL;
glm::mat4x4                            g_World;
glm::mat4x4                            g_View;
glm::mat4x4                            g_Projection;
glm::vec4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );
CCamera CAM;
CCamera * other = new CCamFirst();
CCamera GODCAM;
CRenderTarget BackBuffer;
CSampleState SampleState;
CViewport ViewPort;
CModel Mod;

//variables el segundo render target
CCamera *		MainCamera = NULL;
CCamera *		SecondCamera = NULL;
CTargetView		RenderTargetView2;
CTexture2D		TextureCAMInac;

CGraphicApi GraphicApi;
CSceneManager ScMana;

#if defined(D3D11)
ID3D11Device *ptrDEV = static_cast<ID3D11Device*>(DeviceChido->GetDev());
IDXGISwapChain *ptrSwap = static_cast<IDXGISwapChain*>(SwapChainChido->GetSwap());
ID3D11DeviceContext *ptrDevCont = static_cast<ID3D11DeviceContext*>(DeviceContextChido->GetDevCont());
ID3D11Texture2D *ptrDepht = static_cast<ID3D11Texture2D*>(G_PDepthStencil.GetDepth());
#endif

unsigned int mNumVertices;
unsigned int mNumFaces;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
unsigned int framebuffer;
unsigned int textureColorbuffer;
unsigned int rbo;
glm::vec3 point_pos(2.0f, 2.0f, 0.0f);
glm::vec3 Look;
glm::vec3 Right;
glm::vec3 Up;
glm::mat4x4 BilboardMatrix;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;



//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";


int WholeLevel[10][10] = { 0 };
int Rows = 0;
int Columns = 0;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
int InitDeviceOGL();

void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();

#ifdef GLFW
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
#endif

// !An enum.
/*! enum of VariablesParaElMapa values. */
enum VariablesParaElMapa
{
	/**< enum Paredes. */
	Paredes = 1,

	/**< enum Vacio. */
	Vacio = 2,

	/**< enum Enemigos. */
	Enemigos = 3,

	/**< enum ParPilaresedes. */
	Pilares = 4,

	/**< enum NotColideWalls. */
	NotColideWalls = 5

};

//! A activateConsole function.
	/*!
	  function for activate consele in Directx.
	*/
void activateConsole()
{
	//Create a console for this application
	AllocConsole();
	// Get STDOUT handle
	HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
	FILE* COutputHandle = _fdopen(SystemOutput, "w");

	// Get STDERR handle
	HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
	int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
	FILE* CErrorHandle = _fdopen(SystemError, "w");

	// Get STDIN handle
	HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
	FILE* CInputHandle = _fdopen(SystemInput, "r");

	//make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
	std::ios::sync_with_stdio(true);

	// Redirect the CRT standard input, output, and error handles to the console
	freopen_s(&CInputHandle, "CONIN$", "r", stdin);
	freopen_s(&COutputHandle, "CONOUT$", "w", stdout);
	freopen_s(&CErrorHandle, "CONOUT$", "w", stderr);

	//Clear the error state for each of the C++ standard stream objects. We need to do this, as
	//attempts to access the standard streams before they refer to a valid target will cause the
	//iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
	//to always occur during startup regardless of whether anything has been read from or written to
	//the console or not.
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

}

//! A Laberinto function.
	/*!
	  function for read txt and load laberint of cubes.
	  \param FileLevelName an string.
	*/
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
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#ifdef D3D11

//! A CreateInputLayoutDescFromVertexShaderSignature function.
	/*!
	  function create a autimatic input layaut.
	  \param pShaderBlob an ID3DBlob.
	  \param pD3DDevice an ID3D11Device.
	  \param pInputLayout an strID3D11InputLayouting.
	*/
HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout)
{
	// Reflect shader info
	ID3D11ShaderReflection* pVertexShaderReflection = NULL;
	if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection)))
	{
		return S_FALSE;
	}

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	int offset = 0;
	for (int i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = offset;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; offset += 12;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		//save element desc
		inputLayoutDesc.push_back(elementDesc);
	}

	// Try to create Input Layout
	HRESULT hr = pD3DDevice->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), pInputLayout);

	//Free allocation shader reflection memory
	pVertexShaderReflection->Release();
	return hr;
}
#endif


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------

//! A wWinMain function.
	/*!
	  main Function where the program start and call the rest of the Functions.
	*/
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
	activateConsole();

#ifdef GLFW


	InitDeviceOGL();
	return 0;
	
#endif // GLFW_TRUE

	

	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

	MSG msg = { 0 };


	/* Loop until the user closes the window */


    // Main message loop
    
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
#if defined(D3D11)
			ImVec2 Texture_Size(240, 240);
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Change");



			if (ImGui::Button("Change"))

			{
				CCamera *TEMP = SecondCamera;
				SecondCamera = MainCamera;
				MainCamera = TEMP;
			}
		

			ImGui::End();
			ImGui::Begin("DirectX11 Texture Test");

			ImGui::Image(g_ShaderResource.G_PInactiveRV, Texture_Size);

			ImGui::GetIO().FontGlobalScale;

			ImGui::End();
            Render();
#endif

        }


    }

    CleanupDevice();
	Laberinto("Laberinto.txt");
	return (int)msg.wParam;

}

//! A mouse_button_callback function.
	/*!
	  Function of Opengl for detect mouse input.
	   \param window an GLFWwindow.
	  \param button an int.
	  \param action an int.
	  \param mods an int.
	*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT )
	{
		if (action == GLFW_PRESS)
		{
			double MouseX;
			double MouseY;
			glfwGetCursorPos(window, &MouseX, &MouseY);
			MainCamera->PosIn = { float(MouseX),float(MouseY),0 };
			MainCamera->Fpres = true;
		}

		else if (action == GLFW_RELEASE)
		{
			MainCamera->Fpres = false;
		}
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

//! A mouse_button_callback function.
	/*!
	  Function of Opengl for detect mouse input.
	   \param window an GLFWwindow.
	*/
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
		

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		MainCamera->Move(GLFW_KEY_W);
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		MainCamera->Move(GLFW_KEY_S);
	}
		
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		MainCamera->Move(GLFW_KEY_A);
	}
		
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{

		MainCamera->Move(GLFW_KEY_D);
	}
		
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------

//! A framebuffer_size_callback function.
	/*!
	  Function of Opengl for do the resize of the window.
	   \param window an GLFWwindow.
	   \param width an int.
	   \param height an int.
	*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,width,height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	SecondCamera->setWeight(width);
	SecondCamera->setHeight(height);
	MainCamera->setWeight(width);
	MainCamera->setHeight(height);
	SecondCamera->UpdateProyeccion();
	MainCamera->UpdateProyeccion();
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------

//! A framebuffer_size_callback function.
	/*!
	  Function of Opengl for detect when the mouse is moving.
	   \param window an GLFWwindow.
	   \param xpos an double.
	   \param ypos an double.
	*/
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (MainCamera->Fpres == true)
	{
		/*double MouseX;
		double MouseY;
		glfwGetCursorPos(window, &MouseX, &MouseY);*/
		MainCamera->PosFn = { xpos,ypos,0 };
		glfwSetCursorPos(window, MainCamera->PosIn.x, MainCamera->PosIn.y);
		//SetCursorPos(MainCamera->PosIn.x, MainCamera->PosIn.y);

		MainCamera->Dir = MainCamera->PosIn - MainCamera->PosFn;
		/*float cosine = cosf(CAM.Dir.x);
		float sine = sinf(CAM.Dir.x);*/
		MainCamera->MoveMouse(MainCamera->Dir);
		CBNeverChanges cbNeverChanges;
		cbNeverChanges.mView = MainCamera->GetView();//XMMatrixTranspose( g_View );

	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------

//! A InitWindow function.
	/*!
	  Function for init window of DirectX.
	   \param hInstance an HINSTANCE.
	   \param nCmdShow an int.
	*/
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

	g_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL );



	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);


	Laberinto("Laberinto.txt");
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
#ifdef D3D11
//! A CompileShaderFromFile function.
	/*!
	  Function for compile shader from fileof DirectX.
	   \param szFileName an WCHAR.
	   \param szEntryPoint an LPCSTR.
	   \param szShaderModel an LPCSTR.
	   \param ppBlobOut an ID3DBlob.
	*/
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
#endif

//! A InitDeviceOGL function.
	/*!
	  Function of opengl for init window, create shader, load model, and render.
	*/
int InitDeviceOGL()
{



	// glfw: initialize and configure
   // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyect OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

	// load models
	// -----------


	Model ourModel("Modelo/Scene/Scene.fbx");

	Model ourModel2("Modelo/Scene/Reflect.fbx");


	float Vertices[] = {
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};


	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glm::vec3 Eye = { 0.0f, 1.0f, -6.0f };
	glm::vec3 At = { 0.0f, 1.0f, 0.0f };
	glm::vec3 Up = { 0.0f, 1.0f, 0.0f };

	CCameraDatas D;

	D.Posicion = Eye;
	D.At = At;
	D.Up = Up; //referencia al mundo
	D.W = SCR_WIDTH;
	D.H = SCR_HEIGHT;
	D.Near = 0.1f;
	D.Far = 1000;
	D.Fov = XM_PIDIV4;

	CAM.Init(D);

	Eye = { 0.0f, 20.0f, -6.0f };
	At = { 0.0f, -1.0f, 0.0f };
	Up = { 0.0f, 0.0f, 1.0f };
	D.Posicion = Eye;
	D.At = At;
	D.Up = Up;

	GODCAM.Init(D);


	MainCamera = &CAM;
	SecondCamera = &GODCAM;


	CBNeverChanges cbNeverChanges;
	CBChangeOnResize cbChangesonresize;

	
	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	//mouse
		//----
	glfwSetMouseButtonCallback(window, mouse_button_callback);



	// framebuffer configuration
// -------------------------
	
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// create a color attachment texture
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);


		//seguir a la camara
		Look = glm::normalize(MainCamera->GetPosition() - point_pos);
		Right = glm::cross(glm::normalize(MainCamera->GetUp()), Look);
		Up = glm::cross(Look, Right);

		BilboardMatrix = { Right.x, Right.y,Right.z,0,  Up.x, Up.y,  Up.z, 0, Look.x,  Look.y,Look.z,0,point_pos.x,point_pos.y,point_pos.z,1 };

		
		// render
		// ------
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// feed inputs to dear imgui, start new frame
		ImVec2 Texture_Size(240, 240);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// don't forget to enable shader before setting uniforms
		ourShader.use();

		// view/projection transformations
		
		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 View = glm::transpose(SecondCamera->GetView());
		glm::mat4 Projection = glm::scale(glm::transpose(SecondCamera->GetProyeccion()), glm::vec3(1, -1, 1));


		//glm::mat4 projection = glm::transpose(MainCamera->GetProyeccion()); //glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//glm::mat4 view = glm::transpose(MainCamera->GetView());  //camera.GetViewMatrix();
		ourShader.setMat4("projection", Projection);
		ourShader.setMat4("view", View);
		ourShader.setMat4("model", Model);
		// render the loaded model
		//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		ourModel.Draw(ourShader);
		ourModel2.Draw(ourShader);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		cbChangesonresize.mProjection = glm::transpose(MainCamera->GetProyeccion());
		cbNeverChanges.mView = glm::transpose(MainCamera->GetView());

		ourShader.setMat4("projection", cbChangesonresize.mProjection);
		ourShader.setMat4("view", cbNeverChanges.mView);
		ourShader.setMat4("model", model);
		// render the loaded model
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		ourModel.Draw(ourShader);
		ourModel2.Draw(ourShader);

		glBindVertexArray(VAO);
		model = BilboardMatrix;
		ourShader.setMat4("model", model);

		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// render your GUI
		ImGui::Begin("Change Camera");

		if (ImGui::Button("Change"))

		{
			CCamera *TEMP = SecondCamera;
			SecondCamera = MainCamera;
			MainCamera = TEMP;
		}
		
		ImGui::End();
		ImGui::Begin("OpenGl Texture Test");

		ImGui::Image((void*)textureColorbuffer, Texture_Size);

		ImGui::GetIO().FontGlobalScale;

		ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------

//! A InitDevice function.
	/*!
	  Function of directx for call class of device, load model, shader, etc.
	*/
HRESULT InitDevice()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	unsigned int width = rc.right - rc.left;
	unsigned int height = rc.bottom - rc.top;
#ifdef D3D11
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
	UINT numDriverTypes = ARRAYSIZE(driverTypes);



	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	C_DEVICE_DESC DC;
	DC.createDeviceFlags = 2;
	DC.DriverTypeDe = (DRIVER_TYPE)D3D_DRIVER_TYPE_NULL;
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


	for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		DeviceChido->m_DeviceDesc.DriverTypeDe = (DRIVER_TYPE)driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)DeviceChido->m_DeviceDesc.DriverTypeDe, NULL, DeviceChido->m_DeviceDesc.createDeviceFlags, featureLevels, DeviceChido->m_DeviceDesc.numFeatureLevels,
			D3D11_SDK_VERSION, &SwapChainChido->GetSD(), &ptrSwap, &ptrDEV, &g_featureLevel, &ptrDevCont);
		/*hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
											D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext );*/
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Create a render target view

	//ID3D11Texture2D* pBackBuffer = NULL;

	hr = ptrSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer.pBackBuffer);
	/* hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );*/
	if (FAILED(hr))
		return hr;

	hr = ptrDEV->CreateRenderTargetView(BackBuffer.pBackBuffer, NULL, &G_PRenderTargetView.g_pRenderTargetView);

	/*hr = g_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );*/
	BackBuffer.pBackBuffer->Release();
	/* pBackBuffer->Release();*/
	if (FAILED(hr))
		return hr;

	// Create depth stencil texture
	C_DepthStencil_DESC  DSD;
	DSD.Width = width;
	DSD.Height = height;
	DSD.MipLevels = 1;
	DSD.ArraySize = 1;
	DSD.Format = (FORMAT)DXGI_FORMAT_D24_UNORM_S8_UINT;
	DSD.SampleDesc.Count = 1;
	DSD.SampleDesc.Quality = 0;
	DSD.Usage = (C_USAGE)D3D11_USAGE_DEFAULT;
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
	hr = ptrDEV->CreateTexture2D(&G_PDepthStencil.descDepth, NULL, &ptrDepht);
	/*hr = g_pd3dDevice->CreateTexture2D( &descDepth, NULL, &g_pDepthStencil );*/
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	C_DepthStencilView_DESC DSVD;
	DSVD.Format = (FORMAT)G_PDepthStencil.descDepth.Format;
	DSVD.ViewDimension = (DSV_DIMENSION)D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVD.MipSlice = 0;

	G_PDepthStencilView.init(DSVD, G_PDepthStencil.descDepth.Format);

	/*D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
	descDSV.Format = G_PDepthStencil->m_DepthStencil.descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;*/

	hr = ptrDEV->CreateDepthStencilView(ptrDepht, &G_PDepthStencilView.descDSV, &G_PDepthStencilView.g_pDepthStencilView);
	/* hr = g_pd3dDevice->CreateDepthStencilView( g_pDepthStencil, &descDSV, &g_pDepthStencilView );*/
	if (FAILED(hr))
		return hr;

	//ptrDevCont->OMSetRenderTargets(1, &G_PRenderTargetView.g_pRenderTargetView, G_PDepthStencilView.g_pDepthStencilView);
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
	ptrDevCont->RSSetViewports(1, &ViewPort.data);
	/*g_pImmediateContext->RSSetViewports( 1, &vp );*/

	// Compile the vertex shader

	//ID3DBlob* pVSBlob = NULL;
	hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &G_PVertexShader.pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = ptrDEV->CreateVertexShader(G_PVertexShader.pVSBlob->GetBufferPointer(), G_PVertexShader.pVSBlob->GetBufferSize(), NULL, &G_PVertexShader.g_pVertexShader);
	/*hr = g_pd3dDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );*/
	if (FAILED(hr))
	{
		G_PVertexShader.pVSBlob->Release();
		return hr;
	}

	// Define the input layout
   /* D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE( layout );
*/

// Create the input layout
	hr = CreateInputLayoutDescFromVertexShaderSignature(G_PVertexShader.pVSBlob, ptrDEV, &G_PInputLayer->g_pVertexLayout);
	if (FAILED(hr))
		return hr;

	/*hr = ptrDEV->CreateInputLayout(layout, numElements, G_PVertexShader.pVSBlob->GetBufferPointer(),
		G_PVertexShader.pVSBlob->GetBufferSize(), &G_PInputLayer->g_pVertexLayout);*/
		/*  hr = g_pd3dDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
												pVSBlob->GetBufferSize(), &g_pVertexLayout );*/
	G_PVertexShader.pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Set the input layout
	ptrDevCont->IASetInputLayout(G_PInputLayer->g_pVertexLayout);
	/* g_pImmediateContext->IASetInputLayout( g_pVertexLayout );*/

	 // Compile the pixel shader
	 //ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &G_PPixelShader.pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = ptrDEV->CreatePixelShader(G_PPixelShader.pPSBlob->GetBufferPointer(), G_PPixelShader.pPSBlob->GetBufferSize(), NULL, &G_PPixelShader.g_pPixelShader);
	/*hr = g_pd3dDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );*/
	G_PPixelShader.pPSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
	};

	CBuffer Buf;
	C_Buffer_DESC BD;
	BD.Usage = C_USAGE::C_USAGE_DEFAULT;
	BD.ByteWidth = sizeof(SimpleVertex) * 24;
	BD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
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

	hr = ptrDEV->CreateBuffer(&Buf.bd, &g_VertexBuffer->InitData, &g_VertexBuffer->BVertex.P_Buffer);
	/* hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pVertexBuffer );*/
	if (FAILED(hr))
		return hr;

	//Assimp::Importer Ass;

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	ptrDevCont->IASetVertexBuffers(0, 1, &g_VertexBuffer->BVertex.P_Buffer, &stride, &offset);
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
	C_Index_Buffer_DESC Ind;
	Ind.pSystem = indices;
	g_pIndexBuffer.init(Ind);
	//g_pIndexBuffer->init(Ind);
	//InitData.pSysMem = indices;
	hr = ptrDEV->CreateBuffer(&Buf.bd, &g_pIndexBuffer.InitD, &g_pIndexBuffer.BIndex.P_Buffer);
	/*  hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pIndexBuffer );*/
	if (FAILED(hr))
		return hr;

	// Set index buffer
	ptrDevCont->IASetIndexBuffer(g_pIndexBuffer.BIndex.P_Buffer, DXGI_FORMAT_R16_UINT, 0);
	/* g_pImmediateContext->IASetIndexBuffer( g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );*/

	 // Set primitive topology
	ptrDevCont->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
	hr = ptrDEV->CreateBuffer(&Buf.bd, NULL, &CAM.g_pCBNeverChanges.P_Buffer);
	/* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBNeverChanges );*/
	if (FAILED(hr))
		return hr;
	hr = ptrDEV->CreateBuffer(&Buf.bd, NULL, &GODCAM.g_pCBNeverChanges.P_Buffer);
	/*hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBNeverChangesGOD );*/
	if (FAILED(hr))
		return hr;

	//BD.Usage = C_USAGE::C_USAGE_DEFAULT;
	BD.ByteWidth = sizeof(CBChangeOnResize);
	BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BD.CPUAccessFlags = 0;

	Buf.init(BD);
	//bd.ByteWidth = sizeof(CBChangeOnResize);
	hr = ptrDEV->CreateBuffer(&Buf.bd, NULL, &CAM.g_pCBChangeOnResize.P_Buffer);
	/* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangeOnResize );*/
	if (FAILED(hr))
		return hr;
	hr = ptrDEV->CreateBuffer(&Buf.bd, NULL, &GODCAM.g_pCBChangeOnResize.P_Buffer);
	/* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangeOnResizeGOD );*/
	if (FAILED(hr))
		return hr;
	//BD.Usage = C_USAGE::C_USAGE_DEFAULT;
	BD.ByteWidth = sizeof(CBChangesEveryFrame);
	BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BD.CPUAccessFlags = 0;

	Buf.init(BD);
	//bd.ByteWidth = sizeof(CBChangesEveryFrame);
	hr = ptrDEV->CreateBuffer(&Buf.bd, NULL, &CAM.g_pCBChangesEveryFrame.P_Buffer);
	/* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangesEveryFrame );*/
	if (FAILED(hr))
		return hr;

	hr = ptrDEV->CreateBuffer(&Buf.bd, NULL, &GODCAM.g_pCBChangesEveryFrame.P_Buffer);
	/* hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangesEveryFrame );*/
	if (FAILED(hr))
		return hr;

	// Load the Texture
	hr = D3DX11CreateShaderResourceViewFromFile(ptrDEV, L"seafloor.dds", NULL, NULL, &g_ShaderResource.G_PTextureRV, NULL);
	/*hr = D3DX11CreateShaderResourceViewFromFile( g_pd3dDevice, L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL );*/
	if (FAILED(hr))
		return hr;

	// Create the sample state
	C_SampleState_DESC STD;
	STD.Filter = (FILTER)D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	STD.AddressU = (TEXTURE_ADDRESS_MODE)D3D11_TEXTURE_ADDRESS_WRAP;
	STD.AddressV = (TEXTURE_ADDRESS_MODE)D3D11_TEXTURE_ADDRESS_WRAP;
	STD.AddressW = (TEXTURE_ADDRESS_MODE)D3D11_TEXTURE_ADDRESS_WRAP;
	STD.ComparisonFunc = (COMPARISON_FUNC)D3D11_COMPARISON_NEVER;
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

	hr = ptrDEV->CreateSamplerState(&SampleState.sampDesc, &SampleState.g_pSamplerLinear);
	/*hr = g_pd3dDevice->CreateSamplerState( &sampDesc, &g_pSamplerLinear );*/
	if (FAILED(hr))
		return hr;
#endif

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
#ifdef D3D11
	ptrDevCont->UpdateSubresource(CAM.g_pCBNeverChanges.P_Buffer, 0, NULL, &cbNeverChanges, 0, 0);

    /*g_pImmediateContext->UpdateSubresource( g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );*/
	//CURRENTNEVERCHANGE.P_Buffer = MainCamera->g_pCBNeverChanges.P_Buffer;
    // Initialize the projection matrix
	 //XMMatrixPerspectiveFovLH( XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f );
#endif

	CBNeverChanges cbNeverChanges2;
	cbNeverChanges2.mView = GODCAM.GetView();//XMMatrixTranspose( g_View );
#ifdef D3D11
	ptrDevCont->UpdateSubresource(GODCAM.g_pCBNeverChanges.P_Buffer, 0, NULL, &cbNeverChanges2, 0, 0);

	/*g_pImmediateContext->UpdateSubresource( g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );*/
	//CURRENTNEVERCHANGE.P_Buffer = MainCamera->g_pCBNeverChanges.P_Buffer;
	// Initialize the projection matrix
	 //XMMatrixPerspectiveFovLH( XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f );
#endif


    CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = CAM.GetProyeccion();//XMMatrixTranspose( g_Projection );
#ifdef D3D11
	ptrDevCont->UpdateSubresource(CAM.g_pCBChangeOnResize.P_Buffer, 0, NULL, &cbChangesOnResize, 0, 0);
#endif
	CBChangeOnResize cbChangesOnResize2;
	cbChangesOnResize2.mProjection = GODCAM.GetProyeccion();//XMMatrixTranspose( g_Projection );
#ifdef D3D11
	ptrDevCont->UpdateSubresource(GODCAM.g_pCBChangeOnResize.P_Buffer, 0, NULL, &cbChangesOnResize2, 0, 0);
    /*g_pImmediateContext->UpdateSubresource( g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );*/

	//CURRENTCHANGEONRESIZE.P_Buffer = MainCamera->g_pCBChangeOnResize.P_Buffer;

	C_Texture2D_DESC InacTx;
	ZeroMemory(&InacTx, sizeof(InacTx));
	InacTx.Width = width;
	InacTx.Height = height;
	InacTx.MipLevels = InacTx.ArraySize = 1;
	InacTx.Format = FORMAT_R8G8B8A8_UNORM;
	InacTx.SampleDesc.Count = 1;
	InacTx.Usage = C_USAGE_DEFAULT;
	InacTx.BindFlags = 8 | 32;		
	InacTx.CPUAccessFlags = 65536;
	InacTx.MiscFlags = 0;

	TextureCAMInac.init(InacTx);

	hr = ptrDEV->CreateTexture2D(&TextureCAMInac.Tex_Des, NULL, &TextureCAMInac.m_pTexture);
	if (FAILED(hr))
		return hr;

	//second Render Target View
	C_TargetView_DESC RTV2;
	RTV2.Format = InacTx.Format;
	RTV2.ViewDimension = RTV_DIMENSION_TEXTURE2D;
	RTV2.Texture2D.mipSlice = 0;

	RenderTargetView2.init(RTV2);

	hr = ptrDEV->CreateRenderTargetView(TextureCAMInac.m_pTexture, &RenderTargetView2.m_Desc, &RenderTargetView2.g_pRenderTargetView);
	if (FAILED(hr))
		return hr;

	D3D11_SHADER_RESOURCE_VIEW_DESC viewD;
	viewD.Format = (DXGI_FORMAT)InacTx.Format;
	viewD.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewD.Texture2D.MostDetailedMip = 0;
	viewD.Texture2D.MipLevels = 1;

	hr = ptrDEV->CreateShaderResourceView(TextureCAMInac.m_pTexture, &viewD, &g_ShaderResource.G_PInactiveRV);
	if (FAILED(hr))
		return hr;

	//Set active and inactive camera
	MainCamera = &CAM;
	SecondCamera = &GODCAM;

	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX11_Init(ptrDEV, ptrDevCont);
	ImGui::StyleColorsDark();


	GraphicApi.ChargeMesh("Modelo/Scene.fbx", &ScMana, GraphicApi.m_Model, DeviceContextChido, GraphicApi.m_Importer, ptrDEV);
#endif
	
    return S_OK;
}




//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------

//! A CleanupDevice function.
	/*!
	  Function of directx for clean all pointer.
	*/
void CleanupDevice()
{
#ifdef D3D11
	if (ptrDevCont) ptrDevCont->ClearState();
   /* if( g_pImmediateContext ) g_pImmediateContext->ClearState();*/

	if (SampleState.g_pSamplerLinear) SampleState.g_pSamplerLinear->Release();
    /*if( g_pSamplerLinear ) g_pSamplerLinear->Release();*/
    if(g_ShaderResource.G_PTextureRV) g_ShaderResource.G_PTextureRV->Release();
    if(MainCamera->g_pCBNeverChanges.P_Buffer) MainCamera->g_pCBNeverChanges.P_Buffer->Release();
    if(MainCamera->g_pCBChangeOnResize.P_Buffer) MainCamera->g_pCBChangeOnResize.P_Buffer->Release();
    if(MainCamera->g_pCBChangesEveryFrame.P_Buffer) MainCamera->g_pCBChangesEveryFrame.P_Buffer->Release();
	if (SecondCamera->g_pCBChangesEveryFrame.P_Buffer) SecondCamera->g_pCBChangesEveryFrame.P_Buffer->Release();
	if (SecondCamera->g_pCBNeverChanges.P_Buffer) SecondCamera->g_pCBNeverChanges.P_Buffer->Release();
	if (SecondCamera->g_pCBChangeOnResize.P_Buffer) SecondCamera->g_pCBChangeOnResize.P_Buffer->Release();
	
	if (g_VertexBuffer->BVertex.P_Buffer) g_VertexBuffer->BVertex.P_Buffer->Release();
   /* if( g_pVertexBuffer ) g_pVertexBuffer->Release();*/
    if( g_pIndexBuffer.BIndex.P_Buffer ) g_pIndexBuffer.BIndex.P_Buffer->Release();
	
		if (G_PInputLayer->g_pVertexLayout) G_PInputLayer->g_pVertexLayout->Release();
  /*  if( g_pVertexLayout ) g_pVertexLayout->Release();*/
	if (G_PVertexShader.g_pVertexShader) G_PVertexShader.g_pVertexShader->Release();
    /*if( g_pVertexShader ) g_pVertexShader->Release();*/
	if (G_PPixelShader.g_pPixelShader) G_PPixelShader.g_pPixelShader->Release();
   /* if( g_pPixelShader ) g_pPixelShader->Release();*/
	
	if (ptrDepht) ptrDepht->Release();
   /* if( g_pDepthStencil ) g_pDepthStencil->Release();*/
	
	if (G_PDepthStencilView.g_pDepthStencilView) G_PDepthStencilView.g_pDepthStencilView->Release();
   /* if( g_pDepthStencilView ) g_pDepthStencilView->Release();*/
	
	if (G_PRenderTargetView.g_pRenderTargetView) G_PRenderTargetView.g_pRenderTargetView->Release();
    /*if( g_pRenderTargetView ) g_pRenderTargetView->Release();*/
	
	
	if (ptrSwap) ptrSwap->Release();
   /* if( g_pSwapChain ) g_pSwapChain->Release();*/
	
	if (ptrDevCont) ptrDevCont->Release();
    /*if( g_pImmediateContext ) g_pImmediateContext->Release();*/
	if (ptrDEV) ptrDEV->Release();
    /*if( g_pd3dDevice ) g_pd3dDevice->Release();*/
#endif
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------

//! A WndProc function.
	/*!
	  Function of directx detect events of the window like inputs, move mouse, etc.
	  \param hWnd an HWND.
	   \param message an UINT.
	   \param wParam an WPARAM.
	   \param lParam an LPARAM.
	*/
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		std::cout << "F";
		return true;
	}
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
		case WM_SIZE:
		{
#ifdef D3D11
			if (ptrDevCont != nullptr)
			{
				//Get new window dimensions
				RECT rc;
				GetClientRect(hWnd, &rc);
				UINT width = rc.right - rc.left;
				UINT height = rc.bottom - rc.top;
				//Regenerate world matrix as identity
				g_World = glm::mat4(1.0f);
				//Set w and h for camera
				MainCamera->setHeight(height);
				MainCamera->setWeight(width);
				//Update projection matrix with new params
				MainCamera->UpdateProyeccion();
				//Update CB
				CBChangeOnResize cbChangesOnResize;
				cbChangesOnResize.mProjection = MainCamera->GetProyeccion();
				ptrDevCont->UpdateSubresource(MainCamera->g_pCBChangeOnResize.P_Buffer, 0, NULL, &cbChangesOnResize, 0, 0);

				//camara inactiva
				SecondCamera->setHeight(height);
				SecondCamera->setWeight(width);
				SecondCamera->UpdateProyeccion();

				CBChangeOnResize cbChangesOnResize2;
				cbChangesOnResize2.mProjection = SecondCamera->GetProyeccion();
				ptrDevCont->UpdateSubresource(SecondCamera->g_pCBChangeOnResize.P_Buffer, 0, NULL, &cbChangesOnResize2, 0, 0);



				if (ptrSwap)
				{
					HRESULT h;

					//Release inactive camera texture, SRV and RTV
					TextureCAMInac.m_pTexture->Release();
					g_ShaderResource.G_PInactiveRV->Release();
					RenderTargetView2.g_pRenderTargetView->Release();

					//Resize inactive camera texture					
					C_Texture2D_DESC TD;
					ZeroMemory(&TD, sizeof(TD));
					TD.Width = width;
					TD.Height = height;
					TD.MipLevels = TD.ArraySize = 1;
					TD.Format = FORMAT_R8G8B8A8_UNORM;
					TD.SampleDesc.Count = 1;
					TD.Usage = C_USAGE_DEFAULT;
					TD.BindFlags = 8 | 32;			// D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
					TD.CPUAccessFlags = 65536;	//D3D11_CPU_ACCESS_WRITE;
					TD.MiscFlags = 0;
					TextureCAMInac.init(TD);

					h = ptrDEV->CreateTexture2D(&TextureCAMInac.Tex_Des, NULL, &TextureCAMInac.m_pTexture);

					C_TargetView_DESC RTVD;
					RTVD.Format = TD.Format;
					RTVD.ViewDimension = RTV_DIMENSION_TEXTURE2D;
					RTVD.texture1D.mipSlice = 0;
					RenderTargetView2.init(RTVD);

					h = ptrDEV->CreateRenderTargetView(TextureCAMInac.m_pTexture, &RenderTargetView2.m_Desc, &RenderTargetView2.g_pRenderTargetView);

					D3D11_SHADER_RESOURCE_VIEW_DESC SRV;
					SRV.Format = (DXGI_FORMAT)TD.Format;
					SRV.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
					SRV.Texture2D.MostDetailedMip = 0;
					SRV.Texture2D.MipLevels = 1;

					h = ptrDEV->CreateShaderResourceView(TextureCAMInac.m_pTexture, &SRV, &g_ShaderResource.G_PInactiveRV);

					//camara activa


					ptrDevCont->OMSetRenderTargets(0, 0, 0);
					G_PRenderTargetView.g_pRenderTargetView->Release();
					
					h = ptrSwap->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

					CBuffer tempBack;
					h = ptrSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&tempBack.P_Buffer);
					h = ptrDEV->CreateRenderTargetView(tempBack.P_Buffer, NULL, &G_PRenderTargetView.g_pRenderTargetView);
					tempBack.P_Buffer->Release();

					ptrDepht->Release();

					C_DepthStencil_DESC DepthDesc;
					DepthDesc.Width = width;
					DepthDesc.Height = height;
					DepthDesc.MipLevels = 1;
					DepthDesc.ArraySize = 1;
					DepthDesc.Format = FORMAT_D24_UNORM_S8_UINT;
					DepthDesc.SampleDesc.Count = 1;
					DepthDesc.SampleDesc.Quality = 0;
					DepthDesc.Usage = C_USAGE_DEFAULT;
					DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
					DepthDesc.CPUAccessFlags = 0;
					DepthDesc.MiscFlags = 0;

					G_PDepthStencil.init(DepthDesc);

					h = ptrDEV->CreateTexture2D(&G_PDepthStencil.descDepth, NULL, &ptrDepht);

					C_DepthStencilView_DESC DSVD;
					DSVD.Format = G_PDepthStencil.m_DepthStencil.Format;
					DSVD.ViewDimension = DSV_DIMENSION_TEXTURE2D;
					DSVD.Texture2D.mipSlice = 0;

					G_PDepthStencilView.g_pDepthStencilView->Release();

					G_PDepthStencilView.init(DSVD, G_PDepthStencil.descDepth.Format);

					h = ptrDEV->CreateDepthStencilView(ptrDepht, &G_PDepthStencilView.descDSV, &G_PDepthStencilView.g_pDepthStencilView);

					ptrDevCont->OMSetRenderTargets(1, &G_PRenderTargetView.g_pRenderTargetView, G_PDepthStencilView.g_pDepthStencilView);

					C_Viewport_DESC VD;
					VD.Width = width;
					VD.Height = height;
					VD.MinDepth = 0.f;
					VD.MaxDepth = 1.f;
					VD.TopLeftX = 0;
					VD.TopLeftY = 0;

					CViewport ViewP;
					ViewP.init(VD);
					ptrDevCont->RSSetViewports(1, &ViewP.data);
					
				}
				ImGui::GetStyle().ScaleAllSizes(1	);
			}
#endif
			
			break;
		}

		case WM_KEYDOWN:
		{
#if defined(D3D11)
			MainCamera->Input(wParam);
			CBNeverChanges cb;
			cb.mView = MainCamera->GetView();

			ptrDevCont->UpdateSubresource(MainCamera->g_pCBNeverChanges.P_Buffer, 0, NULL, &cb, 0, 0);
#endif
			break;
		}
		case WM_RBUTTONDOWN:
		{
#if defined(D3D11)
			POINT Mouse;
			GetCursorPos(&Mouse);
			MainCamera->PosIn = { float(Mouse.x),float(Mouse.y),0 };
			MainCamera->Fpres = true;
#endif
			break;

		}
		case WM_MOUSEMOVE:
		{
#ifdef D3D11
				if (MainCamera->Fpres == true)
				{
					POINT MOUSE;
					GetCursorPos(&MOUSE);
					MainCamera->PosFn = { float(MOUSE.x),float(MOUSE.y),0 };
					SetCursorPos(MainCamera->PosIn.x, MainCamera->PosIn.y);

					MainCamera->Dir = MainCamera->PosIn - MainCamera->PosFn;
					/*float cosine = cosf(CAM.Dir.x);
					float sine = sinf(CAM.Dir.x);*/
					MainCamera->MoveMouse(MainCamera->Dir);
					CBNeverChanges cbNeverChanges;
					cbNeverChanges.mView = MainCamera->GetView();//XMMatrixTranspose( g_View );

					ptrDevCont->UpdateSubresource(MainCamera->g_pCBNeverChanges.P_Buffer, 0, NULL, &cbNeverChanges, 0, 0);

					/*g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/

				}	
#endif
			break;
		}
		case WM_RBUTTONUP:
		{
		#ifdef D3D11
			MainCamera->Fpres = false;
		#endif
		}

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------

//! A Render function.
	/*!
	  Function of directx for render the scence in the window.
	*/
void Render()
{
#ifdef D3D11


	// Update our time
	static float t = 0.0f;
	if (DeviceChido->m_DeviceDesc.DriverTypeDe == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)XM_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	// Rotate cube around the origin
	//g_World = XMMatrixRotationY( t );
	glm::vec3 T = { 3, 0, 0 };
	//g_World = glm::translate(MainCamera->GetPosition());


	// Modify the color
	g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

	ptrDevCont->OMSetRenderTargets(1, &RenderTargetView2.g_pRenderTargetView, G_PDepthStencilView.g_pDepthStencilView);

	ptrDevCont->ClearRenderTargetView(RenderTargetView2.g_pRenderTargetView, ClearColor);
	/* g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );*/
	 //
	 // Clear the depth buffer to 1.0 (max depth)
	 //
	ptrDevCont->ClearDepthStencilView(G_PDepthStencilView.g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	/*g_pImmediateContext->ClearDepthStencilView( g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );*/
	//
	// Update variables that change once per frame
	//

	/*CBChangesEveryFrame cb;
	cb.mWorld = glm::transpose( g_World );
	cb.vMeshColor = g_vMeshColor;
	ptrDevCont->UpdateSubresource(SecondCamera->g_pCBChangesEveryFrame.P_Buffer, 0, NULL, &cb, 0, 0);*/
	/*g_pImmediateContext->UpdateSubresource( g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0 );*/


	//
	// Render the cube
	//

	/*ptrDevCont->VSSetShader(G_PVertexShader.g_pVertexShader, NULL, 0);
	ptrDevCont->VSSetConstantBuffers(0, 1, &MainCamera->g_pCBNeverChanges.P_Buffer);
	ptrDevCont->VSSetConstantBuffers(1, 1, &MainCamera->g_pCBChangeOnResize.P_Buffer);
	ptrDevCont->VSSetConstantBuffers(2, 1, &MainCamera->g_pCBChangesEveryFrame.P_Buffer);
	ptrDevCont->PSSetShader(G_PPixelShader.g_pPixelShader, NULL, 0);
	ptrDevCont->PSSetConstantBuffers(2, 1, &MainCamera->g_pCBChangesEveryFrame.P_Buffer);
	ptrDevCont->PSSetShaderResources(0, 1, &g_ShaderResource.G_PTextureRV);
	ptrDevCont->PSSetSamplers(0, 1, &SampleState.g_pSamplerLinear);
	ptrDevCont->DrawIndexed(36, 0, 0);*/


	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	ptrDevCont->IASetVertexBuffers(0, 1, &g_VertexBuffer->BVertex.P_Buffer, &stride, &offset);
	ptrDevCont->IASetIndexBuffer(g_pIndexBuffer.BIndex.P_Buffer, DXGI_FORMAT_R16_UINT, 0);

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
				CBChangesEveryFrame cb;
				cb.mWorld = glm::transpose(g_World);
				cb.vMeshColor = g_vMeshColor;
				ptrDevCont->UpdateSubresource(SecondCamera->g_pCBChangesEveryFrame.P_Buffer, 0, NULL, &cb, 0, 0);

				ptrDevCont->VSSetShader(G_PVertexShader.g_pVertexShader, NULL, 0);
				ptrDevCont->VSSetConstantBuffers(0, 1, &SecondCamera->g_pCBNeverChanges.P_Buffer);
				ptrDevCont->VSSetConstantBuffers(1, 1, &SecondCamera->g_pCBChangeOnResize.P_Buffer);
				ptrDevCont->VSSetConstantBuffers(2, 1, &SecondCamera->g_pCBChangesEveryFrame.P_Buffer);
				ptrDevCont->PSSetShader(G_PPixelShader.g_pPixelShader, NULL, 0);
				ptrDevCont->PSSetConstantBuffers(2, 1, &SecondCamera->g_pCBChangesEveryFrame.P_Buffer);
				ptrDevCont->PSSetShaderResources(0, 1, &g_ShaderResource.G_PTextureRV);
				ptrDevCont->PSSetSamplers(0, 1, &SampleState.g_pSamplerLinear);
				ptrDevCont->DrawIndexed(36, 0, 0);
			}
			T = { DistanceX, 0, DistanceY };
			g_World = glm::translate(T);
			//cb.mWorld = glm::transpose(g_World);
			//cb.vMeshColor = g_vMeshColor;
			//ptrDevCont->UpdateSubresource(SecondCamera->g_pCBChangesEveryFrame.P_Buffer, 0, NULL, &cb, 0, 0);
			/*g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);*/
		}
		DistanceY += 2.5;
		DistanceX = 0;
	}

	CBChangesEveryFrame cbMesh;
	cbMesh.mWorld = {
		1,0,0,MainCamera->GetPosition().x,
		0,1,0,MainCamera->GetPosition().y,
		0,0,1,MainCamera->GetPosition().z,
		0,0,0,1
	};
	cbMesh.vMeshColor = { 1,0,0,1 };
	ptrDevCont->UpdateSubresource(SecondCamera->g_pCBChangesEveryFrame.P_Buffer, 0, NULL, &cbMesh, 0, 0);
	for (int i = 0; i < ScMana.m_MeshInScene.size(); i++)
	{
		ptrDevCont->VSSetConstantBuffers(2, 1, &SecondCamera->g_pCBChangesEveryFrame.P_Buffer);
		ptrDevCont->PSSetShaderResources(0, 1, &ScMana.m_MeshInScene[i]->m_Materials->m_TexDif);
		ptrDevCont->VSSetShaderResources(0, 1, &ScMana.m_MeshInScene[i]->m_Materials->m_TexDif);


		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;

		ptrDevCont->IASetVertexBuffers
		(0,
			1,//numero de buffers que estamos utilizando
			&ScMana.m_MeshInScene[i]->m_VertexBuffer->P_Buffer,//puntero a la lista buffers
			&stride,//un uint que indica el tamaño de un unico vertice
			&offset
		);//un uint que indica el numero del byte en el vertice del que se quiere comenzar a pintar

		ptrDevCont->IASetIndexBuffer
		(
			ScMana.m_MeshInScene[i]->m_Index->P_Buffer,
			DXGI_FORMAT_R16_UINT,
			0
		);

		//Tipo de topologia
		/*Esta segunda función le dice a Direct3D qué tipo de primitiva se usa.*/
		//_devCont.g_pImmediateContextD3D11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		 //Dibuja el búfer de vértices en el búfer posterior 
		ptrDevCont->DrawIndexed(ScMana.m_MeshInScene[i]->m_IndexNum, 0, 0);
	}

	ptrDevCont->OMSetRenderTargets(1, &G_PRenderTargetView.g_pRenderTargetView, G_PDepthStencilView.g_pDepthStencilView);

	ptrDevCont->ClearRenderTargetView(G_PRenderTargetView.g_pRenderTargetView, ClearColor);

	ptrDevCont->ClearDepthStencilView(G_PDepthStencilView.g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	ptrDevCont->IASetVertexBuffers(0, 1, &g_VertexBuffer->BVertex.P_Buffer, &stride, &offset);
	ptrDevCont->IASetIndexBuffer(g_pIndexBuffer.BIndex.P_Buffer, DXGI_FORMAT_R16_UINT, 0);
	//
	// Render the cube
	//
	DistanceX = 0;
	DistanceY = 0;

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
				CBChangesEveryFrame cb;
				cb.mWorld = glm::transpose(g_World);
				cb.vMeshColor = g_vMeshColor;
				ptrDevCont->UpdateSubresource(MainCamera->g_pCBChangesEveryFrame.P_Buffer, 0, NULL, &cb, 0, 0);

				ptrDevCont->VSSetShader(G_PVertexShader.g_pVertexShader, NULL, 0);
				ptrDevCont->VSSetConstantBuffers(0, 1, &MainCamera->g_pCBNeverChanges.P_Buffer);
				ptrDevCont->VSSetConstantBuffers(1, 1, &MainCamera->g_pCBChangeOnResize.P_Buffer);
				ptrDevCont->VSSetConstantBuffers(2, 1, &MainCamera->g_pCBChangesEveryFrame.P_Buffer);
				ptrDevCont->PSSetShader(G_PPixelShader.g_pPixelShader, NULL, 0);
				ptrDevCont->PSSetConstantBuffers(2, 1, &MainCamera->g_pCBChangesEveryFrame.P_Buffer);
				ptrDevCont->PSSetShaderResources(0, 1, &g_ShaderResource.G_PInactiveRV);
				ptrDevCont->PSSetSamplers(0, 1, &SampleState.g_pSamplerLinear);
				ptrDevCont->DrawIndexed(36, 0, 0);
			}
			T = { DistanceX, 0, DistanceY };
			g_World = glm::translate(T);

			/*g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);*/
		}
		DistanceY += 2.5;
		DistanceX = 0;
	}
	cbMesh.mWorld = {
		1,0,0,SecondCamera->GetPosition().x,
		0,1,0,SecondCamera->GetPosition().y,
		0,0,1,SecondCamera->GetPosition().z,
		0,0,0,1
	};
	cbMesh.vMeshColor = { 1,1,1,1 };
	ptrDevCont->UpdateSubresource(MainCamera->g_pCBChangesEveryFrame.P_Buffer, 0, NULL, &cbMesh, 0, 0);
	for (int i = 0; i < ScMana.m_MeshInScene.size(); i++)
	{
		ptrDevCont->VSSetConstantBuffers(2, 1, &MainCamera->g_pCBChangesEveryFrame.P_Buffer);
		ptrDevCont->PSSetShaderResources(0, 1, &ScMana.m_MeshInScene[i]->m_Materials->m_TexDif);
		ptrDevCont->VSSetShaderResources(0, 1, &ScMana.m_MeshInScene[i]->m_Materials->m_TexDif);
		//_devCont->g_pImmediateContextD3D11->UpdateSubresource	(_bufferData->m_BufferD3D11, 0, NULL, &m_MeshData, 0, 0);
		//
		//_devCont->g_pImmediateContextD3D11->VSSetConstantBuffers(2, 1, &_bufferData->m_BufferD3D11);
		//_devCont->g_pImmediateContextD3D11->PSSetConstantBuffers(2, 1, &_bufferData->m_BufferD3D11);

		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;

		ptrDevCont->IASetVertexBuffers
		(0,
			1,//numero de buffers que estamos utilizando
			&ScMana.m_MeshInScene[i]->m_VertexBuffer->P_Buffer,//puntero a la lista buffers
			&stride,//un uint que indica el tamaño de un unico vertice
			&offset
		);//un uint que indica el numero del byte en el vertice del que se quiere comenzar a pintar

		ptrDevCont->IASetIndexBuffer
		(
			ScMana.m_MeshInScene[i]->m_Index->P_Buffer,
			DXGI_FORMAT_R16_UINT,
			0
		);

		//Tipo de topologia
		/*Esta segunda función le dice a Direct3D qué tipo de primitiva se usa.*/
		//_devCont.g_pImmediateContextD3D11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		 //Dibuja el búfer de vértices en el búfer posterior 
		ptrDevCont->DrawIndexed(ScMana.m_MeshInScene[i]->m_IndexNum, 0, 0);
	}
	//
    // Present our back buffer to our front buffer
    //
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ptrSwap->Present(0, 0);


	void Render(glm::mat4x4(g_World));
#endif
  /*  g_pSwapChain->Present( 0, 0 );*/
}
