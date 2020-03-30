#include "Figure.h"
#include <iostream>

//--constructor--

Figure::Figure()
{
	activePoint = Point();
}

Figure::Figure(int _x, int _y, int _name)
{
	activePoint = Point(_x, _y, _name);
}

//destructor
Figure::~Figure()
{

}


//--methods--

//добавление точки (проведение линии от актитвной точки к новой)
void Figure::addPoint(Point obj)
{
	count++;
	obj.name = count;
	activePoint.contPoint(obj);
	obj.contPoint(activePoint);
}
//удаление линии
void Figure::deleteLine(Point& obj1, Point& obj2)
{
	obj1.delContPoint(obj2);
	obj2.delContPoint(obj1);
}
//соединение двух точек
void Figure::contIsolPoint(Point& obj1, Point& obj2)
{
	obj1.contPoint(obj2);
	obj2.contPoint(obj1);
}
//создание фигуры
void Figure::createFigure(Point _point)
{
	activePoint = _point;
	count = 1;
	activePoint.name = count;
}
//текущий статус
void Figure::status()
{
	std::cout << "--status--" << std::endl;
	std::cout << "Active point: #" << activePoint.getName() << std::endl;
	std::cout << "Amount of points: " << count << std::endl;
	std::cout << "----------" << std::endl;
}


//--properties--

Point& Figure::getActivePoint()
{
	return activePoint;
}
void Figure::setActPoint(Point& obj)
{
	activePoint = obj;
}
int Figure::getCount()
{
	return count;
}