#pragma once
#include "Figure.h"

class Point
{
	friend class Figure;

private:
	//coordinates
	int x, y;
	//array of point, that connected with THIS point
	Point** arrPoints;
	//name of point
	int name;
	//count of sons
	int relationCount;

public:
	//--constructors--

	Point();
	Point(int _x, int _y, int _name);
	Point(int _x, int _y);

	//destructor
	~Point();

	//--operators--

	Point& operator= (const Point& _point);

	//--methods--

	bool connectPoint(Point* _point);
	bool disconnectPoint(Point* _point);
	Point* deepSearch(int _name, Figure* _figure);

	//--properties--

	void setName(int _name);
	int getName();
	int getRelationCount();
	Point** getArrPoints();
	int getX();
	int getY();
};