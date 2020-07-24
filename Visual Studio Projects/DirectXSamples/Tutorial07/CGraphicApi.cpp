#include "CGraphicApi.h"

// !A \fn.
/*!
  function for construc the class.
*/
CGraphicApi::CGraphicApi()
{
}

// !A \fn.
/*!
  function for destroy the class.
*/
CGraphicApi::~CGraphicApi()
{
}

//! A \fn.
	/*!
	  function return bool if the mesh was charge, using a model.
	  \param _meshPath an const char.
	  \param _sceneManager an CSceneManager.
	  \param _model an const aiScene.
	  \param _devCont an CDeviceContext.
	  \param _importer an Assimp::Importer.
	  \param _dev an void.
	*/
const aiScene* CGraphicApi::ChargeMesh(const char* _meshPath, CSceneManager* _sceneManager, const aiScene* _model, CDeviceContext* _devCont, void* _dev, Assimp::Importer* Imp)
{

	_model = Imp->ReadFile
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
	return _model;
}

void CGraphicApi::BonesTrasnformation(float Time, std::vector<glm::mat4>& Transform, const aiScene * _model, CSceneManager * _sceneManager)
{
	glm::mat4 Ident = glm::mat4(1.0f);

	unsigned int  AllBones = 0;

	for (int i = 0; i < _sceneManager->m_MeshInScene.size(); i++)
	{
		AllBones = AllBones + _sceneManager->m_MeshInScene.at(i)->m_NumBones;
	}

	float TicksPerSecond = _model->mAnimations[0]->mTicksPerSecond != 0 ? _model->mAnimations[0]->mTicksPerSecond : 25.0f;

	float TimeInTicks = Time * TicksPerSecond;
	float AnimationTime = fmod(TimeInTicks, _model->mAnimations[0]->mDuration);

	for (int i = 0; i < _sceneManager->m_MeshInScene.size(); i++)
	{
		JerarquiaDeNodo(AnimationTime, _model->mRootNode, glm::mat4(1.0f), _model, _sceneManager->m_MeshInScene[i]);
	}

	Transform.resize(AllBones);

	for (int i = 0; i < AllBones; i++)
	{
		for (int j = 0; j < _sceneManager->m_MeshInScene.size(); j++)
		{
			for (int k = 0; k < _sceneManager->m_MeshInScene[j]->m_BoneInfo.size(); k++)
			{
				Transform[i] = _sceneManager->m_MeshInScene[j]->m_BoneInfo[k].Final_Transformation;
				i++;
			}
		}
	}

}

//! A \fn.
	/*!
	  function for the caracteristics of mesh like indices, vertex.
	  \param _model an const aiScene.
	  \param _mesh an CMesh.
	  \param _meshIndex an int.
	  \param _dev an void.
	*/
