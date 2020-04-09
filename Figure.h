#pragma once
#include "Point.h"
class Figure
{
	friend class Point;
private:

	//the point we are working with
	Point* activePoint;
	//the root point
	Point* root;
	//amount of points
	int count;
	//max number of point (name)
	int maxNumber;

public:
	//constructor
	Figure();
	Figure(int _x, int _y, int _name);
	//destructor
	//~Figure();


	//--methods--

	void addPoint(Point* obj1);
	void deleteLine(Point* obj1, bool out_file);
	void createFigure(Point _point);
	void status();
	void contIsolPoint(Point* obj1);
	//Point* byPass(int _name, Point* _obj);

	//--properties--

	Point* getActivePoint();
	Point* getRoot();
	void setActivePoint(Point* obj);
	int getCount();
	int getMaxNumber();
};