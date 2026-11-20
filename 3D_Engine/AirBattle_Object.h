#pragma once
#include<iostream>
#include"Engine3D_Object.h"
using namespace std;

class AirBattle_Object
{
public:
	string Name;
	Engine3D_Object* Object;
	Engine3D_Vector3D Rotation_Degrees;
	Engine3D_Vector3D Rotation_Degrees_Max;

	AirBattle_Object();
	AirBattle_Object(string name, Engine3D_Object* Object);
	~AirBattle_Object();

	void Update__FUNC(Engine3D_Vector3D coordinates, Engine3D_Quaternion orientation);
	Engine3D_Quaternion Rotation__FUNC(string rotation_axis, double theta);
};
