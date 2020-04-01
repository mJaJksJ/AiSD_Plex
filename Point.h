#pragma once
class Point
{
	friend class Figure;

private:
	//coordinates
	int x, y;
	//true, when we already passed this way
	bool locked;
	//array of point, that connected with THIS point
	Point* arrPoints;
	//name of point
	int name;
	//count of sons
	int numbSon;

public:
	//--constructors--

	Point();
	Point(int _x, int _y, int _name);
	Point(int _x, int _y);

	//destructor
	//~Point();

	//--operators--

	Point& operator= (const Point& obj);

	//--methods--

	void contPoint(Point* _contPoint);
	void delContPoint(Point* _contPoint);
	void lock();
	void unlock();
	Point* search(int _name, Point* _obj);

	//--properties--

	int getName();
	int getNumbSon();
	Point* getArrPoints();
	bool isLocked();
	int getX();
	int getY();
};