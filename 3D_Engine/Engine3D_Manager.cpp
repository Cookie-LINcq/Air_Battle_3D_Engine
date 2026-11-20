#include"Engine3D_Manager.h"

Engine3D_Manager::Engine3D_Manager()
{
	this->AmbientLightIntensity = 0.3;
	this->SunLight = Engine3D_Vector3D(0, -1, 0);
	this->screen_width = 1400;
	this->screen_height = 800;
	this->LastUpdateTime_Show = 0;
	this->LastUpdateTime_Warplane = 0;
	this->LastUpdateTime_Bullet = 0;
	this->LastUpdateTime_Missile = 0;
	this->Warplane_number = 2;
	this->Bullet_number = 0;
	this->Missile_number = 0;
	this->MODE_Game = false;
	this->Warplane_list = NULL;
	this->Bullet_list = NULL;
	this->Missile_list = NULL;
	this->camerasnum = CameraNumber;
	this->Cameras_list = new Engine3D_Camera * [this->camerasnum];
	this->Cameras_list[0] = new Engine3D_Camera("CameraA", Engine3D_Vector2D(this->screen_width / 4 - 10, this->screen_height / 2), Engine3D_Vector2D(this->screen_width / 2 - 20, this->screen_height));
	this->Cameras_list[1] = new Engine3D_Camera("CameraB", Engine3D_Vector2D(this->screen_width * 3 / 4 + 10, this->screen_height / 2), Engine3D_Vector2D(this->screen_width / 2 - 20, this->screen_height));
	this->Objects_list = NULL;
	this->objectsnum = 0;
	initgraph(this->screen_width, this->screen_height, EX_SHOWCONSOLE);
	return;
}

Engine3D_Manager::~Engine3D_Manager()
{
	if (this->Warplane_list != NULL)
	{
		for (int i = 0; i < this->Warplane_number; i++)
		{
			delete this->Warplane_list[i];
			this->Warplane_list[i] = NULL;
		}
		delete[]this->Warplane_list;
		this->Warplane_list = NULL;
	}
	if (this->Bullet_list != NULL)
	{
		for (int i = 0; i < this->Bullet_number; i++)
		{
			delete this->Objects_list[i];
			this->Bullet_list[i] = NULL;
		}
		delete[]this->Bullet_list;
		this->Bullet_list = NULL;
	}
	if (this->Cameras_list != NULL)
	{
		for (int i = 0; i < this->camerasnum; i++)
		{
			delete this->Cameras_list[i];
			this->Cameras_list[i] = NULL;
		}
		delete[]this->Cameras_list;
		this->Cameras_list = NULL;
	}
	if (this->Objects_list != NULL)
	{
		for (int i = 0; i < this->objectsnum; i++)
		{
			delete this->Objects_list[i];
			this->Objects_list[i] = NULL;
		}
		delete[]this->Objects_list;
		this->Objects_list = NULL;
	}
	closegraph();
	return;
}

