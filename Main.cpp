#include <iostream>
#include <fstream>
#include "Figure.h"
#include "Point.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using std::cout;
using std::cin;
using std::endl;

const char filename[] = "PlexFile.txt";

enum condition { addPoint, addLine, deleteLine, setActivePoint };

void loadFromFile(Figure* _tree)
{
	Point* tempPoint1;
	Point* tempPoint2;
	std::ifstream in(filename);
	int _count, _name, _x, _y, _numbSon, _nameOfSon;
	int* names;
	bool* flags;
	try
	{
		if (in.is_open())
		{
			in >> _count;
			names = new int[_count];
			flags = new bool[_count];
			//load all points without arrPoints
			for (int i = 0; i < _count; i++)
			{
				in >> _name >> _x >> _y;
				names[i] = _name; flags[i] = true;
				if (i == 0)
				{
					_tree->createFigure(Point(_x, _y));
					_tree->getRoot()->setName(_name);
				}
				else
				{
					_tree->addPoint(&Point(_x, _y));
					_tree->getRoot()->getArrPoints()[_tree->getRoot()->getNumbSon() - 1].setName(_name);
				}
			}
			//add connection with points
			for (int i = 0; i < _count; i++)
			{
				in >> _name >> _numbSon;
				for (int j = 0; j < _numbSon; j++)
				{
					in >> _nameOfSon;
					tempPoint1 = _tree->getRoot()->deepSearch(_name, _tree);
					tempPoint2 = _tree->getRoot()->deepSearch(_nameOfSon, _tree);
					bool flag = tempPoint1->contPoint(tempPoint2);
					tempPoint2->contPoint(tempPoint1);
					if (_name == _tree->getRoot()->getName())
						for (int k = 0; k < _count; k++)
							if (names[k] == _nameOfSon)
								flags[k] = flag;
					if (_nameOfSon == _tree->getRoot()->getName())
						for (int k = 0; k < _count; k++)
							if (names[k] == _name)
								flags[k] = flag;
				}
			}
			//control excess connections
			for (int i = 0; i < _count; i++)
			{
				if (flags[i] == true)
				{
					tempPoint1 = _tree->getRoot()->deepSearch(names[i], _tree);
					_tree->setActivePoint(tempPoint1);
					_tree->deleteLine(_tree->getRoot(), true);
					_tree->setActivePoint(_tree->getRoot());
				}
			}
		}
		else
		{
			throw 1;
		}
		in.close();
	}
	catch (int e)
	{
		cout << "File is not found" << endl;
	}
}

void saveToFile(Figure* _tree)
{
	std::ofstream out(filename);
	try
	{
		if (out.is_open())
		{
			/*
			struct of save to file is next:
			count of points
			(name, x, y) of all points
			(name, numbson, name of all sons) of all points
			*/
			Point* tempPoint;
			out << _tree->getCount() << endl;
			for (int i = 0; i <= _tree->getMaxNumber(); i++)
			{
				tempPoint = NULL;
				tempPoint = _tree->getRoot()->deepSearch(i, _tree);
				if (tempPoint != NULL)
				{
					out << tempPoint->getName() << " " << tempPoint->getX() << " " << tempPoint->getY() << endl;
				}
			}
			for (int i = 0; i <= _tree->getMaxNumber(); i++)
			{
				tempPoint = NULL;
				tempPoint = _tree->getRoot()->deepSearch(i, _tree);
				if (tempPoint != NULL)
				{
					out << tempPoint->getName() << " " << tempPoint->getNumbSon() << endl;
					for (int j = 0; j < tempPoint->getNumbSon(); j++)
					{
						out << tempPoint->getArrPoints()[j].getName() << endl;
					}
				}
			}
		}
		else
		{
			throw 1;
		}
		out.close();
	}
	catch (int e)
	{
		cout << "File is not found" << endl;
	}
}

