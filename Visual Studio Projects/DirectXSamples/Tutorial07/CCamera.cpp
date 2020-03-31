#include "CCamera.h"
#include "../Tutorial07/includes/mat4x4.hpp"


//! An \fn.
	/*!
	  init for class CCamera, init all members of the struc, create and update the view matrix
	  \param CCameraDatas an struc of Ccamera.
	*/
unsigned int CCamera::Init(CCameraDatas D)
{
	setEPosition (D.Posicion);
	setAt(D.At);
	setUp(D.Up); //referencia al mundo
	setFov(D.Fov);
	setWeight(D.W);
	setHeight(D.H);
	setNear(D.Near);
	setFar(D.Far);
	setFront(D.At, D.Posicion);
	setRight(Data.Up, Data.Front);
	setUpTrue(Data.Front, Data.Rigth);
	

	
	CreateViewMatrix();
	UpdateViewMatrix();
	UpdateProyeccion();
	return 0;
}



//! An \fn.
	/*!
	  constructor of the class CCamera, set all members of the struc in 0.
	*/
CCamera::CCamera()
{
	Data.Front = { 0,0,0 };
	Data.Posicion = { 0,0,0 };
	Data.At = { 0,0,0 };
	Data.Up = { 0,0,0 }; //referencia al mundo
	Data.Rigth = { 0,0,0 };
	Data.W = 0;
	Data.H = 0;
	Data.Near = 0;
	Data.Far = 0;
	Data.Fov = 0;
	Up = { 0, 0, 0 };
}

//! An \fn.
	/*!
	  destructor of the class CCamera.
	*/
CCamera::~CCamera()
{
}

//! A \fn.
	/*!
	  function return glm::mat4 the view matrix.
	*/
glm::mat4 CCamera::GetView()
{
	return View;
}

//! A \fn.
	/*!
	  function return glm::mat4 the view Proyeccion.
	*/
glm::mat4 CCamera::GetProyeccion()
{
	return Proyeccion;
}

//! A \fn.
	/*!
	  function set the variable Weight.
	  \param weight an float.
	*/
void CCamera::setWeight(float weight)
{
	Data.W = weight;
}

//! A \fn.
	/*!
	  function return float the varaiable Weight.
	*/
float CCamera::GetWeight()
{
	return Data.W;
}



//! A \fn.
	/*!
	  function set the variable Height.
	  \param Height an float.
	*/
void CCamera::setHeight(float height)
{
	Data.H = height;
}


//! A \fn.
	/*!
	  function return float the varaiable Height.
	*/
float CCamera::GetHeight()
{
	return Data.H;
}

//! A \fn.
	/*!
	  function set the variable Far.
	  \param F an float.
	*/
void CCamera::setFar(float F)
{
	Data.Far = F;
}

//! A \fn.
	/*!
	  function return float the varaiable Far.
	*/
float CCamera::GetFar()
{
	return Data.Far;
}


//! A \fn.
	/*!
	  function set the variable Fov.
	  \param F an float.
	*/
void CCamera::setFov(float FOV)
{
	Data.Fov = FOV;
}


//! A \fn.
	/*!
	  function return float the varaiable Fov.
	*/
float CCamera::GetFov()
{
	return Data.Fov;
}


//! A \fn.
	/*!
	  function set the variable Position.
	  \param P an glm::vec3.
	*/
void CCamera::setEPosition(glm::vec3 P)
{
	Data.Posicion = P;
}



//! A \fn.
/*!
  function return glm::vec3 the varaiable Position.
*/
glm::vec3 CCamera::GetPosition()
{
	return Data.Posicion;
}


//! A \fn.
	/*!
	  function set the variable Position.
	  \param A an glm::vec3.
	*/
void CCamera::setAt(glm::vec3 A)
{
	Data.At = A;
}


//! A \fn.
	/*!
	  function return glm::vec3 the varaiable At.
	*/
glm::vec3 CCamera::GetAt()
{
	return Data.At;
}


//! A \fn.
	/*!
	  function set the variable Position.
	  \param Up an glm::vec3.
	*/
void CCamera::setUp(glm::vec3 Up)
{
	Data.Up = Up;
}


//! A \fn.
	/*!
	  function return glm::vec3 the varaiable Up.
	*/
glm::vec3 CCamera::GetUp()
{
	return Data.Up;
}


//! A \fn.
	/*!
	  function set the variable Fov.
	  \param N an float.
	*/
void CCamera::setNear(float N)
{
	Data.Near = N;
}


//! A \fn.
	/*!
	  function return float the varaiable Near.
	*/
float CCamera::GetNear()
{
	return Data.Near;
}


//! A \fn.
	/*!
	  function set the variable Front.
	  \param At an glm::vec3.
	  \param Posicion an glm::vec3.
	*/
void CCamera::setFront(glm::vec3 At, glm::vec3 Pos)
{
	Data.Front = glm::normalize(At-Pos);
	Front= glm::normalize(At - Pos);
}


