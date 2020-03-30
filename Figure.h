#pragma once
#include "Point.h"
class Figure
{   
private:

	//the point we are working with
	Point activePoint;
	//amount of points
	int count;

public:
	//constructor
	Figure();
	Figure(int _x, int _y, int _name);
	//destructor
	~Figure();


	//--methods--

	void addPoint(Point obj1);
	void deleteLine(Point& obj1, Point& obj2);
	void createFigure(Point _point);
	void status();
	void contIsolPoint(Point& obj1, Point& obj2);


	//--properties--

	Point& getActivePoint();
	void setActPoint(Point& obj);
	int getCount();

};
