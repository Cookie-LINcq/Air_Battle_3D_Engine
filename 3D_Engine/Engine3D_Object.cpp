#include"Engine3D_Object.h"

Engine3D_Object::Engine3D_Object()
{
	this->Name = "";
	this->coordinates_plane = Engine3D_Vector3D(0, 0, 0);
	this->coordinates_plane_constant = Engine3D_Vector3D(0, 0, 0);
	this->coordinates_world = Engine3D_Vector3D(0, 0, 0);
	this->orientation = Engine3D_Quaternion(1, 0, 0, 0);
	this->orientation_object = Engine3D_Quaternion(1, 0, 0, 0);
	this->degrees_rotation_object = Engine3D_Vector3D(0, 0, 0);
	this->maxdegrees_rotation_object = Engine3D_Vector3D(0, 0, 0);
	this->pointnum = 0;
	this->Pointlist = NULL;
	this->linenum = 0;
	this->Linelist = NULL;
	this->trianglenum = 0;
	this->Trianglelist = NULL;
	this->showrange = 10000000;
	return;
}

Engine3D_Object::Engine3D_Object(double x, double y, double z)
{
	this->Name = "";
	this->coordinates_plane = Engine3D_Vector3D(x, y, z);
	this->coordinates_plane_constant = Engine3D_Vector3D(x, y, z);
	this->coordinates_world = Engine3D_Vector3D(x, y, z);
	this->orientation = Engine3D_Quaternion(1, 0, 0, 0);
	this->orientation_object = Engine3D_Quaternion(1, 0, 0, 0);
	this->degrees_rotation_object = Engine3D_Vector3D(0, 0, 0);
	this->maxdegrees_rotation_object = Engine3D_Vector3D(0, 0, 0);
	this->pointnum = 0;
	this->Pointlist = NULL;
	this->linenum = 0;
	this->Linelist = NULL;
	this->trianglenum = 0;
	this->Trianglelist = NULL;
	this->showrange = 10000000;
	return;
}

Engine3D_Object::~Engine3D_Object()
{
	if (this->Pointlist != NULL)
	{
		for (int i = 0; i < this->pointnum; i++)
		{
			delete this->Pointlist[i];
			this->Pointlist[i] = NULL;
		}
		delete[]this->Pointlist;
		this->Pointlist = NULL;
	}
	if (this->Linelist != NULL)
	{
		for (int i = 0; i < this->linenum; i++)
		{
			delete this->Linelist[i];
			this->Linelist[i] = NULL;
		}
		delete[]this->Linelist;
		this->Linelist = NULL;
	}
	if (this->Trianglelist != NULL)
	{
		for (int i = 0; i < this->trianglenum; i++)
		{
			delete this->Trianglelist[i];
			this->Trianglelist[i] = NULL;
		}
		delete[]this->Trianglelist;
		this->Trianglelist = NULL;
	}
	return;
}

void Engine3D_Object::Add_Point(double x, double y, double z, COLORREF color)
{
	this->pointnum++;
	if (this->pointnum == 1)
	{
		this->Pointlist = new Engine3D_Point * [this->pointnum];
		this->Pointlist[0] = new Engine3D_Point(x, y, z, color);
		return;
	}
	Engine3D_Point** newspace = new Engine3D_Point * [this->pointnum];
	for (int i = 0; i < this->pointnum - 1; i++)
	{
		newspace[i] = this->Pointlist[i];
	}
	newspace[this->pointnum - 1] = new Engine3D_Point(x, y, z, color);
	delete[]this->Pointlist;
	this->Pointlist = newspace;
	newspace = NULL;
	return;
}

