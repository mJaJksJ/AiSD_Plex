#include <iostream>
#include "Point.h"
#include "Figure.h"
using namespace std;

void main()
{
	Point obj = Point(1, 1);
	Point* arr = new Point[7];
	for (int i = 0; i < 7; i++)
		arr[i] = Point(i + 1, i + 1);

	Figure fig;
	fig.createFigure(&obj);


	fig.addPoint(arr[0]);
	fig.addPoint(arr[1]);

	fig.setActPoint(&arr[1]);
	fig.addPoint(arr[2]);
	fig.addPoint(arr[3]);

	fig.setActPoint(&arr[3]);
	fig.addPoint(arr[4]);

	fig.setActPoint(&arr[4]);
	fig.addPoint(arr[5]);
	fig.addPoint(arr[6]);


	cout << obj.getNumbSon() << endl;
	for (int i = 0; i < obj.getNumbSon(); i++)
		cout << obj.getArrPoints()[i].getName() << "\t" << obj.getArrPoints()[i].getNumbSon() << endl;


}
	