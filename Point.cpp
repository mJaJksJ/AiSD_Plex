#include "Point.h"
#include <iostream>

//--constructors--

Point::Point()
{
	locked = false;
	numbSon = 0;
	arrPoints = NULL;
}
Point::Point(int _x, int _y, int _name)
{
	locked = false;
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
	locked = false;
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

	for (int i = 0; i < obj.numbSon; i++)
		arrPoints = obj.arrPoints;


	return *this;
}

//--methods--

//connect THIS point with another
void Point::contPoint(Point* _cont_point)
{
	if (numbSon == 0)
	{
		arrPoints = new Point[1];
		arrPoints[0] = *_cont_point;
		numbSon++;
	}
	else
	{
		Point* tempArr = new Point[numbSon + 1];
		//creating temp array for adding point
		for (int i = 0; i < numbSon; i++)
			tempArr[i] = arrPoints[i];

		tempArr[numbSon] = *_cont_point;

		/*for (int i = 0; i < numbSon; i++)
			arrPoints[i].~Point();*/

		numbSon++;

		arrPoints = new Point[numbSon];

		for (int i = 0; i < numbSon; i++)
			arrPoints[i] = tempArr[i];

		/*for (int i = 0; i < numbSon; i++)
			tempArr[i].~Point();*/

		delete[] tempArr;
	}

}
//delete connection with point
void Point::delContPoint(Point* _contPoint)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (arrPoints[i].name != _contPoint->name && i != numbSon)
		i++;
	Point* tempArr = new Point[numbSon - 1];

	while (j < numbSon)
	{
		if (k != i)
		{
			tempArr[j] = arrPoints[k];
			j++;
			k++;
		}
		else
			k++;
	}


	for (i = 0; i < numbSon; i++)
		arrPoints[i].~Point();

	numbSon--;

	arrPoints = new Point[numbSon];
	for (i = 0; i < numbSon; i++)
		arrPoints[i] = tempArr[i];

	for (i = 0; i < numbSon; i++)
		tempArr[i].~Point();
	delete[]tempArr;
}
//lock value will true
void Point::lock()
{
	locked = true;
}
//lock value will false
void Point::unlock()
{
	locked = false;
}

Point* Point::search(int _name, Point* _point)
{
	if (_point->getNumbSon() != 0)
	{
		if (_point->getName() == _name)
		{
			return _point;
		}
		for (int i = 0; i < _point->getNumbSon(); i++)
		{
			if (_point->getArrPoints()[i].getName() > _point->getName())
			{
				Point* tempPoint;
				tempPoint = _point->search(_name, &_point->getArrPoints()[i]);
				if (tempPoint != NULL)
				{
					if (tempPoint->getName() == _name)
					{
						return tempPoint;
					}
				}
			}
			else
			{
				if (_point->getArrPoints()[i].getName() == _name)
				{
					return &_point->getArrPoints()[i];
				}
			}
		}
	}
	else
	{
		if (_point->getName() == _name)
		{
			return _point;
		}
		else
		{
			return NULL;
		}
	}
}
//--properties--

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

bool Point::isLocked()
{
	return locked;
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}