void Engine3D_Manager::Add_Object(double x, double y, double z)
{
	this->objectsnum++;
	COLORREF color = WHITE;
	if (this->objectsnum == 1)
	{
		this->Objects_list = new Engine3D_Object * [this->objectsnum];
		this->Objects_list[0] = new Engine3D_Object(x, y, z);

		Engine3D_Point* A = new Engine3D_Point(-0.5, -0.5, -0.5);
		Engine3D_Point* B = new Engine3D_Point(-0.5, -0.5, +0.5);

		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(-0.5, +0.5, -0.5);
		B->coordinates_object = Engine3D_Vector3D(-0.5, +0.5, +0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(+0.5, -0.5, -0.5);
		B->coordinates_object = Engine3D_Vector3D(+0.5, -0.5, +0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(+0.5, +0.5, -0.5);
		B->coordinates_object = Engine3D_Vector3D(+0.5, +0.5, +0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);

		A->coordinates_object = Engine3D_Vector3D(-0.5, +0.5, -0.5);
		B->coordinates_object = Engine3D_Vector3D(+0.5, +0.5, -0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(-0.5, +0.5, +0.5);
		B->coordinates_object = Engine3D_Vector3D(+0.5, +0.5, +0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(-0.5, -0.5, -0.5);
		B->coordinates_object = Engine3D_Vector3D(+0.5, -0.5, -0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(-0.5, -0.5, +0.5);
		B->coordinates_object = Engine3D_Vector3D(+0.5, -0.5, +0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);

		A->coordinates_object = Engine3D_Vector3D(+0.5, +0.5, -0.5);
		B->coordinates_object = Engine3D_Vector3D(+0.5, -0.5, -0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(+0.5, +0.5, +0.5);
		B->coordinates_object = Engine3D_Vector3D(+0.5, -0.5, +0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(-0.5, +0.5, -0.5);
		B->coordinates_object = Engine3D_Vector3D(-0.5, -0.5, -0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
		A->coordinates_object = Engine3D_Vector3D(-0.5, +0.5, +0.5);
		B->coordinates_object = Engine3D_Vector3D(-0.5, -0.5, +0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);

		Engine3D_Point* C = new Engine3D_Point(-0.5, -0.5, -0.5);
		this->Objects_list[this->objectsnum - 1]->Add_Triangle(Engine3D_Vector3D(A->coordinates_object), B->coordinates_object, C->coordinates_object, Engine3D_Vector3D(0, 0, 255), true);

		return;
	}
	Engine3D_Object** newspace = new Engine3D_Object * [this->objectsnum];
	for (int i = 0; i < this->objectsnum - 1; i++)
	{
		newspace[i] = this->Objects_list[i];
	}
	newspace[this->objectsnum - 1] = new Engine3D_Object(x, y, z);
	delete[]this->Objects_list;
	this->Objects_list = newspace;
	newspace = NULL;
	
	int y_ = -100;
	for (int i = -20000; i < 20000; i = i + 500)
	{
		this->Objects_list[this->objectsnum - 1]->Add_Line(new Engine3D_Point(i, y_, -20000), new Engine3D_Point(i, y_, 20000), color);
	}
	for (int j = -20000; j < 20000; j = j + 500)
	{
		this->Objects_list[this->objectsnum - 1]->Add_Line(new Engine3D_Point(-20000, y_, j), new Engine3D_Point(20000, y_, j), color);
	}

	/*Engine3D_Point* A = new Engine3D_Point(-0.5, -0.5, -0.5);
	Engine3D_Point* B = new Engine3D_Point(-0.5, -0.5, +0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(-0.5, +0.5, -0.5);
	B->coordinates_object = new Engine3D_Vector3D(-0.5, +0.5, +0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(+0.5, -0.5, -0.5);
	B->coordinates_object = new Engine3D_Vector3D(+0.5, -0.5, +0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(+0.5, +0.5, -0.5);
	B->coordinates_object = new Engine3D_Vector3D(+0.5, +0.5, +0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);

	A->coordinates_object = new Engine3D_Vector3D(-0.5, +0.5, -0.5);
	B->coordinates_object = new Engine3D_Vector3D(+0.5, +0.5, -0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(-0.5, +0.5, +0.5);
	B->coordinates_object = new Engine3D_Vector3D(+0.5, +0.5, +0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(-0.5, -0.5, -0.5);
	B->coordinates_object = new Engine3D_Vector3D(+0.5, -0.5, -0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(-0.5, -0.5, +0.5);
	B->coordinates_object = new Engine3D_Vector3D(+0.5, -0.5, +0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);

	A->coordinates_object = new Engine3D_Vector3D(+0.5, +0.5, -0.5);
	B->coordinates_object = new Engine3D_Vector3D(+0.5, -0.5, -0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(+0.5, +0.5, +0.5);
	B->coordinates_object = new Engine3D_Vector3D(+0.5, -0.5, +0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(-0.5, +0.5, -0.5);
	B->coordinates_object = new Engine3D_Vector3D(-0.5, -0.5, -0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);
	A->coordinates_object = new Engine3D_Vector3D(-0.5, +0.5, +0.5);
	B->coordinates_object = new Engine3D_Vector3D(-0.5, -0.5, +0.5);
	this->Objects_list[this->objectsnum - 1]->Add_Line(A, B, color);*/

	return;
}

void Engine3D_Manager::Show()
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	double TIME = NowTime - this->LastUpdateTime_Show;
	BeginBatchDraw();
	cleardevice();
	double X = 0;
	int* Orderlist_DistancetoCamera = NULL;
	int* Orderlist_IDOrder = NULL;
	int t = 0;
	int t2 = 0;
	for (int c = 0; c < this->camerasnum; c++)
	{
		for (int t = 0; t < this->Warplane_number; t++)
		{
			if (this->Cameras_list[c]->name == this->Warplane_list[t]->Name_Camera)
			{
				this->TriangleRendering(this->Cameras_list[c]);
			}
		}
		Orderlist_DistancetoCamera = new int[this->objectsnum];
		Orderlist_IDOrder = new int[this->objectsnum];
		this->BulletRadius_Update(this->Cameras_list[c]);
		for (int i = 0; i < this->objectsnum; i++)
		{
			Orderlist_IDOrder[i] = i;
		}
		for (int i = 0; i < this->objectsnum; i++)
		{
			Orderlist_DistancetoCamera[i] = sqrt(pow(this->Objects_list[i]->coordinates_world.x - this->Cameras_list[c]->coordinates.x, 2) + pow(this->Objects_list[i]->coordinates_world.y - this->Cameras_list[c]->coordinates.y, 2) + pow(this->Objects_list[i]->coordinates_world.z - this->Cameras_list[c]->coordinates.z, 2));
		}
		for (int i = 0; i < this->objectsnum; i++)
		{
			for (int k = 0; k < this->objectsnum - i - 1; k++)
			{
				if (Orderlist_DistancetoCamera[k] < Orderlist_DistancetoCamera[k + 1])
				{
					t = Orderlist_DistancetoCamera[k + 1];
					t2 = Orderlist_IDOrder[k + 1];
					Orderlist_DistancetoCamera[k + 1] = Orderlist_DistancetoCamera[k];
					Orderlist_IDOrder[k + 1] = Orderlist_IDOrder[k];
					Orderlist_DistancetoCamera[k] = t;
					Orderlist_IDOrder[k] = t2;
				}
			}
		}

		X = this->Cameras_list[c]->magnification;
		setcliprgn(this->Cameras_list[c]->screenhrgn);
		int j = 0;
		for (int j2 = 0; j2 < this->objectsnum; j2++)
		{
			/*for (int i = 0; i < this->Objects_list[j]->pointnum; i++)
			{
				if (this->Objects_list[j]->Pointlist[i]->coordinates_camera->z <= -this->Camera->depth)
				{
					setfillcolor(this->Objects_list[j]->Pointlist[i]->color);
					setlinecolor(this->Objects_list[j]->Pointlist[i]->color);
					fillcircle(this->Objects_list[j]->Pointlist[i]->coordinates_screen->x * X + this->screen_width / 4 - 10, this->screen_height / 2 - this->Objects_list[j]->Pointlist[i]->coordinates_screen->y * X, 2);
				}
			}*/
			j = Orderlist_IDOrder[j2];
			if (this->Objects_list[j]->showrange >= (this->Objects_list[j]->coordinates_world - this->Cameras_list[c]->coordinates).GetLength())
			{
				for (int k = 0; k < this->Objects_list[j]->linenum; k++)
				{
					setlinecolor(this->Objects_list[j]->Linelist[k]->color);
					if (this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z <= -this->Cameras_list[c]->depth && this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z <= -this->Cameras_list[c]->depth)
					{
						setlinestyle(PS_SOLID, this->Objects_list[j]->Linelist[k]->radius);
						line(this->Objects_list[j]->Linelist[k]->Point_A->coordinates_screen[c].x * X + this->Cameras_list[c]->screencentre.x, this->Cameras_list[c]->screencentre.y - this->Objects_list[j]->Linelist[k]->Point_A->coordinates_screen[c].y * X, this->Objects_list[j]->Linelist[k]->Point_B->coordinates_screen[c].x * X + this->Cameras_list[c]->screencentre.x, this->Cameras_list[c]->screencentre.y - this->Objects_list[j]->Linelist[k]->Point_B->coordinates_screen[c].y * X);
					}
					if (this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z > -this->Cameras_list[c]->depth && this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z <= -this->Cameras_list[c]->depth)
					{
						Engine3D_Vector2D NewVector(this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].x - (this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].x - this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].x) * (this->Cameras_list[c]->depth + this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z) / (this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z - this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z), this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].y - (this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].y - this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].y) * (this->Cameras_list[c]->depth + this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z) / (this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z - this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z));
						setlinestyle(PS_SOLID, this->Objects_list[j]->Linelist[k]->radius);
						line(NewVector.x * X + this->Cameras_list[c]->screencentre.x, this->Cameras_list[c]->screencentre.y - NewVector.y * X, this->Objects_list[j]->Linelist[k]->Point_B->coordinates_screen[c].x * X + this->Cameras_list[c]->screencentre.x, this->Cameras_list[c]->screencentre.y - this->Objects_list[j]->Linelist[k]->Point_B->coordinates_screen[c].y * X);
					}
					if (this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z <= -this->Cameras_list[c]->depth && this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z > -this->Cameras_list[c]->depth)
					{
						Engine3D_Vector2D NewVector(this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].x - (this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].x - this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].x) * (this->Cameras_list[c]->depth + this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z) / (this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z - this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z), this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].y - (this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].y - this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].y) * (this->Cameras_list[c]->depth + this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z) / (this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[c].z - this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[c].z));
						setlinestyle(PS_SOLID, this->Objects_list[j]->Linelist[k]->radius);
						line(this->Objects_list[j]->Linelist[k]->Point_A->coordinates_screen[c].x * X + this->Cameras_list[c]->screencentre.x, this->Cameras_list[c]->screencentre.y - this->Objects_list[j]->Linelist[k]->Point_A->coordinates_screen[c].y * X, NewVector.x * X + this->Cameras_list[c]->screencentre.x, this->Cameras_list[c]->screencentre.y - NewVector.y * X);
					}
				}
				/*int *Orderlist_DistancetoCamera = new int[this->Objects_list[j]->trianglenum];
				int *Orderlist_IDOrder = new int[this->Objects_list[j]->trianglenum];
				for (int i = 0; i < this->Objects_list[j]->trianglenum; i++)
				{
					this->Objects_list[j]->Trianglelist[i]->Calculate_NearestCoordinatesWorld(*this->Cameras_list[c]->coordinates);
					Orderlist_IDOrder[i] = i;
				}
				for (int i = 0; i < this->Objects_list[j]->trianglenum; i++)
				{
					Orderlist_DistancetoCamera[i] = sqrt(pow(this->Objects_list[j]->Trianglelist[i]->NearestCoordinatesWorld->x - this->Cameras_list[c]->coordinates->x, 2) + pow(this->Objects_list[j]->Trianglelist[i]->NearestCoordinatesWorld->y - this->Cameras_list[c]->coordinates->y, 2) + pow(this->Objects_list[j]->Trianglelist[i]->NearestCoordinatesWorld->z - this->Cameras_list[c]->coordinates->z, 2));
				}
				for (int i = 0; i < this->Objects_list[j]->trianglenum; i++)
				{
					for (int k = 0; k < this->Objects_list[j]->trianglenum - i - 1; k++)
					{
						if (Orderlist_DistancetoCamera[k] < Orderlist_DistancetoCamera[k + 1])
						{
							t = Orderlist_DistancetoCamera[k + 1];
							t2 = Orderlist_IDOrder[k + 1];
							Orderlist_DistancetoCamera[k + 1] = Orderlist_DistancetoCamera[k];
							Orderlist_IDOrder[k + 1] = Orderlist_IDOrder[k];
							Orderlist_DistancetoCamera[k] = t;
							Orderlist_IDOrder[k] = t2;
						}
					}
				}
				int w = 0;*/
				//this->Calculate_TriangleObstruct(this->Cameras_list[c]);
				//int Max = 0;
				/*for (int w = 0; w < this->Objects_list[j]->trianglenum; w++)
				{
					if (this->Objects_list[j]->Trianglelist[w]->ShowOrder > Max)
					{
						Max = this->Objects_list[j]->Trianglelist[w]->ShowOrder;
					}
				}*/
				//for (int Order = 0; Order <= Max; Order++)
				//{
				for (int w = 0; w < this->Objects_list[j]->trianglenum; w++)
				{
					//if (this->Objects_list[j]->Trianglelist[w]->ShowOrder == Order)
					if (this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera[c].z < 0 && this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera[c].z < 0 && this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera[c].z < 0)
					{
						setlinecolor(RGB(this->Objects_list[j]->Trianglelist[w]->color.x, this->Objects_list[j]->Trianglelist[w]->color.y, this->Objects_list[j]->Trianglelist[w]->color.z));
						POINT Points[] = { {this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_screen[c].x * X + this->Cameras_list[c]->screencentre.x, this->Cameras_list[c]->screencentre.y - this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_screen[c].y * X}, {this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_screen[c].x * X + this->Cameras_list[c]->screencentre.x,this->Cameras_list[c]->screencentre.y - this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_screen[c].y * X} , {this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_screen[c].x * X + this->Cameras_list[c]->screencentre.x,this->Cameras_list[c]->screencentre.y - this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_screen[c].y * X} };
						if (this->Objects_list[j]->Trianglelist[w]->solid)
						{
							setfillcolor(RGB(this->Objects_list[j]->Trianglelist[w]->color.x, this->Objects_list[j]->Trianglelist[w]->color.y, this->Objects_list[j]->Trianglelist[w]->color.z));
							fillpolygon(Points, 3);
						}
						else
						{
							polygon(Points, 3);
						}
					}
				}
				//}
			}
		}
		delete[] Orderlist_DistancetoCamera;
		Orderlist_DistancetoCamera = NULL;
		delete[] Orderlist_IDOrder;
		Orderlist_IDOrder = NULL;
		t = 0;
		t2 = 0;
	}
	this->Warplane_Display(X);
	setcliprgn(NULL);
	setlinecolor(WHITE);
	for (int i = 0; i < this->camerasnum; i++)
	{
		line(this->Cameras_list[i]->screencentre.x - this->Cameras_list[i]->screensize.x / 2, this->Cameras_list[i]->screencentre.y - this->Cameras_list[i]->screensize.y / 2, this->Cameras_list[i]->screencentre.x - this->Cameras_list[i]->screensize.x / 2, this->Cameras_list[i]->screencentre.y + this->Cameras_list[i]->screensize.y / 2);
		line(this->Cameras_list[i]->screencentre.x + this->Cameras_list[i]->screensize.x / 2, this->Cameras_list[i]->screencentre.y - this->Cameras_list[i]->screensize.y / 2, this->Cameras_list[i]->screencentre.x + this->Cameras_list[i]->screensize.x / 2, this->Cameras_list[i]->screencentre.y + this->Cameras_list[i]->screensize.y / 2);
		line(this->Cameras_list[i]->screencentre.x - this->Cameras_list[i]->screensize.x / 2, this->Cameras_list[i]->screencentre.y - this->Cameras_list[i]->screensize.y / 2, this->Cameras_list[i]->screencentre.x + this->Cameras_list[i]->screensize.x / 2, this->Cameras_list[i]->screencentre.y - this->Cameras_list[i]->screensize.y / 2);
		line(this->Cameras_list[i]->screencentre.x - this->Cameras_list[i]->screensize.x / 2, this->Cameras_list[i]->screencentre.y + this->Cameras_list[i]->screensize.y / 2, this->Cameras_list[i]->screencentre.x + this->Cameras_list[i]->screensize.x / 2, this->Cameras_list[i]->screencentre.y + this->Cameras_list[i]->screensize.y / 2);
	}
	
	EndBatchDraw();
	this->LastUpdateTime_Show = NowTime;
	return;
}

void Engine3D_Manager::Warplane_Display(double magnification)
{
	for (int i = 0; i < this->Warplane_number; i++)
	{
		this->Warplane_list[i]->Camera_Display__FUNC();
		setcliprgn(this->Find_Camera(this->Warplane_list[i]->Name_Camera)->screenhrgn);
		this->Warplane_list[i]->Screen_Display__FUNC(this->Find_Camera(this->Warplane_list[i]->Name_Camera)->screencentre, Engine3D_Vector2D(this->screen_width, this->screen_height), this->Find_Warplane(this->Warplane_list[i]->Name_Enemy), magnification);
	}
	return;
}

