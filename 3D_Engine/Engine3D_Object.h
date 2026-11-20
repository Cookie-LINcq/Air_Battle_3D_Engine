#pragma once
#include<iostream>
#include"Engine3D_Point.h"
#include"Engine3D_Line.h"
#include"Engine3D_Triangle.h"
#include"Engine3D_Vector3D.h"
#include"Engine3D_Quaternion.h"
#include"Engine3D_Calculation.h"
using namespace std;

class Engine3D_Object
{
public:
	string Name;
	Engine3D_Vector3D coordinates_plane;
	Engine3D_Vector3D coordinates_plane_constant;
	Engine3D_Vector3D coordinates_world;
	Engine3D_Quaternion orientation;
	Engine3D_Quaternion orientation_object;
	Engine3D_Vector3D degrees_rotation_object;
	Engine3D_Vector3D maxdegrees_rotation_object;
	Engine3D_Point** Pointlist;
	int pointnum;
	Engine3D_Line** Linelist;
	int linenum;
	Engine3D_Triangle** Trianglelist;
	int trianglenum;
	double showrange;

	Engine3D_Object();
	Engine3D_Object(double x, double y, double z);
	~Engine3D_Object();

	void Add_Point(double x, double y, double z, COLORREF color = WHITE);
	void Add_Line(Engine3D_Point* Point_A, Engine3D_Point* Point_B, COLORREF color = WHITE, double radius = 2);
	void Add_Triangle(Engine3D_Vector3D Point_A, Engine3D_Vector3D Point_B, Engine3D_Vector3D Point_C, Engine3D_Vector3D color = Engine3D_Vector3D(255, 255, 255), bool solid = false, bool lightsource = false);
	void Calculate_Pointworldcoordinate();
	void Rotation(Engine3D_Vector3D rotation_axis, double theta);
};
