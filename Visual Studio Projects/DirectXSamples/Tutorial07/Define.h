
//*****************************************************************************/
/**
* @File Define.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/03/2020
* @brief inclusion de encabezados y uso de enum y estructuras
* @Bug No kown bug
**/
//****************************************************************************/


#pragma once

//#include <d3d11.h>


/*! \file .h, .hpp and includes in general
	\brief A Documented file.

	this is where include all libraries of i need for the proyect work, including assim, imgui, iostream, D3D11, GLFW, etc.
*/
#include "assimp/Importer.hpp"
#include"assimp/cimport.h"
#include "assimp/material.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../Tutorial07/includes/gtc/matrix_transform.hpp"

#include "includes/imgui/imgui.h"
#include"includes/imgui/imgui_impl_win32.h"
#include "includes/imgui/imgui_impl_dx11.h"
#include "includes/imgui/imgui_impl_glfw.h"
#include "includes/imgui/imgui_impl_opengl3.h"




#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iostream>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

#if defined(GLFW)
#include "glad.h"
#include "glfw3.h"
#include "glm.hpp"
#endif

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include <stdlib.h>
#include <stdio.h>

#include <filesystem>


#define NUM_BONE_PERVERTX 4
#define MAXBONES 100

#ifdef D3D11
//Enum

// !An enum.
/*! enum of usage values. */
enum C_USAGE {

	/**< enum C_USAGE_DEFAULT. */
	C_USAGE_DEFAULT,

	/**< enum C_USAGE_IMMUTABLE. */
	C_USAGE_IMMUTABLE,

	/**< enum C_USAGE_DYNAMIC. */
	C_USAGE_DYNAMIC,

	/**< enum C_USAGE_STAGING. */
	C_USAGE_STAGING
};	


// !An enum.
/*! enum of FORMAT values. */
enum FORMAT
{
	/**< enum FORMAT_UNKNOWN. */
	FORMAT_UNKNOWN,

	/**< enum FORMAT_R32G32B32A32_TYPELESS. */
	FORMAT_R32G32B32A32_TYPELESS,

	/**< enum FORMAT_R32G32B32A32_FLOAT. */
	FORMAT_R32G32B32A32_FLOAT,

	/**< enum FORMAT_R32G32B32A32_UINT. */
	FORMAT_R32G32B32A32_UINT,

	/**< enum FORMAT_R32G32B32A32_SINT. */
	FORMAT_R32G32B32A32_SINT,

	/**< enum FORMAT_R32G32B32_TYPELESS. */
	FORMAT_R32G32B32_TYPELESS,

	/**< enum FORMAT_R32G32B32_FLOAT. */
	FORMAT_R32G32B32_FLOAT,

	/**< enum FORMAT_R32G32B32_UINT. */
	FORMAT_R32G32B32_UINT,

	/**< enum FORMAT_R32G32B32_SINT. */
	FORMAT_R32G32B32_SINT,

	/**< enum FORMAT_R16G16B16A16_TYPELESS. */
	FORMAT_R16G16B16A16_TYPELESS,

	/**< enum FORMAT_R16G16B16A16_FLOAT. */
	FORMAT_R16G16B16A16_FLOAT,

	/**< enum FORMAT_R16G16B16A16_UNORM. */
	FORMAT_R16G16B16A16_UNORM,

	/**< enum FORMAT_R16G16B16A16_UINT. */
	FORMAT_R16G16B16A16_UINT,

	/**< enum FORMAT_R16G16B16A16_SNORM. */
	FORMAT_R16G16B16A16_SNORM,

	/**< enum FORMAT_R16G16B16A16_SINT. */
	FORMAT_R16G16B16A16_SINT,

	/**< enum FORMAT_R32G32_TYPELESS. */
	FORMAT_R32G32_TYPELESS,

	/**< enum FORMAT_R32G32_FLOAT. */
	FORMAT_R32G32_FLOAT,

	/**< enum FORMAT_R32G32_UINT. */
	FORMAT_R32G32_UINT,

	/**< enum FORMAT_R32G32_SINT. */
	FORMAT_R32G32_SINT,

	/**< enum FORMAT_R32G8X24_TYPELESS. */
	FORMAT_R32G8X24_TYPELESS,

