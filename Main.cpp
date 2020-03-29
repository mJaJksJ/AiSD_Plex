#include <iostream>
#include "Figure.h"
#include "Point.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using std::cout;
using std::cin;
using std::endl;

enum condition { addPoint, addLine, deleteLine, setActivePoint };

void menu()
{
	cout << "	|--------------------MENU--------------------|" << endl;
	cout << "	|                                            |" << endl;
	cout << "	| Click number which action you want do      |" << endl;
	cout << "	|____________________________________________|" << endl;
	cout << "	| 0 - create point                           |" << endl;
	cout << "	| 1 - delete point                           |" << endl;
	cout << "	| 2 - delete line                            |" << endl;
	cout << "	| 3 - set active point                       |" << endl;
	cout << "	|____________________________________________|" << endl;
}


//не визуализация а вывод в консоль
void tempDrawer(Point _point)
{
	cout << endl;
	cout << "Point #" << _point.getName() << endl;
	cout << "sons :: ";
	for (int i = 0; i < _point.getNumbSon(); i++)
	{
		cout << _point.getArr_points()[i].getName() << " ";
	}
	cout << endl;

	//cout << "Parent: point #" << (_point->getParentPoint())->getName;
}

//перерисовывание графа при каждом изменении
void redrawing(Point& _point)
{
	if (_point.getNumbSon() != 0)
	{
		for (int i = 0; i < _point.getNumbSon(); i++)
		{
			if (_point.getArr_points()[i].isLocked() == false)
			{
				redrawing(_point.getArr_points()[i]);
			}
			else
			{
				_point.getArr_points()[i].lock();
				tempDrawer(_point.getArr_points()[i]);
			}
		}
		_point.lock();
		tempDrawer(_point);
	}
	else
	{
		_point.lock();
		tempDrawer(_point);
	}

}

//шаблон для др функций, - сама по себе бесполезна
Point walk(Point _point)
{
	if (_point.getNumbSon() != 0)
	{
		for (int i = 0; i < _point.getNumbSon(); i++)
		{
			if (_point.getArr_points()[i].isLocked() == false)
			{
				walk(_point.getArr_points()[i]);
			}
			else
			{
				_point.getArr_points()[i].lock();
				return _point.getArr_points()[i];
			}
		}
		_point.lock();
		return _point;
	}
	else
	{
		_point.lock();
		return _point;
	}
}

//установка флагов на unlocked
void rewalk(Point& _point)
{
	if (_point.getNumbSon() != 0)
	{
		for (int i = 0; i < _point.getNumbSon(); i++)
		{
			if (_point.getArr_points()[i].isLocked() == true)
			{
				walk(_point.getArr_points()[i]);
			}
			else
			{
				_point.getArr_points()[i].unlock();
			}
		}
		_point.unlock();
	}
	else
	{
		_point.unlock();
	}
}

Point& changeActivePoint(int _name, Point& _activePoint)
{
	Point& requiredPoint = _activePoint;
	if (_activePoint.getNumbSon() != 0)
	{
		for (int i = 0; i < _activePoint.getNumbSon(); i++)
		{
			if (_activePoint.getArr_points()[i].getName() == _name)
			{
				requiredPoint = _activePoint.getArr_points()[i];
			}
			if (_activePoint.getArr_points()[i].isLocked() == false)
			{
				walk(_activePoint.getArr_points()[i]);
			}
			else
			{
				_activePoint.getArr_points()[i].lock();
			}
		}
		_activePoint.lock();
		if (_activePoint.getName() == _name)
		{
			requiredPoint = _activePoint;
		}
	}
	else
	{
		_activePoint.lock();
		if (_activePoint.getName() == _name)
		{
			requiredPoint = _activePoint;
		}
	}

	rewalk(_activePoint);
	return requiredPoint;
}

void main()
{
	//---sfml part---
	/*RenderWindow window(VideoMode(500, 500), "Flexis");
	window.clear(Color::White);
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
	//---sfml part---



	Figure tree;
	tree.createFigure(Point(50, 50));*/


	/*cout << tree.getActivePoint().getName();
	cout << "count sons :: " << tree.getActivePoint().getNumbSon() << endl;

	tree.addPoint(Point(100, 50));
	cout << "count sons :: " << tree.getActivePoint().getNumbSon() << endl;
	cout << "count sons :: " << tree.getActivePoint().getArr_points()[0].getNumbSon() << endl;
	tree.addPoint(Point(50, 100));

	for (int i = 0; i < tree.getActivePoint().getNumbSon(); i++)
	{
		cout << tree.getActivePoint().getArr_points()[i].getName();
	}

	tree.setActPoint(changeActivePoint(2, tree.getActivePoint()));
	cout << tree.getActivePoint().getName();
	tree.addPoint(Point(150, 50));
	tree.setActPoint(changeActivePoint(3, tree.getActivePoint()));
	tree.addPoint(Point(50, 150));
	//changeActivePoint(1, tree.getActivePoint());
	redrawing(tree.getActivePoint());*/


	RenderWindow window(VideoMode(800, 600), "Flexis");
	Texture textureMenu;
	textureMenu.loadFromFile("main_menu.jpg");
	Sprite spriteMenu;
	spriteMenu.setTexture(textureMenu);
	spriteMenu.setPosition(0, 0);

	int thisStatus = -1;
	while (window.isOpen())
	{
		Event event, tempEvent;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// закрытие окна
			case Event::Closed:
				window.close();
				break;

				// нажатие клавиши
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Num0)
				{
					thisStatus = addPoint;
				}
				else if (event.key.code == Keyboard::Num1)
				{
					thisStatus = addLine;
				}
				else if (event.key.code == Keyboard::Num1)
				{
					thisStatus = deleteLine;
				}
				else if (event.key.code == Keyboard::Num1)
				{
					thisStatus = setActivePoint;
				}
				break;

				// мы не обрабатываем другие типы событий
			default:
				break;
			}



			/*if (event.type == (Event::KeyPressed == 0))
			{
				window.clear(Color::Magenta);
				int x, y;
				while (window.waitEvent(event))
				{
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Right)
						{
							window.clear(Color::Cyan);
						}
					}
				}
			}*/
		}

		/*if (Keyboard::isKeyPressed(Keyboard::Numpad0))
		{
			window.clear(Color::Blue);
			int x, y;
			while (window.waitEvent(event))
			{
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == Mouse::Right)
					{
						window.clear(Color::Cyan);
					}
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Numpad1))
		{
			window.clear(Color::Yellow);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Numpad2))
		{
			window.clear(Color::Red);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Numpad3))
		{
			window.clear(Color::White);
		}*/
		//window.clear();
		window.draw(spriteMenu);
		window.display();
	}







	/*while (true)
	{

		//---sfml part---
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//---sfml part---

		menu();
		cin >> thisStatus;
		switch (thisStatus)
		{
		case createPoint:
			cout << "whre you want it?" << endl;
			int x, y;
			cout << "x:: "; cin >> x;
			cout << "y:: "; cin >> y;
			if (window.isOpen())
			{
				sfmlPoint.setPosition(Vector2f(x,y));
				window.draw(sfmlPoint);
				window.display();
			}
			//redrawing(tree);
			break;

		case deletePoint:
			//---------------------doing
			//redrawing(tree);
			break;

		case deleteLine:
			//---------------------doing
			//redrawing(tree);
			break;

		case setActivePoint:
			//---------------------doing
			//redrawing(tree);
			break;

		default:
			break;
		}
		//window.display();
		cout << endl << "current active point #" << tree.getActivePoint().getName() << endl;
	}*/
}