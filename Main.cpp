#include <iostream>
#include "Figure.h"
#include "Point.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using std::cout;
using std::cin;
using std::endl;

enum condition { addPoint, addLine, deleteLine, setActivePoint };

//-----------это то что я пытался натворить с обходом---

//не визуализация а вывод в консоль
void tempDrawer(Point _point)
{
	cout << endl;
	cout << "Point #" << _point.getName() << endl;
	cout << "sons :: ";
	for (int i = 0; i < _point.getNumbSon(); i++)
	{
		cout << _point.getArrPoints()[i].getName() << " ";
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
			if (_point.getArrPoints()[i].isLocked() == false)
			{
				redrawing(_point.getArrPoints()[i]);
			}
			else
			{
				_point.getArrPoints()[i].lock();
				tempDrawer(_point.getArrPoints()[i]);
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
			if (_point.getArrPoints()[i].isLocked() == false)
			{
				walk(_point.getArrPoints()[i]);
			}
			else
			{
				_point.getArrPoints()[i].lock();
				return _point.getArrPoints()[i];
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
			if (_point.getArrPoints()[i].isLocked() == true)
			{
				walk(_point.getArrPoints()[i]);
			}
			else
			{
				_point.getArrPoints()[i].unlock();
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
			if (_activePoint.getArrPoints()[i].getName() == _name)
			{
				requiredPoint = _activePoint.getArrPoints()[i];
			}
			if (_activePoint.getArrPoints()[i].isLocked() == false)
			{
				walk(_activePoint.getArrPoints()[i]);
			}
			else
			{
				_activePoint.getArrPoints()[i].lock();
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

//-------------вот до сюда-----------

void main()
{
	//--journal--
	cout << "::Journal::" << endl << endl;
	//--end journal--

	//--sfml--
	//window for drawing
	RenderWindow window(VideoMode(800, 600), "Flexis");
	//texture for menu
	Texture textureMenu;
	textureMenu.loadFromFile("main_menu.jpg");
	//picture of menu
	Sprite spriteMenu;
	spriteMenu.setTexture(textureMenu);
	spriteMenu.setPosition(0, 0);
	//picture of point
	CircleShape sfmlPoint(20);
	//texture of point
	Texture texturePoint;
	texturePoint.loadFromFile("nums.jpg");
	//edge line
	Vertex line[2];
	//--end sfml--

	//for choise event
	int thisStatus = -1;
	//our figure
	Figure tree;

	while (window.isOpen())
	{
		//events processor
		Event event;
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
					cout << "add point::" << endl;
				}
				else if (event.key.code == Keyboard::Num1)
				{
					thisStatus = addLine;
				}
				else if (event.key.code == Keyboard::Num2)
				{
					thisStatus = deleteLine;
				}
				else if (event.key.code == Keyboard::Num3)
				{
					thisStatus = setActivePoint;
				}
				break;

				//нажатие кнопки мыши
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (thisStatus == addPoint)
					{
						if (tree.getCount() == 0)
						{
							tree.createFigure(Point(event.mouseButton.x, event.mouseButton.y));
						}
						else
						{
							tree.addPoint(Point(event.mouseButton.x, event.mouseButton.y));
						}
						//--journal--
						cout << "New point: " << tree.getCount() << endl;
						cout << "x: " << event.mouseButton.x << endl;
						cout << "y: " << event.mouseButton.y << endl;
						cout << endl;
						tree.status();
						cout << endl;
						//--end journal--

						//--sfml--
						sfmlPoint.setPosition(event.mouseButton.x, event.mouseButton.y);
						sfmlPoint.setTexture(&texturePoint);
						sfmlPoint.setTextureRect(IntRect(20 * (tree.getCount() % 10 - 1), 20 * ((tree.getCount() - 1) / 10), 20, 20));

						line[0] = Vertex(Vector2f(tree.getActivePoint().getX(), tree.getActivePoint().getY()));
						line[1] = Vertex(Vector2f(event.mouseButton.x, event.mouseButton.y));
						//--end sfml--

					}
					else if (thisStatus == addLine)
					{

					}
					else if (thisStatus == deleteLine)
					{

					}
					else if (thisStatus == setActivePoint)
					{

					}
				}
				// мы не обрабатываем другие типы событий
			default:
				break;
			}
		}

		//--sfml--
		window.draw(line, 2, sf::Lines);
		window.draw(sfmlPoint);
		window.draw(spriteMenu);
		window.display();
		//--end sfml--
	}

	return;
}