void Engine3D_Object::Add_Line(Engine3D_Point* Point_A, Engine3D_Point* Point_B, COLORREF color, double radius)
{
	this->linenum++;
	if (this->linenum == 1)
	{
		this->Linelist = new Engine3D_Line * [this->linenum];
		this->Linelist[0] = new Engine3D_Line(Point_A, Point_B, color, radius);
		return;
	}
	Engine3D_Line** newspace = new Engine3D_Line * [this->linenum];
	for (int i = 0; i < this->linenum - 1; i++)
	{
		newspace[i] = this->Linelist[i];
	}
	newspace[this->linenum - 1] = new Engine3D_Line(Point_A, Point_B, color, radius);
	delete[]this->Linelist;
	this->Linelist = newspace;
	newspace = NULL;
	return;
}

void Engine3D_Object::Add_Triangle(Engine3D_Vector3D Point_A, Engine3D_Vector3D Point_B, Engine3D_Vector3D Point_C, Engine3D_Vector3D color, bool solid, bool lightsource)
{
	this->trianglenum++;
	if (this->trianglenum == 1)
	{
		this->Trianglelist = new Engine3D_Triangle * [this->trianglenum];
		this->Trianglelist[0] = new Engine3D_Triangle(Point_A, Point_B, Point_C, color, solid, lightsource);
		return;
	}
	Engine3D_Triangle** newspace = new Engine3D_Triangle * [this->trianglenum];
	for (int i = 0; i < this->trianglenum - 1; i++)
	{
		newspace[i] = this->Trianglelist[i];
	}
	newspace[this->trianglenum - 1] = new Engine3D_Triangle(Point_A, Point_B, Point_C, color, solid, lightsource);
	delete[]this->Trianglelist;
	this->Trianglelist = newspace;
	newspace = NULL;
	return;
}

