#pragma once
#include<iostream>
#include<cmath>
#include"Engine3D_Calculation.h"
using namespace std;

class Engine3D_Vector2D
{
public:
	double x, y;
	double length;

	Engine3D_Vector2D();
	Engine3D_Vector2D(double x, double y);
	~Engine3D_Vector2D();

	bool operator==(Engine3D_Vector2D Vector2D);
	bool operator!=(Engine3D_Vector2D Vector2D);
	Engine3D_Vector2D operator*(double coefficient);
	double GetLength();
	double VetorialAngle(Engine3D_Vector2D Vector2D);
	//Engine3D_Vector2D UnitVector();
};
