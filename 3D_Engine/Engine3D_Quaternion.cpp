#include"Engine3D_Quaternion.h"

Engine3D_Quaternion::Engine3D_Quaternion()
{
	this->w = 0;
	this->i = 0;
	this->j = 0;
	this->k = 0;
	this->length = 0;
	return;
}

Engine3D_Quaternion::Engine3D_Quaternion(double w, double i, double j, double k)
{
	this->w = w;
	this->i = i;
	this->j = j;
	this->k = k;
	this->length = sqrt(w * w + i * i + j * j + k * k);
	return;
}

Engine3D_Quaternion::Engine3D_Quaternion(Engine3D_Vector3D Vector3D)
{
	this->w = 0;
	this->i = Vector3D.x;
	this->j = Vector3D.y;
	this->k = Vector3D.z;
	this->length = sqrt(this->w * this->w + this->i * this->i + this->j * this->j + this->k * this->k);
	return;
}

Engine3D_Quaternion::~Engine3D_Quaternion()
{
	return;
}

Engine3D_Quaternion Engine3D_Quaternion::operator*(Engine3D_Quaternion Quaternion)
{
	double w = this->w * Quaternion.w - this->i * Quaternion.i - this->j * Quaternion.j - this->k * Quaternion.k;
	double i = this->i * Quaternion.w + this->w * Quaternion.i - this->k * Quaternion.j + this->j * Quaternion.k;
	double j = this->j * Quaternion.w + this->k * Quaternion.i + this->w * Quaternion.j - this->i * Quaternion.k;
	double k = this->k * Quaternion.w - this->j * Quaternion.i + this->i * Quaternion.j + this->w * Quaternion.k;
	return Engine3D_Quaternion(w, i, j, k);
}

Engine3D_Quaternion Engine3D_Quaternion::Rotation(Engine3D_Vector3D rotation_axis, double theta)
{
	theta = DegreetoRadian(theta);
	return Engine3D_Quaternion(cos(theta / 2), rotation_axis.x * sin(theta / 2), rotation_axis.y * sin(theta / 2), rotation_axis.z * sin(theta / 2)) * *this;
}

Engine3D_Vector3D Engine3D_Quaternion::Get_UnitVector(string axis)
{
	return (*this * Engine3D_Quaternion(Engine3D_Vector3D(axis)) * this->Inverse_Quaternion()).Quaternion_To_Vector3D();
}

Engine3D_Vector3D Engine3D_Quaternion::Quaternion_To_Vector3D()
{
	return Engine3D_Vector3D(this->i, this->j, this->k);
}

Engine3D_Quaternion Engine3D_Quaternion::Inverse_Quaternion()
{
	return Engine3D_Quaternion(this->w, -this->i, -this->j, -this->k);
}

Engine3D_Quaternion Engine3D_Quaternion::RotationFactor(string rotation_axis, double theta)
{
	return Engine3D_Quaternion(1, 0, 0, 0).Rotation(Engine3D_Vector3D(rotation_axis), theta);
}
