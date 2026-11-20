#include"AirBattle_Missile.h"

AirBattle_Missile::AirBattle_Missile(AirBattle_Warplane* Warplane)
{
	this->shouldDestroy = false;
	this->isBooming = false;
	this->warplaneName = Warplane->name;
	this->goalName = Warplane->Name_Enemy;
	this->objectsListID = 0;
	this->firingClock = GetTime_Second_AccurateToMicrosecond();
	this->accelerationTime = 4;
	this->aimingTime = 1;
	this->aimingState = 0;
	this->objectPtr = new Engine3D_Object();
	this->objectPtr->coordinates_world = Engine3D_Vector3D(Warplane->Find_Object__FUNC("DetentHandle")->Object->coordinates_world);
	this->objectPtr->orientation = Engine3D_Quaternion(Warplane->Find_Object__FUNC("DetentHandle")->Object->orientation);
	this->coordinate = this->objectPtr->coordinates_world;
	this->orientation = this->objectPtr->orientation;
	this->translationVelocity = Warplane->Velocity_Translation + Engine3D_Vector3D(0, -40 + Warplane->Velocity_Rotation.x * 1.5, 6);
	this->translationVelocity_Constant = Engine3D_Vector3D(0, 0, -3000);
	this->translationVelocity_Start = Warplane->Velocity_Translation;
	this->translationAcceleration = Engine3D_Vector3D(0, 100, (this->translationVelocity_Constant.z - this->translationVelocity.z) / this->accelerationTime);
	this->rotationVelocity = Engine3D_Vector3D();
	this->rotationVelocity_Max = 0;
	this->rotationSpeed_Basics = 25;
	this->rotationSpeed_Addition = 240;//325必中 270可能必中
	this->destructionTime = 5;
	this->lostTargetClock = 0;
	this->boomTime = 5;
	this->boomClock = 0;
	this->boomColorsListPtr = NULL;
	get<0>(this->boomCoordinatesListPtrsList) = NULL;
	get<1>(this->boomCoordinatesListPtrsList) = NULL;
	get<2>(this->boomCoordinatesListPtrsList) = NULL;
	//this->Object->Add_Triangle(Engine3D_Vector3D(-5, 0, 15), Engine3D_Vector3D(5, 0, 15), Engine3D_Vector3D(0, 0, -15), Engine3D_Vector3D(255, 0, 255), true);
	//this->Object->Add_Triangle(Engine3D_Vector3D(-5, 5, 15), Engine3D_Vector3D(5, 5, 15), Engine3D_Vector3D(0, 5, -15), Engine3D_Vector3D(0, 255, 255), true);
	Engine3D_Vector3D Color(255, 255, 255);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, 1, -6), Engine3D_Vector3D(1, 1, -6), Engine3D_Vector3D(0, 0, -8), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, 1, -6), Engine3D_Vector3D(-1, -1, -6), Engine3D_Vector3D(0, 0, -8), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(1, 1, -6), Engine3D_Vector3D(1, -1, -6), Engine3D_Vector3D(0, 0, -8), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, -1, -6), Engine3D_Vector3D(1, -1, -6), Engine3D_Vector3D(0, 0, -8), Color, true);

	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, -1, -6), Engine3D_Vector3D(1, -1, -6), Engine3D_Vector3D(-1, -1, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, -1, 6), Engine3D_Vector3D(1, -1, 6), Engine3D_Vector3D(1, -1, -6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, 1, -6), Engine3D_Vector3D(-1, -1, -6), Engine3D_Vector3D(-1, 1, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, -1, 6), Engine3D_Vector3D(-1, -1, -6), Engine3D_Vector3D(-1, 1, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(1, 1, -6), Engine3D_Vector3D(1, -1, -6), Engine3D_Vector3D(1, 1, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(1, -1, 6), Engine3D_Vector3D(1, -1, -6), Engine3D_Vector3D(1, 1, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, 1, -6), Engine3D_Vector3D(1, 1, -6), Engine3D_Vector3D(-1, 1, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, 1, 6), Engine3D_Vector3D(1, 1, 6), Engine3D_Vector3D(1, 1, -6), Color, true);
	Color = Engine3D_Vector3D(255, 255, 0);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(1, 0, 0), Engine3D_Vector3D(1, 0, 6), Engine3D_Vector3D(2, 0, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-1, 0, 0), Engine3D_Vector3D(-1, 0, 6), Engine3D_Vector3D(-2, 0, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(0, 1, 0), Engine3D_Vector3D(0, 1, 6), Engine3D_Vector3D(0, 2, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(0, -1, 0), Engine3D_Vector3D(0, -1, 6), Engine3D_Vector3D(0, -2, 6), Color, true);
	Color = Engine3D_Vector3D(0, 255, 255);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(1, 1, 6), Engine3D_Vector3D(-1, 1, 6), Engine3D_Vector3D(-1, -1, 6), Color, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(1, 1, 6), Engine3D_Vector3D(1, -1, 6), Engine3D_Vector3D(-1, -1, 6), Color, true);
	Color = Engine3D_Vector3D(0, 0, 0);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-0.8, 0.8, 6), Engine3D_Vector3D(0.8, 0.8, 6), Engine3D_Vector3D(0, 0, 6), Color, true, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-0.8, 0.8, 6), Engine3D_Vector3D(-0.8, -0.8, 6), Engine3D_Vector3D(0, 0, 6), Color, true, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(0.8, 0.8, 6), Engine3D_Vector3D(0.8, -0.8, 6), Engine3D_Vector3D(0, 0, 6), Color, true, true);
	this->objectPtr->Add_Triangle(Engine3D_Vector3D(-0.8, -0.8, 6), Engine3D_Vector3D(0.8, -0.8, 6), Engine3D_Vector3D(0, 0, 6), Color, true, true);
	return;
}

