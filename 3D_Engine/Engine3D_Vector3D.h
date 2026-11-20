#pragma once
#include<iostream>
#include<cmath>
#include"Engine3D_Calculation.h"
using namespace std;

class Engine3D_Vector3D
{
public:
	double x, y, z;
	double length;

	Engine3D_Vector3D();
	Engine3D_Vector3D(double x, double y, double z);
	Engine3D_Vector3D(string axis);
	~Engine3D_Vector3D();

	Engine3D_Vector3D operator+(Engine3D_Vector3D Vector3D);
	Engine3D_Vector3D operator-(Engine3D_Vector3D Vector3D);
	Engine3D_Vector3D operator*(Engine3D_Vector3D Vector3D);//×ø±êµã³Ë
	Engine3D_Vector3D operator*(double coefficient);
	double DotProduct(Engine3D_Vector3D Vector3D);//µã³Ë
	Engine3D_Vector3D CrossProduct(Engine3D_Vector3D Vector3D);//ÓÒ²æ³Ë
	Engine3D_Vector3D operator/(double coefficient);
	void operator+=(Engine3D_Vector3D Vector3D);
	double GetLength();
	Engine3D_Vector3D UnitVector();
	double VetorialAngle(Engine3D_Vector3D Vector3D);
};
