#pragma once
#include "Point.h"
#include <iostream>
#include <stack>

//--constructors--

Point::Point()
{
	relationCount = 0;
	arrPoints = NULL;
}
Point::Point(int _x, int _y, int _name)
{
	relationCount = 0;
	arrPoints = NULL;
	x = _x;
	y = _y;
	name = _name;
}
Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
	relationCount = 0;
	arrPoints = NULL;
	name = -1;
}

//destructor
Point::~Point()
{
}

//--operators--

Point& Point::operator= (const Point& _point)
{
	x = _point.x;
	y = _point.y;
	name = _point.name;
	relationCount = _point.relationCount;

	for (int i = 0; i < relationCount; i++)
	{
		arrPoints[i]->~Point();
	}

	arrPoints = new Point*[relationCount];
	for (int i = 0; i < _point.relationCount; i++)
	{
		arrPoints[i] = _point.arrPoints[i];
	}

	return *this;
}

//--methods--

//connect THIS point with another
//if returned value is false there was already a connection between points
bool Point::connectPoint(Point* _point)
{
	if (relationCount == 0)
	{
		arrPoints = new Point*[1];
		arrPoints[0] = _point;
		relationCount++;
	}
	else
	{
		for (int i = 0; i < relationCount; i++)
		{
			if (arrPoints[i]->getName() == _point->getName())
			{
				return false; //there was already a connection between points
			}
		}
		
		Point** tempArr = new Point*[relationCount + 1];
		//creating temp array for adding point
		for (int i = 0; i < relationCount; i++)
		{
			tempArr[i] = arrPoints[i];
		}
		tempArr[relationCount] = _point;

		for (int i = 0; i < relationCount; i++)
		{
			arrPoints[i]->~Point();
		}

		relationCount++;

		arrPoints = new Point*[relationCount];

		for (int i = 0; i < relationCount; i++)
		{
			arrPoints[i] = tempArr[i];
		}

		for (int i = 0; i < relationCount; i++)
		{
			tempArr[i]->~Point();
		}
		delete[] tempArr;
	}
	return true; //successful connection
}

//delete connection with point
//if returned value is false there was no line between the points
bool Point::disconnectPoint(Point* _point)
{
	int i = 0;
	int j = 0;
	int k = 0;
	if (relationCount != 0)
	{
		while (arrPoints[i]->name != _point->name && i != relationCount)
		{
			i++;
		}
		if (i == relationCount)
		{
			return false; //there was no line between the points
		}

		Point** tempArr = new Point*[relationCount - 1];
		while (j < relationCount -1)
		{
			if (k != i)
			{
				tempArr[j] = arrPoints[k];
				j++;
				k++;
			}
			else
			{
				k++;
			}
		}
		for (i = 0; i < relationCount; i++)
		{
			arrPoints[i]->~Point();
		}
		relationCount--;

		arrPoints = new Point*[relationCount];
		for (i = 0; i < relationCount; i++)
		{
			arrPoints[i] = tempArr[i];
		}
		for (i = 0; i < relationCount; i++)
		{
			tempArr[i]->~Point();
		}
		delete[]tempArr;

		return true; //successful deletion
	}
	else
	{
		return false; //there was no line between the points
	}
}

//deep search for point with certain name
Point* Point::deepSearch(int _name, Figure* _figure)
{
	int* nodes = new int[_figure->getMaxNumber()];
	for (int i = 0; i < _figure->getMaxNumber(); i++)
	{
		nodes[i] = 0;
	}
	std::stack<Point*> tempStack;
	tempStack.push(_figure->getActivePoint());
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
		for (int j = 0; j < node->getRelationCount(); j++)
		{
			if (nodes[node->getArrPoints()[j]->getName()] != 2)
			{
				tempStack.push(node->getArrPoints()[j]);
				nodes[node->getArrPoints()[j]->getName()] = 1;
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

int Point::getRelationCount()
{
	return relationCount;
}

Point** Point::getArrPoints()
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