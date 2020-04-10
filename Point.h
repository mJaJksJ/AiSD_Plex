#pragma once
#include "Figure.h"

class Point
{
	friend class Figure;

private:
	//coordinates
	int x, y;
	//array of point, that connected with THIS point
	Point* arrPoints;
	//name of point
	int name;
	//count of sons
	int numbSon;

public:
	//--constructors--

	Point();
	Point(int _x, int _y, int _name);
	Point(int _x, int _y);

	//destructor
	//~Point();

	//--operators--

	Point& operator= (const Point& obj);

	//--methods--

	Point* contPoint(Point* _contPoint);
	Point* delContPoint(Point* _contPoint);
	//Point* search(int _name, Point* _obj);
	Point* deepSearch(int _name,  Figure& _figure);

	//--properties--
public:
	void setName(int _name);
	int getName();
	int getNumbSon();
	Point* getArrPoints();
	int getX();
	int getY();
};
