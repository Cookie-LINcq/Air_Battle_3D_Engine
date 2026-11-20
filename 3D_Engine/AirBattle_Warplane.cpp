#include"AirBattle_Warplane.h"

AirBattle_Warplane::AirBattle_Warplane(int ID, Engine3D_Camera* Camera)
{
	this->Camera = Camera;
	this->OVER = false;
	this->Locked = false;
	this->FrontSight_On = false;
	this->Aiming_On = false;
	this->ScreenDisplay_DMGTaken_Gun = 0;
	this->ScreenDisplay_DMGTaken_Gun_Time = 2.3;
	this->ScreenDisplay_DMGTaken_Missile = 0;
	this->ScreenDisplay_DMGTaken_Missile_Time = 5;
	this->FrontSight_Assist = -1;
	this->FrontSight_Assist_Time = 1.2;
	this->FrontSightDegree = 0;
	this->name = "";
	this->Name_Enemy = "";
	this->Name_Defeater = "";
	this->Name_Camera = "";
	this->ID = ID;
	COLORREF COLOR = WHITE;
	Engine3D_Vector3D Color(0, 0, 0);
	this->Key_Accelerate = NULL;
	this->Key_Retard = NULL;
	this->Key_Dive = NULL;
	this->Key_Pullup = NULL;
	this->Key_Leftrotation = NULL;
	this->Key_Rightrotation = NULL;
	this->Key_Leftturn = NULL;
	this->Key_Rightturn = NULL;
	this->Key_Firing = NULL;
	this->Key_Firingclock = NULL;
	this->Key_FrontSightSwitch = NULL;
	this->Key_Aiming = NULL;
	this->Key_Missilefiring = NULL;

	this->HP = 1000;
	this->DFE_Gun = 200;
	this->DMG_Gun = 400;
	this->PNT_Gun = 100;
	this->DFE_Missile = 200;
	this->DMG_Missile = 1000;
	this->PNT_Missile = 100;
	
	this->coordinates = Engine3D_Vector3D(0, 0, 0);
	this->orientation = Engine3D_Quaternion(1, 0, 0, 0);
	this->LastClock_Update = 0;
	this->LastClock_ScreenDisplay = 0;
	this->LastClock_Firing = 0;
	this->LastClock_MissileFiring = 0;
	this->LastClock_FrontSightSwitch = 0;
	this->LastClock_AimingSwitch = 0;
	this->FrontSightSwitchInterval = 0.9;
	this->Velocity_Translation_Constant = Engine3D_Vector3D(0, 0, -600);
	this->Velocity_Translation = this->Velocity_Translation_Constant;
	this->Velocity_Translation_Max = Engine3D_Vector3D(0, 0, -750);
	this->Velocity_Translation_Min = Engine3D_Vector3D(0, 0, -500);
	this->Acceleration_Translation = Engine3D_Vector3D(0, 0, 0);
	this->Velocity_Rotation = Engine3D_Vector3D(0, 0, 0);
	this->Acceleration_Rotation = Engine3D_Vector3D(0, 0, 0);
	this->Maxacceleration_Translation = 170;
	this->Maxacceleration_Rotation = 86;
	this->Maxvelocity_Rotation = 86;
	this->CameraEffect_Translation = 0.01;
	this->CameraEffect_Rotation = 0.1;
	this->CameraEffect_Depth = 0.002;
	this->GunFiringInterval = 0.005;//0.015
	this->GunFiringDistance = 31314;
	this->GunFiringHeatProgress = 0;
	this->GunFiringHeatRate = 0.1;
	this->GunFiringCoolRate = 0.15;
	this->GunFiringPunishClock = 0;
	this->GunFiringPunishTime = 3;
	this->AimingRange = 10000;
	this->AimingSpeed = 0.5;
	this->AimingProgress = 0;
	this->AimingInterval = 0.5;
	this->MissileFiringInterval = 2;
	double Radius = 3;

	switch (ID)
	{
	case 1:
	{
		this->name = "A";
		this->Name_Camera = "CameraA";
		COLOR = LIGHTRED;
		Color.x = 255;
		this->Key_Accelerate = 'W';
		this->Key_Retard = 'S';
		this->Key_Dive = 'T';
		this->Key_Pullup = 'G';
		this->Key_Leftrotation = 'F';
		this->Key_Rightrotation = 'H';
		this->Key_Leftturn = 'A';
		this->Key_Rightturn = 'D';
		this->Key_Firing = 'E';
		this->Key_Firingclock = 'R';
		this->Key_FrontSightSwitch = 'Z';
		this->Key_Aiming = 'Q';
		this->Key_Missilefiring = 'Q';
		//this->coordinates->z = 10000;
		break;
	}
	case 2:
	{
		this->name = "B";
		this->Name_Camera = "CameraB";
		COLOR = LIGHTBLUE;
		Color.z = 255;
		this->Key_Accelerate = 'I';
		this->Key_Retard = 'K';
		this->Key_Dive = VK_UP;
		this->Key_Pullup = VK_DOWN;
		this->Key_Leftrotation = VK_LEFT;
		this->Key_Rightrotation = VK_RIGHT;
		this->Key_Leftturn = 'J';
		this->Key_Rightturn = 'L';
		this->Key_Firing = 'O';
		this->Key_Firingclock = 'P';
		this->Key_FrontSightSwitch = 'M';
		this->Key_Aiming = 'U';
		this->Key_Missilefiring = 'U';
		this->coordinates.z -= 30;
		//this->coordinates->z = -10000;
		//Engine3D_Calculation Calculation;
		//*this->orientation = Calculation.Rotation(Calculation.Get_UnitVector("y", this->orientation), 3.1415926, this->orientation);
		break;
	}
	default:
		break;
	}

	this->object_num = 7;
	this->Object_list = new AirBattle_Object * [object_num];
	this->NowFindObject = NULL;
	
	Engine3D_Object* MainBody = new Engine3D_Object(0, 0, 0);
	//ÓÒÒí
	MainBody->Add_Triangle(Engine3D_Vector3D(8, -0.3, 5), Engine3D_Vector3D(0, -0.6, 5.3), Engine3D_Vector3D(2, -0.3, -3), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(2, -0.3, -3), Engine3D_Vector3D(8, -0.3, 5), Engine3D_Vector3D(2, 0.3, -1), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(8, -0.3, 5), Engine3D_Vector3D(0, -0.3, 5), Engine3D_Vector3D(2, 0.3, -1), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(8, -0.3, 5), Engine3D_Vector3D(0, -0.6, 5.3), Engine3D_Vector3D(0, -0.3, 5), Color, Radius);
	//×óÒí
	MainBody->Add_Triangle(Engine3D_Vector3D(-8, -0.3, 5), Engine3D_Vector3D(0, -0.6, 5.3), Engine3D_Vector3D(-2, -0.3, -3), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-2, -0.3, -3), Engine3D_Vector3D(-8, -0.3, 5), Engine3D_Vector3D(-2, 0.3, -1), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-8, -0.3, 5), Engine3D_Vector3D(0, -0.3, 5), Engine3D_Vector3D(-2, 0.3, -1), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-8, -0.3, 5), Engine3D_Vector3D(0, -0.6, 5.3), Engine3D_Vector3D(0, -0.3, 5), Color, Radius);
	//»úÍ·
	MainBody->Add_Triangle(Engine3D_Vector3D(2, -1, -3), Engine3D_Vector3D(-2, -1, -3), Engine3D_Vector3D(0, -1, -9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(2, -1, -3), Engine3D_Vector3D(2, 1, -3), Engine3D_Vector3D(0, -1, -9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-2, 1, -3), Engine3D_Vector3D(-2, -1, -3), Engine3D_Vector3D(0, -1, -9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(2, 1, -3), Engine3D_Vector3D(-2, 1, -3), Engine3D_Vector3D(0, -1, -9), Color, Radius);
	//ÓÒÎ²Òí
	MainBody->Add_Triangle(Engine3D_Vector3D(1, -0.5, 6.5), Engine3D_Vector3D(4.1, -0.5, 10.5), Engine3D_Vector3D(1, -0.5, 9.5), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(1, -0.5, 6.5), Engine3D_Vector3D(4.1, -0.5, 10.5), Engine3D_Vector3D(1, -0.2, 9.3), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(1, -0.5, 9.5), Engine3D_Vector3D(4.1, -0.5, 10.5), Engine3D_Vector3D(1, -0.2, 9.3), Color, Radius);
	//×óÎ²Òí
	MainBody->Add_Triangle(Engine3D_Vector3D(-1, -0.5, 6.5), Engine3D_Vector3D(-4.1, -0.5, 10.5), Engine3D_Vector3D(-1, -0.5, 9.5), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-1, -0.5, 6.5), Engine3D_Vector3D(-4.1, -0.5, 10.5), Engine3D_Vector3D(-1, -0.2, 9.3), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-1, -0.5, 9.5), Engine3D_Vector3D(-4.1, -0.5, 10.5), Engine3D_Vector3D(-1, -0.2, 9.3), Color, Radius);
	//»úÉí
	MainBody->Add_Triangle(Engine3D_Vector3D(-2, -1, -3), Engine3D_Vector3D(-1, -1, 9), Engine3D_Vector3D(1, -1, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-2, -1, -3), Engine3D_Vector3D(2, -1, -3), Engine3D_Vector3D(1, -1, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(2, -1, -3), Engine3D_Vector3D(2, 1, -3), Engine3D_Vector3D(1, 0, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(2, -1, -3), Engine3D_Vector3D(1, -1, 9), Engine3D_Vector3D(1, 0, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-2, -1, -3), Engine3D_Vector3D(-2, 1, -3), Engine3D_Vector3D(-1, 0, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-2, -1, -3), Engine3D_Vector3D(-1, -1, 9), Engine3D_Vector3D(-1, 0, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-2, 1, -3), Engine3D_Vector3D(2, 1, -3), Engine3D_Vector3D(1, 0, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-2, 1, -3), Engine3D_Vector3D(1, 0, 9), Engine3D_Vector3D(-1, 0, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-1, -1, 9), Engine3D_Vector3D(1, 0, 9), Engine3D_Vector3D(-1, 0, 9), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(-1, -1, 9), Engine3D_Vector3D(1, 0, 9), Engine3D_Vector3D(1, -1, 9), Color, Radius);
	//´¹Ö±Î²Òí
	MainBody->Add_Triangle(Engine3D_Vector3D(0, 0, 7), Engine3D_Vector3D(0.07, 0, 9), Engine3D_Vector3D(0, 2.7, 10), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(0, 0, 7), Engine3D_Vector3D(-0.07, 0, 9), Engine3D_Vector3D(0, 2.7, 10), Color, Radius);
	MainBody->Add_Triangle(Engine3D_Vector3D(0.07, 0, 9), Engine3D_Vector3D(-0.07, 0, 9), Engine3D_Vector3D(0, 2.7, 10), Color, Radius);

	this->Object_list[1] = new AirBattle_Object("MainBody", MainBody);
	this->Object_list[1]->Rotation_Degrees_Max.z = 28.6;

	MainBody = NULL;

	this->Object_list[2] = new AirBattle_Object("Camera", new Engine3D_Object(0, 3, 20));

	this->Object_list[3] = new AirBattle_Object("MachineGun", new Engine3D_Object(0, -1, 3));
	this->Object_list[3]->Rotation_Degrees_Max.z = this->Object_list[1]->Rotation_Degrees_Max.z;

	this->Object_list[0] = new AirBattle_Object("Centre", new Engine3D_Object(0, 0, 0));
	this->Object_list[0]->Object->Add_Line(new Engine3D_Point(0, 0, 0), new Engine3D_Point(0, 0, 0), COLOR, 0);

	this->Object_list[4] = new AirBattle_Object("LeftAileron", new Engine3D_Object(-4.5, -0.3, 4.5));
	this->Object_list[4]->Object->maxdegrees_rotation_object.x = 60;
	this->Object_list[4]->Object->Add_Triangle(Engine3D_Vector3D(-1.5, 0, 0.5), Engine3D_Vector3D(1.5, 0, 0.5), Engine3D_Vector3D(-1.5, 0, 0), Engine3D_Vector3D(255, 255, 255), Radius);
	this->Object_list[4]->Object->Add_Triangle(Engine3D_Vector3D(-1.5, 0, 0), Engine3D_Vector3D(1.5, 0, 0), Engine3D_Vector3D(1.5, 0, 0.5), Engine3D_Vector3D(255, 255, 255), Radius);
	/*this->Object_list[4]->Object->Add_Line(new Engine3D_Point(-1.5, 0, 0.5), new Engine3D_Point(1.5, 0, 0.5), WHITE, Radius);
	this->Object_list[4]->Object->Add_Line(new Engine3D_Point(-1.5, 0, 0.5), new Engine3D_Point(-1.5, 0, 0), WHITE, Radius);
	this->Object_list[4]->Object->Add_Line(new Engine3D_Point(1.5, 0, 0.5), new Engine3D_Point(1.5, 0, 0), WHITE, Radius);*/
	
	this->Object_list[5] = new AirBattle_Object("RightAileron", new Engine3D_Object(4.5, -0.3, 4.5));
	this->Object_list[5]->Object->maxdegrees_rotation_object.x = 60;
	this->Object_list[5]->Object->Add_Triangle(Engine3D_Vector3D(-1.5, 0, 0.5), Engine3D_Vector3D(1.5, 0, 0.5), Engine3D_Vector3D(-1.5, 0, 0), Engine3D_Vector3D(255, 255, 255), Radius);
	this->Object_list[5]->Object->Add_Triangle(Engine3D_Vector3D(-1.5, 0, 0), Engine3D_Vector3D(1.5, 0, 0), Engine3D_Vector3D(1.5, 0, 0.5), Engine3D_Vector3D(255, 255, 255), Radius);

	this->Object_list[6] = new AirBattle_Object("DetentHandle", new Engine3D_Object(0, -10, -7));
	this->Object_list[6]->Rotation_Degrees_Max.z = this->Object_list[1]->Rotation_Degrees_Max.z;

	return;
}

AirBattle_Warplane::~AirBattle_Warplane()
{
	if (this->Object_list != NULL)
	{
		for (int i = 0; i < this->object_num; i++)
		{
			delete this->Object_list[i];
			this->Object_list[i] = NULL;
		}
		delete[]this->Object_list;
		this->Object_list = NULL;
	}
	if (this->NowFindObject != NULL)
	{
		this->NowFindObject = NULL;
	}
	this->Camera = NULL;
	return;
}

void AirBattle_Warplane::Update__FUNC(AirBattle_Warplane* Enemy)
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	double TIME = NowTime - this->LastClock_Update;
	this->Aiming__FUNC(TIME, Enemy);
	if (Enemy->AimingProgress == 1)
	{
		this->Locked = true;
	}
	else
	{
		this->Locked = false;
	}
	this->Find_Object__FUNC("MachineGun")->Rotation_Degrees = this->Find_Object__FUNC("MainBody")->Rotation_Degrees;
	this->Find_Object__FUNC("LeftAileron")->Rotation_Degrees = this->Find_Object__FUNC("MainBody")->Rotation_Degrees;
	this->Find_Object__FUNC("RightAileron")->Rotation_Degrees = this->Find_Object__FUNC("MainBody")->Rotation_Degrees;
	for (int i = 0; i < this->object_num; i++)
	{
		this->Object_list[i]->Update__FUNC(this->coordinates, this->orientation);
	}
	this->LastClock_Update = NowTime;
	return;
}