	/**< enum FORMAT_D32_FLOAT_S8X24_UINT. */
	FORMAT_D32_FLOAT_S8X24_UINT,

	/**< enum FORMAT_R32_FLOAT_X8X24_TYPELESS. */
	FORMAT_R32_FLOAT_X8X24_TYPELESS,

	/**< enum FORMAT_X32_TYPELESS_G8X24_UINT. */
	FORMAT_X32_TYPELESS_G8X24_UINT,

	/**< enum FORMAT_R10G10B10A2_TYPELESS. */
	FORMAT_R10G10B10A2_TYPELESS,

	/**< enum FORMAT_R10G10B10A2_UNORM. */
	FORMAT_R10G10B10A2_UNORM,

	/**< enum FORMAT_R10G10B10A2_UINT. */
	FORMAT_R10G10B10A2_UINT,

	/**< enum FORMAT_R11G11B10_FLOAT. */
	FORMAT_R11G11B10_FLOAT,

	/**< enum FORMAT_R8G8B8A8_TYPELESS. */
	FORMAT_R8G8B8A8_TYPELESS,

	/**< enum FORMAT_R8G8B8A8_UNORM. */
	FORMAT_R8G8B8A8_UNORM,

	/**< enum FORMAT_R8G8B8A8_UNORM_SRGB. */
	FORMAT_R8G8B8A8_UNORM_SRGB,

	/**< enum FORMAT_R8G8B8A8_UINT. */
	FORMAT_R8G8B8A8_UINT,

	/**< enum FORMAT_R8G8B8A8_SNORM. */
	FORMAT_R8G8B8A8_SNORM,

	/**< enum FORMAT_R8G8B8A8_SINT. */
	FORMAT_R8G8B8A8_SINT,

    /**< enum FORMAT_R16G16_TYPELESS. */
	FORMAT_R16G16_TYPELESS,

	/**< enum FORMAT_R16G16_FLOAT. */
	FORMAT_R16G16_FLOAT,

		/**< enum FORMAT_R16G16_UNORM. */
	FORMAT_R16G16_UNORM,

		/**< enum FORMAT_R16G16_UINT. */
	FORMAT_R16G16_UINT,

		/**< enum FORMAT_R16G16_SNORM. */
	FORMAT_R16G16_SNORM,

		/**< enum FORMAT_R16G16_SINT. */
	FORMAT_R16G16_SINT,

		/**< enum FORMAT_R32_TYPELESS. */
	FORMAT_R32_TYPELESS,

		/**< enum FORMAT_D32_FLOAT. */
	FORMAT_D32_FLOAT,

		/**< enum FORMAT_R32_FLOAT. */
	FORMAT_R32_FLOAT,

		/**< enum FORMAT_R32_UINT. */
	FORMAT_R32_UINT,

		/**< enum FORMAT_R32_SINT. */
	FORMAT_R32_SINT,

		/**< enum FORMAT_R24G8_TYPELESS. */
	FORMAT_R24G8_TYPELESS,

		/**< enum FORMAT_D24_UNORM_S8_UINT. */
	FORMAT_D24_UNORM_S8_UINT,

		/**< enum FORMAT_R24_UNORM_X8_TYPELESS. */
	FORMAT_R24_UNORM_X8_TYPELESS,

		/**< enum FORMAT_X24_TYPELESS_G8_UINT. */
	FORMAT_X24_TYPELESS_G8_UINT,

		/**< enum FORMAT_R8G8_TYPELESS. */
	FORMAT_R8G8_TYPELESS,

		/**< enum FORMAT_R8G8_UNORM. */
	FORMAT_R8G8_UNORM,

		/**< enum FORMAT_R8G8_UINT. */
	FORMAT_R8G8_UINT,

		/**< enum FORMAT_R8G8_SNORM. */
	FORMAT_R8G8_SNORM,

		/**< enum FORMAT_R8G8_SINT. */
	FORMAT_R8G8_SINT,

		/**< enum FORMAT_R16_TYPELESS. */
	FORMAT_R16_TYPELESS,

		/**< enum FORMAT_R16_FLOAT. */
	FORMAT_R16_FLOAT,

		/**< enum FORMAT_D16_UNORM. */
	FORMAT_D16_UNORM,

		/**< enum FORMAT_R16_UNORM. */
	FORMAT_R16_UNORM,

