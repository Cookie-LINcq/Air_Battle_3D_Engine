#pragma once
#include<iostream>
#include<easyx.h>
#include"Engine3D_Calculation.h"
#include"Engine3D_Vector3D.h"
#include"Engine3D_Vector2D.h"
using namespace std;

class Engine3D_Point
{
public:
	int camerasnum;
	COLORREF color;
	Engine3D_Vector3D coordinates_object;
	Engine3D_Vector3D coordinates_world;
	Engine3D_Vector3D* coordinates_camera;
	Engine3D_Vector2D* coordinates_screen;

	Engine3D_Point();
	Engine3D_Point(double x, double y, double z, COLORREF color = WHITE, int camerasnum = CameraNumber);
	Engine3D_Point(Engine3D_Vector3D Point, COLORREF color = WHITE, int camerasnum = CameraNumber);
	~Engine3D_Point();
};
