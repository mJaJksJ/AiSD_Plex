#pragma once
#include "Figure.h"
#include <iostream>
using std::cout;
using std::endl;

//--constructor--

Figure::Figure()
{
	activePoint = new Point[1];
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
	Point* tempPoint =  new Point[1];
	tempPoint = obj;
	maxNumber++;
	count++;
	tempPoint->name = maxNumber;
	activePoint = tempPoint->contPoint(activePoint);
	tempPoint = activePoint->contPoint(tempPoint);
	/*obj = tempPoint;*/
	//activePoint->getArrPoints()[activePoint->getNumbSon() - 1].contPoint(activePoint);
}
//delete line between points
void Figure::deleteLine(Point* obj, bool from_file)
{
	Point* tempPoint = new Point[1];
	tempPoint = obj;


	tempPoint = activePoint->delContPoint(tempPoint);
	if (tempPoint != NULL)
	{
		/*activePoint = tempPoint2;*/
		activePoint = tempPoint->delContPoint(activePoint);
		//if delete line between isolated point and another
		if ((tempPoint->getNumbSon() == 0) && (tempPoint->getName() != root->getName()))
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
void Figure::contIsolPoint(Point* obj)
{
	Point* tempPoint = new Point[1];
	tempPoint = obj;
	activePoint = tempPoint->contPoint(activePoint);
		if (tempPoint != NULL)
		{
			//activePoint->getArrPoints()[activePoint->getNumbSon() - 1].contPoint(activePoint);
			tempPoint = activePoint->contPoint(tempPoint);
		}
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
Point* Figure::byPass(int _name, Point* _obj) //  in the first obj is active point
{
	Point* temp = new Point[1];
	temp = _obj;
	int* arr = new int[maxNumber];
	int count = 0;
	bool flag = false;
	bool found = false;
	if (temp->getName() == _name)
		return temp;
	for (int i = 0; i < temp->getNumbSon(); i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (temp->getArrPoints()[i].getName() == arr[j])
			{
				flag = true;
				break;
			}
			else
				continue;
		}
		if (flag == true)
		{
			flag = false;
			continue;
		}
		else if (temp->getArrPoints()[i].getName() != _name)
			continue;
		else
		{
			found = true;
			return  &temp->getArrPoints()[i];
		}
		arr[count] = temp->getName();
		count++;
	}
	if (found != true)
	{
		found = false;
		for (int i = 0; i < temp->getNumbSon(); i++)
		{
			for (int j = 0; j < count; j++)
			{
				if (temp->getArrPoints()[i].getName() == arr[j])
				{
					flag = true;
					break;
				}
				else
					continue;
			}
			if (flag == true)
			{
				flag = false;
				continue;
			}
			else
				byPass(_name, &(temp->getArrPoints()[i]));
		}
	}
}

//--properties-

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

 void Figure:: setRoot(Point* obj)
 {
	 root = obj;
 }
 int Figure::getMaxNumber()
{
	return maxNumber;
}
void Figure::setMaxNumber(int _maxNumber)
{
	maxNumber = _maxNumber;
}