void AirBattle_Warplane::Object_Rotation__FUNC(Engine3D_Object* Object, Engine3D_Vector3D rotation_axis, double theta)
{
	Object->coordinates_plane = (Object->orientation * Engine3D_Quaternion(Object->coordinates_plane) * Object->orientation.Inverse_Quaternion()).Quaternion_To_Vector3D();
	return;
}

void AirBattle_Warplane::Acceleration_Reset__FUNC()
{
	this->Acceleration_Translation = Engine3D_Vector3D(0, 0, 0);
	this->Acceleration_Rotation = Engine3D_Vector3D(0, 0, 0);
	return;
}

void AirBattle_Warplane::Adjustment__FUNC(double TIME, bool MODE_Game)
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	this->Acceleration_Reset__FUNC();
	if (!(GetAsyncKeyState(this->Key_Accelerate) && GetAsyncKeyState(this->Key_Retard)))
	{
		if (GetAsyncKeyState(this->Key_Accelerate) && this->Velocity_Translation.z > this->Velocity_Translation_Max.z)
		{
			if (this->Velocity_Translation.z <= this->Velocity_Translation_Constant.z)
			{
				this->Acceleration_Translation.z = -this->Maxacceleration_Translation;
			}
			else
			{
				this->Acceleration_Translation.z = 2 * -this->Maxacceleration_Translation;
			}
			if (this->Velocity_Translation.z + this->Acceleration_Translation.z * TIME < this->Velocity_Translation_Max.z)
			{
				this->Acceleration_Translation.z = 0;
				this->Velocity_Translation.z = this->Velocity_Translation_Max.z;
			}
		}
		else if (GetAsyncKeyState(this->Key_Retard) && this->Velocity_Translation.z < this->Velocity_Translation_Min.z)
		{
			if (this->Velocity_Translation.z >= this->Velocity_Translation_Constant.z)
			{
				this->Acceleration_Translation.z = this->Maxacceleration_Translation;
			}
			else
			{
				this->Acceleration_Translation.z = 2 * this->Maxacceleration_Translation;
			}
			if (this->Velocity_Translation.z + this->Acceleration_Translation.z * TIME > -this->Velocity_Translation_Max.z)
			{
				this->Acceleration_Translation.z = 0;
				this->Velocity_Translation.z = this->Velocity_Translation_Min.z;
			}
		}
		else
		{
			if (this->Velocity_Translation.z < this->Velocity_Translation_Constant.z)
			{
				if (this->Velocity_Translation.z + this->Maxacceleration_Translation * TIME > this->Velocity_Translation_Constant.z)
				{
					this->Acceleration_Translation.z = 0;
					this->Velocity_Translation.z = this->Velocity_Translation_Constant.z;
				}
				else
				{
					this->Acceleration_Translation.z = this->Maxacceleration_Translation;
				}
			}
			else if (this->Velocity_Translation.z > this->Velocity_Translation_Constant.z)
			{
				if (this->Velocity_Translation.z + this->Maxacceleration_Translation * TIME < this->Velocity_Translation_Constant.z)
				{
					this->Acceleration_Translation.z = 0;
					this->Velocity_Translation.z = this->Velocity_Translation_Constant.z;
				}
				else
				{
					this->Acceleration_Translation.z = -this->Maxacceleration_Translation;
				}
			}
		}
	}
	else
	{
		if (this->Velocity_Translation.z < this->Velocity_Translation_Constant.z)
		{
			if (this->Velocity_Translation.z + this->Maxacceleration_Translation * TIME > this->Velocity_Translation_Constant.z)
			{
				this->Acceleration_Translation.z = 0;
				this->Velocity_Translation.z = this->Velocity_Translation_Constant.z;
			}
			else
			{
				this->Acceleration_Translation.z = this->Maxacceleration_Translation;
			}
		}
		else if (this->Velocity_Translation.z > this->Velocity_Translation_Constant.z)
		{
			if (this->Velocity_Translation.z + this->Maxacceleration_Translation * TIME < this->Velocity_Translation_Constant.z)
			{
				this->Acceleration_Translation.z = 0;
				this->Velocity_Translation.z = this->Velocity_Translation_Constant.z;
			}
			else
			{
				this->Acceleration_Translation.z = -this->Maxacceleration_Translation;
			}
		}
	}
	if (!(GetAsyncKeyState(this->Key_Dive) && GetAsyncKeyState(this->Key_Pullup)))
	{
		if (GetAsyncKeyState(this->Key_Dive) && this->Velocity_Rotation.x > -this->Maxvelocity_Rotation)
		{
			if (this->Velocity_Rotation.x <= 0)
			{
				this->Acceleration_Rotation.x = -this->Maxacceleration_Rotation;
			}
			else
			{
				this->Acceleration_Rotation.x = -2.5 * this->Maxacceleration_Rotation;
			}
			if (this->Velocity_Rotation.x + this->Acceleration_Rotation.x * TIME < -this->Maxvelocity_Rotation)
			{
				this->Acceleration_Rotation.x = 0;
				this->Velocity_Rotation.x = -this->Maxvelocity_Rotation;
			}
		}
		else if (GetAsyncKeyState(this->Key_Pullup) && this->Velocity_Rotation.x < this->Maxvelocity_Rotation)
		{
			if (this->Velocity_Rotation.x >= 0)
			{
				this->Acceleration_Rotation.x = this->Maxacceleration_Rotation;
			}
			else
			{
				this->Acceleration_Rotation.x = 2.5 * this->Maxacceleration_Rotation;
			}
			if (this->Velocity_Rotation.x + this->Acceleration_Rotation.x * TIME > this->Maxvelocity_Rotation)
			{
				this->Acceleration_Rotation.x = 0;
				this->Velocity_Rotation.x = this->Maxvelocity_Rotation;
			}
		}
		else
		{
			if (this->Velocity_Rotation.x < 0)
			{
				this->Acceleration_Rotation.x = 1.5 * this->Maxacceleration_Rotation;
				if (this->Velocity_Rotation.x + this->Acceleration_Rotation.x * TIME > 0)
				{
					this->Acceleration_Rotation.x = 0;
					this->Velocity_Rotation.x = 0;
				}
			}
			else if (this->Velocity_Rotation.x > 0)
			{
				this->Acceleration_Rotation.x = -1.5 * this->Maxacceleration_Rotation;
				if (this->Velocity_Rotation.x + this->Acceleration_Rotation.x * TIME < 0)
				{
					this->Acceleration_Rotation.x = 0;
					this->Velocity_Rotation.x = 0;
				}
			}
		}
	}
	else
	{
		if (this->Velocity_Rotation.x < 0)
		{
			this->Acceleration_Rotation.x = 1.5 * this->Maxacceleration_Rotation;
			if (this->Velocity_Rotation.x + this->Acceleration_Rotation.x * TIME > 0)
			{
				this->Acceleration_Rotation.x = 0;
				this->Velocity_Rotation.x = 0;
			}
		}
		else if (this->Velocity_Rotation.x > 0)
		{
			this->Acceleration_Rotation.x = -1.5 * this->Maxacceleration_Rotation;
			if (this->Velocity_Rotation.x + this->Acceleration_Rotation.x * TIME < 0)
			{
				this->Acceleration_Rotation.x = 0;
				this->Velocity_Rotation.x = 0;
			}
		}
	}
	if (!(GetAsyncKeyState(this->Key_Leftrotation) && GetAsyncKeyState(this->Key_Rightrotation)))
	{
		if (GetAsyncKeyState(this->Key_Leftrotation) && this->Velocity_Rotation.z < this->Maxvelocity_Rotation)
		{
			if (this->Velocity_Rotation.z >= 0)
			{
				this->Acceleration_Rotation.z = this->Maxacceleration_Rotation;
			}
			else
			{
				this->Acceleration_Rotation.z = 2.5 * this->Maxacceleration_Rotation;
			}
			if (this->Velocity_Rotation.z + this->Acceleration_Rotation.z * TIME > this->Maxvelocity_Rotation)
			{
				this->Acceleration_Rotation.z = 0;
				this->Velocity_Rotation.z = this->Maxvelocity_Rotation;
			}
		}
		else if (GetAsyncKeyState(this->Key_Rightrotation) && this->Velocity_Rotation.z > -this->Maxvelocity_Rotation)
		{
			if (this->Velocity_Rotation.z <= 0)
			{
				this->Acceleration_Rotation.z = -this->Maxacceleration_Rotation;
			}
			else
			{
				this->Acceleration_Rotation.z = -2.5 * this->Maxacceleration_Rotation;
			}
			if (this->Velocity_Rotation.z + this->Acceleration_Rotation.z * TIME < -this->Maxvelocity_Rotation)
			{
				this->Acceleration_Rotation.z = 0;
				this->Velocity_Rotation.z = -this->Maxvelocity_Rotation;
			}
		}
		else
		{
			if (this->Velocity_Rotation.z < 0)
			{
				this->Acceleration_Rotation.z = 1.5 * this->Maxacceleration_Rotation;
				if (this->Velocity_Rotation.z + this->Acceleration_Rotation.z * TIME > 0)
				{
					this->Acceleration_Rotation.z = 0;
					this->Velocity_Rotation.z = 0;
				}
			}
			else if (this->Velocity_Rotation.z > 0)
			{
				this->Acceleration_Rotation.z = -1.5 * this->Maxacceleration_Rotation;
				if (this->Velocity_Rotation.z + this->Acceleration_Rotation.z * TIME < 0)
				{
					this->Acceleration_Rotation.z = 0;
					this->Velocity_Rotation.z = 0;
				}
			}
		}
	}
	else
	{
		if (this->Velocity_Rotation.z < 0)
		{
			this->Acceleration_Rotation.z = 1.5 * this->Maxacceleration_Rotation;
			if (this->Velocity_Rotation.z + this->Acceleration_Rotation.z * TIME > 0)
			{
				this->Acceleration_Rotation.z = 0;
				this->Velocity_Rotation.z = 0;
			}
		}
		else if (this->Velocity_Rotation.z > 0)
		{
			this->Acceleration_Rotation.z = -1.5 * this->Maxacceleration_Rotation;
			if (this->Velocity_Rotation.z + this->Acceleration_Rotation.z * TIME < 0)
			{
				this->Acceleration_Rotation.z = 0;
				this->Velocity_Rotation.z = 0;
			}
		}
	}
	if (!(GetAsyncKeyState(this->Key_Leftturn) && GetAsyncKeyState(this->Key_Rightturn)))
	{
		if (GetAsyncKeyState(this->Key_Leftturn))
		{
			/*this->Object_list[0]->orientation = new Engine3D_Quaternion(1, 0, 0, 0);
			this->Object_list[0]->orientation = Calculation.Rotation(Calculation.Get_UnitVector("z", this->Object_list[0]->orientation), 0.5, this->Object_list[0]->orientation);
			*/
			if (this->Velocity_Rotation.y < this->Maxvelocity_Rotation * 0.7)
			{
				
				if (this->Velocity_Rotation.y >= 0)
				{
					this->Acceleration_Rotation.y = this->Maxacceleration_Rotation * 0.7;
				}
				else
				{
					this->Acceleration_Rotation.y = 2.5 * this->Maxacceleration_Rotation * 0.7;
				}
				if (this->Velocity_Rotation.y + this->Acceleration_Rotation.y * TIME > this->Maxvelocity_Rotation * 0.7)
				{
					this->Acceleration_Rotation.y = 0;
					this->Velocity_Rotation.y = this->Maxvelocity_Rotation * 0.7;
				}
			}
		}
		else if (GetAsyncKeyState(this->Key_Rightturn))
		{
			if (this->Velocity_Rotation.y > -this->Maxvelocity_Rotation * 0.7)
			{
				if (this->Velocity_Rotation.y <= 0)
				{
					this->Acceleration_Rotation.y = -this->Maxacceleration_Rotation * 0.7;
				}
				else
				{
					this->Acceleration_Rotation.y = -2.5 * this->Maxacceleration_Rotation * 0.7;
				}
				if (this->Velocity_Rotation.y + this->Acceleration_Rotation.y * TIME < -this->Maxvelocity_Rotation * 0.7)
				{
					this->Acceleration_Rotation.y = 0;
					this->Velocity_Rotation.y = -this->Maxvelocity_Rotation * 0.7;
				}
			}
		}
		else
		{
			if (this->Velocity_Rotation.y < 0)
			{
				this->Acceleration_Rotation.y = 1.5 * this->Maxacceleration_Rotation * 0.7;
				if (this->Velocity_Rotation.y + this->Acceleration_Rotation.y * TIME > 0)
				{
					this->Acceleration_Rotation.y = 0;
					this->Velocity_Rotation.y = 0;
				}
			}
			else if (this->Velocity_Rotation.y > 0)
			{
				this->Acceleration_Rotation.y = -1.5 * this->Maxacceleration_Rotation * 0.7;
				if (this->Velocity_Rotation.y + this->Acceleration_Rotation.y * TIME < 0)
				{
					this->Acceleration_Rotation.y = 0;
					this->Velocity_Rotation.y = 0;
				}
			}
		}
	}
	else
	{
		if (this->Velocity_Rotation.y < 0)
		{
			this->Acceleration_Rotation.y = 1.5 * this->Maxacceleration_Rotation * 0.7;
			if (this->Velocity_Rotation.y + this->Acceleration_Rotation.y * TIME > 0)
			{
				this->Acceleration_Rotation.y = 0;
				this->Velocity_Rotation.y = 0;
			}
		}
		else if (this->Velocity_Rotation.y > 0)
		{
			this->Acceleration_Rotation.y = -1.5 * this->Maxacceleration_Rotation * 0.7;
			if (this->Velocity_Rotation.y + this->Acceleration_Rotation.y * TIME < 0)
			{
				this->Acceleration_Rotation.y = 0;
				this->Velocity_Rotation.y = 0;
			}
		}
	}
	if (GetAsyncKeyState(this->Key_FrontSightSwitch) && NowTime - this->LastClock_FrontSightSwitch > this->FrontSightSwitchInterval)
	{
		if (this->FrontSight_On)
		{
			this->FrontSight_On = false;
			if (this->FrontSight_Assist <= 0)
			{
				this->FrontSight_Assist = -2;
			}
		}
		else
		{
			this->FrontSight_On = true;
			if (this->FrontSight_Assist <= 0)
			{
				this->FrontSight_Assist = -1;
			}
		}
		this->LastClock_FrontSightSwitch = NowTime;
	}
	if (GetAsyncKeyState(this->Key_Aiming) && NowTime - this->LastClock_AimingSwitch > this->AimingInterval)
	{
		if (this->FrontSight_On && this->FrontSight_Assist <= this->FrontSight_Assist_Time / 2)
		{
			if (this->Aiming_On)
			{
				this->Aiming_On = false;
			}
			else
			{
				this->Aiming_On = true;
			}
			this->LastClock_AimingSwitch = NowTime;
		}
		else
		{
			this->FrontSight_On = true;
			if (this->FrontSight_Assist <= 0)
			{
				this->FrontSight_Assist = -1;
			}
			this->LastClock_FrontSightSwitch = NowTime;
		}
	}

	this->Find_Object__FUNC("MainBody");
	this->NowFindObject->Rotation_Degrees.z = this->NowFindObject->Rotation_Degrees_Max.z * this->Velocity_Rotation.y / this->Maxvelocity_Rotation;
	this->Find_Object__FUNC("LeftAileron");
	double Theta = -(this->NowFindObject->Object->maxdegrees_rotation_object.x * 0.4 * this->Velocity_Rotation.y / this->Maxvelocity_Rotation + this->NowFindObject->Object->maxdegrees_rotation_object.x * 0.6 * this->Velocity_Rotation.z / this->Maxvelocity_Rotation);
	this->NowFindObject->Object->degrees_rotation_object.x = Theta;
	this->Find_Object__FUNC("RightAileron");
	Theta = this->NowFindObject->Object->maxdegrees_rotation_object.x * 0.4 * this->Velocity_Rotation.y / this->Maxvelocity_Rotation + this->NowFindObject->Object->maxdegrees_rotation_object.x * 0.6 * this->Velocity_Rotation.z / this->Maxvelocity_Rotation;
	this->NowFindObject->Object->degrees_rotation_object.x = Theta;

	this->Velocity_Translation += this->Acceleration_Translation * TIME;
	this->Velocity_Rotation += this->Acceleration_Rotation * TIME;

	if (MODE_Game)
	{
		this->orientation = this->orientation * this->orientation.RotationFactor("x", this->Velocity_Rotation.x * TIME) * this->orientation.RotationFactor("y", this->Velocity_Rotation.y * TIME) * this->orientation.RotationFactor("z", this->Velocity_Rotation.z * TIME);
		this->coordinates += this->orientation.Get_UnitVector("z") * this->Velocity_Translation.z * TIME;
	}

	return;
}