//! A \fn.
	/*!
	  function return glm::vec3 the varaiable Front.
	*/
glm::vec3 CCamera::GetFront()
{
	return Data.Front;
}


//! A \fn.
	/*!
	  function set the variable Right.
	  \param Up an glm::vec3.
	  \param Fr an glm::vec3.
	*/
void CCamera::setRight(glm::vec3 Up, glm::vec3 Fr)
{
	Data.Rigth = glm::normalize(glm::cross(Up, Fr));
}


//! A \fn.
	/*!
	  function return glm::vec3 the varaiable Rigth.
	*/
glm::vec3 CCamera::GetRight()
{
	return Data.Rigth;
}


//! A \fn.
	/*!
	  function set the variable up.
	  \param Up an glm::vec3.
	  \param Fr an glm::vec3.
	*/
void CCamera::setUpTrue(glm::vec3 Fr, glm::vec3 Ri)
{
	Up = glm::normalize(glm::cross(Fr, Ri));
}


//! A \fn.
	/*!
	  function update de view matrix, with rigth, Up, Front and At.
	*/
int CCamera::UpdateViewMatrix()
{
	Data.Rigth = { View[0][0],  View[0][1], View[0][2] };
	Data.Up = { View[1][0],View[1][1],View[1][2] };
	Up = Data.Up;
	//Front = { View[2][0],View[2][1],View[2][2] };
	Data.Front = { View[2][0],View[2][1],View[2][2] };
	Data.At = GetFront() + GetPosition();
	return 0;
}


//! A \fn.
	/*!
	  function update de proyeccion matrix with Fov, Weight, Heigth, Near and Far.
	*/
void CCamera::UpdateProyeccion()
{
	Proyeccion = glm::perspectiveFovLH(Data.Fov, Data.W, Data.H, Data.Near, Data.Far);
	Proyeccion = glm::transpose(Proyeccion);
}


//! A \fn.
	/*!
	  function for move camera with the input and update the view matrix.
	  \param Traslation an WPARAM.
	*/
int CCamera::Move(WPARAM Traslation)
{
	if (Traslation == 'w' || Traslation == 'W')
	{
		//if (GodC == true)
		//{
			Data.Posicion += Data.Front;
		//}
		//else
		//{
		//	Data.Posicion += Front;
		//}
	}
	else if (Traslation == 'a' || Traslation == 'A')
	{
		Data.Posicion -= Data.Rigth;
	}
	else if (Traslation == 's' || Traslation == 'S')
	{
		//if (GodC == true)
		//{
			Data.Posicion -= Data.Front;
		//}
		//else
		//{
		//	Data.Posicion -= Front;
		//z}
	}
	else if (Traslation == 'd' || Traslation == 'D')
	{
		Data.Posicion += Data.Rigth;
	}
	Ejes =
	{
		Data.Rigth.x, Data.Rigth.y, Data.Rigth.z, 0,
		Up.x, Up.y, Up.z, 0,
		Data.Front.x, Data.Front.y, Data.Front.z, 0,
		0,0,0,1
	};
	Posicion =
	{
		1, 0, 0, -Data.Posicion.x,
		0, 1, 0, -Data.Posicion.y,
		0, 0, 1, -Data.Posicion.z,
		0, 0 , 0, 1
	};

	Posicion *= Ejes;

	View = Posicion;
	UpdateViewMatrix();
	return 0;
}


//! A \fn.
	/*!
	  function for rotate camera with the input and update the view matrix.
	  \param RotX an WPARAM.
	*/
