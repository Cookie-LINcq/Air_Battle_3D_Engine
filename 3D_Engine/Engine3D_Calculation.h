#pragma once
#include<iostream>
#include<cmath>
#include<chrono>
using namespace std;

constexpr double PI = 3.1415926;
constexpr int CameraNumber = 2;
constexpr double EPSILON = 1e-6;

double GetTime_Second_AccurateToMicrosecond();
double DegreetoRadian(double degree);
double RadiantoDegree(double radian);