AirBattle_Object* AirBattle_Warplane::Find_Object__FUNC(string Name)
{
	for (int i = 0; i < this->object_num; i++)
	{
		if (this->Object_list[i]->Name == Name)
		{
			this->NowFindObject = this->Object_list[i];
			return this->Object_list[i];
		}
	}
	this->NowFindObject = NULL;
	return NULL;
}

void AirBattle_Warplane::DMG_Taken__FUNC(string TYPE, AirBattle_Warplane* Charger)
{
	if (TYPE == "Gun")
	{
		this->ScreenDisplay_DMGTaken_Gun = this->ScreenDisplay_DMGTaken_Gun_Time;
		this->HP -= Charger->DMG_Gun * Charger->PNT_Gun / this->DFE_Gun;
	}
	else if (TYPE == "Missile")
	{
		this->ScreenDisplay_DMGTaken_Missile = this->ScreenDisplay_DMGTaken_Missile_Time;
		this->HP -= Charger->DMG_Missile * Charger->PNT_Missile / this->DFE_Missile;
	}
	if (this->HP <= 0)
	{
		this->OVER = true;
		this->Name_Defeater = Charger->name;
	}
	return;
}

void AirBattle_Warplane::Aiming__FUNC(double TIME, AirBattle_Warplane* Enemy)
{
	if (!this->FrontSight_On || (Enemy->coordinates - this->coordinates).GetLength() > this->AimingRange)
	{
		this->Aiming_On = false;
	}
	if (!this->Aiming_On && this->AimingProgress > 0)
	{
		this->AimingProgress -= this->AimingSpeed * TIME * 2;
		if (this->AimingProgress < 0)
		{
			this->AimingProgress = 0;
		}
	}
	if (this->FrontSight_Assist <= this->FrontSight_Assist_Time / 2 && this->FrontSight_On && this->Aiming_On)
	{
		this->AimingProgress += this->AimingSpeed * TIME;
		if (this->AimingProgress > 1)
		{
			this->AimingProgress = 1;
		}
	}
	return;
}

