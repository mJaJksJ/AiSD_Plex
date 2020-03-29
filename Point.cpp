#include "Point.h"
#include <iostream>
//constructors
Point::Point()
{
	locked = false;
	numb_son = 0;
	arr_points = NULL;
}
Point::Point(int _x, int _y, int _name)
{
	locked = false;
	numb_son = 0;
	arr_points = NULL;
	x = _x;
	y = _y;
	name = _name;
}
Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
	numb_son = 0;
	locked = false;
	arr_points = NULL;
	name = -1;
}
//destructor
Point::~Point()
{

}

//operators
Point& Point::operator= (const Point& obj)
{
	x = obj.x;
	y = obj.y;
	name = obj.name;

	for (int i = 0; i < obj.numb_son; i++)
		arr_points = obj.arr_points;


	return *this;
}

//methods
void Point::contPoint(Point& _cont_point)
{
	if (numb_son == 0)
	{
		arr_points = new Point[1];
		arr_points[0] = _cont_point;
		numb_son++;
	}
	else
	{
		Point* tempArr = new Point[numb_son + 1];
		//creating temp array for adding point
		for (int i = 0; i < numb_son; i++)
			tempArr[i] = arr_points[i];

		tempArr[numb_son] = _cont_point;

		for (int i = 0; i < numb_son; i++)
			arr_points[i].~Point();

		numb_son++;

		arr_points = new Point[numb_son];

		for (int i = 0; i < numb_son; i++)
			arr_points[i] = tempArr[i];

		for (int i = 0; i < numb_son; i++)
			tempArr[i].~Point();

		delete[] tempArr;
	}

}

void Point::delContPoint(Point& _contPoint)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (arr_points[i].name != _contPoint.name && i != numb_son)
		i++;
	Point* tempArr = new Point[numb_son - 1];

	while (j < numb_son)
	{
		if (k != i)
		{
			tempArr[j] = arr_points[k];
			j++;
			k++;
		}
		else
			k++;
	}


	for (i = 0; i < numb_son; i++)
		arr_points[i].~Point();

	numb_son--;

	arr_points = new Point[numb_son];
	for (i = 0; i < numb_son; i++)
		arr_points[i] = tempArr[i];

	for (i = 0; i < numb_son; i++)
		tempArr[i].~Point();
	delete[]tempArr;
}

void Point::lock()
{
	locked = true;
}

void Point::unlock()
{
	locked = false;
}

//properties
int Point::getName()
{
	return name;
}

int Point::getNumbSon()
{
	return numb_son;
}

Point* Point::getArr_points()
{
	return arr_points;
}

bool Point::isLocked()
{
	return locked;
}