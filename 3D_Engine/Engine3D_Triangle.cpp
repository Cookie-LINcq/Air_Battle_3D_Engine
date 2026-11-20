#include"Engine3D_Triangle.h"

Engine3D_Triangle::Engine3D_Triangle()
{
	//this->ShowOrder = -1;
	this->color_constant = Engine3D_Vector3D(255, 255, 255);
	this->color = Engine3D_Vector3D(255, 255, 255);
	this->solid = false;
	this->lightsource = false;
	this->Point_A = NULL;
	this->Point_B = NULL;
	this->Point_C = NULL;
	this->NormalVector = Engine3D_Vector3D(0, 0, 0);
	return;
}

Engine3D_Triangle::Engine3D_Triangle(Engine3D_Vector3D Point_A, Engine3D_Vector3D Point_B, Engine3D_Vector3D Point_C, Engine3D_Vector3D color, bool solid, bool lightsource)
{
	//this->ShowOrder = -1;
	this->color_constant = color;
	this->color = color;
	this->solid = solid;
	this->lightsource = lightsource;
	this->Point_A = new Engine3D_Point(Point_A);
	this->Point_B = new Engine3D_Point(Point_B);
	this->Point_C = new Engine3D_Point(Point_C);
	this->NormalVector = Engine3D_Vector3D(0, 0, 0);
	return;
}

Engine3D_Triangle::~Engine3D_Triangle()
{
	if (this->Point_A != NULL)
	{
		delete this->Point_A;
		this->Point_A = NULL;
	}
	if (this->Point_B != NULL)
	{
		delete this->Point_B;
		this->Point_B = NULL;
	}
	if (this->Point_C != NULL)
	{
		delete this->Point_C;
		this->Point_C = NULL;
	}
	return;
}

void Engine3D_Triangle::Calculate_NormalVector()
{
	this->NormalVector.x = (this->Point_B->coordinates_world.y - this->Point_A->coordinates_world.y) * (this->Point_C->coordinates_world.z - this->Point_A->coordinates_world.z) - (this->Point_C->coordinates_world.y - this->Point_A->coordinates_world.y) * (this->Point_B->coordinates_world.z - this->Point_A->coordinates_world.z);
	this->NormalVector.y = (this->Point_B->coordinates_world.z - this->Point_A->coordinates_world.z) * (this->Point_C->coordinates_world.x - this->Point_A->coordinates_world.x) - (this->Point_C->coordinates_world.z - this->Point_A->coordinates_world.z) * (this->Point_B->coordinates_world.x - this->Point_A->coordinates_world.x);
	this->NormalVector.z = (this->Point_B->coordinates_world.x - this->Point_A->coordinates_world.x) * (this->Point_C->coordinates_world.y - this->Point_A->coordinates_world.y) - (this->Point_C->coordinates_world.x - this->Point_A->coordinates_world.x) * (this->Point_B->coordinates_world.y - this->Point_A->coordinates_world.y);
	this->NormalVector = this->NormalVector.UnitVector();
	return;
}