void AirBattle_Warplane::Camera_Display__FUNC()
{
	this->Find_Object__FUNC("Camera");
	this->NowFindObject->Object->coordinates_plane = this->NowFindObject->Object->coordinates_plane_constant;
	this->Camera->coordinates = this->NowFindObject->Object->coordinates_world;
	this->Camera->orientation = this->NowFindObject->Object->orientation;
	this->Camera->depth = this->Camera->depth_constant;
	this->CameraDisplayEffect_DMG_Taken__FUNC();
	this->CameraDisplayEffect_Motion__FUNC();
	return;
}

void AirBattle_Warplane::CameraDisplayEffect_DMG_Taken__FUNC()
{
	this->Find_Object__FUNC("Camera");
	if (this->ScreenDisplay_DMGTaken_Gun > 0)
	{
		double Sway = (rand() % 3 - 1) * pow(this->ScreenDisplay_DMGTaken_Gun / this->ScreenDisplay_DMGTaken_Gun_Time, 4) / 3;
		this->NowFindObject->Object->coordinates_plane += Engine3D_Vector3D(Sway, Sway, Sway);
	}
	if (this->ScreenDisplay_DMGTaken_Missile > 0)
	{
		double Sway = (rand() % 5 - 2) * pow(this->ScreenDisplay_DMGTaken_Missile / this->ScreenDisplay_DMGTaken_Missile_Time, 4);
		this->NowFindObject->Object->coordinates_plane += Engine3D_Vector3D(Sway, Sway, Sway);
		this->Camera->depth += 0.5 * pow(this->ScreenDisplay_DMGTaken_Missile / this->ScreenDisplay_DMGTaken_Missile_Time, 4);
	}
	return;
}