void Engine3D_Manager::Calculate_Pointcameracoordinate()
{
	for (int a = 0; a < this->camerasnum; a++)
	{
		for (int j = 0; j < this->objectsnum; j++)
		{
			for (int k = 0; k < this->Objects_list[j]->linenum; k++)
			{
				this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[a] = (this->Cameras_list[a]->orientation.Inverse_Quaternion() * Engine3D_Quaternion(this->Objects_list[j]->Linelist[k]->Point_A->coordinates_world - this->Cameras_list[a]->coordinates) * this->Cameras_list[a]->orientation).Quaternion_To_Vector3D();
				this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[a] = (this->Cameras_list[a]->orientation.Inverse_Quaternion() * Engine3D_Quaternion(this->Objects_list[j]->Linelist[k]->Point_B->coordinates_world - this->Cameras_list[a]->coordinates) * this->Cameras_list[a]->orientation).Quaternion_To_Vector3D();
			}
			for (int i = 0; i < this->Objects_list[j]->trianglenum; i++)
			{
				this->Objects_list[j]->Trianglelist[i]->Point_A->coordinates_camera[a] = (this->Cameras_list[a]->orientation.Inverse_Quaternion() * Engine3D_Quaternion(this->Objects_list[j]->Trianglelist[i]->Point_A->coordinates_world - this->Cameras_list[a]->coordinates) * this->Cameras_list[a]->orientation).Quaternion_To_Vector3D();
				this->Objects_list[j]->Trianglelist[i]->Point_B->coordinates_camera[a] = (this->Cameras_list[a]->orientation.Inverse_Quaternion() * Engine3D_Quaternion(this->Objects_list[j]->Trianglelist[i]->Point_B->coordinates_world - this->Cameras_list[a]->coordinates) * this->Cameras_list[a]->orientation).Quaternion_To_Vector3D();
				this->Objects_list[j]->Trianglelist[i]->Point_C->coordinates_camera[a] = (this->Cameras_list[a]->orientation.Inverse_Quaternion() * Engine3D_Quaternion(this->Objects_list[j]->Trianglelist[i]->Point_C->coordinates_world - this->Cameras_list[a]->coordinates) * this->Cameras_list[a]->orientation).Quaternion_To_Vector3D();
			}
			/*for (int i = 0; i < this->Objects_list[j]->pointnum; i++)
			{
				this->Objects_list[j]->Pointlist[i]->coordinates_camera = Calculation.Vector3D_Subtraction(*this->Objects_list[j]->Pointlist[i]->coordinates_world, *Camera->coordinates);
				Engine3D_Quaternion pointcoordinatescamera(0, this->Objects_list[j]->Pointlist[i]->coordinates_camera->x, this->Objects_list[j]->Pointlist[i]->coordinates_camera->y, this->Objects_list[j]->Pointlist[i]->coordinates_camera->z);
				Engine3D_Quaternion inversequaternion_orientation(Camera->orientation->w, -Camera->orientation->i, -Camera->orientation->j, -Camera->orientation->k);
				pointcoordinatescamera = *Calculation.Quaternion_Multiplication(inversequaternion_orientation, pointcoordinatescamera);
				pointcoordinatescamera = *Calculation.Quaternion_Multiplication(pointcoordinatescamera, *Camera->orientation);
				this->Objects_list[j]->Pointlist[i]->coordinates_camera->x = pointcoordinatescamera.i;
				this->Objects_list[j]->Pointlist[i]->coordinates_camera->y = pointcoordinatescamera.j;
				this->Objects_list[j]->Pointlist[i]->coordinates_camera->z = pointcoordinatescamera.k;
			}
			for (int w = 0; w < this->Objects_list[j]->trianglenum; w++)
			{
				this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera = Calculation.Vector3D_Subtraction(*this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_world, *Camera->coordinates);
				Engine3D_Quaternion pointcoordinatescamera_A(0, this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->x, this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->y, this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->z);
				Engine3D_Quaternion inversequaternion_orientation_A(Camera->orientation->w, -Camera->orientation->i, -Camera->orientation->j, -Camera->orientation->k);
				pointcoordinatescamera_A = *Calculation.Quaternion_Multiplication(inversequaternion_orientation_A, pointcoordinatescamera_A);
				pointcoordinatescamera_A = *Calculation.Quaternion_Multiplication(pointcoordinatescamera_A, *Camera->orientation);
				this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->x = pointcoordinatescamera_A.i;
				this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->y = pointcoordinatescamera_A.j;
				this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->z = pointcoordinatescamera_A.k;

				this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera = Calculation.Vector3D_Subtraction(*this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_world, *Camera->coordinates);
				Engine3D_Quaternion pointcoordinatescamera_B(0, this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->x, this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->y, this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->z);
				Engine3D_Quaternion inversequaternion_orientation_B(Camera->orientation->w, -Camera->orientation->i, -Camera->orientation->j, -Camera->orientation->k);
				pointcoordinatescamera_B = *Calculation.Quaternion_Multiplication(inversequaternion_orientation_B, pointcoordinatescamera_B);
				pointcoordinatescamera_B = *Calculation.Quaternion_Multiplication(pointcoordinatescamera_B, *Camera->orientation);
				this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->x = pointcoordinatescamera_B.i;
				this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->y = pointcoordinatescamera_B.j;
				this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->z = pointcoordinatescamera_B.k;

				this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera = Calculation.Vector3D_Subtraction(*this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_world, *Camera->coordinates);
				Engine3D_Quaternion pointcoordinatescamera_C(0, this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->x, this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->y, this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->z);
				Engine3D_Quaternion inversequaternion_orientation_C(Camera->orientation->w, -Camera->orientation->i, -Camera->orientation->j, -Camera->orientation->k);
				pointcoordinatescamera_C = *Calculation.Quaternion_Multiplication(inversequaternion_orientation_C, pointcoordinatescamera_C);
				pointcoordinatescamera_C = *Calculation.Quaternion_Multiplication(pointcoordinatescamera_C, *Camera->orientation);
				this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->x = pointcoordinatescamera_C.i;
				this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->y = pointcoordinatescamera_C.j;
				this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->z = pointcoordinatescamera_C.k;
			}*/
		}
	}
	return;
}

void Engine3D_Manager::Calculate_Pointscreencoordinate()
{
	for (int j = 0; j < this->objectsnum; j++)
	{
		for (int i = 0; i < this->camerasnum; i++)
		{
			for (int k = 0; k < this->Objects_list[j]->linenum; k++)
			{
				this->Objects_list[j]->Linelist[k]->Point_A->coordinates_screen[i] = Engine3D_Vector2D(this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[i].x, this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[i].y) * (-this->Cameras_list[i]->depth / this->Objects_list[j]->Linelist[k]->Point_A->coordinates_camera[i].z);
				this->Objects_list[j]->Linelist[k]->Point_B->coordinates_screen[i] = Engine3D_Vector2D(this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[i].x, this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[i].y) * (-this->Cameras_list[i]->depth / this->Objects_list[j]->Linelist[k]->Point_B->coordinates_camera[i].z);
			}
			for (int w = 0; w < this->Objects_list[j]->trianglenum; w++)
			{
				this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_screen[i] = Engine3D_Vector2D(this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera[i].x, this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera[i].y) * (-this->Cameras_list[i]->depth / this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera[i].z);
				this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_screen[i] = Engine3D_Vector2D(this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera[i].x, this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera[i].y) * (-this->Cameras_list[i]->depth / this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera[i].z);
				this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_screen[i] = Engine3D_Vector2D(this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera[i].x, this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera[i].y) * (-this->Cameras_list[i]->depth / this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera[i].z);
			}
		}	
		/*for (int i = 0; i < this->Objects_list[j]->pointnum; i++)
		{
			Engine3D_Vector2D Pointcoordinatescamera(this->Objects_list[j]->Pointlist[i]->coordinates_camera->x, this->Objects_list[j]->Pointlist[i]->coordinates_camera->y);
			*this->Objects_list[j]->Pointlist[i]->coordinates_screen = Pointcoordinatescamera * (-this->Camera->depth / this->Objects_list[j]->Pointlist[i]->coordinates_camera->z);
		}
		for (int w = 0; w < this->Objects_list[j]->trianglenum; w++)
		{
			Engine3D_Vector2D Pointcoordinatescamera_A(this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->x, this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->y);
			*this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_screen = Pointcoordinatescamera_A * (-this->Camera->depth / this->Objects_list[j]->Trianglelist[w]->Point_A->coordinates_camera->z);

			Engine3D_Vector2D Pointcoordinatescamera_B(this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->x, this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->y);
			*this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_screen = Pointcoordinatescamera_B * (-this->Camera->depth / this->Objects_list[j]->Trianglelist[w]->Point_B->coordinates_camera->z);
		
			Engine3D_Vector2D Pointcoordinatescamera_C(this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->x, this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->y);
			*this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_screen = Pointcoordinatescamera_C * (-this->Camera->depth / this->Objects_list[j]->Trianglelist[w]->Point_C->coordinates_camera->z);
		}*/
	}
	return;
}

void Engine3D_Manager::CALCULATE_All()
{
	for (int i = 0; i < this->Warplane_number; i++)
	{
		if (this->Warplane_list[i]->OVER)
		{
			this->MODE_Game = false;
			cout << "Victor:  " << this->Warplane_list[i]->Name_Defeater << endl << "HP:  ";
			for (int j = 0; j < this->Warplane_number; j++)
			{
				cout << this->Warplane_list[j]->name << " " << this->Warplane_list[j]->HP << "      ";
			}
			cout << endl;
			system("pause");
		}
	}
	for (int i = 0; i < this->objectsnum; i++)
	{
		this->Objects_list[i]->Calculate_Pointworldcoordinate();
	}
	this->Calculate_Pointcameracoordinate();
	this->Calculate_Pointscreencoordinate();
	return;
}

void Engine3D_Manager::Add_Warplane()
{
	this->Warplane_list = new AirBattle_Warplane * [2];
	this->Warplane_list[0] = new AirBattle_Warplane(1, this->Cameras_list[0]);
	this->Warplane_list[1] = new AirBattle_Warplane(2, this->Cameras_list[1]);
	this->objectsnum = this->Warplane_list[0]->object_num + this->Warplane_list[1]->object_num;
	this->Objects_list = new Engine3D_Object * [this->objectsnum];
	if (this->objectsnum < this->Warplane_list[0]->object_num)
	{
		return;
	}
	for (int i = 0; i < this->Warplane_list[0]->object_num; i++)
	{
		this->Objects_list[i] = this->Warplane_list[0]->Object_list[i]->Object;
	}
	for (int j = this->Warplane_list[0]->object_num; j < this->objectsnum; j++)
	{
		this->Objects_list[j] = this->Warplane_list[1]->Object_list[j - this->Warplane_list[0]->object_num]->Object;
	}
	this->Warplane_list[0]->Name_Enemy = this->Warplane_list[1]->name;
	this->Warplane_list[1]->Name_Enemy = this->Warplane_list[0]->name;
	return;
}

