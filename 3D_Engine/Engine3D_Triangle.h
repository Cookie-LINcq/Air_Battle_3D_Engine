#pragma once
#include<iostream>
#include<easyx.h>
#include"Engine3D_Calculation.h"
#include"Engine3D_Point.h"
using namespace std;

class Engine3D_Triangle
{
public:
	//int ShowOrder;
	bool solid;
	bool lightsource;
	Engine3D_Vector3D color;
	Engine3D_Vector3D color_constant;
	Engine3D_Point* Point_A;
	Engine3D_Point* Point_B;
	Engine3D_Point* Point_C;
	Engine3D_Vector3D NormalVector;

	Engine3D_Triangle();
	Engine3D_Triangle(Engine3D_Vector3D Point_A, Engine3D_Vector3D Point_B, Engine3D_Vector3D Point_C, Engine3D_Vector3D color = Engine3D_Vector3D(255, 255, 255), bool solid = false, bool lightsource = false);
	~Engine3D_Triangle();

	void Calculate_NormalVector();
};
