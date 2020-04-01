#include "Figure.h"
#include <iostream>

//--constructor--

Figure::Figure()
{
	activePoint = &Point();
}

Figure::Figure(int _x, int _y, int _name)
{
	activePoint = &Point(_x, _y, _name);
}

//destructor
//Figure::~Figure()
//{

//}


//--methods--

//äîáàâëåíèå òî÷êè (ïðîâåäåíèå ëèíèè îò àêòèòâíîé òî÷êè ê íîâîé)
void Figure::addPoint(Point* obj)
{
	count++;
	obj->name = count;
	activePoint->contPoint(obj);
	//obj->contPoint(activePoint);
	activePoint->getArrPoints()[activePoint->getNumbSon() - 1].contPoint(activePoint);

}
//óäàëåíèå ëèíèè
void Figure::deleteLine(Point* obj1, Point* obj2)
{
	obj1->delContPoint(obj2);
	obj2->delContPoint(obj1);
}
//ñîåäèíåíèå äâóõ òî÷åê
void Figure::contIsolPoint(Point* obj1)
{
	activePoint->contPoint(obj1);
	activePoint->getArrPoints()[activePoint->getNumbSon() - 1].contPoint(activePoint);
}
//ñîçäàíèå ôèãóðû
void Figure::createFigure(Point _point)
{
	root = &_point;
	activePoint = root;
	count = 1;
	activePoint->name = count;
}
//òåêóùèé ñòàòóñ
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
Point* Figure::byPass(int _name, Point* _obj) //  in the first obj is active point
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
}

//--properties--

Point* Figure::getActivePoint()
{
	return activePoint;
}
void Figure::setActivePoint(Point* obj)
{
	std::cout << "++" << obj->getNumbSon();
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