void CGraphicApi::MeshRead(const aiScene * _model, CMesh * _mesh, int _meshIndex, void * _dev)
{
	std::vector <std::uint32_t> indis;
	indis.reserve(_model->mMeshes[_meshIndex]->mNumFaces * 3);
	int numVertex = _model->mMeshes[_meshIndex]->mNumVertices;
	int numVIndex = (_model->mMeshes[_meshIndex]->mNumFaces * 3);
	int NumBones = (_model->mMeshes[_meshIndex]->mNumBones);
	_mesh->m_vBonesPerVertx.resize(numVertex);

	SimpleVertex* meshVertex = new SimpleVertex[numVertex];
	WORD* meshIndex = new WORD[numVIndex];

	for (int i = 0; i < NumBones; i++)
	{
		//obtener nombre del hueso en base al mesh
		int BoneIndex = 0;
		std::string BoneName(_model->mMeshes[_meshIndex]->mBones[i]->mName.data);

		//revisar si el mesh tiene el hueso, si esta indice
		if (_mesh->m_BoneMapping.find(BoneName) == _mesh->m_BoneMapping.end())
		{
			BoneIndex = _mesh->m_NumBones;
			_mesh->m_NumBones++;
			BONES_INFO bi;
			_mesh->m_BoneInfo.push_back(bi);
		}
		//si no tine lo agrega
		else
		{
			BoneIndex = _mesh->m_BoneMapping[BoneName];
		}

		_mesh->m_BoneMapping[BoneName] = BoneIndex;
		_mesh->m_BoneInfo[BoneIndex].Bone_Offset = glm::transpose(glm::make_mat4(&_model->mMeshes[_meshIndex]->mBones[i]->mOffsetMatrix.a1));

		for (int j = 0; j < _model->mMeshes[_meshIndex]->mBones[i]->mNumWeights; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				meshVertex[_model->mMeshes[_meshIndex]->mBones[i]->mWeights[j].mVertexId].IDBone[k] = BoneIndex;
				meshVertex[_model->mMeshes[_meshIndex]->mBones[i]->mWeights[j].mVertexId].Weights[k] = _model->mMeshes[_meshIndex]->mBones[i]->mWeights[j].mWeight;
			}
		}
	}

	
	for (std::uint32_t faceIdx = 0u; faceIdx < _model->mMeshes[_meshIndex]->mNumFaces; faceIdx++)
	{
		indis.push_back(_model->mMeshes[_meshIndex]->mFaces[faceIdx].mIndices[0u]);
		indis.push_back(_model->mMeshes[_meshIndex]->mFaces[faceIdx].mIndices[1u]);
		indis.push_back(_model->mMeshes[_meshIndex]->mFaces[faceIdx].mIndices[2u]);
	}

	

	for (int i = 0; i < numVertex; i++)
	{
		meshVertex[i].msPos.x = _model->mMeshes[_meshIndex]->mVertices[i].x;
		meshVertex[i].msPos.y = _model->mMeshes[_meshIndex]->mVertices[i].y;
		meshVertex[i].msPos.z = _model->mMeshes[_meshIndex]->mVertices[i].z;

	/*	meshVertex[i].msNormal.x = _model->mMeshes[_meshIndex]->mNormals[i].x;
		meshVertex[i].msNormal.y = _model->mMeshes[_meshIndex]->mNormals[i].y;
		meshVertex[i].msNormal.z = _model->mMeshes[_meshIndex]->mNormals[i].z;*/

		meshVertex[i].texcoord.x = _model->mMeshes[_meshIndex]->mTextureCoords[0][i].x;
		meshVertex[i].texcoord.y = _model->mMeshes[_meshIndex]->mTextureCoords[0][i].y;

		/*meshVertex[i].msBinormal.x = _model->mMeshes[_meshIndex]->mBitangents[i].x;
		meshVertex[i].msBinormal.y = _model->mMeshes[_meshIndex]->mBitangents[i].y;
		meshVertex[i].msBinormal.z = _model->mMeshes[_meshIndex]->mBitangents[i].z;

		meshVertex[i].msTangent.x = _model->mMeshes[_meshIndex]->mTangents[i].x;
		meshVertex[i].msTangent.y = _model->mMeshes[_meshIndex]->mTangents[i].y;
		meshVertex[i].msTangent.z = _model->mMeshes[_meshIndex]->mTangents[i].z;*/
		
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

//! A \fn.
	/*!
	  function for search and read texture of model.
	  \param _model an const aiScene.
	  \param _mesh an CMesh.
	  \param _meshIndex an int.
	  \param _dev an void.
	*/
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

const aiNodeAnim * CGraphicApi::AnimatinFindNode(const std::string NameNod, const aiAnimation * Anim)
{
	for (int i = 0; i < Anim->mNumChannels; i++)
	{
		const aiNodeAnim * Temp = Anim->mChannels[i];
		if (std::string(Temp->mNodeName.data) == NameNod)
		{
			return Temp;
		}
	}

	return nullptr;
}

void CGraphicApi::JerarquiaDeNodo(float TimeAnim, const aiNode * Node, const glm::mat4 Transform, const aiScene* Model, CMesh * _mesh)
{
	std::string NameNod(Node->mName.data);
	const aiAnimation * Animation = Model->mAnimations[0];


	glm::mat4 glmTransform = glm::transpose(glm::make_mat4(&Node->mTransformation.a1));

	const aiNodeAnim *animNode = AnimatinFindNode(NameNod, Animation);

	//aiMatrix4x4 _Transform = Node->mTransformation;
	//const aiNodeAnim * NodeAnim = AnimatinFindNode(NameNod, Animation);
	//aiMatrix4x4 TransNod = Node->mTransformation;
	//aiMatrix4x4 TransGlobal = Transform * TransNod;

	if (animNode)
	{
		//scale
		aiVector3D Scaling;
		CalcInterpolatedScaling(Scaling, TimeAnim, animNode);
		glm::mat4 ScalingM = glm::mat4(1.0f);

		glm::vec3 ScalingGLM(Scaling.x, Scaling.y, Scaling.z);
		glm::scale(ScalingM, ScalingGLM);

		//rotation
		aiQuaternion RotationQ;
		CalcInterpolatedRotation(RotationQ, TimeAnim, animNode);
		glm::quat RotationQGLM(RotationQ.w, RotationQ.x, RotationQ.y, RotationQ.z);
		glm::mat4 RotationM = glm::toMat4(RotationQGLM);

		//traslation
		aiVector3D Traslation;
		CalcInterpolatedPosition(Traslation, TimeAnim, animNode);
		glm::mat4 TraslationM = glm::mat4(1.f);
		TraslationM[3][0] = Traslation.x;
		TraslationM[3][1] = Traslation.y;
		TraslationM[3][2] = Traslation.z;

		//make final transform
		glmTransform = TraslationM * RotationM * ScalingM;
	}

	glm::mat4 GlobalTransform = Transform * glmTransform;

	if (_mesh->m_BoneMapping.find(NameNod) != _mesh->m_BoneMapping.end())
	{
		unsigned int BoneIndex = _mesh->m_BoneMapping[NameNod];
		_mesh->m_BoneInfo[BoneIndex].Final_Transformation = GlobalTransform * _mesh->m_BoneInfo[BoneIndex].Bone_Offset;
	}

	for (int i = 0; i < Node->mNumChildren; i++)
	{
		JerarquiaDeNodo(TimeAnim, Node->mChildren[i], GlobalTransform, Model, _mesh);
	}
}

int CGraphicApi::FindPosition(float AnimationTime, const aiNodeAnim * pNodeAnim)
{
	for (int i = 0; i < pNodeAnim->mNumPositionKeys-1; i++)
	{
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i+1].mTime)
		{
			return i;
		}

	}
	assert(0);
	return 0;
}

int CGraphicApi::FindRotation(float AnimationTime, const aiNodeAnim * pNodeAnim)
{
	assert(pNodeAnim->mNumRotationKeys > 0);

	for (int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
	{
		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i+1].mTime)
		{
			return i;
		}
	}
	assert(0);
	return 0;
}

int CGraphicApi::FindScaling(float AnimationTime, const aiNodeAnim * pNodeAnim)
{
	assert(pNodeAnim->mNumScalingKeys > 0);

	for (int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
	{
		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime)
		{
			return i;
		}
	}
	assert(0);
	return 0;
}

void CGraphicApi::CalcInterpolatedPosition(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1) {
		Out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}

	unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
	unsigned int NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}

void CGraphicApi::CalcInterpolatedRotation(aiQuaternion & Out, float AnimationTime, const aiNodeAnim * pNodeAnim)
{
	if (pNodeAnim->mNumRotationKeys == 1) {
		Out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
	unsigned int NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
	Out = Out.Normalize();
}

void CGraphicApi::CalcInterpolatedScaling(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1) {
		Out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
	unsigned int NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}
