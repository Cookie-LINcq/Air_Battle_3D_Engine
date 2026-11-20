#pragma once
#include<iostream>
#include"AirBattle_Object.h"
#include"Engine3D_Vector3D.h"
#include"Engine3D_Quaternion.h"
#include"Engine3D_Object.h"
#include"Engine3D_Camera.h"
using namespace std;

class AirBattle_Warplane
{
public:
//Warplane 参数
	//1 信息
	string name, Name_Enemy, Name_Defeater, Name_Camera;
	int ID;
	//2 运算参数
	//2.1 坐标方向
	Engine3D_Vector3D coordinates;
	Engine3D_Quaternion orientation;
	//2.2 速度与加速度
	//2.2.1 平移
	//2.2.1.1 速度
	Engine3D_Vector3D Velocity_Translation;
	Engine3D_Vector3D Velocity_Translation_Constant;
	Engine3D_Vector3D Velocity_Translation_Max;
	Engine3D_Vector3D Velocity_Translation_Min;
	//2.2.1.2 加速度
	Engine3D_Vector3D Acceleration_Translation;
	double Maxacceleration_Translation;
	//2.2.2 旋转
	//2.2.2.1 速度
	Engine3D_Vector3D Velocity_Rotation;
	double Maxvelocity_Rotation;
	//2.2.2.2 加速度
	Engine3D_Vector3D Acceleration_Rotation;
	double Maxacceleration_Rotation;
	//3 包含物件
	int object_num;
	AirBattle_Object** Object_list;
	AirBattle_Object* NowFindObject;
	//4 数据更新时刻
	//4.1 函数执行
	double LastClock_Update;
	double LastClock_ScreenDisplay;
	//4.2 键盘操控
	double LastClock_FrontSightSwitch;
	double LastClock_AimingSwitch;
	//4.3 开火	
	double LastClock_Firing;
	//4.4 导弹发射
	double LastClock_MissileFiring;
	//5 准星数据
	double FrontSightSwitchInterval;
	double FrontSightDegree;
	double FrontSight_Assist, FrontSight_Assist_Time;
	//6 瞄准数据
	double AimingInterval;//瞄准控制间隔
	double AimingRange;//瞄准范围
	double AimingSpeed;//瞄准速度
	double AimingProgress;//瞄准进度
	//7 相机数据
	Engine3D_Camera* Camera;
	double CameraEffect_Translation;
	double CameraEffect_Rotation;
	double CameraEffect_Depth;
	//8 机枪数据
	double GunFiringInterval;
	double GunFiringDistance;
	double GunFiringHeatProgress;
	double GunFiringHeatRate;//百分比每秒
	double GunFiringCoolRate;//百分比每秒
	double GunFiringPunishClock;//过热时刻
	double GunFiringPunishTime;//过热惩罚时间
	//9 按键状态
	bool FrontSight_On;
	bool Aiming_On;
	//10 屏幕特效参数
	//10.1 受到伤害
	//10.1.1 机枪
	double ScreenDisplay_DMGTaken_Gun, ScreenDisplay_DMGTaken_Gun_Time;
	//10.1.2 导弹
	double ScreenDisplay_DMGTaken_Missile, ScreenDisplay_DMGTaken_Missile_Time;
	//11 飞机属性
	double HP, DFE_Gun, DMG_Gun, PNT_Gun, DFE_Missile, DMG_Missile, PNT_Missile;
	//    血量 防御_枪  伤害_枪  穿透_枪  防御_导弹    伤害_导弹    穿透_导弹
	//12 按键信息
	char Key_Accelerate, Key_Retard, Key_Dive, Key_Pullup, Key_Leftrotation, Key_Rightrotation, Key_Leftturn, Key_Rightturn, Key_Firing, Key_Firingclock, Key_FrontSightSwitch, Key_Aiming, Key_Missilefiring;
	//   加速            减速        俯冲      拉升        左旋              右旋               左转          右转           机枪开火    机枪开火锁       准星开关              瞄准        导弹发射
	//13 状态
	bool OVER, Locked;
	//14 导弹数据
	double MissileFiringInterval;

//Warplane 函数
	AirBattle_Warplane(int ID, Engine3D_Camera* Camera);
	~AirBattle_Warplane();

	AirBattle_Object* Find_Object__FUNC(string Name);
	void Update__FUNC(AirBattle_Warplane* Enemy);
	void Object_Rotation__FUNC(Engine3D_Object* Object, Engine3D_Vector3D rotation_axis, double theta);
	void Acceleration_Reset__FUNC();
	void Adjustment__FUNC(double TIME, bool MODE_Game);
	void DMG_Taken__FUNC(string TYPE, AirBattle_Warplane* Charger);
	void Aiming__FUNC(double TIME, AirBattle_Warplane* Enemy);
	void Camera_Display__FUNC();
	void CameraDisplayEffect_DMG_Taken__FUNC();
	void CameraDisplayEffect_Motion__FUNC();
	void Screen_Display__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize, AirBattle_Warplane* Enemy, double X);
	void ScreenDisplayEffect_DMG_Taken__FUNC(Engine3D_Vector2D Centre, double TIME, Engine3D_Vector2D ScreenSize);
	void ScreenDisplayEffect_Over__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize);
	void ScreenDisplayEffect_EnemyArrow__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize, AirBattle_Warplane* Enemy, double X);
	void ScreenDisplayEffect_FrontSight__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize, AirBattle_Warplane* Enemy, double X, double TIME);
	void ScreenDisplayEffect_Locked__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize, AirBattle_Warplane* Enemy);
	void ScreenDisplayEffect_GunFiringHeat__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize);
	void ScreenDisplayEffect_MissileFiringHeat__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize);
};
