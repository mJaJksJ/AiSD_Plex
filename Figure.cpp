#include "Figure.h"
#include <iostream>
//constructor
Figure::Figure()
{
	actPoint = Point();
}

Figure::Figure(int _x, int _y, int _name)
{
	actPoint = Point(_x, _y, _name);
}

//destructor
Figure::~Figure()
{

}
//methods
void Figure::addPoint(Point obj)
{
	count++;
	obj.name = count;
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

void Figure::createFigure(Point _point)
{
	actPoint = _point;
	count = 1;
	actPoint.name = count;
}

void Figure::status()
{
	std::cout << "--status--" << std::endl;
	std::cout << "Active point: #" << actPoint.getName() << std::endl;
	std::cout << "Amount of points: " << count << std::endl;
	std::cout << "----------" << std::endl;
}

//properties
Point& Figure::getActivePoint()
{
	return actPoint;
}
void Figure::setActPoint(Point& obj)
{
	actPoint = obj;
}

int Figure::getCount()
{
	return count;
}