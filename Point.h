#pragma once
class Point
{
	friend class Figure;
	//coordinates
private:
	int x, y;
	//true, when we already passed this way
	bool locked;
	//array of point, that connected with THIS point
	Point* arr_points;
	//name of point
	int name;
	//count of sons
	int numb_son;
	//constructor
public:
	Point();
	Point(int _x, int _y, int _name);
	Point(int _x, int _y);
	//destructor
	~Point();
	//operators
	Point& operator= (const Point& obj);
	//methods
	//connect THIS point with another
	void contPoint(Point& _contPoint);
	//delete connection with point
	void delContPoint(Point& _contPoint);
	void lock();
	void unlock();
	//properties
	int getName();
	int getNumbSon();
	Point* getArr_points();
	bool isLocked();
};