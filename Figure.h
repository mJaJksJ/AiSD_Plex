#pragma once
#include "Point.h"
class Figure
{
	//Родитель всех родителей точка
	Point* rootPoint;
	//Точка активная в данный момент (будет родительской при создании новых)
	Point* activePoint;
	//количество точек /*нужно для наименования новой точки*/
	int vNum;

public:

	Figure();
	~Figure();

	//создание корневой точки
	void createFigure(Point _point);
	//добавление точки и создание отрезка activePoint - _point
	void addPoint(Point _point);
	//установка новой activePoint
	void setActivePoint(Point* _activePoint);
	//возвращение новой activePoint
	Point* getActivePoint();
	//удаление точки
	void deletePoint(Point* _point);
	//удаление отрезка
	void deleteLine(Point* point1, Point* point2);
	//вернуть корневую точку
	Point* getRoot();
};

