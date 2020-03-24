#pragma once
#include <iostream>
#include "Figure.h"

using std::cout;
using std::endl;

Figure::Figure()
{
	cout << "create figure";
}

Figure::~Figure()
{
	cout << "ququmber";
}

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

Point* Figure::getActivePoint()
{
	return this->activePoint;
}

Point* Figure::getRoot()
{
	return rootPoint;
}