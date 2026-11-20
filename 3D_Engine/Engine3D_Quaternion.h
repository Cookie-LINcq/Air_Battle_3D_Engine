#pragma once
#include<iostream>
#include<cmath>
#include"Engine3D_Calculation.h"
#include"Engine3D_Vector3D.h"
using namespace std;

class Engine3D_Quaternion
{
public:
	double w, i, j, k;
	double length;

	Engine3D_Quaternion();
	Engine3D_Quaternion(double w, double i, double j, double k);
	Engine3D_Quaternion(Engine3D_Vector3D Vector3D);
	~Engine3D_Quaternion();

	Engine3D_Quaternion operator*(Engine3D_Quaternion Quaternion);
	Engine3D_Quaternion Rotation(Engine3D_Vector3D rotation_axis, double theta);
	Engine3D_Vector3D Get_UnitVector(string axis);
	Engine3D_Vector3D Quaternion_To_Vector3D();
	Engine3D_Quaternion Inverse_Quaternion();
	Engine3D_Quaternion RotationFactor(string rotation_axis, double theta);
};