void Engine3D_Manager::Warplane_Update()
{
	this->Warplane_list[0]->Update__FUNC(this->Warplane_list[1]);
	this->Warplane_list[1]->Update__FUNC(this->Warplane_list[0]);
	return;
}

void Engine3D_Manager::Warplane_Adjustment()
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	double TIME = NowTime - this->LastUpdateTime_Warplane;
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (this->MODE_Game)
		{
			this->MODE_Game = false;
		}
		else
		{
			this->MODE_Game = true;
		}
		Sleep(200);
	}
	for (int i = 0; i < this->Warplane_number; i++)
	{
		this->Warplane_list[i]->Adjustment__FUNC(TIME, MODE_Game);
		if (this->Warplane_list[i]->GunFiringHeatProgress == 1)
		{
			if (NowTime - this->Warplane_list[i]->GunFiringPunishClock > this->Warplane_list[i]->GunFiringPunishTime)
			{
				this->Warplane_list[i]->GunFiringHeatProgress -= this->Warplane_list[i]->GunFiringCoolRate * TIME;
			}
		}
		else if (GetAsyncKeyState(this->Warplane_list[i]->Key_Firing) || GetKeyState(this->Warplane_list[i]->Key_Firingclock))
		{
			this->Firing(this->Warplane_list[i]);
			this->Warplane_list[i]->GunFiringHeatProgress += this->Warplane_list[i]->GunFiringHeatRate * TIME;
			if (this->Warplane_list[i]->GunFiringHeatProgress > 1)
			{
				this->Warplane_list[i]->GunFiringHeatProgress = 1;
				this->Warplane_list[i]->GunFiringPunishClock = NowTime;
			}
		}
		else
		{
			this->Warplane_list[i]->GunFiringHeatProgress -= this->Warplane_list[i]->GunFiringCoolRate * TIME;
			if (this->Warplane_list[i]->GunFiringHeatProgress < 0)
			{
				this->Warplane_list[i]->GunFiringHeatProgress = 0;
			}
		}
		if (GetAsyncKeyState(this->Warplane_list[i]->Key_Missilefiring) && this->Warplane_list[i]->AimingProgress == 1)
		{
			this->Warplane_list[i]->Aiming_On = true;
			this->MissileFiring(this->Warplane_list[i]);
		}
	}
	this->LastUpdateTime_Warplane = NowTime;
	return;
}

void Engine3D_Manager::Add_Bullet(AirBattle_Warplane* Warplane)
{
	this->Bullet_number++;
	if (this->Bullet_number == 1)
	{
		this->Bullet_list = new AirBattle_Bullet * [1];
		this->Bullet_list[0] = new AirBattle_Bullet(Warplane);
	}
	else
	{
		AirBattle_Bullet** newspace = new AirBattle_Bullet * [this->Bullet_number];
		for (int i = 0; i < this->Bullet_number - 1; i++)
		{
			newspace[i] = this->Bullet_list[i];
		}
		newspace[this->Bullet_number - 1] = new AirBattle_Bullet(Warplane);
		delete[]this->Bullet_list;
		this->Bullet_list = newspace;
		newspace = NULL;
	}
	this->Bullet_list[this->Bullet_number - 1]->objectsListID = this->objectsnum;

	this->objectsnum++;
	Engine3D_Object** newspace2 = new Engine3D_Object * [this->objectsnum];
	for (int i = 0; i < this->objectsnum - 1; i++)
	{
		newspace2[i] = this->Objects_list[i];
	}
	newspace2[this->objectsnum - 1] = this->Bullet_list[this->Bullet_number - 1]->objectPtr;
	delete[]this->Objects_list;
	this->Objects_list = newspace2;
	newspace2 = NULL;
	return;
}

void Engine3D_Manager::Add_Missile(AirBattle_Warplane* Warplane)
{
	this->Missile_number++;
	if (this->Missile_number == 1)
	{
		this->Missile_list = new AirBattle_Missile * [1];
		this->Missile_list[0] = new AirBattle_Missile(Warplane);
	}
	else
	{
		AirBattle_Missile** newspace = new AirBattle_Missile * [this->Missile_number];
		for (int i = 0; i < this->Missile_number - 1; i++)
		{
			newspace[i] = this->Missile_list[i];
		}
		newspace[this->Missile_number - 1] = new AirBattle_Missile(Warplane);
		delete[]this->Missile_list;
		this->Missile_list = newspace;
		newspace = NULL;
	}
	this->Missile_list[this->Missile_number - 1]->objectsListID = this->objectsnum;

	this->objectsnum++;
	Engine3D_Object** newspace2 = new Engine3D_Object * [this->objectsnum];
	for (int i = 0; i < this->objectsnum - 1; i++)
	{
		newspace2[i] = this->Objects_list[i];
	}
	newspace2[this->objectsnum - 1] = this->Missile_list[this->Missile_number - 1]->objectPtr;
	delete[]this->Objects_list;
	this->Objects_list = newspace2;
	newspace2 = NULL;
	return;
}

void Engine3D_Manager::Bullet_Update()
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	double TIME = NowTime - this->LastUpdateTime_Bullet;
	for (int i = 0; i < this->Bullet_number; i++)
	{
		Engine3D_Vector3D BulletLastCoordinates = this->Bullet_list[i]->coordinate;
		this->Bullet_list[i]->update(TIME);
		for (int j = 0; j < this->Warplane_number; j++)
		{
			if (this->Bullet_list[i]->warplaneName != this->Warplane_list[j]->name)
			{
				if ((this->Warplane_list[j]->coordinates - (this->Bullet_list[i]->coordinate + (this->Bullet_list[i]->orientation * Engine3D_Quaternion(0, 0, 0, -1) * this->Bullet_list[i]->orientation.Inverse_Quaternion()).Quaternion_To_Vector3D() * (this->Bullet_list[i]->dangerRadius - (this->Bullet_list[i]->speed * TIME + this->Bullet_list[i]->dangerRadius) / 2))).GetLength() <= (this->Bullet_list[i]->speed * TIME + this->Bullet_list[i]->dangerRadius) / 2)
				{
					int DetectionNumber = ceil((this->Bullet_list[i]->coordinate - BulletLastCoordinates).GetLength() / this->Bullet_list[i]->dangerRadius);
					Engine3D_Vector3D DetectionCoordinates;
					for (int k = 0; k < DetectionNumber; k++)
					{
						DetectionCoordinates = this->Bullet_list[i]->coordinate + ((this->Bullet_list[i]->orientation * Engine3D_Quaternion(0, 0, 0, 1) * this->Bullet_list[i]->orientation.Inverse_Quaternion()).Quaternion_To_Vector3D() * this->Bullet_list[i]->dangerRadius) * k;
						if ((this->Warplane_list[j]->coordinates - DetectionCoordinates).GetLength() <= this->Bullet_list[i]->dangerRadius)
						{
							this->Bullet_list[i]->shouldDestroy = true;
							this->Warplane_list[j]->DMG_Taken__FUNC("Gun", this->Find_Warplane(this->Bullet_list[i]->warplaneName));
							break;
						}
					}
				}
			}
		}
		if (this->Bullet_list[i]->shouldDestroy)
		{
			for (int l = 0; l < this->Bullet_number; l++)
			{
				this->Bullet_list[l]->objectPtr = NULL;
			}
			this->objectsnum--;
			Engine3D_Object** newspace = new Engine3D_Object * [this->objectsnum];
			for (int j = 0; j < this->Bullet_list[i]->objectsListID; j++)
			{
				if (j >= this->objectsnum)
				{
					break;
				}
				newspace[j] = this->Objects_list[j];
			}
			for (int k = this->Bullet_list[i]->objectsListID; k < this->objectsnum; k++)
			{
				newspace[k] = this->Objects_list[k + 1];
			}
			delete[]this->Objects_list;
			this->Objects_list = newspace;
			newspace = NULL;
			this->Bullet_number--;
			for (int j = 0; j < this->Missile_number; j++)
			{
				if (this->Missile_list[j]->objectsListID > this->Bullet_list[i]->objectsListID)
				{
					this->Missile_list[j]->objectsListID--;
				}
			}
			delete this->Bullet_list[i];
			AirBattle_Bullet** newspace2 = new AirBattle_Bullet * [this->Bullet_number];
			for (int m = 0; m < i; m++)
			{
				newspace2[m] = this->Bullet_list[m];
			}
			for (int n = i; n < this->Bullet_number; n++)
			{
				newspace2[n] = this->Bullet_list[n + 1];
				newspace2[n]->objectsListID--;
			}
			delete[]this->Bullet_list;
			this->Bullet_list = newspace2;
			newspace2 = NULL;
			for (int q = 0; q < this->Bullet_number; q++)
			{
				this->Bullet_list[q]->objectPtr = this->Objects_list[this->Bullet_list[q]->objectsListID];
			}
			i--;
		}
	}
	this->LastUpdateTime_Bullet = NowTime;
	return;
}

void Engine3D_Manager::Missile_Update()
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	double TIME = NowTime - this->LastUpdateTime_Missile;
	int TYPE = 0;
	for (int i = 0; i < this->Missile_number; i++)
	{
		TYPE = this->Missile_list[i]->update(TIME, this->Find_Warplane(this->Missile_list[i]->goalName), this->Find_Warplane(this->Missile_list[i]->warplaneName)->AimingProgress);
		switch (TYPE)
		{
		case -1:
		{
			for (int l = 0; l < this->Missile_number; l++)
			{
				this->Missile_list[l]->objectPtr = NULL;
			}
			this->objectsnum--;
			Engine3D_Object** newspace = new Engine3D_Object * [this->objectsnum];
			for (int j = 0; j < this->Missile_list[i]->objectsListID; j++)
			{
				if (j >= this->objectsnum)
				{
					break;
				}
				newspace[j] = this->Objects_list[j];
			}
			for (int k = this->Missile_list[i]->objectsListID; k < this->objectsnum; k++)
			{
				newspace[k] = this->Objects_list[k + 1];
			}
			delete[]this->Objects_list;
			this->Objects_list = newspace;
			newspace = NULL;
			this->Missile_number--;
			for (int j = 0; j < this->Bullet_number; j++)
			{
				if (this->Bullet_list[j]->objectsListID > this->Missile_list[i]->objectsListID)
				{
					this->Bullet_list[j]->objectsListID--;
				}
			}
			delete this->Missile_list[i];
			AirBattle_Missile** newspace2 = new AirBattle_Missile * [this->Missile_number];
			for (int m = 0; m < i; m++)
			{
				newspace2[m] = this->Missile_list[m];
			}
			for (int n = i; n < this->Missile_number; n++)
			{
				newspace2[n] = this->Missile_list[n + 1];
				newspace2[n]->objectsListID--;
			}
			delete[]this->Missile_list;
			this->Missile_list = newspace2;
			newspace2 = NULL;
			for (int q = 0; q < this->Missile_number; q++)
			{
				this->Missile_list[q]->objectPtr = this->Objects_list[this->Missile_list[q]->objectsListID];
			}
			i--;
			break;
		}
		case 1:
		{
			this->Find_Warplane(this->Missile_list[i]->goalName)->DMG_Taken__FUNC("Missile", this->Find_Warplane(this->Missile_list[i]->warplaneName));
			break;
		}
		default:
			break;
		}
	}
	this->LastUpdateTime_Missile = NowTime;
	return;
}

