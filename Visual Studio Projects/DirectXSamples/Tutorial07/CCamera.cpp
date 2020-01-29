#include "CCamera.h"
#include <glm.hpp>
#include <mat4x4.hpp>

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

CCamera::~CCamera()
{
}

glm::mat4 CCamera::GetView()
{
	return View;
}

glm::mat4 CCamera::GetProyeccion()
{
	return Proyeccion;
}

void CCamera::setWeight(float weight)
{
	Data.W = weight;
}

float CCamera::GetWeight()
{
	return Data.W;
}

void CCamera::setHeight(float height)
{
	Data.H = height;
}

float CCamera::GetHeight()
{
	return Data.H;
}

void CCamera::setFar(float F)
{
	Data.Far = F;
}

float CCamera::GetFar()
{
	return Data.Far;
}

void CCamera::setFov(float FOV)
{
	Data.Fov = FOV;
}

float CCamera::GetFov()
{
	return Data.Fov;
}

void CCamera::setEPosition(glm::vec3 P)
{
	Data.Posicion = P;
}

glm::vec3 CCamera::GetPosition()
{
	return Data.Posicion;
}

void CCamera::setAt(glm::vec3 A)
{
	Data.At = A;
}

glm::vec3 CCamera::GetAt()
{
	return Data.At;
}

void CCamera::setUp(glm::vec3 Up)
{
	Data.Up = Up;
}

glm::vec3 CCamera::GetUp()
{
	return Data.Up;
}

void CCamera::setNear(float N)
{
	Data.Near = N;
}

float CCamera::GetNear()
{
	return Data.Near;
}

void CCamera::setFront(glm::vec3 At, glm::vec3 Pos)
{
	Data.Front = glm::normalize(At-Pos);
	Front= glm::normalize(At - Pos);
}

glm::vec3 CCamera::GetFront()
{
	return Data.Front;
}

void CCamera::setRight(glm::vec3 Up, glm::vec3 Fr)
{
	Data.Rigth = glm::normalize(glm::cross(Up, Fr));
}

glm::vec3 CCamera::GetRight()
{
	return Data.Rigth;
}

void CCamera::setUpTrue(glm::vec3 Fr, glm::vec3 Ri)
{
	Up = glm::normalize(glm::cross(Fr, Ri));
}

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

void CCamera::UpdateProyeccion()
{
	Proyeccion = glm::perspectiveFovLH(Data.Fov, Data.W, Data.H, Data.Near, Data.Far);
	Proyeccion = glm::transpose(Proyeccion);
}

int CCamera::Move(WPARAM Traslation)
{
	if (Traslation == 'w' || Traslation == 'W')
	{
		if (GodC == true)
		{
			Data.Posicion += Data.Front;
		}
		else
		{
			Data.Posicion += Front;
		}
	}
	else if (Traslation == 'a' || Traslation == 'A')
	{
		Data.Posicion -= Data.Rigth;
	}
	else if (Traslation == 's' || Traslation == 'S')
	{
		if (GodC == true)
		{
			Data.Posicion -= Data.Front;
		}
		else
		{
			Data.Posicion -= Front;
		}
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

void CCamera::MoveMouse(glm::fvec3 Dir)
{
	RotMouse(Dir);
	UpdateViewMatrix();
	CreateViewMatrix();
}

void CCamera::RotMouse(glm::fvec3 Dir)
{
	RotMouseX(Dir);
	UpdateViewMatrix();
	RotMouseY(Dir);
}

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
