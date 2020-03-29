#pragma once
#include "Point.h"
class Figure
{   //the point we are working with
private:
	Point actPoint;
	//count of points
	int count;

public:
	//constructor
	Figure();
	Figure(int _x, int _y, int _name);
	//destructor
	~Figure();
	//methods

	void addPoint(Point obj1);

	void delLine(Point& obj1, Point& obj2);

	void createFigure(Point _point);

	//properties

	Point& getActivePoint();

	void setActPoint(Point& obj);

	void contIsolPoint(Point& obj1, Point& obj2);

};
