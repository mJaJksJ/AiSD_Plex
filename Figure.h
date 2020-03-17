#include "Point.h"
class Figure
{
	//Родитель всех родителей точка
	Point* rootPoint;
	//Точка активная в данный момент (будет родительской при создании новых)
	Point* activePoint;

public:

	Figure();
	~Figure();

	//создание корневой точки
	void createFigure(Point _point);
	//добавление точки и создание отрезка activePoint - _point
	void addPoint(Point _point);
	//установка новой activePoint
	void s_activePoint(Point* _activePoint);
	//удаление точки
	void deletePoint(Point* _point);
	//удаление отрезка
	void deleteLine(Point* point1, Point* point2);
};

