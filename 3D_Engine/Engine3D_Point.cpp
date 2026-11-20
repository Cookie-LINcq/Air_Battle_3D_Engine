#include"Engine3D_Point.h"

Engine3D_Point::Engine3D_Point()
{
	this->color = WHITE;
	this->coordinates_object = Engine3D_Vector3D(0, 0, 0);
	this->coordinates_world = Engine3D_Vector3D(0, 0, 0);
	this->camerasnum = 3;
	this->coordinates_camera = new Engine3D_Vector3D[this->camerasnum];
	this->coordinates_screen = new Engine3D_Vector2D[this->camerasnum];
	for (int i = 0; i < this->camerasnum; i++)
	{
		this->coordinates_camera[i] = Engine3D_Vector3D();
		this->coordinates_screen[i] = Engine3D_Vector2D();
	}
	return;
}

Engine3D_Point::Engine3D_Point(double x, double y, double z, COLORREF color, int camerasnum)
{
	this->color = color;
	this->coordinates_object = Engine3D_Vector3D(x, y, z);
	this->coordinates_world = Engine3D_Vector3D(x, y, z);
	this->camerasnum = camerasnum;
	this->coordinates_camera = new Engine3D_Vector3D[camerasnum];
	this->coordinates_screen = new Engine3D_Vector2D[camerasnum];
	for (int i = 0; i < camerasnum; i++)
	{
		this->coordinates_camera[i] = Engine3D_Vector3D(x, y, z);
		this->coordinates_screen[i] = Engine3D_Vector2D(x, y);
	}
	return;
}

Engine3D_Point::Engine3D_Point(Engine3D_Vector3D Point, COLORREF color, int camerasnum)
{
	this->color = color;
	this->coordinates_object = Point;
	this->coordinates_world = Point;
	this->camerasnum = camerasnum;
	this->coordinates_camera = new Engine3D_Vector3D[camerasnum];
	this->coordinates_screen = new Engine3D_Vector2D[camerasnum];
	for (int i = 0; i < camerasnum; i++)
	{
		this->coordinates_camera[i] = Point;
		this->coordinates_screen[i] = Engine3D_Vector2D(Point.x, Point.y);
	}
	return;
}

Engine3D_Point::~Engine3D_Point()
{
	if (this->coordinates_camera != NULL)
	{
		delete[] this->coordinates_camera;
		this->coordinates_camera = NULL;
	}
	if (this->coordinates_screen != NULL)
	{
		delete[] this->coordinates_screen;
		this->coordinates_screen = NULL;
	}
	return;
}
