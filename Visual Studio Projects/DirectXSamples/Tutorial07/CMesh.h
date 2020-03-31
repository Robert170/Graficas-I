#pragma once

#include "Define.h"
#include "CBuffer.h"
#include "CDevice.h"
#include "CDeviceContext.h"
#include "CMaterial.h"
#include <vector>

class CMesh
{

public:
	//! A constructor.
	/*!
	  function for use the constructor of the class CMesh.
	*/
	CMesh();

	//! A destroyer.
	/*!
	  function for use the destroyer of the class CMesh.
	*/
	~CMesh();


	//! An init.
	/*!
	  init for class CMesh
	*/
	void Init();

	//! An Update.
	/*!
	  Update for class CMesh
	*/
	void Update();

	//! An Render.
	/*!
	  Render for class CMesh.
	  \param _devCont an CDeviceContext.
	  \param _bufferData an CBuffer.
	  \param _dev an CDevice.
	*/
	void Render(CDeviceContext *_devCont, CBuffer* _bufferData, CDevice* _dev);

	//! An Delete.
	/*!
	  Delete for class CMesh.
	*/
	void Delete();

	//! An AddChildren.
	/*!
	  AddChildren for class CMesh.
	  \param _newChild an CMesh.
	*/
	void AddChildren(CMesh* _newChild);


	//! An SetParent.
	/*!
	  SetParent for class CMesh.
	  \param _parent an CMesh.
	*/
	void SetParent(CMesh* _parent);

	//! An SetVertex.
	/*!
	  SetVertex for class CMesh.
	  \param MyVertex an SimpleVertex.
	  \param numVertex an int.
	*/
	void SetVertex(SimpleVertex* MyVertex, int numVertex);


	//! An SetIndexList.
	/*!
	  SetIndexList for class CMesh.
	  \param _index an WORD.
	  \param numIndex an int.
	*/
	void SetIndexList(WORD* _index, int numIndex);

	//! An GetIndexList.
	/*!
	  GetIndexList for class CMesh, return m_MyIndex.
	  \param SimpleVertex an SimpleVertex.
	  \param numVertex an int.
	*/
	WORD*& GetIndexList(SimpleVertex* SimpleVertex, int numVertex) { return m_MyIndex; };

	//! An GetVertex.
	/*!
	  GetVertex for class CMesh, return m_MyVertex.
	*/
	SimpleVertex* GetVertex() { return m_MyVertex; };

	//! An GetVertexNum.
	/*!
	  GetVertex for class CMesh, return m_VertexNum.
	*/
	int GetVertexNum() { return m_VertexNum; };

	//! An GetIndexNum.
	/*!
	  GetVertex for class CMesh, return m_IndexNum.
	*/
	int GetIndexNum() { return m_IndexNum; };


	//! An GetVertexBuffer.
	/*!
	  GetVertexBuffer for class CMesh, return m_VertexBuffer.
	*/
	CBuffer*& GetVertexBuffer() { return m_VertexBuffer; };
#ifdef D3D11

	//! An SetVertexBuffer.
	/*!
	  SetVertexBuffer for class CMesh, set m_VertexBuffer, only fo D3D11.
	*/
	void SetVertexBuffer(ID3D11Buffer* _pVertexB) { m_VertexBuffer->P_Buffer = _pVertexB; };

	//! An SetIndexBuffer.
	/*!
	  SetIndexBuffer for class CMesh, set m_Index, only fo D3D11.
	*/
	void SetIndexBuffer(ID3D11Buffer* _pIndexB) { m_Index->P_Buffer = _pIndexB; };
#endif // DEBUG


	
	//! An GetIndexBuffer.
	/*!
	  GetIndexBuffer for class CMesh, return m_Index.
	*/
	CBuffer*& GetIndexBuffer() { return m_Index; };

	//! An SetSceneID.
	/*!
	  SetSceneID for class CMesh, set m_SceneId.
	*/
	void SetSceneID(int ID) { m_SceneId = ID; };

	//! An GetSceneID.
	/*!
	  GetSceneID for class CMesh, return m_SceneId.
	*/
	int GetSceneID() { return m_SceneId; };


	//Variables-----

	//! A public variable.
	/*!
	  variable string for the difuse name.
	*/
	std::string		m_DifuceName;

	//! A public variable.
	/*!
	  variable pointer CMaterial for the materials.
	*/
	CMaterial*	m_Materials;

public:
	//Variables-----

	//! A public variable.
	/*!
	  variable pointer CMesh for the Parent.
	*/
	CMesh*				m_Parent;

	//! A public variable.
	/*!
	  variable vector of CMesh for the m_Children.
	*/
	std::vector<CMesh*>	m_Children;

	//! A public variable.
	/*!
	  variable vector4 for the m_Transform.
	*/
	glm::vec4		m_Transform;

	//! A public variable.
	/*!
	  variable pointer CBuffer for the m_VertexBuffer.
	*/
	CBuffer*		m_VertexBuffer = nullptr;

	//! A public variable.
	/*!
	  variable pointer CBuffer for the m_Index.
	*/
	CBuffer*		m_Index = nullptr;

	//! A public variable.
	/*!
	  variable pointer SimpleVertex for the m_MyVertex.
	*/
	SimpleVertex*		m_MyVertex = nullptr;

	//! A public variable.
	/*!
	  variable pointer WORD for the m_MyIndex.
	*/
	WORD*				m_MyIndex = nullptr;

	//! A public variable.
	/*!
	  variable int for the m_VertexNum.
	*/
	int					m_VertexNum = 0;

	//! A public variable.
	/*!
	  variable int for the m_IndexNum.
	*/
	int					m_IndexNum = 0;

	//! A public variable.
	/*!
	  variable int for the m_SceneId.
	*/
	int					m_SceneId = -1;
	
	//! A public variable.
	/*!
	  variable CBChangesEveryFrame for the m_MeshData.
	*/
	CBChangesEveryFrame m_MeshData;
};