		/**< enum FORMAT_R16_UINT. */
	FORMAT_R16_UINT,

		/**< enum FORMAT_R16_SINT. */
	FORMAT_R16_SNORM,

		/**< enum FORMAT_R16_SINT. */
	FORMAT_R16_SINT,

		/**< enum FORMAT_R8_TYPELESS. */
	FORMAT_R8_TYPELESS,

		/**< enum FORMAT_R8_UNORM. */
	FORMAT_R8_UNORM,

		/**< enum FORMAT_R8_UINT. */
	FORMAT_R8_UINT,

		/**< enum FORMAT_R8_SNORM. */
	FORMAT_R8_SNORM,

		/**< enum FORMAT_R8_SINT. */
	FORMAT_R8_SINT,

		/**< enum FORMAT_A8_UNORM. */
	FORMAT_A8_UNORM,

		/**< enum FORMAT_R1_UNORM. */
	FORMAT_R1_UNORM,

		/**< enum FORMAT_R9G9B9E5_SHAREDEXP. */
	FORMAT_R9G9B9E5_SHAREDEXP,

		/**< enum FORMAT_R8G8_B8G8_UNORM. */
	FORMAT_R8G8_B8G8_UNORM,

		/**< enum FORMAT_G8R8_G8B8_UNORM. */
	FORMAT_G8R8_G8B8_UNORM,

		/**< enum FORMAT_BC1_TYPELESS. */
	FORMAT_BC1_TYPELESS,

		/**< enum FORMAT_BC1_UNORM. */
	FORMAT_BC1_UNORM,

		/**< enum FORMAT_BC1_UNORM_SRGB. */
	FORMAT_BC1_UNORM_SRGB,

		/**< enum FORMAT_BC2_TYPELESS. */
	FORMAT_BC2_TYPELESS,

		/**< enum FORMAT_BC2_UNORM. */
	FORMAT_BC2_UNORM,

		/**< enum FORMAT_BC2_UNORM_SRGB. */
	FORMAT_BC2_UNORM_SRGB,

		/**< enum FORMAT_BC3_TYPELESS. */
	FORMAT_BC3_TYPELESS,

		/**< enum FORMAT_BC3_UNORM. */
	FORMAT_BC3_UNORM,

		/**< enum FORMAT_BC3_UNORM_SRGB. */
	FORMAT_BC3_UNORM_SRGB,

		/**< enum FORMAT_BC4_TYPELESS. */
	FORMAT_BC4_TYPELESS,

		/**< enum FORMAT_BC4_UNORM. */
	FORMAT_BC4_UNORM,

		/**< enum FORMAT_BC4_SNORM. */
	FORMAT_BC4_SNORM,

		/**< enum FORMAT_BC5_TYPELESS. */
	FORMAT_BC5_TYPELESS,

		/**< enum FORMAT_BC5_UNORM. */
	FORMAT_BC5_UNORM,

		/**< enum FORMAT_BC5_SNORM. */
	FORMAT_BC5_SNORM,

		/**< enum FORMAT_B5G6R5_UNORM. */
	FORMAT_B5G6R5_UNORM,

		/**< enum FORMAT_B5G5R5A1_UNORM. */
	FORMAT_B5G5R5A1_UNORM,

		/**< enum FORMAT_B8G8R8A8_UNORM. */
	FORMAT_B8G8R8A8_UNORM,

		/**< enum FORMAT_B8G8R8X8_UNORM. */
	FORMAT_B8G8R8X8_UNORM,

		/**< enum FORMAT_R10G10B10_XR_BIAS_A2_UNORM. */
	FORMAT_R10G10B10_XR_BIAS_A2_UNORM,

		/**< enum FORMAT_B8G8R8A8_TYPELESS. */
	FORMAT_B8G8R8A8_TYPELESS,

		/**< enum FORMAT_B8G8R8A8_UNORM_SRGB. */
	FORMAT_B8G8R8A8_UNORM_SRGB,

		/**< enum FORMAT_B8G8R8X8_TYPELESS. */
	FORMAT_B8G8R8X8_TYPELESS,

		/**< enum FORMAT_B8G8R8X8_UNORM_SRGB. */
	FORMAT_B8G8R8X8_UNORM_SRGB,

		/**< enum FORMAT_BC6H_TYPELESS. */
	FORMAT_BC6H_TYPELESS,

