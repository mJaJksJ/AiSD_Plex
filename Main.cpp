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
		int name;
		//events processor
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// çàêðûòèå îêíà
			case Event::Closed:
				window.close();
				break;

				// íàæàòèå êëàâèøè
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Num0)
				{
					thisStatus = addPoint;
					cout << "add point::" << endl;
				}
				else if (event.key.code == Keyboard::Num1)
				{
					thisStatus = addLine;
					cout << "add line between active and your points:: \n(write name of point)\nline beetwen " << tree.getActivePoint()->getName() << "and : ";
					cin >> name;
					cout << endl;
					tree.contIsolPoint(tree.getRoot()->search(name, tree.getRoot()));
					line[0] = Vertex(Vector2f(tree.getActivePoint()->getX(), tree.getActivePoint()->getY()));
					line[1] = Vertex(Vector2f(tree.getRoot()->search(name, tree.getRoot())->getX(), tree.getRoot()->search(name, tree.getRoot())->getY()));

					tree.status();
					cout << endl;
				}
				else if (event.key.code == Keyboard::Num2)
				{
					thisStatus = deleteLine;
				}
				else if (event.key.code == Keyboard::Num3)
				{
					thisStatus = setActivePoint;
					cout << "change active point:: \n(write name for new active point)\nnew active point: #";
					cin >> name;
					tree.setActivePoint(tree.getRoot()->search(name, tree.getRoot()));

					cout << endl;
					cout << tree.getActivePoint()->getName();
					tree.status();
				}
				break;

				//íàæàòèå êíîïêè ìûøè
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

						line[0] = Vertex(Vector2f(tree.getActivePoint()->getX(), tree.getActivePoint()->getY()));
						line[1] = Vertex(Vector2f(event.mouseButton.x, event.mouseButton.y));
						//--end sfml--

						thisStatus = -1;
					}
				}
				// ìû íå îáðàáàòûâàåì äðóãèå òèïû ñîáûòèé
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