void AirBattle_Warplane::CameraDisplayEffect_Motion__FUNC()
{
	this->Find_Object__FUNC("Camera");
	this->NowFindObject->Object->coordinates_plane.z += this->CameraEffect_Translation * (this->Velocity_Translation.GetLength() - this->Velocity_Translation_Constant.GetLength());
	this->Camera->orientation = this->Camera->orientation * this->Camera->orientation.RotationFactor("x", this->CameraEffect_Rotation * -this->Velocity_Rotation.x) * this->Camera->orientation.RotationFactor("y", this->CameraEffect_Rotation * -this->Velocity_Rotation.y) * this->Camera->orientation.RotationFactor("z", this->CameraEffect_Rotation * -this->Velocity_Rotation.z);
	this->Camera->depth -= this->CameraEffect_Depth * (this->Velocity_Translation.GetLength() - this->Velocity_Translation_Constant.GetLength());
	return;
}

void AirBattle_Warplane::Screen_Display__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize, AirBattle_Warplane* Enemy, double X)
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	double TIME = NowTime - this->LastClock_ScreenDisplay;
	this->ScreenDisplayEffect_DMG_Taken__FUNC(Centre, TIME, ScreenSize);
	this->ScreenDisplayEffect_Locked__FUNC(Centre, ScreenSize, Enemy);
	this->ScreenDisplayEffect_GunFiringHeat__FUNC(Centre, ScreenSize);
	this->ScreenDisplayEffect_MissileFiringHeat__FUNC(Centre, ScreenSize);
	this->ScreenDisplayEffect_EnemyArrow__FUNC(Centre, ScreenSize, Enemy, X);
	this->ScreenDisplayEffect_FrontSight__FUNC(Centre, ScreenSize, Enemy, X, TIME);
	this->ScreenDisplayEffect_Over__FUNC(Centre, ScreenSize);
	this->LastClock_ScreenDisplay = NowTime;
	return;
}

