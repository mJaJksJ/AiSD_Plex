#include "Figure.h"
//constructor
Figure::Figure()
{
	actPoint = Point();
}
//methods

 Figure::Figure(int _x, int _y, int _name)
{
	 actPoint = Point(_x, _y, _name);
}

void Figure::addPoint(Point& obj)
{
	actPoint.contPoint(obj);
	obj.contPoint(actPoint);
}

void Figure::delLine(Point& obj1, Point& obj2)
{
	obj1.delContPoint(obj2);
	obj2.delContPoint(obj1);
}

void Figure::contIsolPoint(Point& obj1, Point& obj2)
{
	obj1.contPoint(obj2);
	obj2.contPoint(obj1);
}
//properties
Point Figure::getActPoint()
{
	return actPoint;
}
void Figure::setActPoint(Point& obj)
{
	actPoint = obj;
}