void Engine3D_Manager::BulletRadius_Update(Engine3D_Camera* Camera)
{
	for (int i = 0; i < this->Bullet_number; i++)
	{
		this->Bullet_list[i]->update_Radius(Camera);
	}
	return;
}

void Engine3D_Manager::Firing(AirBattle_Warplane* Warplane)
{
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	if (NowTime - Warplane->LastClock_Firing >= Warplane->GunFiringInterval)
	{
		this->Add_Bullet(Warplane);
		Warplane->LastClock_Firing = NowTime;
	}
	return;
}

void Engine3D_Manager::MissileFiring(AirBattle_Warplane* Warplane)
{
	//if (Warplane->AimingProgress != 1) { return; }
	double NowTime = GetTime_Second_AccurateToMicrosecond();
	if (NowTime - Warplane->LastClock_MissileFiring >= Warplane->MissileFiringInterval)
	{
		this->Add_Missile(Warplane);
		Warplane->LastClock_MissileFiring = NowTime;
	}
	return;
}

AirBattle_Warplane* Engine3D_Manager::Find_Warplane(string Name)
{
	for (int i = 0; i < this->Warplane_number; i++)
	{
		if (this->Warplane_list[i]->name == Name)
		{
			return this->Warplane_list[i];
		}
	}
	return NULL;
}

Engine3D_Camera* Engine3D_Manager::Find_Camera(string Name)
{
	for (int i = 0; i < this->camerasnum; i++)
	{
		if (this->Cameras_list[i]->name == Name)
		{
			return this->Cameras_list[i];
		}
	}
	return NULL;
}

void Engine3D_Manager::TriangleRendering(Engine3D_Camera* Camera)
{
	for (int i = 0; i < this->objectsnum; i++)
	{
		for (int j = 0; j < this->Objects_list[i]->trianglenum; j++)
		{
			if (this->Objects_list[i]->Trianglelist[j]->lightsource)
			{
				this->Objects_list[i]->Trianglelist[j]->color = this->Objects_list[i]->Trianglelist[j]->color_constant;
				continue;
			}
			this->Objects_list[i]->Trianglelist[j]->Calculate_NormalVector();
			if (this->Objects_list[i]->Trianglelist[j]->NormalVector.VetorialAngle(Camera->coordinates - this->Objects_list[i]->Trianglelist[j]->Point_A->coordinates_world) < 90)
			{
				this->Objects_list[i]->Trianglelist[j]->NormalVector = this->Objects_list[i]->Trianglelist[j]->NormalVector * -1;
			}
			if (cos(DegreetoRadian(this->Objects_list[i]->Trianglelist[j]->NormalVector.VetorialAngle(this->SunLight))) <= 0)
			{
				this->Objects_list[i]->Trianglelist[j]->color = this->Objects_list[i]->Trianglelist[j]->color_constant * this->AmbientLightIntensity;
			}
			else
			{
				double Result = this->AmbientLightIntensity + cos(DegreetoRadian(this->Objects_list[i]->Trianglelist[j]->NormalVector.VetorialAngle(this->SunLight)));
				if (Result > 1)
				{
					Result = 1;
				}
				this->Objects_list[i]->Trianglelist[j]->color = this->Objects_list[i]->Trianglelist[j]->color_constant * Result;
			}
		}
	}
	return;
}

bool Engine3D_Manager::TrianglePointIntersection(Engine3D_Vector2D TriangleA, Engine3D_Vector2D TriangleB, Engine3D_Vector2D TriangleC, Engine3D_Vector2D Point)
{
	if (Point == TriangleA || Point == TriangleB || Point == TriangleC)
	{
		return true;
	}
	double Sabp = this->Calculate_TriangleArea(TriangleA, TriangleB, Point);
	double Sbcp = this->Calculate_TriangleArea(TriangleB, TriangleC, Point);
	double Sacp = this->Calculate_TriangleArea(TriangleA, TriangleC, Point);
	double Sabc = this->Calculate_TriangleArea(TriangleA, TriangleB, TriangleC);
	if (Sabp + Sbcp + Sacp <= Sabc + EPSILON)
	{
		return true;
	}
	else
	{
		return false;
	}
}

tuple<int, Engine3D_Vector2D*> Engine3D_Manager::Calculate_TriangleRelation(Engine3D_Triangle* Original, Engine3D_Triangle* Compare, int CameraID)//内部点数量，特殊点
{
	Engine3D_Vector2D Points[3] = { Original->Point_A->coordinates_screen[CameraID] , Original->Point_B->coordinates_screen[CameraID] , Original->Point_C->coordinates_screen[CameraID] };
	bool PointIsInside[3] = { false,false,false };
	int OinsideNum = 0;
	for (int i = 0; i < 3; i++)
	{
		if (this->TrianglePointIntersection(Compare->Point_A->coordinates_screen[CameraID], Compare->Point_B->coordinates_screen[CameraID], Compare->Point_C->coordinates_screen[CameraID], Points[i]))
		{
			PointIsInside[i] = true;
			OinsideNum++;
		}
	}
	Engine3D_Vector2D InsidePoint[3] = { {0,0},{0,0},{0,0} };
	int th = 0;
	for (int i = 0; i < OinsideNum; i++)
	{
		if (PointIsInside[i])
		{
			InsidePoint[th] = Points[i];
			th++;
		}
	}
	return make_tuple(OinsideNum, InsidePoint);
}

double Engine3D_Manager::Calculate_TriangleArea(Engine3D_Vector2D PointA, Engine3D_Vector2D PointB, Engine3D_Vector2D PointC)
{
	Engine3D_Vector2D AB(PointB.x - PointA.x, PointB.y - PointA.y);
	Engine3D_Vector2D AC(PointC.x - PointA.x, PointC.y - PointA.y);
	double ABdotAC = (PointB.x - PointA.x) * (PointC.x - PointA.x) + (PointB.y - PointA.y) * (PointC.y - PointA.y);
	double modAB = sqrt(pow(PointB.x - PointA.x, 2) + pow(PointB.y - PointA.y, 2));
	double modAC = sqrt(pow(PointC.x - PointA.x, 2) + pow(PointC.y - PointA.y, 2));
	double Alpha = acos(ABdotAC / (modAB * modAC));
	return 0.5 * modAB * modAC * sin(Alpha);
}