void CCamera::Rotation(WPARAM RotX)
{
	float cosine = cosf(0.01);
	float sine = sinf(0.01);
	glm::mat4 ROTATION;

	
	//rotacion yaw
	if (RotX == '5')
	{
		ROTATION = {
		cosine, -sine,   0.0f, 0.0f,
		sine,    cosine, 0.0f, 0.0f,
		0.0f,    0.0f,   1.0f, 0.0f,
		0.0f,    0.0f,   0.0f, 1.0f
		};

		View *= ROTATION;
	}
	else if (RotX == '8')
	{
		cosine = cosf(-0.01);
		sine = sinf(-0.01);
		ROTATION = {
			cosine, -sine,   0.0f, 0.0f,
			sine,    cosine, 0.0f, 0.0f,
			0.0f,    0.0f,   1.0f, 0.0f,
			0.0f,    0.0f,   0.0f, 1.0f
		};

		View *= ROTATION;
	}
	//rotacion pitch
	if (RotX == VK_LEFT)
	{
		ROTATION = {
			cosine, 0.0f,  sine, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f,
			-sine,   0.0f,  cosine, 0.0f,
			0.0f,    0.0f,   0.0f, 1.0f
		};
		View *= ROTATION;
	}
	else if (RotX == VK_RIGHT)
	{
		cosine = cosf(-0.01);
		sine = sinf(-0.01);
		ROTATION = {
			cosine, 0.0f,  sine, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f,
			-sine,   0.0f,  cosine, 0.0f,
			0.0f,    0.0f,   0.0f, 1.0f
		};
		View *= ROTATION;
	}
	//rotacion roll
	if (RotX == VK_UP)
	{
		if (limitRollU < 20)
		{
			ROTATION = {
			 1.0f, 0.0f,  0.0f, 0.0f,
			0.0f,  cosine, -sine, 0.0f,
			0.0f,  sine,  cosine, 0.0f,
			0.0f,    0.0f,   0.0f, 1.0f
			};
			
			if (limitRollD <= 0)
			{
				limitRollU++;
				View *= ROTATION;
			}
			else
			{
				limitRollD--;
				View *= ROTATION;
			}
		}
		
	}
	else if (RotX == VK_DOWN)
	{
		if (limitRollD < 20)
		{
			cosine = cosf(-0.01);
			sine = sinf(-0.01);
			ROTATION = {
				 1.0f, 0.0f,  0.0f, 0.0f,
				0.0f,  cosine, -sine, 0.0f,
				0.0f,  sine,  cosine, 0.0f,
				0.0f,    0.0f,   0.0f, 1.0f
			};
			
			if (limitRollU <= 0)
			{
				limitRollD++;
				View *= ROTATION;
			}
			else
			{
				limitRollU--;
				View *= ROTATION;
			}
		}
		
	}

	
	UpdateViewMatrix();
}


//! A \fn.
	/*!
	  function for detect the input and know what do whit the input, rotate, move or nothing.
	  \param INPUT an WPARAM.
	*/
void CCamera::Input(WPARAM INPUT)
{
	if (INPUT == VK_UP || INPUT == VK_DOWN || INPUT == VK_LEFT || INPUT == VK_RIGHT || INPUT == '5' || INPUT == '8')
	{
		Rotation(INPUT);
	}

	else
	{
		Move(INPUT);
	}
}



	//! A \fn.
		/*!
		  function for move the mouse and update the biew matrix.
		  \param Dir an glm::fvec3.
		*/
void CCamera::MoveMouse(glm::fvec3 Dir)
{
	RotMouse(Dir);
	UpdateViewMatrix();
	//CreateViewMatrix();
}

//! A \fn.
	/*!
	  function for call the rotation of the mouse and update the view matrix.
	  \param Dir an glm::fvec3.
	*/
void CCamera::RotMouse(glm::fvec3 Dir)
{
	RotMouseX(Dir);
	UpdateViewMatrix();
	RotMouseY(Dir);
}

//! A \fn.
	/*!
	  function for rotate the mouse in x.
	  \param Dir an glm::fvec3.
	*/
void CCamera::RotMouseX(glm::fvec3 Dir)
{
	float cosine = cosf(Dir.x/100);
	float sine = sinf(Dir.x/100);
	glm::mat4 ROTATION;
		ROTATION = {
			cosine, 0.0f,  sine, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f,
			-sine,   0.0f,  cosine, 0.0f,
			0.0f,    0.0f,   0.0f, 1.0f
		};
		View *= ROTATION;
}


//! A \fn.
	/*!
	  function for rotate the mouse in y.
	  \param Dir an glm::fvec3.
	*/
void CCamera::RotMouseY(glm::fvec3 Dir)
{
	float cosine = cosf(Dir.y / 100);
	float sine = sinf(Dir.y / 100);
	glm::mat4 ROTATION;
	ROTATION = {
			 1.0f, 0.0f,  0.0f, 0.0f,
			0.0f,  cosine, -sine, 0.0f,
			0.0f,  sine,  cosine, 0.0f,
			0.0f,    0.0f,   0.0f, 1.0f
	};
	View *= ROTATION;
}


//! A \fn.
	/*!
	  function for create the view matrix using diferent menmbers of the struc and matrixs.
	*/
void CCamera::CreateViewMatrix()
{
	Data.Front = Data.At - Data.Posicion ;
	Data.Front = glm::normalize(Data.Front);

	Data.Rigth = glm::cross(Data.Up,Data.Front);
	Data.Rigth = glm::normalize(Data.Rigth);

	Up = glm::cross(Data.Front, Data.Rigth);
	Data.Up = Up;
	//(Fr, Ri)

	Ejes =
	{
		Data.Rigth.x, Data.Rigth.y, Data.Rigth.z, 0,
		Up.x, Up.y, Up.z, 0,
		Data.Front.x, Data.Front.y, Data.Front.z, 0,
		0,0,0,1
	};
	Posicion =
	{
		1, 0, 0, -Data.Posicion.x,
		0, 1, 0, -Data.Posicion.y,
		0, 0, 1, -Data.Posicion.z,
		0, 0 , 0, 1
	};

	Posicion *= Ejes;

	View = Posicion;
}