AirBattle_Missile::~AirBattle_Missile()
{
	if (this->objectPtr != NULL)
	{
		delete this->objectPtr;
		this->objectPtr = NULL;
	}
	return;
}

int AirBattle_Missile::update(double TIME, AirBattle_Warplane* Goal, int Aiming)
{
	double CLOCK = GetTime_Second_AccurateToMicrosecond();
	if (CLOCK - this->lostTargetClock > this->destructionTime && this->aimingState == -1)
	{
		this->isBooming = true;
	}
	if (this->isBooming)
	{		
		return this->booming() * -1;
	}
	this->update_Fire();
	this->coordinate = this->objectPtr->coordinates_world;
	/*if (GoalVec.x > 0)
	{
		this->Acceleration_Rotation.y = this->Maxacceleration_Rotation * GoalVec.x;
	}
	else
	{
		this->Acceleration_Rotation.y = this->Maxacceleration_Rotation * GoalVec.x;
	}
	if (GoalVec.y > 0)
	{
		this->Acceleration_Rotation.x = this->Maxacceleration_Rotation * GoalVec.y;
	}
	else
	{
		this->Acceleration_Rotation.x = this->Maxacceleration_Rotation * GoalVec.y;
	}
	if (GoalVec.z < 0)
	{
		cout << GoalVec.x << "	" << GoalVec.y << endl;
	}
	this->Velocity_Rotation += this->Acceleration_Rotation * TIME;
	if (this->Velocity_Rotation.GetLength() > this->Maxvelocity_Rotation)
	{
		this->Velocity_Rotation = this->Velocity_Rotation.UnitVector() * this->Maxvelocity_Rotation;
	}
	this->orientation = this->orientation * this->orientation.RotationFactor("x", this->Velocity_Rotation.x * TIME) * this->orientation.RotationFactor("y", this->Velocity_Rotation.y * TIME) * this->orientation.RotationFactor("z", this->Velocity_Rotation.z * TIME);*/
	if (this->aimingState == 0)
	{
		if (CLOCK - this->firingClock >= this->aimingTime)
		{
			this->aimingState = 1;
		}
	}
	if (this->aimingState == 1)// && Aiming == 1)
	{
		Engine3D_Vector3D DirectionVec = Goal->coordinates - this->coordinate;
		this->rotationVelocity_Max = this->rotationSpeed_Basics;
		DirectionVec = (this->orientation.Inverse_Quaternion() * Engine3D_Quaternion(DirectionVec) * this->orientation).Quaternion_To_Vector3D();
		if (DirectionVec.z < 0)
		{
			if (DirectionVec.z > Goal->Velocity_Translation.z * 2)
			{
				this->rotationVelocity_Max += this->rotationSpeed_Addition * pow((Goal->Velocity_Translation.z * -2 + DirectionVec.z) / Goal->Velocity_Translation.z * -0.5, 3);
			}
			if (DirectionVec.x > 0)
			{
				this->rotationVelocity.y = -this->rotationVelocity_Max;
			}
			else
			{
				this->rotationVelocity.y = this->rotationVelocity_Max;
			}
			if (DirectionVec.y > 0)
			{
				this->rotationVelocity.x = this->rotationVelocity_Max;
			}
			else
			{
				this->rotationVelocity.x = -this->rotationVelocity_Max;
			}
		}
		else
		{
			this->aimingState = -1;
			this->lostTargetClock = CLOCK;
		}
		//this->orientation = Engine3D_Quaternion((Goal - this->coordinates).UnitVector());
		this->orientation = this->orientation * this->orientation.RotationFactor("x", this->rotationVelocity.x * TIME) * this->orientation.RotationFactor("y", this->rotationVelocity.y * TIME) * this->orientation.RotationFactor("z", this->rotationVelocity.z * TIME);
		//this->orientation = this->orientation.Rotation(this->orientation.Get_UnitVector("z"), 180);
	}
	this->translationVelocity += this->translationAcceleration * TIME;
	if (this->translationVelocity.z < this->translationVelocity_Constant.z)
	{
		this->translationVelocity.z = this->translationVelocity_Constant.z;
		this->translationAcceleration.z = 0;
	}
	if (this->translationVelocity.y > 0)
	{
		this->translationVelocity.y = 0;
		this->translationAcceleration.y = 0;
	}
	this->coordinate += this->orientation.Get_UnitVector("x") * this->translationVelocity.x * TIME + this->orientation.Get_UnitVector("y") * this->translationVelocity.y * TIME + this->orientation.Get_UnitVector("z") * this->translationVelocity.z * TIME;
	this->objectPtr->coordinates_world = this->coordinate;
	this->objectPtr->orientation = this->orientation;
	if ((this->coordinate - Goal->coordinates).GetLength() < 20)
	{
		this->isBooming = true;
		return 1;
	}

	/*if ((*this->Object->coordinates_world - *this->coordinates_start).GetLength() > this->distance)
	{
		this->destruction = true;
	}
	else
	{
		this->danger_radius = this->danger_radius_basics + this->danger_radius_additional * (*this->Object->coordinates_world - *this->coordinates_start).GetLength() / this->distance;
	}*/
	return 0;
}

