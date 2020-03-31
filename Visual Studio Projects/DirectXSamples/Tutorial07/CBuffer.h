//*****************************************************************************/
/**
* @File CBuffer.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief abstraccion de buffer
* @Bug No kown bug
**/
//****************************************************************************/

/*! \file Define.h
	\brief A Documented file.

	.h where include eneum, struc an other things for class use.
*/
#include "Define.h"

/*! \def D3D11

	definition for use D3D11.
*/
#ifdef D3D11
#include <d3d11.h>
#elif defined (OGL) 

#endif

#include "CDevice.h"
#pragma once

// !An struct.
/*! struc for class buffer. */
struct C_Buffer_DESC
{
	/**< struct unsigned int ByteWidth. */
	unsigned int ByteWidth; 
	
	/**< struct unsigned int BindFlags. */
	unsigned int  BindFlags; 

	/**< struct unsigned int CPUAccessFlags. */
	unsigned int  CPUAccessFlags;

	/**< struct unsigned int MiscFlags. */
	unsigned int  MiscFlags; 

	/**< struct unsigned int StructureByteStride. */
	unsigned int  StructureByteStride; 

#if defined(D3D11)

	/**< struct C_USAGE Usage. */
	C_USAGE		Usage; 
#endif

};

class CBuffer
{
public:
	//! An init.
	/*!
	  init for class buffer.
	  \param _C_DEVICE_DESC an struc of buffer.
	*/
	int init(C_Buffer_DESC& _C_DEVICE_DESC);
	
	void update();
	void detroy();
	void render();

	//! A public variable.
	/*!
	  variable of buffer desc.
	*/
	C_Buffer_DESC  m_Buffer;
	

	//! A public variable.
	/*!
	  variable using direckX:
	  static void createVertexBuffer(int _numvertex, const aiScene* _model, SimpleVertex* _vertex, ID3D11Buffer*& _buffer, void* _dev);
	  static void createIndexBuffer(int numindices, const aiScene* _model, WORD* _index, ID3D11Buffer*& _buffer, void* _dev);
	  D3D11_BUFFER_DESC bd;
	  ID3D11Buffer*   P_Buffer = NULL;.
	*/
#if defined(D3D11)
	static void createVertexBuffer(int _numvertex, const aiScene* _model, SimpleVertex* _vertex, ID3D11Buffer*& _buffer, void* _dev);
	static void createIndexBuffer(int numindices, const aiScene* _model, WORD* _index, ID3D11Buffer*& _buffer, void* _dev);
	D3D11_BUFFER_DESC bd;
	ID3D11Buffer*   P_Buffer = NULL;
	
#endif
	
};