void main()
{
	cout << "::Journal::" << endl << endl;

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
	sfmlPoint.setTexture(&texturePoint);
	//edge line
	Vertex line[2];

	//for choice event
	int thisStatus = -1;
	//our figure
	Figure tree;
	//loadFromFile(&tree);
	Point* tempPoint1;
	Point* tempPoint2;
	std::ifstream in(filename);
	int _count, _name, _x, _y, _numbSon, _nameOfSon;
	int* names;
	bool* flags;
	try
	{
		if (in.is_open())
		{
			in >> _count;
			names = new int[_count];
			flags = new bool[_count];
			//load all points without arrPoints
			for (int i = 0; i < _count; i++)
			{
				in >> _name >> _x >> _y;
				names[i] = _name; flags[i] = true;
				if (i == 0)
				{
					tree.createFigure(Point(_x, _y));
					tree.getRoot()->setName(_name);
				}
				else
				{
					tree.addPoint(&Point(_x, _y));
					tree.getRoot()->getArrPoints()[tree.getRoot()->getNumbSon() - 1].setName(_name);
				}
			}
			//add connection with points
			for (int i = 0; i < _count; i++)
			{
				in >> _name >> _numbSon;
				for (int j = 0; j < _numbSon; j++)
				{
					in >> _nameOfSon;
					tempPoint1 = tree.getRoot()->deepSearch(_name, &tree);
					tempPoint2 = tree.getRoot()->deepSearch(_nameOfSon, &tree);
					bool flag = tempPoint1->contPoint(tempPoint2);
					tempPoint2->contPoint(tempPoint1);
					if (_name == tree.getRoot()->getName())
						for (int k = 0; k < _count; k++)
							if (names[k] == _nameOfSon)
								flags[k] = flag;
					if (_nameOfSon == tree.getRoot()->getName())
						for (int k = 0; k < _count; k++)
							if (names[k] == _name)
								flags[k] = flag;
				}
			}
			//control excess connections
			for (int i = 0; i < _count; i++)
			{
				if (flags[i] == true)
				{
					tempPoint1 = tree.getRoot()->deepSearch(names[i], &tree);
					tree.setActivePoint(tempPoint1);
					tree.deleteLine(tree.getRoot(), true);
					tree.setActivePoint(tree.getRoot());
				}
			}
		}
		else
		{
			throw 1;
		}
		in.close();
	}
	catch (int e)
	{
		cout << "File is not found" << endl;
	}


	while (window.isOpen())
	{
		int name;
		//events processor
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed:
				if (event.key.code == Keyboard::Num0)
				{
					thisStatus = addPoint;
					cout << "add point::" << endl;
				}
				else if (event.key.code == Keyboard::Num1)
				{
					thisStatus = addLine;
					if (tree.getCount() < 3)
						cout << "add line::\nnot enough points, first add at least three points" << endl << endl;
					else
					{
						cout << "add line between active and your points:: \n(write name of point)\nline beetwen " << tree.getActivePoint()->getName() << " and : ";
						cin >> name; cout << endl;
						tree.contIsolPoint(tree.getRoot()->deepSearch(name, &tree));
					}
					tree.status();	cout << endl;
				}
				else if (event.key.code == Keyboard::Num2)
				{
					thisStatus = deleteLine;
					cout << "delete line between active and your points:: \n(write name of point)\nline beetwen " << tree.getActivePoint()->getName() << " and : ";
					cin >> name; cout << endl;
					tree.deleteLine(tree.getRoot()->deepSearch(name, &tree), false);
					tree.status();	cout << endl;
				}
				else if (event.key.code == Keyboard::Num3)
				{
					thisStatus = setActivePoint;
					cout << "change active point:: \n(write name for new active point)\nnew active point: #";
					cin >> name;
					tree.setActivePoint(tree.getRoot()->deepSearch(name, &tree));
					cout << endl;
					tree.status();
				}
				break;

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
							tree.addPoint(&Point(event.mouseButton.x, event.mouseButton.y));
						}
						cout << "New point: " << tree.getCount() << endl;
						cout << "x: " << event.mouseButton.x << endl;
						cout << "y: " << event.mouseButton.y << endl;
						cout << endl;
						tree.status();
						cout << endl;

						thisStatus = -1;
					}
				}

			default:
				break;
			}

			//---Drawer---
			Point* tempPoint;
			window.clear();
			// <------------------------------------------------------------------------ THERE IS A BIG PROBLEM WITH DRAWER OR SEARCH
			for (int i = 1; i <= tree.getMaxNumber(); i++)
			{
				tempPoint = NULL;
				tempPoint = tree.getRoot()->deepSearch(i, &tree);
				if (tempPoint != NULL)
				{
					for (int j = 0; j < tempPoint->getNumbSon(); j++)
					{
						line[0] = Vertex(Vector2f(tempPoint->getX(), tempPoint->getY()));
						line[1] = Vertex(Vector2f(tempPoint->getArrPoints()[j].getX(), tempPoint->getArrPoints()[j].getY()));
						window.draw(line, 2, sf::Lines);
					}
					sfmlPoint.setPosition(tempPoint->getX() - 20, tempPoint->getY() - 20);
					sfmlPoint.setTextureRect(IntRect(20 * (tempPoint->getName() % 10), 20 * (tempPoint->getName() / 10), 20, 20));
					window.draw(sfmlPoint);
				}
			}

		}

		window.draw(spriteMenu);
		window.display();
	}
	saveToFile(&tree);
	return;
}