		/**< enum FORMAT_BC6H_UF16. */
	FORMAT_BC6H_UF16,

		/**< enum FORMAT_BC6H_SF16. */
	FORMAT_BC6H_SF16,

		/**< enum FORMAT_BC7_TYPELESS. */
	FORMAT_BC7_TYPELESS,

		/**< enum FORMAT_BC7_UNORM. */
	FORMAT_BC7_UNORM,

		/**< enum FORMAT_BC7_UNORM_SRGB. */
	FORMAT_BC7_UNORM_SRGB,

	/**< enum FORMAT_FORCE_UINT. */
	FORMAT_FORCE_UINT

};

// !An enum.
/*! enum of DSV_DIMENSION values. */
enum DSV_DIMENSION
{
	/**< enum DSV_DIMENSION_UNKNOWN. */
	DSV_DIMENSION_UNKNOWN = 0,

	/**< enum DSV_DIMENSION_TEXTURE1D. */
	DSV_DIMENSION_TEXTURE1D = 1,

	/**< enum DSV_DIMENSION_TEXTURE1DARRAY. */
	DSV_DIMENSION_TEXTURE1DARRAY = 2,

	/**< enum DSV_DIMENSION_TEXTURE2D. */
	DSV_DIMENSION_TEXTURE2D = 3,

	/**< enum DSV_DIMENSION_TEXTURE2DARRAY. */
	DSV_DIMENSION_TEXTURE2DARRAY = 4,

	/**< enum DSV_DIMENSION_TEXTURE2DMS. */
	DSV_DIMENSION_TEXTURE2DMS = 5,

	/**< enum DSV_DIMENSION_TEXTURE2DMSARRAY. */
	DSV_DIMENSION_TEXTURE2DMSARRAY = 6
};

// !An enum.
/*! enum of RTV_DIMENSION values. */
enum RTV_DIMENSION
{
	/**< enum RTV_DIMENSION_UNKNOWN. */
	RTV_DIMENSION_UNKNOWN = 0,

	/**< enum RTV_DIMENSION_BUFFER. */
	RTV_DIMENSION_BUFFER = 1,

	/**< enum RTV_DIMENSION_TEXTURE1D. */
	RTV_DIMENSION_TEXTURE1D = 2,

	/**< enum RTV_DIMENSION_TEXTURE1DARRAY. */
	RTV_DIMENSION_TEXTURE1DARRAY = 3,

	/**< enum RTV_DIMENSION_TEXTURE2D. */
	RTV_DIMENSION_TEXTURE2D = 4,

	/**< enum RTV_DIMENSION_TEXTURE2DARRAY. */
	RTV_DIMENSION_TEXTURE2DARRAY = 5,

	/**< enum RTV_DIMENSION_TEXTURE2DMS. */
	RTV_DIMENSION_TEXTURE2DMS = 6,

	/**< enum RTV_DIMENSION_TEXTURE2DMSARRAY. */
	RTV_DIMENSION_TEXTURE2DMSARRAY = 7,

	/**< enum RTV_DIMENSION_TEXTURE3D. */
	RTV_DIMENSION_TEXTURE3D = 8
};

// !An enum.
/*! enum of SWAP_EFFECT values. */
enum SWAP_EFFECT
{
	/**< enum SWAP_EFFECT_DISCARD. */
	SWAP_EFFECT_DISCARD = 0,

	/**< enum SWAP_EFFECT_SEQUENTIAL. */
	SWAP_EFFECT_SEQUENTIAL = 1
};

// !An enum.
/*! enum of MODE_SCANLINE_ORDER values. */
enum MODE_SCANLINE_ORDER
{
	/**< enum MODE_SCANLINE_ORDER_UNSPECIFIED. */
	MODE_SCANLINE_ORDER_UNSPECIFIED = 0,

	/**< enum MODE_SCANLINE_ORDER_PROGRESSIVE. */
	MODE_SCANLINE_ORDER_PROGRESSIVE = 1,

	/**< enum MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST. */
	MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST = 2,

	/**< enum MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST. */
	MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST = 3
};

// !An enum.
/*! enum of MODE_SCALING values. */
enum MODE_SCALING
{
	/**< enum MODE_SCALING_UNSPECIFIED. */
	MODE_SCALING_UNSPECIFIED = 0,

