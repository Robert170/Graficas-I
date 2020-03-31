//*****************************************************************************/
/**
* @File CCamera.h
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



// !An struct.
/*! struc for class CCamera. */
struct CCameraDatas
{
	/**< struct glm::vec3 Front. */
	glm::vec3 Front;  

	/**< struct glm::vec3 Posicion. */
	glm::vec3 Posicion; 

	/**< struct glm::vec3 At. */
	glm::vec3 At;

	/**< struct glm::vec3 Up. */
	glm::vec3 Up; 

	/**< struct glm::vec3 Rigth. */
	glm::vec3 Rigth;  

	/**< struct float W. */
	float W; 

	/**< struct float H. */
	float H; 

	/**< struct float Near. */
	float Near;  

	/**< struct float Far. */
	float Far;  

	/**< struct float Fov. */
	float Fov; 

};


class CCamera
{
	//! A private variable.
	/*!
	  variable for use the struc CCameraDatas.
	*/
	CCameraDatas Data;

	//! A private variable.
	/*!
	  variable for use the glm::vec3 Up.
	*/
	glm::vec3 Up;

	//! A private variable.
	/*!
	  variable for use the glm::vec3 Front.
	*/
	glm::vec3 Front;

	//! A private variable.
	/*!
	  variable for use the glm::mat4 Proyeccion.
	*/
	glm::mat4 Proyeccion;

	//! A private variable.
	/*!
	  variable for use the glm::mat4 Ejes.
	*/
	glm::mat4 Ejes;

	//! A private variable.
	/*!
	  variable for use the glm::mat4 Posicion.
	*/
	glm::mat4 Posicion;

	//! A private variable.
	/*!
	  variable for use the int limitPitchU.
	*/
	int limitPitchU = 0;

	//! A private variable.
	/*!
	  variable for use the int limitPitchD.
	*/
	int limitPitchD = 0;

	//! A private variable.
	/*!
	  variable for use the int limitRollU.
	*/
	int limitRollU = 0;

	//! A private variable.
	/*!
	  variable for use the int limitRollD.
	*/
	int limitRollD = 0;

public:

	//! An init.
	/*!
	  init for class buffer.
	  \param D an struc of CCameraDatas.
	*/
	unsigned int Init(CCameraDatas D);

	//! A public variable.
	/*!
	  variable for know if is pressed.
	*/
	bool Fpres = false;

	//! A public variable.
	/*!
	  variable for know if god cam is active.
	*/
	bool GodC = false;

	//! A public variable.
	/*!
	  variable for know if rotation is able.
	*/
	bool RotF = false;

	//! A public variable.
	/*!
	  variable glm::vec3 for init position.
	*/
	glm::vec3 PosIn;

	//! A public variable.
	/*!
	  variable glm::vec3 for final position.
	*/
	glm::vec3 PosFn;

	//! A public variable.
	/*!
	  variable glm::vec3 for direcction of mouse.
	*/
	glm::vec3 Dir;

	//! A public variable.
	/*!
	  variable glm::mat4 for view matrix.
	*/
	glm::mat4 View;

	//! A public function.
	/*!
	  function return glm::mat4 the view matrix.
	*/
	glm::mat4 GetView();


	//! A public function.
	/*!
	  function return glm::mat4 the projection matrix.
	*/
	glm::mat4 GetProyeccion();
	

	//! A public function.
	/*!
	  function set the variable Weight.
	  \param weight an float.
	*/
	void setWeight(float weight);

	//! A public function.
	/*!
	  function return float the varaiable Weight.
	*/
	float GetWeight();
	

	//! A public function.
	/*!
	  function set the variable Height.
	   \param Height an float.
	*/
	void setHeight(float height);

	//! A public function.
	/*!
	  function return float the varaiable Height.
	*/
	float GetHeight();
	

	//! A public function.
	/*!
	  function set the variable Far.
	  \param F an float.
	*/
	void setFar(float F);

	//! A public function.
	/*!
	  function return float the varaiable Far.
	*/
	float GetFar();
	

	//! A public function.
	/*!
	  function set the variable Fov.
	  \param F an float.
	*/
	void setFov(float FOV);

	//! A public function.
	/*!
	  function return float the varaiable Fov.
	*/
	float GetFov();
	

