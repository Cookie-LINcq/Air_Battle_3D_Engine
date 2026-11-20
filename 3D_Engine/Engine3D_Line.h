#pragma once
#include<iostream>
#include"Engine3D_Point.h"
#include"Engine3D_Vector3D.h"
#include"Engine3D_Vector2D.h"
using namespace std;

class Engine3D_Line
{
public:
	double radius;
	COLORREF color;
	Engine3D_Point* Point_A;
	Engine3D_Point* Point_B;

	Engine3D_Line();
	Engine3D_Line(Engine3D_Point* Point_A, Engine3D_Point* Point_B, COLORREF color = WHITE, double radius = 2);
	~Engine3D_Line();
};