void AirBattle_Warplane::ScreenDisplayEffect_DMG_Taken__FUNC(Engine3D_Vector2D Centre, double TIME, Engine3D_Vector2D ScreenSize)
{
	if (this->ScreenDisplay_DMGTaken_Gun > 0)
	{
		int effect_length = 70;
		int opacity = 255 * pow(this->ScreenDisplay_DMGTaken_Gun / this->ScreenDisplay_DMGTaken_Gun_Time, 4);
		setlinecolor(RGB(opacity, 0, 0));
		setfillcolor(RGB(opacity, 0, 0));		
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, ScreenSize.y, Centre.x - ScreenSize.x / 4 + 10 + effect_length * pow(this->ScreenDisplay_DMGTaken_Gun / this->ScreenDisplay_DMGTaken_Gun_Time, 4), 0);
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, effect_length * pow(this->ScreenDisplay_DMGTaken_Gun / this->ScreenDisplay_DMGTaken_Gun_Time, 4), Centre.x + ScreenSize.x / 4 - 10, 0);
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, ScreenSize.y, Centre.x + ScreenSize.x / 4 - 10, ScreenSize.y - effect_length * pow(this->ScreenDisplay_DMGTaken_Gun / this->ScreenDisplay_DMGTaken_Gun_Time, 4));
		fillrectangle(Centre.x + ScreenSize.x / 4 - 10 - effect_length * pow(this->ScreenDisplay_DMGTaken_Gun / this->ScreenDisplay_DMGTaken_Gun_Time, 4), ScreenSize.y, Centre.x + ScreenSize.x / 4 - 10, 0);
		this->ScreenDisplay_DMGTaken_Gun -= TIME;
	}
	if (this->ScreenDisplay_DMGTaken_Missile > 0)
	{
		int effect_length = 500;
		int opacity = 255 * pow(this->ScreenDisplay_DMGTaken_Missile / this->ScreenDisplay_DMGTaken_Missile_Time, 4);
		setlinecolor(RGB(opacity, 0, 0));
		setfillcolor(RGB(opacity, 0, 0));
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, ScreenSize.y, Centre.x - ScreenSize.x / 4 + 10 + effect_length * pow(this->ScreenDisplay_DMGTaken_Missile / this->ScreenDisplay_DMGTaken_Missile_Time, 4), 0);
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, effect_length * pow(this->ScreenDisplay_DMGTaken_Missile / this->ScreenDisplay_DMGTaken_Missile_Time, 4), Centre.x + ScreenSize.x / 4 - 10, 0);
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, ScreenSize.y, Centre.x + ScreenSize.x / 4 - 10, ScreenSize.y - effect_length * pow(this->ScreenDisplay_DMGTaken_Missile / this->ScreenDisplay_DMGTaken_Missile_Time, 4));
		fillrectangle(Centre.x + ScreenSize.x / 4 - 10 - effect_length * pow(this->ScreenDisplay_DMGTaken_Missile / this->ScreenDisplay_DMGTaken_Missile_Time, 4), ScreenSize.y, Centre.x + ScreenSize.x / 4 - 10, 0);
		this->ScreenDisplay_DMGTaken_Missile -= TIME;
	}
	return;
}

void AirBattle_Warplane::ScreenDisplayEffect_Over__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize)
{
	if (this->HP <= 0)
	{
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, ScreenSize.y, Centre.x + ScreenSize.x / 4 - 10, 0);
	}
	return;
}