	/**< enum MODE_SCALING_CENTERED. */
	MODE_SCALING_CENTERED = 1,

	/**< enum MODE_SCALING_STRETCHED. */
	MODE_SCALING_STRETCHED = 2
};


// !An enum.
/*! enum of TEXTURE_ADDRESS_MODE values. */
enum TEXTURE_ADDRESS_MODE
{
	/**< enum TEXTURE_ADDRESS_WRAP. */
	TEXTURE_ADDRESS_WRAP = 1,

	/**< enum TEXTURE_ADDRESS_MIRROR. */
	TEXTURE_ADDRESS_MIRROR = 2,

	/**< enum TEXTURE_ADDRESS_CLAMP. */
	TEXTURE_ADDRESS_CLAMP = 3,

	/**< enum TEXTURE_ADDRESS_BORDER. */
	TEXTURE_ADDRESS_BORDER = 4,

	/**< enum TEXTURE_ADDRESS_MIRROR_ONCE. */
	TEXTURE_ADDRESS_MIRROR_ONCE = 5
};


// !An enum.
/*! enum of FILTER values. */
enum FILTER
{
	/**< enum FILTER_MIN_MAG_MIP_POINT. */
	FILTER_MIN_MAG_MIP_POINT = 0,

	/**< enum FILTER_MIN_MAG_POINT_MIP_LINEAR. */
	FILTER_MIN_MAG_POINT_MIP_LINEAR = 0x1,

	/**< enum FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT. */
	FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x4,

	/**< enum FILTER_MIN_POINT_MAG_MIP_LINEAR. */
	FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,

	/**< enum FILTER_MIN_LINEAR_MAG_MIP_POINT. */
	FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,

	/**< enum FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR. */
	FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,

	/**< enum FILTER_MIN_MAG_LINEAR_MIP_POINT. */
	FILTER_MIN_MAG_LINEAR_MIP_POINT = 0x14,

	/**< enum FILTER_MIN_MAG_MIP_LINEAR. */
	FILTER_MIN_MAG_MIP_LINEAR = 0x15,

	/**< enum FILTER_ANISOTROPIC. */
	FILTER_ANISOTROPIC = 0x55,

	/**< enum FILTER_COMPARISON_MIN_MAG_MIP_POINT. */
	FILTER_COMPARISON_MIN_MAG_MIP_POINT = 0x80,

	/**< enum FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR. */
	FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR = 0x81,

	/**< enum FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT. */
	FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x84,

	/**< enum FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR. */
	FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR = 0x85,

	/**< enum FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT. */
	FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT = 0x90,

	/**< enum FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR. */
	FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,

	/**< enum FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT. */
	FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT = 0x94,

	/**< enum FILTER_COMPARISON_MIN_MAG_MIP_LINEAR. */
	FILTER_COMPARISON_MIN_MAG_MIP_LINEAR = 0x95,

	/**< enum FILTER_COMPARISON_ANISOTROPIC. */
	FILTER_COMPARISON_ANISOTROPIC = 0xd5
};

// !An enum.
/*! enum of COMPARISON_FUNC values. */
enum COMPARISON_FUNC
{
	/**< enum COMPARISON_NEVER. */
	COMPARISON_NEVER = 1,

	/**< enum COMPARISON_LESS. */
	COMPARISON_LESS = 2,

	/**< enum COMPARISON_EQUAL. */
	COMPARISON_EQUAL = 3,

	/**< enum COMPARISON_LESS_EQUAL. */
	COMPARISON_LESS_EQUAL = 4,

	/**< enum COMPARISON_GREATER. */
	COMPARISON_GREATER = 5,

	/**< enum COMPARISON_NOT_EQUAL. */
	COMPARISON_NOT_EQUAL = 6,

	/**< enum COMPARISON_GREATER_EQUAL. */
	COMPARISON_GREATER_EQUAL = 7,

	/**< enum COMPARISON_ALWAYS. */
	COMPARISON_ALWAYS = 8
};

// !An enum.
/*! enum of INPUT_CLASSIFICATION values. */
enum INPUT_CLASSIFICATION
{
	/**< enum INPUT_PER_VERTEX_DATA. */
	INPUT_PER_VERTEX_DATA = 0,

