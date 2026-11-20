#include"Engine3D_Vector3D.h"

Engine3D_Vector3D::Engine3D_Vector3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->length = 0;
	return;
}

Engine3D_Vector3D::Engine3D_Vector3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->length = sqrt(x * x + y * y + z * z);
	return;
}

Engine3D_Vector3D::Engine3D_Vector3D(string axis)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	if (axis == "x")
	{
		this->x = 1;
	}
	else if (axis == "y")
	{
		this->y = 1;
	}
	else if (axis == "z")
	{
		this->z = 1;
	}
	this->length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	return;
}

Engine3D_Vector3D::~Engine3D_Vector3D()
{
	return;
}

Engine3D_Vector3D Engine3D_Vector3D::operator+(Engine3D_Vector3D Vector3D)
{
	return Engine3D_Vector3D(this->x + Vector3D.x, this->y + Vector3D.y, this->z + Vector3D.z);
}

Engine3D_Vector3D Engine3D_Vector3D::operator-(Engine3D_Vector3D Vector3D)
{
	return Engine3D_Vector3D(this->x - Vector3D.x, this->y - Vector3D.y, this->z - Vector3D.z);
}

Engine3D_Vector3D Engine3D_Vector3D::operator*(Engine3D_Vector3D Vector3D)
{
	return Engine3D_Vector3D(this->x * Vector3D.x, this->y * Vector3D.y, this->z * Vector3D.z);
}

Engine3D_Vector3D Engine3D_Vector3D::operator*(double coefficient)
{
	return Engine3D_Vector3D(this->x * coefficient, this->y * coefficient, this->z * coefficient);
}

double Engine3D_Vector3D::DotProduct(Engine3D_Vector3D Vector3D)
{
	return this->x * Vector3D.x + this->y * Vector3D.y + this->z * Vector3D.z;
}

Engine3D_Vector3D Engine3D_Vector3D::CrossProduct(Engine3D_Vector3D Vector3D)
{
	return Engine3D_Vector3D(this->y * Vector3D.z - this->z * Vector3D.y, this->z * Vector3D.x - this->x * Vector3D.z, this->x * Vector3D.y - this->y * Vector3D.x);
}

Engine3D_Vector3D Engine3D_Vector3D::operator/(double coefficient)
{
	return Engine3D_Vector3D(this->x / coefficient, this->y / coefficient, this->z / coefficient);
}

void Engine3D_Vector3D::operator+=(Engine3D_Vector3D Vector3D)
{
	this->x += Vector3D.x;
	this->y += Vector3D.y;
	this->z += Vector3D.z;
	return;
}

double Engine3D_Vector3D::GetLength()
{
	this->length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	return this->length;
}

Engine3D_Vector3D Engine3D_Vector3D::UnitVector()
{
	if (this->GetLength() == 0)
	{
		return *this;
	}
	return *this / this->GetLength();
}

double Engine3D_Vector3D::VetorialAngle(Engine3D_Vector3D Vector3D)
{
	double VectorDot = this->x * Vector3D.x + this->y * Vector3D.y + this->z * Vector3D.z;
	double CosAngle = VectorDot / (this->GetLength() * Vector3D.GetLength());
	double Radian = acos(CosAngle);
	return RadiantoDegree(Radian);
}
