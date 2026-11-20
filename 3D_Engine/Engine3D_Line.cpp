#include"Engine3D_Line.h"

Engine3D_Line::Engine3D_Line()
{
	this->color = WHITE;
	this->radius = 1;
	this->Point_A = NULL;
	this->Point_B = NULL;
	return;
}

Engine3D_Line::Engine3D_Line(Engine3D_Point* Point_A, Engine3D_Point* Point_B, COLORREF color, double radius)
{
	this->color = color;
	this->radius = radius;
	this->Point_A = Point_A;
	this->Point_B = Point_B;
	return;
}

Engine3D_Line::~Engine3D_Line()
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
	return;
}
