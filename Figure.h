#pragma once
#include "Point.h"
class Figure
{
	friend class Point;
private:

	//the point we are working with
	Point* activePoint;
	//amount of points
	int count;
	//max number of point (name)
	int maxNumber;

public:
	//constructor
	Figure();
	Figure(int _x, int _y, int _name);
	//destructor
	~Figure();


	//--methods--

	void addPoint(Point* _point);
	void deleteLine(Point* _point, bool out_file);
	void createFigure(Point _point);
	void status();
	void connectIsolatedPoint(Point* _point);

	//--properties--

	Point* getActivePoint();
	void setActivePoint(Point* _point);
	int getCount();
	int getMaxNumber();
	void setMaxNumber(int _maxNumber);
};