tuple<int, Engine3D_Vector2D> Engine3D_Manager::Segment2DIntersection(Engine3D_Vector2D P1, Engine3D_Vector2D P2, Engine3D_Vector2D P3, Engine3D_Vector2D P4)
{
	Engine3D_Vector2D IntPoint(0, 0);
	struct Calculation
	{
		bool Equal(double f1, double f2) {
			return (abs(f1 - f2) < EPSILON);
		}
	};
	struct POINTF
	{
		Calculation Calculation;
		double x, y;
		POINTF(double x, double y)
		{
			this->x = x;
			this->y = y;
		}
		POINTF(Engine3D_Vector2D Point)
		{
			this->x = Point.x;
			this->y = Point.y;
		}
		//判断两点是否相等
		bool operator==(const POINTF& p2) {
			return (Calculation.Equal(this->x, p2.x) && Calculation.Equal(this->y, p2.y));
		}
		//比较两点坐标大小，先比较x坐标，若相同则比较y坐标
		bool operator>(const POINTF& p2) {
			return (this->x > p2.x || (Calculation.Equal(this->x, p2.x) && this->y > p2.y));
		}
		//计算两向量外积
		double operator^(const POINTF& p2) {
			return (this->x * p2.y - this->y * p2.x);
		}
	};
	POINTF p1(P1), p2(P2), p3(P3), p4(P4);
	Calculation Calculation;
	//判定两线段位置关系，并求出交点(如果存在)。返回值列举如下：
	//[有重合] 完全重合(6)，1个端点重合且共线(5)，部分重合(4)
	//[无重合] 两端点相交(3)，交于线上(2)，正交(1)，无交(0)，参数错误(-1)
	//保证参数p1!=p2，p3!=p4
	if (p1 == p2 || p3 == p4) {
		return make_tuple(-1, IntPoint); //返回-1代表至少有一条线段首尾重合，不能构成线段
	}
	//为方便运算，保证各线段的起点在前，终点在后。
	if (p1 > p2) {
		swap(p1, p2);
	}
	if (p3 > p4) {
		swap(p3, p4);
	}
	//判定两线段是否完全重合
	if (p1 == p3 && p2 == p4) {
		return make_tuple(6, IntPoint);
	}
	//求出两线段构成的向量
	POINTF v1(p2.x - p1.x, p2.y - p1.y), v2(p4.x - p3.x, p4.y - p3.y);
	//求两向量外积，平行时外积为0
	double Corss = v1 ^ v2;
	//如果起点重合
	if (p1 == p3) {
		IntPoint.x = p1.x;
		IntPoint.y = p1.y;
		//起点重合且共线(平行)返回5；不平行则交于端点，返回3
		return make_tuple(Calculation.Equal(Corss, 0) ? 5 : 3, IntPoint);
	}
	//如果终点重合
	if (p2 == p4) {
		IntPoint.x = p2.x;
		IntPoint.y = p2.y;
		//终点重合且共线(平行)返回5；不平行则交于端点，返回3
		return make_tuple(Calculation.Equal(Corss, 0) ? 5 : 3, IntPoint);
	}
	//如果两线端首尾相连
	if (p1 == p4) {
		IntPoint.x = p1.x;
		IntPoint.y = p1.y;
		return make_tuple(3, IntPoint);
	}
	if (p2 == p3) {
		IntPoint.x = p2.x;
		IntPoint.y = p2.y;
		return make_tuple(3, IntPoint);
	}//经过以上判断，首尾点相重的情况都被排除了
	//将线段按起点坐标排序。若线段1的起点较大，则将两线段交换
	if (p1 > p3) {
		swap(p1, p3);
		swap(p2, p4);
		//更新原先计算的向量及其外积
		swap(v1, v2);
		Corss = v1 ^ v2;
	}
	//处理两线段平行的情况
	if (Calculation.Equal(Corss, 0)) {
		//做向量v1(p1, p2)和vs(p1,p3)的外积，判定是否共线
		POINTF vs = { p3.x - p1.x, p3.y - p1.y };
		//外积为0则两平行线段共线，下面判定是否有重合部分
		if (Calculation.Equal(v1 ^ vs, 0)) {
			//前一条线的终点大于后一条线的起点，则判定存在重合
			if (p2 > p3) {
				IntPoint.x = p3.x;
				IntPoint.y = p3.y;
				return make_tuple(4, IntPoint); //返回值4代表线段部分重合
			}
		}//若三点不共线，则这两条平行线段必不共线。
		//不共线或共线但无重合的平行线均无交点
		return make_tuple(0, IntPoint);
	} //以下为不平行的情况，先进行快速排斥试验
	//x坐标已有序，可直接比较。y坐标要先求两线段的最大和最小值
	double ymax1 = p1.y, ymin1 = p2.y, ymax2 = p3.y, ymin2 = p4.y;
	if (ymax1 < ymin1) {
		swap(ymax1, ymin1);
	}
	if (ymax2 < ymin2) {
		swap(ymax2, ymin2);
	}
	//如果以两线段为对角线的矩形不相交，则无交点
	if (p1.x > p4.x || p2.x < p3.x || ymax1 < ymin2 || ymin1 > ymax2) {
		return make_tuple(0, IntPoint);
	}//下面进行跨立试验
	POINTF vs1 = { p1.x - p3.x, p1.y - p3.y }, vs2 = { p2.x - p3.x, p2.y - p3.y };
	POINTF vt1 = { p3.x - p1.x, p3.y - p1.y }, vt2 = { p4.x - p1.x, p4.y - p1.y };
	double s1v2, s2v2, t1v1, t2v1;
	//根据外积结果判定否交于线上
	if (Calculation.Equal(s1v2 = vs1 ^ v2, 0) && p4 > p1 && p1 > p3) {
		IntPoint.x = p1.x;
		IntPoint.y = p1.y;
		return make_tuple(2, IntPoint);
	}
	if (Calculation.Equal(s2v2 = vs2 ^ v2, 0) && p4 > p2 && p2 > p3) {
		IntPoint.x = p2.x;
		IntPoint.y = p2.y;
		return make_tuple(2, IntPoint);
	}
	if (Calculation.Equal(t1v1 = vt1 ^ v1, 0) && p2 > p3 && p3 > p1) {
		IntPoint.x = p3.x;
		IntPoint.y = p3.y;
		return make_tuple(2, IntPoint);
	}
	if (Calculation.Equal(t2v1 = vt2 ^ v1, 0) && p2 > p4 && p4 > p1) {
		IntPoint.x = p4.x;
		IntPoint.y = p4.y;
		return make_tuple(2, IntPoint);
	} //未交于线上，则判定是否相交
	if (s1v2 * s2v2 > 0 || t1v1 * t2v1 > 0) {
		return make_tuple(0, IntPoint);
	} //以下为相交的情况，算法详见文档
	//计算二阶行列式的两个常数项
	double ConA = p1.x * v1.y - p1.y * v1.x;
	double ConB = p3.x * v2.y - p3.y * v2.x;
	//计算行列式D1和D2的值，除以系数行列式的值，得到交点坐标
	IntPoint.x = (ConB * v1.x - ConA * v2.x) / Corss;
	IntPoint.y = (ConB * v1.y - ConA * v2.y) / Corss;
	//正交返回1
	return make_tuple(1, IntPoint);
}

double Engine3D_Manager::Calculate_RayTriangleIntersectionDistance(Engine3D_Vector2D Ray, Engine3D_Triangle* Triangle, int CameraID)
{
	Engine3D_Vector3D V1 = Triangle->Point_A->coordinates_camera[CameraID];
	Engine3D_Vector3D V2 = Triangle->Point_B->coordinates_camera[CameraID];
	Engine3D_Vector3D V3 = Triangle->Point_C->coordinates_camera[CameraID];
	Engine3D_Vector3D E1 = V2 - V1;
	Engine3D_Vector3D E2 = V3 - V1;
	Engine3D_Vector3D S = Engine3D_Vector3D(0, 0, 0) - V1;
	Engine3D_Vector3D S2 = S.CrossProduct(E1);
	Engine3D_Vector3D D(Ray.x, Ray.y, -this->Cameras_list[CameraID]->depth);
	Engine3D_Vector3D S1 = D.CrossProduct(E2);
	double b1 = S1.DotProduct(S) / S1.DotProduct(E1);
	double b2 = S2.DotProduct(D) / S1.DotProduct(E1);
	if (!(b1 >= -EPSILON && b2 >= -EPSILON && b1 + b2 <= 1 + EPSILON))
	{
		cout << "ERROR__Calculate_RayTriangleIntersectionDistance" << endl;
		system("pause");
	}
	/*if (!(b1 >= -EPSILON && b2 >= -EPSILON && b1 + b2 <= 1 + EPSILON))
	{
		cout << "Distance:  " << (V1 * (1 - b1 - b2) + V2 * b1 + V3 * b2).GetLength() << endl;
		cout << "Ray:  (" << Ray.x << "," << Ray.y << ")" << endl;
		cout << "Triangle:  (" << V1.x << "," << V1.y << "," << V1.z << ")  ";
		cout << "(" << V2.x << ", " << V2.y << ", " << V2.z << ")  ";
		cout << "(" << V3.x << ", " << V3.y << ", " << V3.z << ")  ";
		system("pause");
	}*/
	return (V1 * (1 - b1 - b2) + V2 * b1 + V3 * b2).GetLength();
}

