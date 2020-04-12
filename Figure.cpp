#pragma once
#include "Figure.h"
#include <iostream>
using std::cout;
using std::endl;

//--constructor--

Figure::Figure()
{
	activePoint = &Point();
	count = 0;
	maxNumber = 0;
}

Figure::Figure(int _x, int _y, int _name)
{
	activePoint = &Point(_x, _y, _name);
	count = 0;
	maxNumber = 0;
}

//destructor
Figure::~Figure()
{
}


//--methods--

//add point (and connect it with active point)
void Figure::addPoint(Point* _point)
{
	maxNumber++;
	count++;
	_point->name = maxNumber;
	activePoint->connectPoint(_point);
	activePoint->getArrPoints()[activePoint->getRelationCount() - 1]->connectPoint(activePoint);
}

//delete line between points
void Figure::deleteLine(Point* _point, bool fromFile)
{
	if (activePoint->getName() == _point->getName())
	{
		cout << "this is the same point" << endl << endl;
	}
	else
	{
		bool flag = activePoint->disconnectPoint(_point);
		if (flag)
		{
			_point->disconnectPoint(activePoint);
			//if delete line between isolated point and another
			if (_point->getRelationCount() == 0)
				count--;
		}
		else
		{
			if (!fromFile)
			{
				cout << "there was no line between these points" << endl << endl;
			}
		}
	}
}

//connect this point with active point
void Figure::connectIsolatedPoint(Point* _point)
{
	if (activePoint->getName() == _point->getName())
	{
		cout << "this is the same point" << endl << endl;
	}
	else
	{
		bool flag = activePoint->connectPoint(_point);
		if (flag)
		{
			activePoint->getArrPoints()[activePoint->getRelationCount() - 1]->connectPoint(activePoint);
		}
		else
		{
			cout << "there was already a line between these  points" << endl << endl;
		}
	}
}

//create figure (first point)
void Figure::createFigure(Point _point)
{
	activePoint = &_point;
	count = 1;
	maxNumber = 1;
	activePoint->name = maxNumber;
}

//show status
void Figure::status()
{
	cout << "--status--" << endl;
	cout << "Active point: #" << activePoint->getName() << endl;
	cout << "Amount of points: " << count << endl;
	cout << "Amount of sons of active point: " << activePoint->getRelationCount() << endl;
	if (activePoint->getRelationCount() > 0)
	{
		cout << "Sons of active point: ";
		for (int i = 0; i < activePoint->getRelationCount(); i++)
		{
			cout << activePoint->getArrPoints()[i]->getName() << " ";
		}
	}
	cout << endl;
	cout << "----------" << endl;
}

//--properties--

Point* Figure::getActivePoint()
{
	return activePoint;
}

void Figure::setActivePoint(Point* _point)
{
	activePoint = _point;
}

int Figure::getCount()
{
	return count;
}

int Figure::getMaxNumber()
{
	return maxNumber;
}

void Figure::setMaxNumber(int _maxNumber)
{
	maxNumber = _maxNumber;
}