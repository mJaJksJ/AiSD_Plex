#include <iostream>
#include "Figure.h"
#include "Point.h"

using std::cout;
using std::cin;
using std::endl;

enum condition { createPoint, deletePoint, deleteLine, setActivePoint };

void menu()
{
	cout << "	|--------------------MENU--------------------|" << endl;
	cout << "	|                                            |" << endl;
	cout << "	| Write number which action you want do      |" << endl;
	cout << "	|____________________________________________|" << endl;
	cout << "	| 0 - create point                           |" << endl;
	cout << "	| 1 - delete point                           |" << endl;
	cout << "	| 2 - delete line                            |" << endl;
	cout << "	| 3 - set active point                       |" << endl;
	cout << "	|____________________________________________|" << endl;
}

//не визуализация а вывод в консоль
void tempDrawer(Point* _point)
{
	cout << endl;
	cout << "Point #" << _point->getName() << endl;
	cout << "Parent: point #" << (_point->getParentPoint())->getName;
}

//перерисовывание графа при каждом изменении
void redrawing(Figure _tree)
{
	/*
	тут код для обхода графа
	*/

	tempDrawer(_tree.getRoot());
}

void main()
{
	Figure tree;
	tree.createFigure(Point(50, 50));
	int thisStatus;
	while (true)
	{
		menu();
		cin >> thisStatus;
		switch (thisStatus)
		{
		case createPoint:
			//---------------------doing
			redrawing(tree);
			break;

		case deletePoint:
			//---------------------doing
			redrawing(tree);
			break;

		case deleteLine:
			//---------------------doing
			redrawing(tree);
			break;

		case setActivePoint:
			//---------------------doing
			redrawing(tree);
			break;

		default:
			break;
		}
		cout << endl << "current active point #" << tree.getActivePoint();
	}
}