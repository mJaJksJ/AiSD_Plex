#pragma once
class Point
{
	//координаты точки
	int x, y;
	//название точки
	int name;
    //точка, порадившая эту
	Point* parentPoint;
	//точки, порождаемые этой
	Point** childPoint;

public:

	Point(int _x, int _y);
	Point();
	~Point();

	Point& operator=(Point left);

	Point* getParentPoint();
	void setParentPoint(Point* _parentPoint);
	void setName(int _name);
	int getName();

	//добаление точки-сына к activePoint
	void addChild(Point _point);
};