void AirBattle_Missile::update_Fire()
{
	for (int i = this->objectPtr->trianglenum - 1; i > this->objectPtr->trianglenum - 5; i--)
	{
		this->objectPtr->Trianglelist[i]->color_constant.x = 255 * pow((this->translationVelocity.z - this->translationVelocity_Start.z) / (this->translationVelocity_Constant.z - this->translationVelocity_Start.z), 0.3);
		this->objectPtr->Trianglelist[i]->Point_C->coordinates_object.z = 6 + 7 * pow((this->translationVelocity.z - this->translationVelocity_Start.z) / (this->translationVelocity_Constant.z - this->translationVelocity_Start.z), 0.3);
	}
	return;
}

bool AirBattle_Missile::booming()
{
	double Clock = GetTime_Second_AccurateToMicrosecond();
	if (this->boomClock == 0)
	{
		this->boomClock = Clock;
		this->boomColorsListPtr = new Engine3D_Vector3D[this->objectPtr->trianglenum];
		get<0>(this->boomCoordinatesListPtrsList) = new Engine3D_Vector3D[this->objectPtr->trianglenum];
		get<1>(this->boomCoordinatesListPtrsList) = new Engine3D_Vector3D[this->objectPtr->trianglenum];
		get<2>(this->boomCoordinatesListPtrsList) = new Engine3D_Vector3D[this->objectPtr->trianglenum];
		for (int i = 0; i < this->objectPtr->trianglenum; i++)
		{
			get<0>(this->boomCoordinatesListPtrsList)[i] = Engine3D_Vector3D(rand() % 400 - 199, rand() % 400 - 199, rand() % 400 - 199);
			get<1>(this->boomCoordinatesListPtrsList)[i] = Engine3D_Vector3D(rand() % 400 - 199, rand() % 400 - 199, rand() % 400 - 199);
			get<2>(this->boomCoordinatesListPtrsList)[i] = Engine3D_Vector3D(rand() % 400 - 199, rand() % 400 - 199, rand() % 400 - 199);
			this->boomColorsListPtr[i] = Engine3D_Vector3D(rand() % 56 + 200, rand() % 100 + 100, 0);
			this->objectPtr->Trianglelist[i]->lightsource = true;
		}
		return false;
	}
	if (Clock - this->boomClock > this->boomTime)
	{
		delete[] get<0>(this->boomCoordinatesListPtrsList);
		delete[] get<1>(this->boomCoordinatesListPtrsList);
		delete[] get<2>(this->boomCoordinatesListPtrsList);
		return true;
	}
	double Multiple = (Clock - this->boomClock) / this->boomTime;
	for (int i = 0; i < this->objectPtr->trianglenum; i++)
	{
		this->objectPtr->Trianglelist[i]->color_constant = Engine3D_Vector3D(this->boomColorsListPtr[i].x * pow(1 - Multiple, 2), this->boomColorsListPtr[i].y * pow(1 - Multiple, 2), this->boomColorsListPtr[i].z);
		this->objectPtr->Trianglelist[i]->Point_A->coordinates_object = get<0>(this->boomCoordinatesListPtrsList)[i] * pow(Multiple, 0.4);
		this->objectPtr->Trianglelist[i]->Point_B->coordinates_object = get<1>(this->boomCoordinatesListPtrsList)[i] * pow(Multiple, 0.4);
		this->objectPtr->Trianglelist[i]->Point_C->coordinates_object = get<2>(this->boomCoordinatesListPtrsList)[i] * pow(Multiple, 0.4);
	}
	return false;
}
