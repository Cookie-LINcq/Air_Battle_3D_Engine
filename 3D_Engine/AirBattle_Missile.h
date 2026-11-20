#pragma once
#include<iostream>
#include<tuple>
#include"AirBattle_Warplane.h"
using namespace std;

class AirBattle_Missile
{
public:
	bool shouldDestroy;//该销毁
	bool isBooming;
	string warplaneName, goalName;
	int objectsListID;
	double firingClock;
	double accelerationTime;
	double aimingTime;
	int aimingState;//0.未瞄准 1.已瞄准 -1.丢失目标
	Engine3D_Object* objectPtr;
	Engine3D_Vector3D coordinate;
	Engine3D_Quaternion orientation;
	Engine3D_Vector3D translationVelocity;
	Engine3D_Vector3D translationVelocity_Constant;
	Engine3D_Vector3D translationVelocity_Start;
	Engine3D_Vector3D translationAcceleration;
	Engine3D_Vector3D rotationVelocity;
	double rotationVelocity_Max;
	double destructionTime;
	double lostTargetClock;
	double rotationSpeed_Basics, rotationSpeed_Addition;

	double boomTime;
	double boomClock;
	Engine3D_Vector3D* boomColorsListPtr;//RGB
	tuple<Engine3D_Vector3D*, Engine3D_Vector3D*, Engine3D_Vector3D*> boomCoordinatesListPtrsList;

	AirBattle_Missile(AirBattle_Warplane* Warplane);
	~AirBattle_Missile();

	int update(double TIME, AirBattle_Warplane* Goal, int Aiming);//return 0.Nothing 1.JustBoom -1.clean
	void update_Fire();
	bool booming();//return clean?
};
