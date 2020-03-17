#pragma once
class Point
{
	//координаты точки
	int x, y;
	//точка, порадившая эту
	Point* parentPoint;
	//точки, порождаемые этой
	Point** childPoint;

public:

	Point(int _x, int _y);
	Point();
	~Point();

	Point& operator=(Point left);

	Point* g_parentPoint();
	void s_parentPoint(Point* _parentPoint);
	
	//добаление точки-сына к activePoint
	void addChild(Point _point);
};