void Engine3D_Object::Calculate_Pointworldcoordinate()
{
	for (int j = 0; j < this->linenum; j++)
	{
		this->Linelist[j]->Point_A->coordinates_world = ((this->orientation * this->orientation_object) * Engine3D_Quaternion(this->Linelist[j]->Point_A->coordinates_object) * (this->orientation * this->orientation_object).Inverse_Quaternion()).Quaternion_To_Vector3D() + this->coordinates_world;
		this->Linelist[j]->Point_B->coordinates_world = ((this->orientation * this->orientation_object) * Engine3D_Quaternion(this->Linelist[j]->Point_B->coordinates_object) * (this->orientation * this->orientation_object).Inverse_Quaternion()).Quaternion_To_Vector3D() + this->coordinates_world;
	}
	for (int i = 0; i < this->trianglenum; i++)
	{
		this->Trianglelist[i]->Point_A->coordinates_world = ((this->orientation * this->orientation_object) * Engine3D_Quaternion(this->Trianglelist[i]->Point_A->coordinates_object) * (this->orientation * this->orientation_object).Inverse_Quaternion()).Quaternion_To_Vector3D() + this->coordinates_world;
		this->Trianglelist[i]->Point_B->coordinates_world = ((this->orientation * this->orientation_object) * Engine3D_Quaternion(this->Trianglelist[i]->Point_B->coordinates_object) * (this->orientation * this->orientation_object).Inverse_Quaternion()).Quaternion_To_Vector3D() + this->coordinates_world;
		this->Trianglelist[i]->Point_C->coordinates_world = ((this->orientation * this->orientation_object) * Engine3D_Quaternion(this->Trianglelist[i]->Point_C->coordinates_object) * (this->orientation * this->orientation_object).Inverse_Quaternion()).Quaternion_To_Vector3D() + this->coordinates_world;
	}
	/*for (int i = 0; i < this->pointnum; i++)
	{
		Engine3D_Quaternion coordinate_object(0, this->Pointlist[i]->coordinates_object->x, this->Pointlist[i]->coordinates_object->y, this->Pointlist[i]->coordinates_object->z);
		Engine3D_Quaternion inversequaternion_orientation(this->orientation->w, -this->orientation->i, -this->orientation->j, -this->orientation->k);
		Engine3D_Quaternion WorldCoordinate = Calculation.Quaternion_Multiplication(*this->orientation, coordinate_object);
		WorldCoordinate = Calculation.Quaternion_Multiplication(WorldCoordinate, inversequaternion_orientation);
		this->Pointlist[i]->coordinates_world->x = WorldCoordinate.i + this->coordinates_world->x;
		this->Pointlist[i]->coordinates_world->y = WorldCoordinate.j + this->coordinates_world->y;
		this->Pointlist[i]->coordinates_world->z = WorldCoordinate.k + this->coordinates_world->z;
	}
	for (int k = 0; k < this->trianglenum; k++)
	{
		Engine3D_Quaternion coordinate_object_A(0, this->Trianglelist[k]->Point_A->coordinates_object->x, this->Trianglelist[k]->Point_A->coordinates_object->y, this->Trianglelist[k]->Point_A->coordinates_object->z);
		Engine3D_Quaternion inversequaternion_orientation_A(this->orientation->w, -this->orientation->i, -this->orientation->j, -this->orientation->k);
		Engine3D_Quaternion WorldCoordinate_A = Calculation.Quaternion_Multiplication(*this->orientation, coordinate_object_A);
		WorldCoordinate_A = Calculation.Quaternion_Multiplication(WorldCoordinate_A, inversequaternion_orientation_A);
		this->Trianglelist[k]->Point_A->coordinates_world->x = WorldCoordinate_A.i + this->coordinates_world->x;
		this->Trianglelist[k]->Point_A->coordinates_world->y = WorldCoordinate_A.j + this->coordinates_world->y;
		this->Trianglelist[k]->Point_A->coordinates_world->z = WorldCoordinate_A.k + this->coordinates_world->z;

		Engine3D_Quaternion coordinate_object_B(0, this->Trianglelist[k]->Point_B->coordinates_object->x, this->Trianglelist[k]->Point_B->coordinates_object->y, this->Trianglelist[k]->Point_B->coordinates_object->z);
		Engine3D_Quaternion inversequaternion_orientation_B(this->orientation->w, -this->orientation->i, -this->orientation->j, -this->orientation->k);
		Engine3D_Quaternion WorldCoordinate_B = Calculation.Quaternion_Multiplication(*this->orientation, coordinate_object_B);
		WorldCoordinate_B = Calculation.Quaternion_Multiplication(WorldCoordinate_B, inversequaternion_orientation_B);
		this->Trianglelist[k]->Point_B->coordinates_world->x = WorldCoordinate_B.i + this->coordinates_world->x;
		this->Trianglelist[k]->Point_B->coordinates_world->y = WorldCoordinate_B.j + this->coordinates_world->y;
		this->Trianglelist[k]->Point_B->coordinates_world->z = WorldCoordinate_B.k + this->coordinates_world->z;

		Engine3D_Quaternion coordinate_object_C(0, this->Trianglelist[k]->Point_C->coordinates_object->x, this->Trianglelist[k]->Point_C->coordinates_object->y, this->Trianglelist[k]->Point_C->coordinates_object->z);
		Engine3D_Quaternion inversequaternion_orientation_C(this->orientation->w, -this->orientation->i, -this->orientation->j, -this->orientation->k);
		Engine3D_Quaternion WorldCoordinate_C = Calculation.Quaternion_Multiplication(*this->orientation, coordinate_object_C);
		WorldCoordinate_C = Calculation.Quaternion_Multiplication(WorldCoordinate_C, inversequaternion_orientation_C);
		this->Trianglelist[k]->Point_C->coordinates_world->x = WorldCoordinate_C.i + this->coordinates_world->x;
		this->Trianglelist[k]->Point_C->coordinates_world->y = WorldCoordinate_C.j + this->coordinates_world->y;
		this->Trianglelist[k]->Point_C->coordinates_world->z = WorldCoordinate_C.k + this->coordinates_world->z;
	}*/
	return;
}

void Engine3D_Object::Rotation(Engine3D_Vector3D rotation_axis, double theta)
{
	this->orientation = this->orientation.Rotation(rotation_axis, theta);
	return;
}
