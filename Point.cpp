#pragma once
#include "Point.h"
#include <iostream>
#include <stack>

//--constructors--

Point::Point()
{
	//locked = false;
	numbSon = 0;
	arrPoints = NULL;
}
Point::Point(int _x, int _y, int _name)
{
	//locked = false;
	numbSon = 0;
	arrPoints = NULL;
	x = _x;
	y = _y;
	name = _name;
}
Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
	numbSon = 0;
	//locked = false;
	arrPoints = NULL;
	name = -1;
}

//destructor
//Point::~Point()
//{

//}

//--operators--

Point& Point::operator= (const Point& obj)
{
	x = obj.x;
	y = obj.y;
	name = obj.name;

	numbSon = obj.numbSon;
	/*delete[] arrPoints;*/
	arrPoints = new Point[numbSon];
	for (int i = 0; i < obj.numbSon; i++)
		arrPoints[i] = obj.arrPoints[i];

	return *this;
}

//--methods--

//connect THIS point with another
//if returned value is false there was already a connection between points
Point* Point::contPoint(Point* _cont_point)
{
	Point* tempPoint = new Point[1];
	tempPoint = _cont_point;
	if (numbSon == 0)
	{
		arrPoints = new Point[1];
		arrPoints[0] = *tempPoint;
		numbSon++;

		/*tempPoint.arrPoints = new Point[1];
		tempPoint.arrPoints[0] = *this;
		tempPoint.numbSon++;*/

	}
	else
	{
		for (int i = 0; i < numbSon; i++)
		{ 
			if (arrPoints[i].name == tempPoint->name)
				return NULL; //there was already a connection between points
			}
		Point* tempArr = new Point[numbSon + 1];
		//creating temp array for adding point
		for (int i = 0; i < numbSon; i++)
			tempArr[i] = arrPoints[i];
		tempArr[numbSon] = *tempPoint;
		numbSon++;
		arrPoints = new Point[numbSon];
		for (int i = 0; i < numbSon; i++)
			arrPoints[i] = tempArr[i];



		/*tempArr = new Point[tempPoint.numbSon + 1];
		for (int i = 0; i < tempPoint.numbSon; i++)
			tempArr[i] = tempPoint.arrPoints[i];
		tempPoint.arrPoints[tempPoint.numbSon] = *this;
		tempPoint.numbSon++;
		tempPoint.arrPoints = new Point[tempPoint.numbSon];
		for (int i = 0; i < tempPoint.numbSon; i++)
			tempPoint.arrPoints[i] = arrPoints[i];*/

		
			/*delete[] tempArr;*/
	}
	return tempPoint; //successful connection
}
//delete connection with point
//if returned value is false there was no line between the points
Point* Point::delContPoint( Point* _contPoint)
{
	Point* tempPoint = new Point[1];
	tempPoint = _contPoint;
	int i = 0;
	int j = 0;
	int k = 0;
	if (tempPoint->numbSon != 0)
	{
		while (tempPoint->arrPoints[i].name != name && i != tempPoint->numbSon)
			i++;

		if (i == tempPoint->numbSon)
			return NULL; //there was no line between the points

		Point* tempArr = new Point[tempPoint->numbSon - 1];

		while (j < tempPoint->numbSon - 1)
		{
			if (k != i)
			{
				tempArr[j] = tempPoint->arrPoints[k];
				j++;
				k++;
			}
			else
				k++;
		}



		tempPoint->numbSon--;

		tempPoint->arrPoints = new Point[tempPoint->numbSon];
		for (i = 0; i < tempPoint->numbSon; i++)
			tempPoint->arrPoints[i] = tempArr[i];
		
		delete[]tempArr;

		return tempPoint; //successful deletion
	}
	else
		return NULL; //there was no line between the points
}

//Point* Point::search(int _name, Point* _point)
//{
//	if (_point->getNumbSon() != 0)
//	{
//		if (_point->getName() == _name)
//		{
//			return _point;
//		}
//		for (int i = 0; i < _point->getNumbSon(); i++)
//		{
//			if (_point->getArrPoints()[i].getName() > _point->getName())
//			{
//				Point* tempPoint;
//				tempPoint = _point->search(_name, &_point->getArrPoints()[i]);
//				if (tempPoint != NULL)
//				{
//					if (tempPoint->getName() == _name)
//					{
//						return tempPoint;
//					}
//				}
//			}
//			else
//			{
//				if (_point->getArrPoints()[i].getName() == _name)
//				{
//					return &_point->getArrPoints()[i];
//				}
//			}
//		}
//	}
//	else
//	{
//		if (_point->getName() == _name)
//		{
//			return _point;
//		}
//		else
//		{
//			return NULL;
//		}
//	}
//}

Point* Point::deepSearch(int _name, Figure& _figure)
{
	Figure fig;
	//fig = _figure;
	/*bool flag = false;*/
	int* nodes = new int[_figure.getMaxNumber()];
	for (int i = 0; i < _figure.getMaxNumber(); i++)
	{
		nodes[i] = 0;
	}
	std::stack<Point*> tempStack;
	/*Point* temp = new Point[1];*/
	
	tempStack.push(_figure.root);
	while (!tempStack.empty())
	{
		Point* node = tempStack.top();
		if (node->getName() == _name)
		{
			return node;
		}
		tempStack.pop();
		if (nodes[node->getName()] == 2)
		{
			continue;
		}
		nodes[node->getName()] = 2;
		for (int j = 0; j < node->getNumbSon(); j++)
		{
			if (nodes[node->getArrPoints()[j].getName()] != 2)
			{
				tempStack.push(&node->getArrPoints()[j]);
				nodes[node->getArrPoints()[j].getName()] = 1;
			}
		}
	}
	
		return NULL;
}
//--properties--

void Point::setName(int _name)
{
	name = _name;
}

int Point::getName()
{
	return name;
}

int Point::getNumbSon()
{
	return numbSon;
}

Point* Point::getArrPoints()
{
	return arrPoints;
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}
