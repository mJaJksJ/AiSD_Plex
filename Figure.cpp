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
//Figure::~Figure()
//{
//}


//--methods--

//add point (and connect it with active point)
void Figure::addPoint(Point* obj)
{
	maxNumber++;
	count++;
	obj->name = maxNumber;
	activePoint->contPoint(obj);
	//obj->contPoint(activePoint);
	activePoint->getArrPoints()[activePoint->getNumbSon() - 1].contPoint(activePoint);

}
//delete line between points
void Figure::deleteLine(Point* obj, bool from_file)
{
	bool flag = activePoint->delContPoint(obj);
	if (flag)
	{
		obj->delContPoint(activePoint);
		//if delete line between isolated point and another
		if ((obj->getNumbSon() == 0) && (obj->getName() != root->getName()))
			count--;
		if ((activePoint->getNumbSon() == 0) && (activePoint->getName() != root->getName()))
		{
			activePoint = root;
			count--;
		}
	}
	else
		if (!from_file)
			cout << "there was no line between these points" << endl << endl;
}
//connect added point with active point
void Figure::contIsolPoint(Point* obj1)
{
	bool flag = activePoint->contPoint(obj1);
	if (flag)
		activePoint->getArrPoints()[activePoint->getNumbSon() - 1].contPoint(activePoint);
	else
		cout << "there was already a line between these  points" << endl << endl;
}
//create figure (first point)
void Figure::createFigure(Point _point)
{
	root = &_point;
	activePoint = root;
	count = 1;
	maxNumber = 1;
	activePoint->name = maxNumber;
}
//show status
void Figure::status()
{
	std::cout << "--status--" << std::endl;
	std::cout << "Active point: #" << activePoint->getName() << std::endl;
	std::cout << "Amount of points: " << count << std::endl;
	std::cout << "Amount of sons of active point: " << activePoint->getNumbSon() << std::endl;
	if (activePoint->getNumbSon() > 0)
	{
		std::cout << "Sons of active point: ";
		for (int i = 0; i < activePoint->getNumbSon(); i++)
			std::cout << activePoint->getArrPoints()[i].getName() << " ";
	}
	std::cout << std::endl;
	std::cout << "----------" << std::endl;
}

//bypass for search the point
/*Point* Figure::byPass(int _name, Point* _obj) //  in the first obj is active point
{
	bool found = false;
	for (int i = 0; i < _obj->getNumbSon(); i++)
	{
		if (_obj->getArrPoints()[i].isLocked() == true)
			continue;
		else if (_obj->getArrPoints()[i].getName() != _name)
			continue;
		else
		{
			std::cout << _obj->getArrPoints()[i].getName();
			found = true;
			return  &_obj->getArrPoints()[i];
		}
	}
	_obj->lock();
	if (found != true)
	{
		for (int i = 0; i < _obj->getNumbSon(); i++)
		{
			if (_obj->getArrPoints()[i].isLocked() == true)
				continue;
			else
				byPass(_name, &_obj->getArrPoints()[i]);
		}
	}
}*/

//--properties--

Point* Figure::getActivePoint()
{
	return activePoint;
}
void Figure::setActivePoint(Point* obj)
{
	activePoint = obj;
}
int Figure::getCount()
{
	return count;
}
Point* Figure::getRoot()
{
	return root;
}
int Figure::getMaxNumber()
{
	return maxNumber;
}
void Figure::setMaxNumber(int _maxNumber)
{
	maxNumber = _maxNumber;
}