#include <iostream>
#include "Point.h"

Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

Point::Point()
{
	x = 0;
	y = 0;
	parentPoint = NULL;
	childPoint = NULL;
}

Point& Point::operator=(Point left)
{
	Point right;
	right.x = left.x;
	right.y = left.y;
	right.parentPoint = left.parentPoint;
	right.childPoint = left.childPoint;
	right.name = left.name;
	/*why error?*/
	return *right;
}

Point* Point::getParentPoint()
{
	return parentPoint;
}

void Point::setParentPoint(Point* _parentPoint)
{
	parentPoint = _parentPoint;
}

void Point::setName(int _name)
{
	name = _name;
}