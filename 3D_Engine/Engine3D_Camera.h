#pragma once
#include<iostream>
#include<easyx.h>
#include<cmath>
#include"Engine3D_Calculation.h"
#include"Engine3D_Vector3D.h"
#include"Engine3D_Vector2D.h"
#include"Engine3D_Quaternion.h"
using namespace std;

class Engine3D_Camera
{
public:
	string name;
	double magnification;
	double LastUpdateTime;
	double Sensitivity_Translation, Sensitivity_Rotation;
	Engine3D_Vector3D coordinates;
	Engine3D_Quaternion orientation;
	double width, height, depth;
	double depth_constant;
	Engine3D_Vector2D screencentre;
	Engine3D_Vector2D screensize;
	HRGN screenhrgn;

	Engine3D_Camera(string name = "", Engine3D_Vector2D screencentre = Engine3D_Vector2D(0, 0), Engine3D_Vector2D screensize = Engine3D_Vector2D(0, 0));
	~Engine3D_Camera();
};