void AirBattle_Warplane::ScreenDisplayEffect_EnemyArrow__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize, AirBattle_Warplane* Enemy, double X)
{
	setlinecolor(LIGHTGREEN);
	setfillcolor(LIGHTGREEN);
	setlinestyle(PS_SOLID, 3);
	Engine3D_Vector2D ScreenCoordinates(0, 0);
	//fillrectangle(Centre.x - ScreenSize.x / 4 + 10, ScreenSize.y, Centre.x + ScreenSize.x / 4 - 10, 0);
	Engine3D_Vector3D CoordinatesCamera;
	Engine3D_Vector2D CoordinatesScreen;
	Enemy->Find_Object__FUNC("Centre");
	if (this->ID == 1)
	{
		CoordinatesCamera = Enemy->NowFindObject->Object->Linelist[0]->Point_A->coordinates_camera[0];
		CoordinatesScreen = Enemy->NowFindObject->Object->Linelist[0]->Point_A->coordinates_screen[0];
	}
	else
	{
		CoordinatesCamera = Enemy->NowFindObject->Object->Linelist[0]->Point_A->coordinates_camera[1];
		CoordinatesScreen = Enemy->NowFindObject->Object->Linelist[0]->Point_A->coordinates_screen[1];
	}
	if (CoordinatesCamera.z > 0 || CoordinatesScreen.x * X < -ScreenSize.x / 4 + 10 || CoordinatesScreen.x * X > ScreenSize.x / 4 - 10 || CoordinatesScreen.y * X < -ScreenSize.y / 2 || CoordinatesScreen.y * X > ScreenSize.y / 2)
	{
		ScreenCoordinates.x = CoordinatesScreen.x * X;
		ScreenCoordinates.y = CoordinatesScreen.y * X;
		if (CoordinatesCamera.z > 0)
		{
			ScreenCoordinates.x = -ScreenCoordinates.x;
			ScreenCoordinates.y = -ScreenCoordinates.y;
		}
		ScreenCoordinates = ScreenCoordinates * ((ScreenSize.x / 4 - 10 + ScreenSize.y / 2) / 2.5 / ScreenCoordinates.GetLength());
		//line(Centre.x + ScreenCoordinates.x / 1.05, Centre.y - ScreenCoordinates.y / 1.05, Centre.x + ScreenCoordinates.x, Centre.y - ScreenCoordinates.y);
		double Theta = Engine3D_Vector2D(1, 0).VetorialAngle(ScreenCoordinates);//½Ç¶È
		double theta = DegreetoRadian(160 + Theta);
		line(Centre.x + ScreenCoordinates.x + 13 * cos(theta), Centre.y - ScreenCoordinates.y - 13 * sin(theta), Centre.x + ScreenCoordinates.x, Centre.y - ScreenCoordinates.y);
		theta = DegreetoRadian(-160 + Theta);
		line(Centre.x + ScreenCoordinates.x + 13 * cos(theta), Centre.y - ScreenCoordinates.y - 13 * sin(theta), Centre.x + ScreenCoordinates.x, Centre.y - ScreenCoordinates.y);
	}
	return;
}

void AirBattle_Warplane::ScreenDisplayEffect_FrontSight__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize, AirBattle_Warplane* Enemy, double X, double TIME)
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	Engine3D_Vector3D CoordinatesCamera;
	Engine3D_Vector2D CoordinatesScreen;
	Enemy->Find_Object__FUNC("Centre");
	if (this->ID == 1)
	{
		CoordinatesCamera = Enemy->NowFindObject->Object->Linelist[0]->Point_A->coordinates_camera[0];
		CoordinatesScreen = Enemy->NowFindObject->Object->Linelist[0]->Point_A->coordinates_screen[0];
	}
	else
	{
		CoordinatesCamera = Enemy->NowFindObject->Object->Linelist[0]->Point_A->coordinates_camera[1];
		CoordinatesScreen = Enemy->NowFindObject->Object->Linelist[0]->Point_A->coordinates_screen[1];
	}
	if (CoordinatesCamera.z > 0 || CoordinatesScreen.x * X < -ScreenSize.x / 4 + 10 || CoordinatesScreen.x * X > ScreenSize.x / 4 - 10 || CoordinatesScreen.y * X < -ScreenSize.y / 2 || CoordinatesScreen.y * X > ScreenSize.y / 2)
	{
		if (this->Aiming_On)
		{
			this->Aiming_On = false;
			this->LastClock_AimingSwitch = NowTime;
		}
		this->FrontSight_Assist = -1;
		return;
	}
	else if (this->FrontSight_Assist == -1)
	{
		this->FrontSight_Assist = this->FrontSight_Assist_Time;
	}
	else if (this->FrontSight_Assist == -2)
	{
		this->FrontSight_Assist = this->FrontSight_Assist_Time / 2;
	}
	if (!this->FrontSight_On && this->FrontSight_Assist == 0)
	{
		return;
	}
	int opacity = 255;
	double radius = 0;
	if (ScreenSize.x / 4 - 10 < ScreenSize.y / 2)
	{
		radius = ScreenSize.x / 4 - 10;
	}
	else
	{
		radius = ScreenSize.y / 2;
	}
	Engine3D_Vector3D Camera_CoordinatesPlane(this->Find_Object__FUNC("Camera")->Object->coordinates_plane);
	radius = radius * Camera_CoordinatesPlane.GetLength() / (Camera_CoordinatesPlane.GetLength() + (Enemy->coordinates - (this->coordinates + Camera_CoordinatesPlane)).GetLength());
	if (radius < 10)
	{
		radius = 10;
	}
	double size = radius / 1.5;
	if (this->FrontSight_Assist > 0)
	{
		if (this->FrontSight_Assist > this->FrontSight_Assist_Time / 2)
		{
			radius *= pow(this->FrontSight_Assist / this->FrontSight_Assist_Time * 2, 2);
			size *= pow(this->FrontSight_Assist / this->FrontSight_Assist_Time * 2, 1.5);
			if (this->FrontSight_Assist - TIME < this->FrontSight_Assist_Time / 2)
			{
				this->FrontSight_Assist = this->FrontSight_Assist_Time / 2;
			}
		}
		if (!this->FrontSight_On && this->FrontSight_Assist < this->FrontSight_Assist_Time / 2)
		{
			size *= sqrt(this->FrontSight_Assist / this->FrontSight_Assist_Time * 2);
			opacity *= sqrt(this->FrontSight_Assist / this->FrontSight_Assist_Time * 2);
		}
		this->FrontSight_Assist -= TIME;
		if (this->FrontSight_Assist < 0)
		{
			this->FrontSight_Assist = 0;
		}
	}
	double DegreeTHETA = 0;
	if (this->AimingProgress > 1)
	{
		DegreeTHETA = this->FrontSightDegree + 45 + 45 * sqrt(this->AimingProgress - 1);
	}
	else
	{
		DegreeTHETA = this->FrontSightDegree + 45 * sqrt(this->AimingProgress);
	}
	double RadiusTheta = 0;
	double DegreeTheta = DegreeTHETA;
	CoordinatesScreen.x = Centre.x + CoordinatesScreen.x * X;
	CoordinatesScreen.y = Centre.y - CoordinatesScreen.y * X;
	radius = sqrt(radius * radius * 2);
	if ((Enemy->coordinates - this->coordinates).GetLength() > this->AimingRange)
	{
		opacity *= 0.7;
	}
	if (this->AimingProgress == 1)
	{
		setlinecolor(RGB(0, 255, 0));
		setfillcolor(RGB(0, 255, 0));
	}
	else
	{
		setlinecolor(RGB(opacity, opacity, opacity));
		setfillcolor(RGB(opacity, opacity, opacity));
	}
	setlinestyle(PS_SOLID, 2);
	DegreeTheta -= 45;
	for (int i = 0; i < 4; i++)
	{
		DegreeTheta += 90;
		RadiusTheta = DegreetoRadian(DegreeTheta);
		line(CoordinatesScreen.x + radius * cos(RadiusTheta), CoordinatesScreen.y - radius * sin(RadiusTheta), CoordinatesScreen.x + radius * cos(RadiusTheta) + size * cos(RadiusTheta + 0.75 * PI), CoordinatesScreen.y - radius * sin(RadiusTheta) - size * sin(RadiusTheta + 0.75 * PI));
		line(CoordinatesScreen.x + radius * cos(RadiusTheta), CoordinatesScreen.y - radius * sin(RadiusTheta), CoordinatesScreen.x + radius * cos(RadiusTheta) + size * cos(RadiusTheta - 0.75 * PI), CoordinatesScreen.y - radius * sin(RadiusTheta) - size * sin(RadiusTheta - 0.75 * PI));
	}
	if (this->AimingProgress != 0)
	{
		RadiusTheta = 0;
		DegreeTheta = DegreeTHETA;
		radius *= 0.5;
		double gap = radius * pow(1 - this->AimingProgress, 3) * 3;
		size *= 1.3 - radius * pow(1 - this->AimingProgress, 3) / radius;
		double aimingangle = 0.2 * PI;
		opacity = 255 * (1 - pow(1 - sqrt(this->AimingProgress), 1.2));
		setlinecolor(RGB(opacity, 0, 0));
		setfillcolor(RGB(opacity, 0, 0));
		setlinestyle(PS_SOLID, 2);
		for (int i = 0; i < 4; i++)
		{
			DegreeTheta += 90;
			RadiusTheta = DegreetoRadian(DegreeTheta);
			line(CoordinatesScreen.x + radius * cos(RadiusTheta) + gap * cos(RadiusTheta + aimingangle), CoordinatesScreen.y - radius * sin(RadiusTheta) - gap * sin(RadiusTheta + aimingangle), CoordinatesScreen.x + radius * cos(RadiusTheta) + gap * cos(RadiusTheta + aimingangle) + size * cos(RadiusTheta + aimingangle), CoordinatesScreen.y - radius * sin(RadiusTheta) - gap * sin(RadiusTheta + aimingangle) - size * sin(RadiusTheta + aimingangle));
			line(CoordinatesScreen.x + radius * cos(RadiusTheta) + gap * cos(RadiusTheta - aimingangle), CoordinatesScreen.y - radius * sin(RadiusTheta) - gap * sin(RadiusTheta - aimingangle), CoordinatesScreen.x + radius * cos(RadiusTheta) + gap * cos(RadiusTheta - aimingangle) + size * cos(RadiusTheta - aimingangle), CoordinatesScreen.y - radius * sin(RadiusTheta) - gap * sin(RadiusTheta - aimingangle) - size * sin(RadiusTheta - aimingangle));
		}
	}
	return;
}