	/**< enum INPUT_PER_INSTANCE_DATA. */
	INPUT_PER_INSTANCE_DATA = 1
};

// !An enum.
/*! enum of DRIVER_TYPE values. */
enum DRIVER_TYPE
{
	/**< enum DRIVER_TYPE_UNKNOWN. */
	DRIVER_TYPE_UNKNOWN = 0,

	/**< enum DRIVER_TYPE_HARDWARE. */
	DRIVER_TYPE_HARDWARE = (DRIVER_TYPE_UNKNOWN + 1),

	/**< enum DRIVER_TYPE_REFERENCE. */
	DRIVER_TYPE_REFERENCE = (DRIVER_TYPE_HARDWARE + 1),

	/**< enum DRIVER_TYPE_NULL. */
	DRIVER_TYPE_NULL = (DRIVER_TYPE_REFERENCE + 1),

	/**< enum DRIVER_TYPE_SOFTWARE. */
	DRIVER_TYPE_SOFTWARE = (DRIVER_TYPE_NULL + 1),

	/**< enum DRIVER_TYPE_WARP. */
	DRIVER_TYPE_WARP = (DRIVER_TYPE_SOFTWARE + 1)
};

// !An enum.
/*! enum of BFlags values. */
enum BFlags
{
	/**< enum VERTEX. */
	VERTEX = 0x1L,

	/**< enum INDEX. */
	INDEX = 0x2L,

	/**< enum CONSTANT. */
	CONSTANT = 0x4L,

};


//Estructuras

// !An struct.
/*! struc VIEWPORT. */
struct VIEWPORT
{
	/**< struct float TopLeftX. */
	float TopLeftX;

	/**< struct float TopLeftY. */
	float TopLeftY;

	/**< struct float Width. */
	float Width;

	/**< struct float Height. */
	float Height;

	/**< struct float MinDepth. */
	float MinDepth;

	/**< struct float MaxDepth. */
	float MaxDepth;
};

// !An struct.
/*! struc BUFFER_RTV. */
struct BUFFER_RTV
{
	union
	{
		/**< struct unsigned int firstElement. */
		unsigned int firstElement;

		/**< struct unsigned int elementOffset. */
		unsigned int elementOffset;
	};
	union
	{
		/**< struct unsigned int numElements. */
		unsigned int numElements;

		/**< struct unsigned int elementWidth. */
		unsigned int elementWidth;
	};
};

// !An struct.
/*! struc TEX1D_DSV. */
struct TEX1D_DSV
{
	/**< struct unsigned int mipSlice. */
	unsigned int mipSlice;
};

// !An struct.
/*! struc TEX1D_ARRAY_DSV. */
struct TEX1D_ARRAY_DSV
{
	/**< struct unsigned int mipSlice. */
	unsigned int mipSlice;

	/**< struct unsigned int firstArraySlice. */
	unsigned int firstArraySlice;

	/**< struct unsigned int arraySize. */
	unsigned int arraySize;
};

// !An struct.
/*! struc TEX1D_ARRAY_DSV. */
struct TEX2D_DSV
{
	/**< struct unsigned int mipSlice. */
	unsigned int mipSlice;
};

// !An struct.
/*! struc TEX1D_ARRAY_DSV. */
struct TEX2D_ARRAY_DSV
{
	/**< struct unsigned int mipSlice. */
	unsigned int mipSlice;

	/**< struct unsigned int firstArraySlice. */
	unsigned int firstArraySlice;

	/**< struct unsigned int arraySize. */
	unsigned int arraySize;
};

// !An struct.
/*! struc TEX2DMS_DSV. */
struct TEX2DMS_DSV
{
	/**< struct unsigned int unusedField_NothingToDefine. */
	unsigned int unusedField_NothingToDefine;
};

// !An struct.
/*! struc TEX2DMS_ARRAY_DSV. */
struct TEX2DMS_ARRAY_DSV
{
	/**< struct unsigned int firstArraySize. */
	unsigned int firstArraySize;

	/**< struct unsigned int arraySize. */
	unsigned int arraySize;
};

// !An struct.
/*! struc TEX3D_RTV. */
struct TEX3D_RTV
{
	/**< struct unsigned int mipSlice. */
	unsigned int mipSlice;

	/**< struct unsigned int mipSlice. */
	unsigned int firstWSlice;

