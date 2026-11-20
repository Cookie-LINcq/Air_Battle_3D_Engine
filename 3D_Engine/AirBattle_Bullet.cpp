#include"AirBattle_Bullet.h"

AirBattle_Bullet::AirBattle_Bullet(AirBattle_Warplane* Warplane)
{
	this->objectsListID = 0;
	this->shouldDestroy = false;
	this->objectPtr = new Engine3D_Object();
	this->distance = Warplane->GunFiringDistance;
	this->speed = 3000 - Warplane->Velocity_Translation.z;//1800
	this->radius = 4;
	this->color = YELLOW;
	this->objectPtr->coordinates_world = Engine3D_Vector3D(Warplane->Find_Object__FUNC("MachineGun")->Object->coordinates_world);
	this->objectPtr->orientation = Engine3D_Quaternion(Warplane->Find_Object__FUNC("MachineGun")->Object->orientation);
	this->coordinate = Engine3D_Vector3D(this->objectPtr->coordinates_world);
	this->coordinate_Start = Engine3D_Vector3D(this->objectPtr->coordinates_world);
	this->orientation = Engine3D_Quaternion(this->objectPtr->orientation);
	this->objectPtr->showrange = this->distance;
	this->dangerRadius_Basics = 15;//18
	this->dangerRadius_Additional = 100;//15
	this->dangerRadius = this->dangerRadius_Basics;
	this->warplaneName = Warplane->name;
	this->objectPtr->Add_Line(new Engine3D_Point(-3.5, 0, -8), new Engine3D_Point(-3.5, 0, 0), this->color, this->radius);
	this->objectPtr->Add_Line(new Engine3D_Point(3.5, 0, -8), new Engine3D_Point(3.5, 0, 0), this->color, this->radius);
	return;
}

AirBattle_Bullet::~AirBattle_Bullet()
{
	if (this->objectPtr != NULL)
	{
		delete this->objectPtr;
		this->objectPtr = NULL;
	}
	return;
}

void AirBattle_Bullet::update(double TIME)
{
	this->objectPtr->coordinates_world = this->objectPtr->coordinates_world + (this->objectPtr->orientation * Engine3D_Quaternion(0, 0, 0, -1) * this->objectPtr->orientation.Inverse_Quaternion()).Quaternion_To_Vector3D() * this->speed * TIME;
	this->coordinate = this->objectPtr->coordinates_world;
	this->orientation = this->objectPtr->orientation;
	if ((this->objectPtr->coordinates_world - this->coordinate_Start).GetLength() > this->distance)
	{
		this->shouldDestroy = true;
	}
	else
	{
		this->dangerRadius = this->dangerRadius_Basics + this->dangerRadius_Additional * (this->objectPtr->coordinates_world - this->coordinate_Start).GetLength() / this->distance;
	}
	return;
}

void AirBattle_Bullet::update_Radius(Engine3D_Camera* Camera)
{
	for (int i = 0; i < this->objectPtr->linenum; i++)
	{
		this->objectPtr->Linelist[i]->radius = this->radius * (this->objectPtr->showrange - ((this->objectPtr->coordinates_world - Camera->coordinates).GetLength())) / this->objectPtr->showrange;
	}
	return;
}
