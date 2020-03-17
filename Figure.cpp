#include <iostream>
#include "Figure.h"

void Figure::createFigure(Point _point)
{
	this->rootPoint = &_point;
}

void Figure::addPoint(Point _point)
{
	Point newPoint;
	newPoint = _point;
	newPoint.s_parentPoint(this->activePoint);

	this->activePoint->addChild(newPoint);
}

void Figure::s_activePoint(Point* _activePoint)
{
	activePoint = _activePoint;
}