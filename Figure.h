#pragma once
#include "Point.h"
class Figure
{
private:

	//the point we are working with
	Point* activePoint;
	//the root point
	Point* root;
	//amount of points
	int count;

public:
	//constructor
	Figure();
	Figure(int _x, int _y, int _name);
	//destructor
	//~Figure();


	//--methods--

	void addPoint(Point* obj1);
	void deleteLine(Point* obj1);
	void createFigure(Point _point);
	void status();
	void contIsolPoint(Point* obj1);
	Point* byPass(int _name, Point* _obj);

	//--properties--

	Point* getActivePoint();
	Point* getRoot();
	void setActivePoint(Point* obj);
	int getCount();

};