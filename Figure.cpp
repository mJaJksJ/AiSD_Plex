#include "Figure.h"
//methods
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

//properties
Point Figure::getActPoint()
{
	return actPoint;
}
void Figure::setActPoint(Point& obj)
{
	actPoint = obj;
}
