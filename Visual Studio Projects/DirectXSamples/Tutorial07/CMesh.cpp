#include "CMesh.h"
//! A constructor.
	/*!
	  function for the class.
	*/
CMesh::CMesh()
{
	m_VertexBuffer = new CBuffer;
	m_Index = new CBuffer;
	m_Materials = new CMaterial;
	m_MeshData.mWorld = {
		1,0,0,0.010,
		0,1,0,0.010,
		0,0,1,0.010,
		0,0,0,1
	};
	m_MeshData.vMeshColor = { 1,0,0,1 };
}

//! A destroyer.
	/*!
	  function for use the destroyer of the class CMesh.
	*/
CMesh::~CMesh()
{
	
}

// !A \fn.
/*!
  function for init m_VertexBuffer and m_Index.
*/
void CMesh::Init()
{
	m_VertexBuffer = new CBuffer;
	m_Index = new CBuffer;
}

// !A \fn.
/*!
  function for update the class.
*/
void CMesh::Update()
{
}

//! An \fn.
	/*!
	  Render for class CMesh.
	  \param _devCont an CDeviceContext.
	  \param _bufferData an CBuffer.
	  \param _dev an CDevice.
	*/
void CMesh::Render(CDeviceContext * _devCont, CBuffer * _bufferData, CDevice * _dev)
{
#if defined(D3D11)
	m_MeshData.mWorld = {
		1,0,0,0.0010,
		0,1,0,0.0010,
		0,0,1,0.0010,
		0,0,0,1
	};
	m_MeshData.vMeshColor = { 1,0,0,1 };
	_devCont->g_pImmediateContext->PSSetShaderResources(0, 1, &m_Materials->m_TexDif);
	_devCont->g_pImmediateContext->VSSetShaderResources(0, 1, &m_Materials->m_TexDif);

	std::string title;
	std::string title2;

	std::stringstream ss;

	ss << "mesh ";
	ss << m_SceneId;
	ss >> title;
	ss >> title2;

	title += " ";
	title += title2;



	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	_devCont->g_pImmediateContext->IASetVertexBuffers
	(0,
		1,//numero de buffers que estamos utilizando
		&m_VertexBuffer->P_Buffer,//puntero a la lista buffers
		&stride,//un uint que indica el tamaño de un unico vertice
		&offset
	);//un uint que indica el numero del byte en el vertice del que se quiere comenzar a pintar


	_devCont->g_pImmediateContext->IASetIndexBuffer
	(
		m_Index->P_Buffer,
		DXGI_FORMAT_R16_UINT,
		0
	);

	//Tipo de topologia
	/*Esta segunda función le dice a Direct3D qué tipo de primitiva se usa.*/
	//_devCont.g_pImmediateContextD3D11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	 //Dibuja el búfer de vértices en el búfer posterior 
	_devCont->g_pImmediateContext->DrawIndexed(m_IndexNum, 0, 0);
	if (m_Children.size() > 0) {}
#endif // D3D11
	
}

//! An \fn.
	/*!
	  funcion for free memory of buffer, like m_VertexBuffer and m_Index.
	  
	*/
void CMesh::Delete()
{
	m_Materials->Shutdown();

	if (m_VertexBuffer != nullptr) {

		m_VertexBuffer->detroy();
		delete m_VertexBuffer;
		m_VertexBuffer = nullptr;
	}
	if (m_Index != nullptr) {

		m_Index->detroy();
		delete m_Index;
		m_Index = nullptr;
	}
	if (m_MyVertex != nullptr) {

		delete m_MyVertex;
		m_MyVertex = nullptr;
	}
}


//! An \fn.
/*!
  AddChildren for class CMesh.
  \param _newChild an CMesh.
*/
void CMesh::AddChildren(CMesh * _newChild)
{
	m_Children.push_back(_newChild);
}


//! An \fn.
	/*!
	  SetParent for class CMesh.
	  \param _parent an CMesh.
	*/
void CMesh::SetParent(CMesh * _parent)
{
	m_Parent = _parent;
}

//! An \fn.
	/*!
	  SetVertex for class CMesh.
	  \param MyVertex an SimpleVertex.
	  \param numVertex an int.
	*/
void CMesh::SetVertex(SimpleVertex * MyVertex, int numVertex)
{
	m_VertexNum = numVertex;
	m_MyVertex = MyVertex;
}

//! An \fn.
	/*!
	  SetIndexList for class CMesh.
	  \param _index an WORD.
	  \param numIndex an int.
	*/
void CMesh::SetIndexList(WORD * _index, int numIndex)
{
	m_MyIndex = _index;
	m_IndexNum = numIndex;
}


