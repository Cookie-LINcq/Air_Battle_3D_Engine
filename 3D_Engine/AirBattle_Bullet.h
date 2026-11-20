#pragma once
#include<iostream>
#include"Engine3D_Camera.h"
#include"AirBattle_Warplane.h"
#include"Engine3D_Object.h"
#include"Engine3D_Vector3D.h"
#include"Engine3D_Quaternion.h"
#include"Engine3D_Point.h"
#include"Engine3D_Calculation.h"
using namespace std;

class AirBattle_Bullet
{
public:
	int objectsListID;
	bool shouldDestroy;//¸ÃÏú»Ù
	Engine3D_Object* objectPtr;
	double distance;
	double speed;
	double radius;
	COLORREF color;
	Engine3D_Vector3D coordinate;
	Engine3D_Vector3D coordinate_Start;
	Engine3D_Quaternion orientation;

	double dangerRadius, dangerRadius_Basics, dangerRadius_Additional;
	string warplaneName;

	AirBattle_Bullet(AirBattle_Warplane* Warplane);
	~AirBattle_Bullet();

	void update(double TIME);
	void update_Radius(Engine3D_Camera* Camera);
};
