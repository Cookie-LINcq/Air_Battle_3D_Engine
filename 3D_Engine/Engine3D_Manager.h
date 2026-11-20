#pragma once
#include<iostream>
#include<easyx.h>
#include<tuple>
#include"Engine3D_Calculation.h"
#include"Engine3D_Camera.h"
#include"Engine3D_Object.h"
#include"Engine3D_Quaternion.h"
#include"AirBattle_Warplane.h"
#include"AirBattle_Object.h"
#include"AirBattle_Bullet.h"
#include"AirBattle_Missile.h"
using namespace std;

class Engine3D_Manager
{
public:
	double LastUpdateTime_Show;
	double LastUpdateTime_Warplane;
	double LastUpdateTime_Bullet;
	double LastUpdateTime_Missile;
	int Warplane_number;
	int Bullet_number, Missile_number;
	bool MODE_Game;
	AirBattle_Warplane** Warplane_list;
	AirBattle_Bullet** Bullet_list;
	AirBattle_Missile** Missile_list;
	Engine3D_Camera** Cameras_list;
	int camerasnum;
	Engine3D_Object** Objects_list;
	int objectsnum;
	int screen_width, screen_height;
	Engine3D_Vector3D SunLight;
	double AmbientLightIntensity;
	
	Engine3D_Manager();
	~Engine3D_Manager();

	void Add_Object(double x, double y, double z);
	void Show();
	void Warplane_Display(double magnification);
	void Calculate_Pointcameracoordinate();
	void Calculate_Pointscreencoordinate();
	void CALCULATE_All();
	void Add_Warplane();
	void Warplane_Update();
	void Warplane_Adjustment();
	void Add_Bullet(AirBattle_Warplane* Warplane);
	void Add_Missile(AirBattle_Warplane* Warplane);
	void Bullet_Update();
	void Missile_Update();
	void BulletRadius_Update(Engine3D_Camera* Camera);
	void Firing(AirBattle_Warplane* Warplane);
	void MissileFiring(AirBattle_Warplane* Warplane);
	AirBattle_Warplane* Find_Warplane(string Name);
	Engine3D_Camera* Find_Camera(string Name);
	void TriangleRendering(Engine3D_Camera* Camera);
	bool TrianglePointIntersection(Engine3D_Vector2D TriangleA, Engine3D_Vector2D TriangleB, Engine3D_Vector2D TriangleC, Engine3D_Vector2D Point);
	tuple<int, Engine3D_Vector2D*> Calculate_TriangleRelation(Engine3D_Triangle* Original, Engine3D_Triangle* Compare, int CameraID);//内部点数量，内部点
	double Calculate_TriangleArea(Engine3D_Vector2D PointA, Engine3D_Vector2D PointB, Engine3D_Vector2D PointC);
	tuple<int, Engine3D_Vector2D> Segment2DIntersection(Engine3D_Vector2D P1, Engine3D_Vector2D P2, Engine3D_Vector2D P3, Engine3D_Vector2D P4);
	double Calculate_RayTriangleIntersectionDistance(Engine3D_Vector2D Ray, Engine3D_Triangle* Triangle, int CameraID);
	void Calculate_TriangleObstruct(Engine3D_Camera* Camera);//计算三角形遮挡  已完成，但效果不好，未投入使用
	//bool DeleteTriangleBehind(int** TriangleBehind, int* TriangleBehindNum, int NowTriangle, int FindTriangle);
	//void Camera_Adjustment();
};
