#include <iostream>
#include "Figure.h"

void Figure::createFigure(Point _point)
{
	this->rootPoint = &_point;
	this->vNum = 1;
	this->rootPoint->setName(this->vNum);
}

void Figure::addPoint(Point _point)
{
	Point newPoint;
	newPoint = _point;
	newPoint.setParentPoint(this->activePoint);
	this->vNum++;
	newPoint.setName(vNum);

	this->activePoint->addChild(newPoint);
}

void Figure::setActivePoint(Point* _activePoint)
{
	activePoint = _activePoint;
}