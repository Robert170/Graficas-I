
//*****************************************************************************/
/**
* @File CDevice.h
* @Author Roberto Ramírez Ontiveros (xc1700@hotmail.com)
* @date  10/02/2020
* @brief implementar camara
* @Bug No kown bug
**/
//****************************************************************************/


#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

#include "CBuffer.h"
#include "includes/gtc/matrix_transform.hpp"
#include "includes/gtx/rotate_vector.hpp"
#include <xnamath.h>



struct CCameraDatas
{
	glm::vec3 Front;
	glm::vec3 Posicion;
	glm::vec3 At;
	glm::vec3 Up; //referencia al mundo
	glm::vec3 Rigth;
	float W;
	float H;
	float Near;
	float Far;
	float Fov;

};

class CCamera
{

	CCameraDatas Data;

	glm::vec3 Up;
	glm::vec3 Front;

	
	glm::mat4 Proyeccion;
	glm::mat4 Ejes;
	glm::mat4 Posicion;

	int limitPitchU = 0;
	int limitPitchD = 0;
	int limitRollU = 0;
	int limitRollD = 0;

public:


	unsigned int Init(CCameraDatas D);
	bool Fpres = false;
	bool GodC = false;
	bool RotF = false;
	glm::vec3 PosIn;
	glm::vec3 PosFn;
	glm::vec3 Dir;

	glm::mat4 View;
	glm::mat4 GetView();
	glm::mat4 GetProyeccion();
	//
	void setWeight(float weight);
	float GetWeight();
	//
	void setHeight(float height);
	float GetHeight();
	//
	void setFar(float F);
	float GetFar();
	//
	void setFov(float FOV);
	float GetFov();
	//
	void setEPosition(glm::vec3 P);
	glm::vec3 GetPosition();
	//
	void setAt(glm::vec3 A);
	glm::vec3 GetAt();
	//
	void setUp(glm::vec3 Up);
	glm::vec3 GetUp();
	//
	void setNear(float N);
	float GetNear();
	//
	void setFront(glm::vec3 At,glm::vec3 Posicion);
	glm::vec3 GetFront();
	//
	void setRight(glm::vec3 up, glm::vec3 Fr	);
	glm::vec3 GetRight();
	//
	void setUpTrue(glm::vec3 Fr, glm::vec3 Ri);



	int UpdateViewMatrix();
	//
	void UpdateProyeccion();
	//
	int Move(WPARAM Traslation);
	//
	void Rotation(WPARAM RotX);
	//
	void Input(WPARAM INPUT);
	void MoveMouse(glm::fvec3 Dir);
	void RotMouse(glm::fvec3 Dir);
	void RotMouseX(glm::fvec3 Dir);
	void RotMouseY(glm::fvec3 Dir);
	void CreateViewMatrix();
	/*CVector3 GetFront();
	CVector3 GetRigth();
	CVector3 GetUpD();*/

	CBuffer		g_pCBNeverChanges;
	CBuffer		g_pCBChangeOnResize;
	
	CBuffer		g_pCBChangesEveryFrame;

	CCamera();
	~CCamera();
};


