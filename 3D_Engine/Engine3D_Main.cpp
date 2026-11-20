#include<iostream>
#include<chrono>
#include"Engine3D_Calculation.h"
#include"Engine3D_Manager.h"
using namespace std;
int main()
{
    srand((unsigned int)time(NULL));
	Engine3D_Manager EM;

	EM.Add_Warplane();
	EM.Add_Object(0, 0, 0);

    /*cout << get<0>(EM.Segment2DIntersection(Engine3D_Vector2D(0, 0), Engine3D_Vector2D(10, 0), Engine3D_Vector2D(10, 0), Engine3D_Vector2D(5, 5)));
    Engine3D_Triangle* A = new Engine3D_Triangle(new Engine3D_Point(2, 0, -1), new Engine3D_Point(10, 0, -1), new Engine3D_Point(5, 5, -1));
    Engine3D_Triangle* B = new Engine3D_Triangle(new Engine3D_Point(0, 0, -1), new Engine3D_Point(10, 0, -1), new Engine3D_Point(5, 10, -1));

    cout << endl << get<0>(EM.Calculate_TriangleRelation(A, B, 0));
    system("pause");*/

	while (true)
	{
		//*EM.SunLight = Engine3D_Quaternion(*EM.SunLight).Rotation(Engine3D_Vector3D(1, 0, 0), 0.1).Quaternion_To_Vector3D();

		EM.CALCULATE_All();
		EM.Warplane_Update();
		EM.Bullet_Update();
        EM.Missile_Update();

		//EM.Warplane_list[0]->coordinates->z = EM.Warplane_list[0]->coordinates->z - 0.1;
		//cout << EM.Objects_list[0]->Linelist[0]->Point_A->coordinates_screen->y << endl;
		//EM.Camera_Adjustment();
		
		//EM.Warplane_list[0]->Object_list[0]->Object->orientation = Calculation.Rotation(Calculation.Get_UnitVector("z", EM.Warplane_list[0]->Object_list[0]->Object->orientation), 20, EM.Warplane_list[0]->Object_list[0]->Object->orientation);

		EM.Show();
		EM.Warplane_Adjustment();
		//cout << EM.Camera->coordinates->x << "  " << EM.Camera->coordinates->y << "  " << EM.Camera->coordinates->z << endl;
		//system("pause");
	}

	system("pause");
	return 0;
}

