#include"AirBattle_Object.h"

AirBattle_Object::AirBattle_Object()
{
	this->Name = "";
	this->Object = NULL;
	this->Rotation_Degrees = Engine3D_Vector3D(0, 0, 0);
	this->Rotation_Degrees_Max = Engine3D_Vector3D(0, 0, 0);
	return;
}

AirBattle_Object::AirBattle_Object(string name, Engine3D_Object* Object)
{
	this->Name = name;
	this->Object = Object;
	this->Rotation_Degrees = Engine3D_Vector3D(0, 0, 0);
	this->Rotation_Degrees_Max = Engine3D_Vector3D(0, 0, 0);
	return;
}

AirBattle_Object::~AirBattle_Object()
{
	if (this->Object != NULL)
	{
		delete this->Object;
		this->Object = NULL;
	}
	return;
}

void AirBattle_Object::Update__FUNC(Engine3D_Vector3D coordinates, Engine3D_Quaternion orientation)
{
	this->Object->orientation = orientation * this->Rotation__FUNC("x", this->Rotation_Degrees.x) * this->Rotation__FUNC("y", this->Rotation_Degrees.y) * this->Rotation__FUNC("z", this->Rotation_Degrees.z);
	this->Object->orientation_object = this->Rotation__FUNC("x", this->Object->degrees_rotation_object.x) * this->Rotation__FUNC("y", this->Object->degrees_rotation_object.y) * this->Rotation__FUNC("z", this->Object->degrees_rotation_object.z);
	this->Object->coordinates_world = (this->Object->orientation * Engine3D_Quaternion(this->Object->coordinates_plane) * this->Object->orientation.Inverse_Quaternion()).Quaternion_To_Vector3D() + coordinates;
	return;
}

Engine3D_Quaternion AirBattle_Object::Rotation__FUNC(string rotation_axis, double theta)
{
	return Engine3D_Quaternion(1, 0, 0, 0).Rotation(Engine3D_Quaternion(1, 0, 0, 0).Get_UnitVector(rotation_axis), theta);
}
