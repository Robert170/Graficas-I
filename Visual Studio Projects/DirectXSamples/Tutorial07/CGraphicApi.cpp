#include "CGraphicApi.h"

CGraphicApi::CGraphicApi()
{
}

CGraphicApi::~CGraphicApi()
{
}

bool CGraphicApi::ChargeMesh(const char * _meshPath, CSceneManager * _sceneManager, const aiScene * _model, CDeviceContext *_devCont, Assimp::Importer * _importer, void * _dev)
{

	_model = _importer->ReadFile
	(_meshPath,
		aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded |
		aiProcess_FindInstances |
		aiProcess_ValidateDataStructure |
		aiProcess_OptimizeMeshes |
		aiProcess_Debone |
		0);
	if (_model == nullptr) {

		std::string toAdvice = "\nCouldn't find the object in the direcction:\n";
		toAdvice += _meshPath;
		return false;
	}

	CMesh* newmesh = new CMesh;
	char* token = NULL;
	char* nextToken = NULL;
	std::string path = _meshPath;

	token = strtok_s((char*)path.c_str(), "/", &nextToken);

	std::string teturesFolder = token;
	teturesFolder += "\\";
	token = (char*)teturesFolder.c_str();
	newmesh->m_Materials->m_Diroftextures = token;

	std::string dirName = newmesh->m_Materials->m_Diroftextures;

	MeshRead(_model, newmesh, 0, _dev);
	ReadTextureMesh(_model, newmesh, 0, _dev);
	_sceneManager->AddMesh(newmesh);

	if (_model->mNumMeshes > 1) {

		for (unsigned int i = 1; i < _model->mNumMeshes; i += (unsigned int)1) {

			CMesh* childmesh = new CMesh;
			childmesh->SetParent(newmesh);
			newmesh->AddChildren(childmesh);
			childmesh->m_Materials->m_Diroftextures = dirName;
			MeshRead(_model, childmesh, i, _dev);
			ReadTextureMesh(_model, childmesh, i, _dev);
			_sceneManager->AddMesh(childmesh);
		}
	}
	return true;
}

void CGraphicApi::MeshRead(const aiScene * _model, CMesh * _mesh, int _meshIndex, void * _dev)
{
	std::vector <std::uint32_t> indis;
	indis.reserve(_model->mMeshes[_meshIndex]->mNumFaces * 3);
	int numVertex = _model->mMeshes[_meshIndex]->mNumVertices;
	int numVIndex = (_model->mMeshes[_meshIndex]->mNumFaces * 3);
	for (std::uint32_t faceIdx = 0u; faceIdx < _model->mMeshes[_meshIndex]->mNumFaces; faceIdx++)
	{
		indis.push_back(_model->mMeshes[_meshIndex]->mFaces[faceIdx].mIndices[0u]);
		indis.push_back(_model->mMeshes[_meshIndex]->mFaces[faceIdx].mIndices[1u]);
		indis.push_back(_model->mMeshes[_meshIndex]->mFaces[faceIdx].mIndices[2u]);
	}

	SimpleVertex* meshVertex = new SimpleVertex[numVertex];
	WORD* meshIndex = new WORD[numVIndex];

	for (int i = 0; i < numVertex; i++)
	{
		meshVertex[i].Pos.x = _model->mMeshes[_meshIndex]->mVertices[i].x;
		meshVertex[i].Pos.y = _model->mMeshes[_meshIndex]->mVertices[i].y;
		meshVertex[i].Pos.z = _model->mMeshes[_meshIndex]->mVertices[i].z;
		meshVertex[i].Tex.x = _model->mMeshes[_meshIndex]->mTextureCoords[0][i].x;
		meshVertex[i].Tex.y = _model->mMeshes[_meshIndex]->mTextureCoords[0][i].y;
	}
	_mesh->SetVertex(meshVertex, numVertex);
#ifdef D3D11
	CBuffer::createVertexBuffer(numVertex, _model, meshVertex, _mesh->GetVertexBuffer()->P_Buffer, _dev);
#endif // D3D11

	

	for (int i = 0; i < numVIndex; i++)
	{
		meshIndex[i] = (WORD)indis[i];
	}
	_mesh->SetIndexList(meshIndex, numVIndex);
#ifdef D3D11
	CBuffer::createIndexBuffer(numVIndex, _model, meshIndex, _mesh->GetIndexBuffer()->P_Buffer, _dev);
#endif // D3D11

	
}

void CGraphicApi::ReadTextureMesh(const aiScene * _model, CMesh * _mesh, int _meshIndex, void * _dev)
{
	const aiMaterial* pMaterial = _model->mMaterials[_model->mMeshes[_meshIndex]->mMaterialIndex];

	//Difuse texture
	if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		aiString Path;
		_mesh->m_Materials->m_HasDifuse = true;
		if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
		{
			_mesh->m_Materials->m_DifuseName = _mesh->m_Materials->m_Diroftextures;
			_mesh->m_Materials->m_DifuseName += (std::string) Path.data;
			wchar_t wtext[50];
			char* token = NULL;
			char* nextToken = NULL;
			token = strtok_s((char*)_mesh->m_Materials->m_DifuseName.c_str(), ".", &nextToken);
			std::string pngextencion = token;
			pngextencion += ".png";
			token = (char*)pngextencion.c_str();

			LPCSTR direcTextur = token;
			LPCWSTR dir = (LPCWSTR)pngextencion.c_str();


			int stringLength = MultiByteToWideChar(CP_ACP, 0, pngextencion.data(), pngextencion.length(), 0, 0);
			std::wstring wstr(stringLength, 0);
			MultiByteToWideChar(CP_ACP, 0, pngextencion.data(), pngextencion.length(), &wstr[0], stringLength);
			dir = (LPCWSTR)wstr.c_str();
			//ID3D11Device* dev = static_cast<ID3D11Device*>(_dev);
#ifdef D3D11
			D3DX11CreateShaderResourceViewFromFile(static_cast<ID3D11Device*>(_dev), dir, NULL, NULL, &_mesh->m_Materials->m_TexDif, NULL);
#endif // DEBUG

			
		}
	}
}