void AirBattle_Warplane::ScreenDisplayEffect_Locked__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize, AirBattle_Warplane* Enemy)
{
	if (Enemy->AimingProgress > 0)
	{
		int effect_length = 30;
		setlinecolor(RGB(180 * Enemy->AimingProgress, (180 * (1 - Enemy->AimingProgress) + 100) * Enemy->AimingProgress, 0));
		setfillcolor(RGB(180 * Enemy->AimingProgress, (180 * (1 - Enemy->AimingProgress) + 100) * Enemy->AimingProgress, 0));
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, ScreenSize.y, Centre.x - ScreenSize.x / 4 + 10 + effect_length * pow(Enemy->AimingProgress, 1.5), 0);
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, effect_length * pow(Enemy->AimingProgress, 1.5), Centre.x + ScreenSize.x / 4 - 10, 0);
		fillrectangle(Centre.x - ScreenSize.x / 4 + 10, ScreenSize.y, Centre.x + ScreenSize.x / 4 - 10, ScreenSize.y - effect_length * pow(Enemy->AimingProgress, 1.5));
		fillrectangle(Centre.x + ScreenSize.x / 4 - 10 - effect_length * pow(Enemy->AimingProgress, 1.5), ScreenSize.y, Centre.x + ScreenSize.x / 4 - 10, 0);
	}
	return;
}

void AirBattle_Warplane::ScreenDisplayEffect_GunFiringHeat__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize)
{
	if (this->GunFiringHeatProgress > 0)
	{
		int effect_borderwidth = 3;
		int effect_length = 200;
		int effect_width = 15;
		Engine3D_Vector2D lowerleftpoint(Centre.x - ScreenSize.x / 4 + 30, Centre.y + ScreenSize.y / 2 - 100);
		setlinestyle(PS_SOLID, effect_borderwidth);
		if (this->GunFiringHeatProgress == 1)
		{
			setlinecolor(RGB(255, 0, 0));
		}
		else
		{
			setlinecolor(RGB(255, 255, 255));
		}
		setfillcolor(RGB(0, 0, 0));
		fillrectangle(lowerleftpoint.x - effect_borderwidth, lowerleftpoint.y + effect_borderwidth, lowerleftpoint.x + effect_length + effect_borderwidth, lowerleftpoint.y - effect_width - effect_borderwidth);
		int G = 255 - 200 * (this->GunFiringHeatProgress - 0.8) / 0.2;
		if (this->GunFiringHeatProgress < 0.8)
		{
			G = 255;
		}
		setlinecolor(RGB(255, G, 0));
		setfillcolor(RGB(255, G, 0));
		fillrectangle(lowerleftpoint.x, lowerleftpoint.y, lowerleftpoint.x + effect_length * this->GunFiringHeatProgress, lowerleftpoint.y - effect_width);
	}
	return;
}

void AirBattle_Warplane::ScreenDisplayEffect_MissileFiringHeat__FUNC(Engine3D_Vector2D Centre, Engine3D_Vector2D ScreenSize)
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	if (NowTime - this->LastClock_MissileFiring < this->MissileFiringInterval)
	{
		int effect_borderwidth = 3;
		int effect_length = 200;
		int effect_width = 15;
		Engine3D_Vector2D lowerleftpoint(Centre.x - ScreenSize.x / 4 + 30, Centre.y + ScreenSize.y / 2 - 70);
		setlinestyle(PS_SOLID, effect_borderwidth);
		setlinecolor(RGB(255, 255, 255));
		setfillcolor(RGB(0, 0, 0));
		fillrectangle(lowerleftpoint.x - effect_borderwidth, lowerleftpoint.y + effect_borderwidth, lowerleftpoint.x + effect_length + effect_borderwidth, lowerleftpoint.y - effect_width - effect_borderwidth);
		double Progress = (NowTime - this->LastClock_MissileFiring) / this->MissileFiringInterval;
		int R = 255 - 100 * pow(Progress, 3);
		int G = 55 + 200 * pow(Progress, 3);
		setlinecolor(RGB(R, G, 0));
		setfillcolor(RGB(R, G, 0));
		fillrectangle(lowerleftpoint.x, lowerleftpoint.y, lowerleftpoint.x + effect_length * Progress, lowerleftpoint.y - effect_width);
	}
	return;
}
