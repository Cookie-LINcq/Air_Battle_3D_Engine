#include"Engine3D_Vector2D.h"

Engine3D_Vector2D::Engine3D_Vector2D()
{
	this->x = 0;
	this->y = 0;
	this->length = 0;
	return;
}

Engine3D_Vector2D::Engine3D_Vector2D(double x, double y)
{
	this->x = x;
	this->y = y;
	this->length = sqrt(x * x + y * y);
	return;
}

Engine3D_Vector2D::~Engine3D_Vector2D()
{
	return;
}

bool Engine3D_Vector2D::operator==(Engine3D_Vector2D Vector2D)
{
	if (abs(this->x - Vector2D.x) < EPSILON && abs(this->y - Vector2D.y) < EPSILON)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Engine3D_Vector2D::operator!=(Engine3D_Vector2D Vector2D)
{
	if (abs(this->x - Vector2D.x) < EPSILON && abs(this->y - Vector2D.y) < EPSILON)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Engine3D_Vector2D Engine3D_Vector2D::operator*(double coefficient)
{
	return Engine3D_Vector2D(this->x * coefficient, this->y * coefficient);
}

double Engine3D_Vector2D::GetLength()
{
	this->length = sqrt(this->x * this->x + this->y * this->y);
	return this->length;
}

double Engine3D_Vector2D::VetorialAngle(Engine3D_Vector2D Vector2D)
{
	double theta = atan2(Vector2D.y, Vector2D.x) - atan2(this->y, this->x);//»¡¶È
	if (theta > PI)
	{
		theta -= 2 * PI;
	}
	if (theta < -PI)
	{
		theta += 2 * PI;
	}
	return RadiantoDegree(theta);//½Ç¶È
}

/*Engine3D_Vector2D Engine3D_Vector2D::UnitVector()
{
	return *this * (1 / this->GetLength());
}*/
