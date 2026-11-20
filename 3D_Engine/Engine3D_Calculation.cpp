#include"Engine3D_Calculation.h"

double GetTime_Second_AccurateToMicrosecond()
{
	return double(chrono::time_point_cast<chrono::microseconds>(chrono::system_clock::now()).time_since_epoch().count()) / 1000000;
}

double DegreetoRadian(double degree)
{
	return degree * PI / 180;
}

double RadiantoDegree(double radian)
{
	return radian * 180 / PI;
}
