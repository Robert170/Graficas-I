#pragma once
#include "Define.h"

#include "CDeviceContext.h"
#include "CDevice.h"
#include <string>
#include "CMesh.h"
#include "CSceneManager.h"

class CGraphicApi
{
public:
	CGraphicApi();
	~CGraphicApi();

	const aiScene* m_Model = new const aiScene();
	Assimp::Importer* m_Importer = new Assimp::Importer();

	bool
		ChargeMesh(const char* _meshPath, CSceneManager* _sceneManager, const aiScene* _model, CDeviceContext* _devCont, Assimp::Importer* _importer, void* _dev);

private:
	void
		MeshRead(const aiScene* _model, CMesh* _mesh, int _meshIndex, void* _dev);

	void
		ReadTextureMesh(const aiScene* _model, CMesh* _mesh, int _meshIndex, void* _dev);
};