void Engine3D_Manager::Calculate_TriangleObstruct(Engine3D_Camera* Camera)//未投入使用
{
	int cameraID = 0;
	for (int i = 0; i < this->camerasnum; i++)
	{
		if (this->Cameras_list[i]->name == Camera->name)
		{
			cameraID = i;
			break;
		}
	}
	int trianglenum = 0;
	for (int i = 0; i < this->objectsnum; i++)
	{
		for (int j = 0; j < this->Objects_list[i]->trianglenum; j++)
		{
			if (this->Objects_list[i]->Trianglelist[j]->Point_A->coordinates_camera[cameraID].z < 0 && this->Objects_list[i]->Trianglelist[j]->Point_B->coordinates_camera[cameraID].z < 0 && this->Objects_list[i]->Trianglelist[j]->Point_C->coordinates_camera[cameraID].z < 0)
			{
				trianglenum++;
			}
		}
	}
	if (trianglenum <= 0)
	{
		return;
	}
	Engine3D_Triangle** TriangleList = new Engine3D_Triangle * [trianglenum];
	int nownum = 0;
	for (int i = 0; i < this->objectsnum; i++)
	{
		for (int j = 0; j < this->Objects_list[i]->trianglenum; j++)
		{
			if (nownum < trianglenum && this->Objects_list[i]->Trianglelist[j]->Point_A->coordinates_camera[cameraID].z < 0 && this->Objects_list[i]->Trianglelist[j]->Point_B->coordinates_camera[cameraID].z < 0 && this->Objects_list[i]->Trianglelist[j]->Point_C->coordinates_camera[cameraID].z < 0)
			{
				TriangleList[nownum] = this->Objects_list[i]->Trianglelist[j];
				nownum++;
			}
		}
	}
	
	/*trianglenum = 4;
	TriangleList[0]->Point_A->coordinates_camera[0] = new Engine3D_Vector3D(-10, 0, -50);
	TriangleList[0]->Point_B->coordinates_camera[0] = new Engine3D_Vector3D(10, 0, -50);
	TriangleList[0]->Point_C->coordinates_camera[0] = new Engine3D_Vector3D(0, 100, -50);
	TriangleList[1]->Point_A->coordinates_camera[0] = new Engine3D_Vector3D(-10, 0, -60);
	TriangleList[1]->Point_B->coordinates_camera[0] = new Engine3D_Vector3D(10, 0, -60);
	TriangleList[1]->Point_C->coordinates_camera[0] = new Engine3D_Vector3D(0, 100, -60);
	TriangleList[2]->Point_A->coordinates_camera[0] = new Engine3D_Vector3D(-10, 0, -70);
	TriangleList[2]->Point_B->coordinates_camera[0] = new Engine3D_Vector3D(10, 0, -70);
	TriangleList[2]->Point_C->coordinates_camera[0] = new Engine3D_Vector3D(0, 100, -70);
	TriangleList[3]->Point_A->coordinates_camera[0] = new Engine3D_Vector3D(-10, 0, -80);
	TriangleList[3]->Point_B->coordinates_camera[0] = new Engine3D_Vector3D(10, 0, -80);
	TriangleList[3]->Point_C->coordinates_camera[0] = new Engine3D_Vector3D(0, 100, -80);*/

	int** TriangleRelation = new int* [trianglenum];//[i][j] i相对于j的关系: 0:无关/1:前/-1:后
	for (int i = 0; i < trianglenum; i++)
	{
		TriangleRelation[i] = new int[trianglenum];
		for (int j = 0; j < trianglenum; j++)
		{
			TriangleRelation[i][j] = 0;
		}
	}
	Engine3D_Vector2D RayList[3] = { {0,0},{0,0},{0,0} };
	int NowRayNumber = 0;
	bool Continue = false;
	bool SkipRay = false;
	bool Break = false;
	for (int i = 0; i < trianglenum; i++)
	{
		for (int j = 0; j < trianglenum; j++)
		{
			if (i == j || TriangleRelation[i][j] != 0) { continue; }
			NowRayNumber = 0;
			Continue = false;
			/*tuple<int, Engine3D_Vector2D*> Self = this->Calculate_TriangleRelation(TriangleList[i], TriangleList[j], cameraID);
			tuple<int, Engine3D_Vector2D*> Target = this->Calculate_TriangleRelation(TriangleList[j], TriangleList[i], cameraID);
			for (int l = 0; l < get<0>(Self); l++)
			{
				SkipRay = false;
				for (int a = 0; a < NowRayNumber; a++)
				{
					if (RayList[a] == get<1>(Self)[l])
					{
						SkipRay = true;
						break;
					}
				}
				if (SkipRay) { continue; }
				RayList[NowRayNumber] = get<1>(Self)[l];
				NowRayNumber++;
				if (NowRayNumber == 3) { Continue = true; break; }
			}
			if (Continue) { continue; }
			for (int o = 0; o < get<0>(Target); o++)
			{
				SkipRay = false;
				for (int a = 0; a < NowRayNumber; a++)
				{
					if (RayList[a] == get<1>(Target)[o])
					{
						SkipRay = true;
						break;
					}
				}
				if (SkipRay) { continue; }
				RayList[NowRayNumber] = get<1>(Target)[o];
				NowRayNumber++;
				if (NowRayNumber == 3) { Continue = true; break; }
			}
			if (Continue) { continue; }*/
			int Type = -1;
			Engine3D_Vector2D IntPoint;
			Engine3D_Point* Point_I1 = NULL;
			Engine3D_Point* Point_I2 = NULL;
			Engine3D_Point* Point_J1 = NULL;
			Engine3D_Point* Point_J2 = NULL;
			for (int m = 0; m < 3; m++)
			{
				switch (m)
				{
				case 0: {Point_I1 = TriangleList[i]->Point_A; Point_I2 = TriangleList[i]->Point_B; break; }
				case 1: {Point_I1 = TriangleList[i]->Point_B; Point_I2 = TriangleList[i]->Point_C; break; }
				case 2: {Point_I1 = TriangleList[i]->Point_C; Point_I2 = TriangleList[i]->Point_A; break; }
				default:
					break;
				}
				for (int n = 0; n < 3; n++)
				{
					switch (n)
					{
					case 0: {Point_J1 = TriangleList[j]->Point_A; Point_J2 = TriangleList[j]->Point_B; break; }
					case 1: {Point_J1 = TriangleList[j]->Point_B; Point_J2 = TriangleList[j]->Point_C; break; }
					case 2: {Point_J1 = TriangleList[j]->Point_C; Point_J2 = TriangleList[j]->Point_A; break; }
					default:
						break;
					}
					tie(Type, IntPoint) = this->Segment2DIntersection(Point_I1->coordinates_screen[cameraID], Point_I2->coordinates_screen[cameraID], Point_J1->coordinates_screen[cameraID], Point_J2->coordinates_screen[cameraID]);
					if (Type == 1)
					{
						SkipRay = false;
						for (int a = 0; a < NowRayNumber; a++)
						{
							if (RayList[a] == IntPoint)
							{
								SkipRay = true;
								break;
							}
						}
						if (SkipRay) { continue; }
						double DistanceI = this->Calculate_RayTriangleIntersectionDistance(IntPoint, TriangleList[i], cameraID);
						double DistanceJ = this->Calculate_RayTriangleIntersectionDistance(IntPoint, TriangleList[j], cameraID);
						if (abs(DistanceI - DistanceJ) <= EPSILON)
						{
							TriangleRelation[i][j] = 0;
							TriangleRelation[j][i] = 0;
						}
						else if (DistanceI - DistanceJ < -EPSILON)
						{
							TriangleRelation[i][j] = 1;
							TriangleRelation[j][i] = -1;
							Continue = true;
							break;
						}
						else if (DistanceI - DistanceJ > EPSILON)
						{
							TriangleRelation[i][j] = -1;
							TriangleRelation[j][i] = 1;
							Continue = true;
							break;
						}
						RayList[NowRayNumber] = IntPoint;
						NowRayNumber++;
						if (NowRayNumber == 3) { Continue = true; break; }
					}
				}
				if (Continue) { break; }
			}
			/*cout << endl << "------------------------------------------------" << endl << "A(" << TriangleList[i]->Point_A->coordinates_screen[cameraID]->x << "," << TriangleList[i]->Point_A->coordinates_screen[cameraID]->y << ")";
			cout << "B(" << TriangleList[i]->Point_B->coordinates_screen[cameraID]->x << "," << TriangleList[i]->Point_B->coordinates_screen[cameraID]->y << ")";
			cout << "C(" << TriangleList[i]->Point_C->coordinates_screen[cameraID]->x << "," << TriangleList[i]->Point_C->coordinates_screen[cameraID]->y << ")";
			cout << endl;
			cout << "A(" << TriangleList[j]->Point_A->coordinates_screen[cameraID]->x << "," << TriangleList[j]->Point_A->coordinates_screen[cameraID]->y << ")";
			cout << "B(" << TriangleList[j]->Point_B->coordinates_screen[cameraID]->x << "," << TriangleList[j]->Point_B->coordinates_screen[cameraID]->y << ")";
			cout << "C(" << TriangleList[j]->Point_C->coordinates_screen[cameraID]->x << "," << TriangleList[j]->Point_C->coordinates_screen[cameraID]->y << ")";
			cout << endl;
			cout << "INT  :  ";
			for (int s = 0; s < NowRayNumber; s++)
			{
				cout << "(" << RayList[s].x << "," << RayList[s].y << ")";
			}
			cout << endl << "------------------------------------------------" << endl;*/
			Point_I1 = NULL;
			Point_I2 = NULL;
			Point_J1 = NULL;
			Point_J2 = NULL;
		}
	}

	/*for (int i = 0; i < trianglenum; i++)
	{
		for (int j = 0; j < trianglenum; j++)
		{
			if (i == j) { continue; }
			cout << endl << "-----------------------------------" << endl << "TriangleList[i]:" << endl;
			cout << "A (" << TriangleList[i]->Point_A->coordinates_camera[cameraID]->x << "," << TriangleList[i]->Point_A->coordinates_camera[cameraID]->y << "," << TriangleList[i]->Point_A->coordinates_camera[cameraID]->z << ")   ";
			cout << "B (" << TriangleList[i]->Point_B->coordinates_camera[cameraID]->x << "," << TriangleList[i]->Point_B->coordinates_camera[cameraID]->y << "," << TriangleList[i]->Point_B->coordinates_camera[cameraID]->z << ")   ";
			cout << "C (" << TriangleList[i]->Point_C->coordinates_camera[cameraID]->x << "," << TriangleList[i]->Point_C->coordinates_camera[cameraID]->y << "," << TriangleList[i]->Point_C->coordinates_camera[cameraID]->z << ")   ";
			cout << endl << "TriangleList[j]:" << endl;
			cout << "A (" << TriangleList[j]->Point_A->coordinates_camera[cameraID]->x << "," << TriangleList[j]->Point_A->coordinates_camera[cameraID]->y << "," << TriangleList[j]->Point_A->coordinates_camera[cameraID]->z << ")   ";
			cout << "B (" << TriangleList[j]->Point_B->coordinates_camera[cameraID]->x << "," << TriangleList[j]->Point_B->coordinates_camera[cameraID]->y << "," << TriangleList[j]->Point_B->coordinates_camera[cameraID]->z << ")   ";
			cout << "C (" << TriangleList[j]->Point_C->coordinates_camera[cameraID]->x << "," << TriangleList[j]->Point_C->coordinates_camera[cameraID]->y << "," << TriangleList[j]->Point_C->coordinates_camera[cameraID]->z << ")   ";
			cout << endl << "Relation:  " << TriangleRelation[i][j] << endl;
		}
	}
	system("pause");*/
	
	/*for (int i = 0; i < trianglenum; i++)
	{
		for (int j = 0; j < trianglenum; j++)
		{
			cout << TriangleRelation[i][j] << endl;
		}
		cout<<"i:   " << TriangleBehindNum[i] << endl;
	}
	system("pause");*/

	int** TriangleBehind = new int* [trianglenum];
	int* TriangleBehindNum = new int[trianglenum];
	for (int i = 0; i < trianglenum; i++)
	{
		TriangleBehindNum[i] = 0;
		for (int j = 0; j < trianglenum; j++)
		{
			if (TriangleRelation[i][j] == 1)
			{
				TriangleBehindNum[i]++;
			}
		}
		TriangleBehind[i] = new int[TriangleBehindNum[i]];
		int n = 0;
		for (int j = 0; j < trianglenum; j++)
		{
			if (TriangleRelation[i][j] == 1)
			{
				TriangleBehind[i][n] = j;
				n++;
			}
		}
	}

	/*for (int i = 0; i < trianglenum; i++)
	{
		cout << endl << "----------------------------------------------------" << endl;
		cout << "No. " << i << " :   " << endl;
		for (int j = 0; j < TriangleBehindNum[i]; j++)
		{
			cout << TriangleBehind[i][j] << " ";
		}
		cout << endl << "----------------------------------------------------" << endl;
	}
	system("pause");*/
	
	int* TriangleDistanceOrdinal = new int[trianglenum];
	int* TriangleDistanceOrdinalHistory = new int[trianglenum];
	for (int i = 0; i < trianglenum; i++)
	{
		TriangleDistanceOrdinal[i] = 0;
		TriangleDistanceOrdinalHistory[i] = 0;
	}
	for (int i = 0; i < trianglenum; i++)
	{
		for (int j = 0; j < TriangleBehindNum[i]; j++)
		{
			TriangleDistanceOrdinal[TriangleBehind[i][j]] = -1;
		}
	}
	
	/*for (int i = 0; i < trianglenum; i++)
	{
		cout << endl << "----------------------------------------------------" << endl;
		cout << "No. " << i << " :   " << endl;
		cout << "TriangleDistanceOrdinal:  " << TriangleDistanceOrdinal[i] << endl;
		cout << "TriangleBehindNum:  " << TriangleBehindNum[i] << endl;
		for (int j = 0; j < TriangleBehindNum[i]; j++)
		{
			cout << TriangleBehind[i][j] << " ";
		}
		cout << endl << "----------------------------------------------------" << endl;
	}
	system("pause");*/

	/*if (trianglenum > 56)
	{
		cout << endl << "----------------------------------------------------" << endl;
		cout << "56:  " << endl;
		cout << "(" << TriangleList[56]->Point_A->coordinates_camera[0]->x << "," << TriangleList[56]->Point_A->coordinates_camera[0]->y << "," << TriangleList[56]->Point_A->coordinates_camera[0]->z << ")  "
			<< "(" << TriangleList[56]->Point_B->coordinates_camera[0]->x << "," << TriangleList[56]->Point_B->coordinates_camera[0]->y << "," << TriangleList[56]->Point_B->coordinates_camera[0]->z << ")  "
			<< "(" << TriangleList[56]->Point_C->coordinates_camera[0]->x << "," << TriangleList[56]->Point_C->coordinates_camera[0]->y << "," << TriangleList[56]->Point_C->coordinates_camera[0]->z << ")  " << endl;
		cout << "TriangleBehindNum:  " << TriangleBehindNum[56] << endl;
		for (int j = 0; j < TriangleBehindNum[56]; j++)
		{
			cout << TriangleBehind[56][j] << " ";
		}
		cout << endl << "----------------------------------------------------" << endl;
		cout << endl << "----------------------------------------------------" << endl;
		cout << "37:  " << endl;
		cout << "(" << TriangleList[37]->Point_A->coordinates_camera[0]->x << "," << TriangleList[37]->Point_A->coordinates_camera[0]->y << "," << TriangleList[37]->Point_A->coordinates_camera[0]->z << ")  "
			<< "(" << TriangleList[37]->Point_B->coordinates_camera[0]->x << "," << TriangleList[37]->Point_B->coordinates_camera[0]->y << "," << TriangleList[37]->Point_B->coordinates_camera[0]->z << ")  "
			<< "(" << TriangleList[37]->Point_C->coordinates_camera[0]->x << "," << TriangleList[37]->Point_C->coordinates_camera[0]->y << "," << TriangleList[37]->Point_C->coordinates_camera[0]->z << ")  " << endl;
		cout << "TriangleBehindNum:  " << TriangleBehindNum[37] << endl;
		for (int j = 0; j < TriangleBehindNum[37]; j++)
		{
			cout << TriangleBehind[37][j] << " ";
		}
		cout << endl << "----------------------------------------------------" << endl;
		cout << endl << "----------------------------------------------------" << endl;
		cout << "35:  " << endl;
		cout << "(" << TriangleList[35]->Point_A->coordinates_camera[0]->x << "," << TriangleList[35]->Point_A->coordinates_camera[0]->y << "," << TriangleList[35]->Point_A->coordinates_camera[0]->z << ")  "
			<< "(" << TriangleList[35]->Point_B->coordinates_camera[0]->x << "," << TriangleList[35]->Point_B->coordinates_camera[0]->y << "," << TriangleList[35]->Point_B->coordinates_camera[0]->z << ")  "
			<< "(" << TriangleList[35]->Point_C->coordinates_camera[0]->x << "," << TriangleList[35]->Point_C->coordinates_camera[0]->y << "," << TriangleList[35]->Point_C->coordinates_camera[0]->z << ")  " << endl;
		cout << "TriangleBehindNum:  " << TriangleBehindNum[35] << endl;
		for (int j = 0; j < TriangleBehindNum[35]; j++)
		{
			cout << TriangleBehind[35][j] << " ";
		}
		cout << endl << "----------------------------------------------------" << endl;
		system("pause");
	}*/

	int DistanceOrdinal = 0;
	bool run = true;
	while (run)
	{
		run = false;
		for (int i = 0; i < trianglenum; i++)
		{
			TriangleDistanceOrdinalHistory[i] = TriangleDistanceOrdinal[i];
		}
		//cout << DistanceOrdinal << endl;
		for (int i = 0; i < trianglenum; i++)
		{
			if (TriangleDistanceOrdinal[i] == DistanceOrdinal)
			{
				//cout << endl << "----------------------------------------------------" << endl;
				//cout << "No. " << i << endl;
				//cout << "DistanceOrdinal:  " << DistanceOrdinal << endl;
				//cout << "TriangleBehindNum:  " << TriangleBehindNum[i] << endl;
				if (TriangleBehindNum[i] > 0) { run = true; }
				for (int j = 0; j < TriangleBehindNum[i]; j++)
				{
					//cout << TriangleBehind[i][j] << " ";
					TriangleDistanceOrdinal[TriangleBehind[i][j]] = DistanceOrdinal + 1;
				}
				//cout << endl << "----------------------------------------------------" << endl;
				//system("pause");
			}
		}
		DistanceOrdinal++;
		if (run)
		{
			for (int i = 0; i < DistanceOrdinal + 1; i++)
			{
				run = false;
				for (int j = 0; j < trianglenum; j++)
				{				
					if (TriangleDistanceOrdinal[j] == i)
					{
						run = true;
					}
				}
				if (!run) { break; }
			}
		}
	}

	int Max = 0;
	for (int i = 0; i < trianglenum; i++)
	{
		if (TriangleDistanceOrdinalHistory[i] > Max)
		{
			Max = TriangleDistanceOrdinalHistory[i];
		}
	}
	for (int i = 0; i < this->objectsnum; i++)
	{
		for (int j = 0; j < this->Objects_list[i]->trianglenum; j++)
		{
			//this->Objects_list[i]->Trianglelist[j]->ShowOrder = -1;
		}
	}
	for (int i = 0; i < trianglenum; i++)
	{
		//TriangleList[i]->ShowOrder = Max - TriangleDistanceOrdinalHistory[i];
	}
	return;
}

