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
	CMesh();
	~CMesh();

	void Init();

	void Update();

	void Render(CDeviceContext *_devCont, CBuffer* _bufferData, CDevice* _dev);

	void Delete();

	void AddChildren(CMesh* _newChild);

	void SetParent(CMesh* _parent);

	void SetVertex(SimpleVertex* MyVertex, int numVertex);

	void SetIndexList(WORD* _index, int numIndex);

	WORD*& GetIndexList(SimpleVertex* MyVertex, int numVertex) { return m_MyIndex; };

	SimpleVertex* GetVertex() { return m_MyVertex; };

	int GetVertexNum() { return m_VertexNum; };

	int GetIndexNum() { return m_IndexNum; };

	CBuffer*& GetVertexBuffer() { return m_VertexBuffer; };
#ifdef D3D11
	void SetVertexBuffer(ID3D11Buffer* _pVertexB) { m_VertexBuffer->P_Buffer = _pVertexB; };

	void SetIndexBuffer(ID3D11Buffer* _pIndexB) { m_Index->P_Buffer = _pIndexB; };
#endif // DEBUG


	

	CBuffer*& GetIndexBuffer() { return m_Index; };


	void SetSceneID(int ID) { m_SceneId = ID; };

	int GetSceneID() { return m_SceneId; };


	//Variables-----
	std::string		m_DifuceName;
	CMaterial*	m_Materials;

public:
	//Variables-----
	CMesh*				m_Parent;
	std::vector<CMesh*>	m_Children;
	glm::vec4		m_Transform;
	CBuffer*		m_VertexBuffer = nullptr;
	CBuffer*		m_Index = nullptr;
	SimpleVertex*		m_MyVertex = nullptr;
	WORD*				m_MyIndex = nullptr;
	int					m_VertexNum = 0;
	int					m_IndexNum = 0;
	int					m_SceneId = -1;
	
	CBChangesEveryFrame m_MeshData;
};

