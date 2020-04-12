#include <iostream>
#include <fstream>
#include "Figure.h"
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using std::cout;
using std::cin;
using std::endl;
using std::list;

const char filename[] = "PlexFile.txt";

enum condition { addPoint, addLine, deleteLine, setActivePoint };

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
				tempPoint = _tree->getActivePoint()->deepSearch(i, _tree);
				if (tempPoint != NULL)
				{
					out << tempPoint->getName() << " " << tempPoint->getX() << " " << tempPoint->getY() << endl;
				}
			}
			for (int i = 0; i <= _tree->getMaxNumber(); i++)
			{
				tempPoint = NULL;
				tempPoint = _tree->getActivePoint()->deepSearch(i, _tree);
				if (tempPoint != NULL)
				{
					out << tempPoint->getName() << " " << tempPoint->getNumbSon() << endl;
					for (int j = 0; j < tempPoint->getNumbSon(); j++)
					{
						out << tempPoint->getArrPoints()[j]->getName() << endl;
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
	list<Point> treePoints = {};
	//loadFromFile(&tree);
	Point* tempPoint1;
	Point* tempPoint2;
	Point* tempActivePoint;
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
					treePoints.push_back(Point(_x,_y));
					treePoints.back().setName(_name);
					tree.createFigure(treePoints.back());
					tree.getActivePoint()->setName(_name);
					tree.setMaxNumber(_name);
				}
				else
				{
					treePoints.push_back(Point(_x, _y));
					treePoints.back().setName(_name);
					tree.addPoint(&treePoints.back());
					tree.getActivePoint()->deepSearch(tree.getMaxNumber(), &tree)->setName(_name);
					tree.setMaxNumber(_name);
				}
			}
			tree.setMaxNumber(_name);
			//add connection with points
			for (int i = 0; i < _count; i++)
			{
				in >> _name >> _numbSon;
				for (int j = 0; j < _numbSon; j++)
				{
					in >> _nameOfSon;
					tempActivePoint = tree.getActivePoint();
					tempPoint1 = tempActivePoint->deepSearch(_name, &tree);
					tempPoint2 = tempActivePoint->deepSearch(_nameOfSon, &tree);
					bool flag = tempPoint1->contPoint(tempPoint2);
					tempPoint2->contPoint(tempPoint1);
					if (_name == tempActivePoint->getName())
						for (int k = 0; k < _count; k++)
							if (names[k] == _nameOfSon)
								flags[k] = flag;
					if (_nameOfSon == tempActivePoint->getName())
						for (int k = 0; k < _count; k++)
							if (names[k] == _name)
								flags[k] = flag;
					tree.setActivePoint(tempActivePoint);
				}
			}
			//control excess connections
			for (int i = 1; i < _count; i++)
			{
				if (flags[i] == true)
				{
					tempPoint1 = tree.getActivePoint()->deepSearch(names[i], &tree);
					tree.deleteLine(tempPoint1, true);
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
						tree.contIsolPoint(tree.getActivePoint()->deepSearch(name, &tree));
					}
					tree.status();	cout << endl;
				}
				else if (event.key.code == Keyboard::Num2)
				{
					thisStatus = deleteLine;
					cout << "delete line between active and your points:: \n(write name of point)\nline beetwen " << tree.getActivePoint()->getName() << " and : ";
					cin >> name; cout << endl;
					tree.deleteLine(tree.getActivePoint()->deepSearch(name, &tree), false);
					tree.status();	cout << endl;
				}
				else if (event.key.code == Keyboard::Num3)
				{
					thisStatus = setActivePoint;
					cout << "change active point:: \n(write name for new active point)\nnew active point: #";
					cin >> name;
					tree.setActivePoint(tree.getActivePoint()->deepSearch(name, &tree));
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
							treePoints.push_back(Point(event.mouseButton.x, event.mouseButton.y));
							tree.createFigure(treePoints.back());
						}
						else
						{
							treePoints.push_back(Point(event.mouseButton.x, event.mouseButton.y));
							tree.addPoint(&treePoints.back());
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
				tempPoint = tree.getActivePoint()->deepSearch(i, &tree);
				if (tempPoint != NULL)
				{
					for (int j = 0; j < tempPoint->getNumbSon(); j++)
					{
						line[0] = Vertex(Vector2f(tempPoint->getX(), tempPoint->getY()));
						line[1] = Vertex(Vector2f(tempPoint->getArrPoints()[j]->getX(), tempPoint->getArrPoints()[j]->getY()));
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