/*#include <iostream>
#include <cmath>
using namespace std;
struct POINTF {float x; float y;};
bool Equal(float f1, float f2) {
  return (abs(f1 - f2) < 1e-4f);
}
//判断两点是否相等
bool operator==(const POINTF &p1, const POINTF &p2) {
  return (Equal(p1.x, p2.x) && Equal(p1.y, p2.y));
}
//比较两点坐标大小，先比较x坐标，若相同则比较y坐标
bool operator>(const POINTF &p1, const POINTF &p2) {
  return (p1.x > p2.x || (Equal(p1.x, p2.x) && p1.y > p2.y));
}
//计算两向量外积
float operator^(const POINTF &p1, const POINTF &p2) {
  return (p1.x * p2.y - p1.y * p2.x);
}
//判定两线段位置关系，并求出交点(如果存在)。返回值列举如下：
//[有重合] 完全重合(6)，1个端点重合且共线(5)，部分重合(4)
//[无重合] 两端点相交(3)，交于线上(2)，正交(1)，无交(0)，参数错误(-1)
int Intersection(POINTF p1, POINTF p2, POINTF p3, POINTF p4, POINTF &Int) {
  //保证参数p1!=p2，p3!=p4
  if (p1 == p2 || p3 == p4) {
    return -1; //返回-1代表至少有一条线段首尾重合，不能构成线段
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
    return 6;
  }
  //求出两线段构成的向量
  POINTF v1 = {p2.x - p1.x, p2.y - p1.y}, v2 = {p4.x - p3.x, p4.y - p3.y};
  //求两向量外积，平行时外积为0
  float Corss = v1 ^ v2;
  //如果起点重合
  if (p1 == p3) {
    Int = p1;
    //起点重合且共线(平行)返回5；不平行则交于端点，返回3
    return (Equal(Corss, 0) ? 5 : 3);
  }
  //如果终点重合
  if (p2 == p4) {
    Int = p2;
    //终点重合且共线(平行)返回5；不平行则交于端点，返回3
    return (Equal(Corss, 0) ? 5 : 3);
  }
  //如果两线端首尾相连
  if (p1 == p4) {
    Int = p1;
    return 3;
  }
  if (p2 == p3) {
    Int = p2;
    return 3;
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
  if (Equal(Corss, 0)) {
    //做向量v1(p1, p2)和vs(p1,p3)的外积，判定是否共线
    POINTF vs = {p3.x - p1.x, p3.y - p1.y};
    //外积为0则两平行线段共线，下面判定是否有重合部分
    if (Equal(v1 ^ vs, 0)) {
      //前一条线的终点大于后一条线的起点，则判定存在重合
      if (p2 > p3) {
        Int = p3;
        return 4; //返回值4代表线段部分重合
      }
    }//若三点不共线，则这两条平行线段必不共线。
    //不共线或共线但无重合的平行线均无交点
    return 0;
  } //以下为不平行的情况，先进行快速排斥试验
  //x坐标已有序，可直接比较。y坐标要先求两线段的最大和最小值
  float ymax1 = p1.y, ymin1 = p2.y, ymax2 = p3.y, ymin2 = p4.y;
  if (ymax1 < ymin1) {
    swap(ymax1, ymin1);
  }
  if (ymax2 < ymin2) {
    swap(ymax2, ymin2);
  }
  //如果以两线段为对角线的矩形不相交，则无交点
  if (p1.x > p4.x || p2.x < p3.x || ymax1 < ymin2 || ymin1 > ymax2) {
    return 0;
  }//下面进行跨立试验
  POINTF vs1 = {p1.x - p3.x, p1.y - p3.y}, vs2 = {p2.x - p3.x, p2.y - p3.y};
  POINTF vt1 = {p3.x - p1.x, p3.y - p1.y}, vt2 = {p4.x - p1.x, p4.y - p1.y};
  float s1v2, s2v2, t1v1, t2v1;
  //根据外积结果判定否交于线上
  if (Equal(s1v2 = vs1 ^ v2, 0) && p4 > p1 && p1 > p3) {
    Int = p1;
    return 2;
  }
  if (Equal(s2v2 = vs2 ^ v2, 0) && p4 > p2 && p2 > p3) {
    Int = p2;
    return 2;
  }
  if (Equal(t1v1 = vt1 ^ v1, 0) && p2 > p3 && p3 > p1) {
    Int = p3;
    return 2;
  }
  if (Equal(t2v1 = vt2 ^ v1, 0) && p2 > p4 && p4 > p1) {
    Int = p4;
    return 2;
  } //未交于线上，则判定是否相交
  if(s1v2 * s2v2 > 0 || t1v1 * t2v1 > 0) {
    return 0;
  } //以下为相交的情况，算法详见文档
  //计算二阶行列式的两个常数项
  float ConA = p1.x * v1.y - p1.y * v1.x;
  float ConB = p3.x * v2.y - p3.y * v2.x;
  //计算行列式D1和D2的值，除以系数行列式的值，得到交点坐标
  Int.x = (ConB * v1.x - ConA * v2.x) / Corss;
  Int.y = (ConB * v1.y - ConA * v2.y) / Corss;
  //正交返回1
  return 1;
}
//主函数
int main(void) {
  //随机生成100个测试数据
  for (int i = 0; i < 100; ++i) {
    POINTF p1, p2, p3, p4, Int;
    p1.x = (float)(rand() % 10); p1.y = (float)(rand() % 10);
    p2.x = (float)(rand() % 10); p2.y = (float)(rand() % 10);
    p3.x = (float)(rand() % 10); p3.y = (float)(rand() % 10);
    p4.x = (float)(rand() % 10); p4.y = (float)(rand() % 10);
    int nr = Intersection(p1, p2, p3, p4, Int);
    cout << "[(";
    cout << (int)p1.x << ',' << (int)p1.y << "),(";
    cout << (int)p2.x << ',' << (int)p2.y << ")]--[(";
    cout << (int)p3.x << ',' << (int)p3.y << "),(";
    cout << (int)p4.x << ',' << (int)p4.y << ")]: ";
    cout << nr;
    if (nr > 0) {
      cout << '(' << Int.x << ',' << Int.y << ')';
    }
    cout << endl;
  }
  return 0;
}
*/