	/**< struct unsigned int mipSlice. */
	unsigned int wSize;
};

// !An struct.
/*! struc RATIONAL. */
struct RATIONAL
{
	/**< struct unsigned int Numerator. */
	unsigned int Numerator;

	/**< struct unsigned int Denominator. */
	unsigned int Denominator;
};

// !An struct.
/*! struc MODE_DESC. */
struct MODE_DESC
{
	/**< struct unsigned int Width. */
	unsigned int Width;

	/**< struct unsigned int Height. */
	unsigned int Height;

	/**< struct RATIONAL RefreshRate. */
	RATIONAL RefreshRate;

	/**< struct FORMAT Format. */
	FORMAT Format;

	/**< struct MODE_SCANLINE_ORDER ScanlineOrdering. */
	MODE_SCANLINE_ORDER ScanlineOrdering;

	/**< struct MODE_SCALING Scaling. */
	MODE_SCALING Scaling;
};

// !An struct.
/*! struc SAMPLE_DESC. */
struct SAMPLE_DESC
{
	/**< struct unsigned int Count. */
	unsigned int Count;

	/**< struct unsigned int Quality. */
	unsigned int Quality;
};

// !An struct.
/*! struc SWAP_CHAIN_DESC. */
struct SWAP_CHAIN_DESC
{
	/**< struct MODE_DESC BufferDesc. */
	MODE_DESC BufferDesc;

	/**< struct SAMPLE_DESC SampleDesc. */
	SAMPLE_DESC SampleDesc;

	/**< struct C_USAGE BufferUsage. */
	C_USAGE BufferUsage;

	/**< struct unsigned int BufferCount. */
	unsigned int BufferCount;

	/**< struct unsigned int OutputWindow. */
	unsigned int OutputWindow;

	/**< struct bool Windowed. */
	bool Windowed;

	/**< struct SWAP_EFFECT SwapEffect. */
	SWAP_EFFECT SwapEffect;

	/**< struct unsigned int Flags. */
	unsigned int Flags;
};

// !An struct.
/*! struc SAMPLER_DESC. */
struct SAMPLER_DESC
{

	/**< struct FILTER Filter. */
	FILTER Filter;

	/**< struct TEXTURE_ADDRESS_MODE AddressU. */
	TEXTURE_ADDRESS_MODE AddressU;

	/**< struct TEXTURE_ADDRESS_MODE AddressV. */
	TEXTURE_ADDRESS_MODE AddressV;

	/**< struct TEXTURE_ADDRESS_MODE AddressW. */
	TEXTURE_ADDRESS_MODE AddressW;

	/**< struct float MipLODBias. */
	float MipLODBias;

	/**< struct unsigned int MaxAnisotropy. */
	unsigned int MaxAnisotropy;

	/**< struct COMPARISON_FUNC ComparisonFunc. */
	COMPARISON_FUNC ComparisonFunc;

	/**< struct float BorderColor. */
	float BorderColor[4];

	/**< struct float MinLOD. */
	float MinLOD;

	/**< struct float MaxLOD. */
	float MaxLOD;
};

#endif

// !An struct.
/*! struc SimpleVertex. */
struct SimpleVertex
{
	/**< struct glm::vec3 Pos. */
	glm::vec3 msPos;
	//XMFLOAT3 Pos;


	/**< struct glm::vec2 Tex. */
	glm::vec2 texcoord;


	int IDBone[4];

	float  Weights[4] = { 0.0f };

	//glm::vec3 msNormal;

	//
	////XMFLOAT2 Tex;

	//glm::vec3 msBinormal;

	//glm::vec3 msTangent;


	//unsigned int Index[4];
	//glm::vec4 BoneWeight[4];

};

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

// !An struct.
/*! struc CBChangesEveryFrame. */
struct CBChangesEveryFrame
{
	glm::mat4x4 mWorld;
	glm::vec4 vMeshColor;
	/**< struct glm::mat4x4 mWorld. */
	/**< structglm::vec4 vMeshColor. */
	
	glm::vec4 vViewPos;

	//XMFLOAT4 vMeshColor;
};

struct CBLight
{

	glm::vec4 lightDir;
	glm::vec3 lightPointPos;
	glm::vec4 lightPointAtt;
};

struct CBBones
{
	glm::mat4 Bones_CB[100];
};

