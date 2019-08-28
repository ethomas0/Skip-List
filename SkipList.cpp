#include "stdafx.h"
#include "SkipList.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;



int main()

{
	srand(static_cast<unsigned int>(time(0)));

	SkipList list;

	for (int i = 0; i < 25; i++)//inserting random numbers for testing

	{

		list.insert(rand() % 100);

	}
	list.testConnections();

	list.printLevels();

	cout << endl << "List: ";

	list.print();

	int userInput = 0;
	cout << "Which Node would you like to delete? "; // for testing

	cin >> userInput;

	list.remove(userInput);

	cout << endl << "List: ";

	list.print();
	list.testConnections();
	//cout << endl;

	system("pause");



	return 0;

}