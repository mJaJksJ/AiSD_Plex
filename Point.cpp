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
	/*why error?*/
	return *right;
}

Point* Point::g_parentPoint()
{
	return parentPoint;
}

void Point::s_parentPoint(Point* _parentPoint)
{
	parentPoint = _parentPoint;
}