/*bool Engine3D_Manager::DeleteTriangleBehind(int** TriangleBehind, int* TriangleBehindNum, int NowTriangle, int FindTriangle)
{
	cout << "NowTriangle:  " << NowTriangle << "      ";
	cout << "TriangleBehindNum[NowTriangle]:   " << TriangleBehindNum[NowTriangle];
	cout << endl;
	for (int i = 0; i < TriangleBehindNum[NowTriangle]; i++)
	{
		if (TriangleBehind[NowTriangle][i] == FindTriangle)
		{
			return true;
		}
		else
		{
			cout << "TriangleBehind:   " << TriangleBehind[NowTriangle][i];
			if (this->DeleteTriangleBehind(TriangleBehind, TriangleBehindNum, TriangleBehind[NowTriangle][i], FindTriangle))
			{
				return true;
			}
		}
	}
	
	return false;
}*/

/*void Engine3D_Manager::Camera_Adjustment()
{
	double TIME = GetTime_Second_AccurateToMicrosecond() - this->Camera->LastUpdateTime;

	//平移
	if (GetAsyncKeyState('W'))
	{
		Engine3D_Vector3D Z_UnitVector = this->Camera->orientation->Get_UnitVector("z");
		this->Camera->coordinates->x = this->Camera->coordinates->x - Z_UnitVector.x * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->y = this->Camera->coordinates->y - Z_UnitVector.y * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->z = this->Camera->coordinates->z - Z_UnitVector.z * this->Camera->Sensitivity_Translation * TIME;
	}
	if (GetAsyncKeyState('S'))
	{
		Engine3D_Vector3D Z_UnitVector = this->Camera->orientation->Get_UnitVector("z");
		this->Camera->coordinates->x = this->Camera->coordinates->x + Z_UnitVector.x * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->y = this->Camera->coordinates->y + Z_UnitVector.y * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->z = this->Camera->coordinates->z + Z_UnitVector.z * this->Camera->Sensitivity_Translation * TIME;
	}
	if (GetAsyncKeyState('A'))
	{
		Engine3D_Vector3D X_UnitVector = this->Camera->orientation->Get_UnitVector("x");
		this->Camera->coordinates->x = this->Camera->coordinates->x - X_UnitVector.x * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->y = this->Camera->coordinates->y - X_UnitVector.y * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->z = this->Camera->coordinates->z - X_UnitVector.z * this->Camera->Sensitivity_Translation * TIME;
	}
	if (GetAsyncKeyState('D'))
	{
		Engine3D_Vector3D X_UnitVector = this->Camera->orientation->Get_UnitVector("x");
		this->Camera->coordinates->x = this->Camera->coordinates->x + X_UnitVector.x * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->y = this->Camera->coordinates->y + X_UnitVector.y * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->z = this->Camera->coordinates->z + X_UnitVector.z * this->Camera->Sensitivity_Translation * TIME;
	}
	if (GetAsyncKeyState('R'))
	{
		Engine3D_Vector3D Y_UnitVector = this->Camera->orientation->Get_UnitVector("y");
		this->Camera->coordinates->x = this->Camera->coordinates->x + Y_UnitVector.x * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->y = this->Camera->coordinates->y + Y_UnitVector.y * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->z = this->Camera->coordinates->z + Y_UnitVector.z * this->Camera->Sensitivity_Translation * TIME;
	}
	if (GetAsyncKeyState('F'))
	{
		Engine3D_Vector3D Y_UnitVector = this->Camera->orientation->Get_UnitVector("y");
		this->Camera->coordinates->x = this->Camera->coordinates->x - Y_UnitVector.x * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->y = this->Camera->coordinates->y - Y_UnitVector.y * this->Camera->Sensitivity_Translation * TIME;
		this->Camera->coordinates->z = this->Camera->coordinates->z - Y_UnitVector.z * this->Camera->Sensitivity_Translation * TIME;
	}

	//旋转
	if (GetAsyncKeyState('I'))
	{
		*this->Camera->orientation = this->Camera->orientation->Rotation(this->Camera->orientation->Get_UnitVector("x"), this->Camera->Sensitivity_Rotation* TIME);
	}
	if (GetAsyncKeyState('K'))
	{
		*this->Camera->orientation = this->Camera->orientation->Rotation(this->Camera->orientation->Get_UnitVector("x"), -this->Camera->Sensitivity_Rotation * TIME);
	}
	if (GetAsyncKeyState('J'))
	{
		*this->Camera->orientation = this->Camera->orientation->Rotation(this->Camera->orientation->Get_UnitVector("y"), this->Camera->Sensitivity_Rotation * TIME);
	}
	if (GetAsyncKeyState('L'))
	{
		*this->Camera->orientation = this->Camera->orientation->Rotation(this->Camera->orientation->Get_UnitVector("y"), -this->Camera->Sensitivity_Rotation * TIME);
	}
	if (GetAsyncKeyState('U'))
	{
		*this->Camera->orientation = this->Camera->orientation->Rotation(this->Camera->orientation->Get_UnitVector("z"), this->Camera->Sensitivity_Rotation * TIME);
	}
	if (GetAsyncKeyState('O'))
	{
		*this->Camera->orientation = this->Camera->orientation->Rotation(this->Camera->orientation->Get_UnitVector("z"), -this->Camera->Sensitivity_Rotation * TIME);
	}

	//其他
	if (GetAsyncKeyState('N'))
	{
		this->Camera->depth = this->Camera->depth + 0.0005;
	}
	if (GetAsyncKeyState('M'))
	{
		this->Camera->depth = this->Camera->depth - 0.0005;
	}

	this->Camera->LastUpdateTime = GetTime_Second_AccurateToMicrosecond();

	return;
}*/
