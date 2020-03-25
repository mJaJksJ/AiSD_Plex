#pragma once
#include "Point.h"
class Figure
{   //the point we are working with
private:
	Point actPoint;
	//count of points
	int count;
	
public:
	//methods
	void addPoint(Point& obj1);

	void delLine(Point& obj1, Point& obj2);

	//properties
	Point getActPoint();

	void setActPoint(Point& obj);

};

