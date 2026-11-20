#include"Engine3D_Camera.h"

Engine3D_Camera::Engine3D_Camera(string name, Engine3D_Vector2D screencentre, Engine3D_Vector2D screensize)
{
	this->name = name;
	this->magnification = 500;
	this->LastUpdateTime = 0;
	this->Sensitivity_Translation = 4;
	this->Sensitivity_Rotation = 1;
	this->coordinates = Engine3D_Vector3D(0, 0, 0);
	this->orientation = Engine3D_Quaternion(1, 0, 0, 0);
	this->width = 100;//´ı¶¨
	this->height = 100;//´ı¶¨
	this->depth = 1;//´ı¶¨
	this->depth_constant = 1;
	this->screencentre = screencentre;
	this->screensize = screensize;
	this->screenhrgn = CreateRectRgn(this->screencentre.x - this->screensize.x / 2, this->screencentre.y - this->screensize.y / 2, this->screencentre.x + this->screensize.x / 2, this->screencentre.y + this->screensize.y / 2);
	return;
}

Engine3D_Camera::~Engine3D_Camera()
{
	return;
}
