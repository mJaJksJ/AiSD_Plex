#include <iostream>
#include "Figure.h"
#include "Point.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using std::cout;
using std::cin;
using std::endl;

enum condition { addPoint, addLine, deleteLine, setActivePoint };

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
						tree.contIsolPoint(tree.getRoot()->search(name, tree.getRoot()));
					}
					tree.status();	cout << endl;
				}
				else if (event.key.code == Keyboard::Num2)
				{
					thisStatus = deleteLine;
					cout << "delete line between active and your points:: \n(write name of point)\nline beetwen " << tree.getActivePoint()->getName() << " and : ";
					cin >> name; cout << endl;
					tree.deleteLine(tree.getRoot()->search(name, tree.getRoot()));
					tree.status();	cout << endl;
				}
				else if (event.key.code == Keyboard::Num3)
				{
					thisStatus = setActivePoint;
					cout << "change active point:: \n(write name for new active point)\nnew active point: #";
					cin >> name;
					tree.setActivePoint(tree.getRoot()->search(name, tree.getRoot()));
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
				tempPoint = tree.getRoot()->search(i, tree.getRoot());
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

	return;
}