	//! A public function.
	/*!
	  function set the variable Position.
	  \param P an glm::vec3.
	*/
	void setEPosition(glm::vec3 P);

	//! A public function.
	/*!
	  function return glm::vec3 the varaiable Position.
	*/
	glm::vec3 GetPosition();
	

	//! A public function.
	/*!
	  function set the variable Position.
	  \param A an glm::vec3.
	*/
	void setAt(glm::vec3 A);

	//! A public function.
	/*!
	  function return glm::vec3 the varaiable At.
	*/
	glm::vec3 GetAt();
	

	//! A public function.
	/*!
	  function set the variable Position.
	  \param Up an glm::vec3.
	*/
	void setUp(glm::vec3 Up);

	//! A public function.
	/*!
	  function return glm::vec3 the varaiable Up.
	*/
	glm::vec3 GetUp();
	

	//! A public function.
	/*!
	  function set the variable Fov.
	  \param N an float.
	*/
	void setNear(float N);

	//! A public function.
	/*!
	  function return float the varaiable Near.
	*/
	float GetNear();
	

	//! A public function.
	/*!
	  function set the variable Front.
	  \param At an glm::vec3.
	  \param Posicion an glm::vec3.
	*/
	void setFront(glm::vec3 At,glm::vec3 Posicion);

	//! A public function.
	/*!
	  function return glm::vec3 the varaiable Front.
	*/
	glm::vec3 GetFront();
	

	//! A public function.
	/*!
	  function set the variable Right.
	  \param Up an glm::vec3.
	  \param Fr an glm::vec3.
	*/
	void setRight(glm::vec3 up, glm::vec3 Fr	);

	//! A public function.
	/*!
	  function return glm::vec3 the varaiable Rigth.
	*/
	glm::vec3 GetRight();
	

	//! A public function.
	/*!
	  function set the variable Up.
	  \param Up an glm::vec3.
	  \param Fr an glm::vec3.
	*/
	void setUpTrue(glm::vec3 Fr, glm::vec3 Ri);


	//! A public variable.
	/*!
	  variable for know the MovementSpeed of the camera.
	*/
	float MovementSpeed = 2.5F;

	//! A public function.
	/*!
	  function update de view matrix.
	*/
	int UpdateViewMatrix();
	

	//! A public function.
	/*!
	  function update de proyeccion matrix.
	*/
	void UpdateProyeccion();
	

	//! A public function.
	/*!
	  function for move camera.
	  \param Traslation an WPARAM.
	*/
	int Move(WPARAM Traslation);
	

	//! A public function.
	/*!
	  function for rotate camera.
	  \param RotX an WPARAM.
	*/
	void Rotation(WPARAM RotX);
	

	//! A public function.
	/*!
	  function for detect the input.
	  \param INPUT an WPARAM.
	*/
	void Input(WPARAM INPUT);

	//! A public function.
	/*!
	  function for move the mouse.
	  \param Dir an glm::fvec3.
	*/
	void MoveMouse(glm::fvec3 Dir);

	//! A public function.
	/*!
	  function for call the rotation of the mouse.
	  \param Dir an glm::fvec3.
	*/
	void RotMouse(glm::fvec3 Dir);

	//! A public function.
	/*!
	  function for rotate the mouse in x.
	  \param Dir an glm::fvec3.
	*/
	void RotMouseX(glm::fvec3 Dir);

	//! A public function.
	/*!
	  function for rotate the mouse in y.
	  \param Dir an glm::fvec3.
	*/
	void RotMouseY(glm::fvec3 Dir);

	//! A public function.
	/*!
	  function for create the view matrix.
	*/
	void CreateViewMatrix();


	//! A public variable.
	/*!
	  variable for use the buffer whit name g_pCBNeverChanges.
	*/
	CBuffer		g_pCBNeverChanges;

	//! A public variable.
	/*!
	  variable for use the buffer whit name g_pCBChangeOnResize.
	*/
	CBuffer		g_pCBChangeOnResize;
	
	//! A public variable.
	/*!
	  variable for use the buffer whit name g_pCBChangesEveryFrame.
	*/
	CBuffer		g_pCBChangesEveryFrame;

	//! A constructor.
	/*!
	  A constructor for class CCamera.
	*/
	CCamera();

	//! A destructor.
	/*!
	  A destructor for class CCamera.
	*/
	~CCamera();

};


