#include "stdafx.h"
#include "SkipList.h"
#include <ctime>           //for srand(static_cast<unsigned int>(time(0)));
#include <cstdlib>            //for rand()
#include <iostream>
using namespace std;


SkipList::SkipList()

{

	head = new Node(INT_MIN);
	head->next = new Node(INT_MAX);
	head->next->prev = head;
	maxLevel = 1;
	
}



SkipList::Node* SkipList::find(const int key)//public find

{

	return find(key, head);

}



void SkipList::print()//public print

{

	printLevel(1);

}



bool SkipList::insert(const int value)//public insert

{

	Node* minBoundry = find(value);//sets up where to insert

	Node* maxBoundry = minBoundry->next;//makes kind of a boundry of where to insert

	if (minBoundry->key == value)//if duplicate

	{
		//cout << "Duplicate: " << value << endl; for testing purposes

		return false;

	}

	else

	{

		minBoundry->next = new Node(value, minBoundry, maxBoundry);

		maxBoundry->prev = minBoundry->next;//moving pointers to point to new node

		minBoundry->next->listLevel = minBoundry->listLevel;

		addLevel(minBoundry->next);

		return true;

	}

}



bool SkipList::remove(const int key)//public remove

{

	Node* itarator = find(key);

	if (itarator->key == key)

	{

		while (itarator->below != nullptr)//deleting if node has multiple levels 

		{

			itarator->prev->next = itarator->next;//move pointers around it

			itarator->next->prev = itarator->prev;

			itarator = itarator->below;

			delete itarator->above;

		}

		itarator->prev->next = itarator->next;//moving pointers

		itarator->next->prev = itarator->prev;

		delete itarator;//deleting node on bottom level

		removeLevels();

	}

	else

	{

		cout << key << " Key Not Found" << endl;

		return false;

	}



}



void SkipList::addLevel(Node * currNode)

{

	Node* it = nullptr;

	for (int currLevel = 2; (rand() % 2) == 0; ++currLevel) //50% chance(except for first time, I add a level giving the illusion of chance) (even # are the stopping point) 

	{

		if (currLevel > maxLevel) //CASE: no level above exists yet

		{

			maxLevel++;

			currNode->above = new Node(currNode->key, nullptr, nullptr, nullptr, currNode);

			currNode = currNode->above;

			currNode->listLevel = currLevel;

			head->above = new Node(INT_MIN, nullptr, currNode, nullptr, head);

			head = head->above;

			head->listLevel = currLevel;

			currNode->prev = head;

			currNode->next = new Node(INT_MAX, currNode, nullptr);

			currNode->next->listLevel = currLevel;

		}

		else //CASE: Level exists already, add currNode to current level

		{

			it = head;

			while (it->listLevel > currLevel) //go to same level where you want to add.

			{

				it = it->below;

			}

			while (it->next->key < currNode->key) //navigate

				it = it->next;

			currNode->above = new Node(currNode->key, it, it->next, nullptr, currNode);

			currNode = currNode->above;

			currNode->listLevel = currLevel;

			it->next = currNode;

			currNode->next->prev = currNode;

		}



	}



}



void SkipList::removeLevels()

{

	while (head->next->key == INT_MAX && maxLevel > 1)

	{

		delete head->next;

		head = head->below;

		delete head->above;

		head->above = nullptr;

		maxLevel--;

	}



}



void SkipList::printLevel(int level)

{

	Node* itarator = head;

	while (itarator->listLevel != level)
	{
		itarator = itarator->below;
	}

	while (itarator != nullptr)

	{

		if (itarator->key == INT_MIN)

			cout << "MIN   ";

		else if (itarator->key == INT_MAX)

			cout << "   MAX";

		else

			cout << itarator->key << ",";

		itarator = itarator->next;

	}

	cout << endl;



}



void SkipList::printLevels()//prints all levels

{

	for (int i = maxLevel; i > 0; i--)

	{

		printLevel(i);

	}

}

void SkipList::testConnections()
{
	Node *it = head;
	while (it->below != nullptr)
	{		
		it = it->below;		
	}
	while (it->key != INT_MAX)
	{
		if (it->next->prev == it)
		{
			it = it->next;
		}
		else
		{
			cout << "Bad connection at " << it->key << endl;
			return;
		}
	}
	cout << "All connections passed" << endl;

}







SkipList::Node * SkipList::find(const int key, Node * currNode)

{

	if (key == currNode->key)
	{

		return currNode;//return found

	}

	if (key >= currNode->next->key)//checking ahead 

	{

		find(key, currNode->next);

	}

	else if (currNode->below != nullptr)//nothing on the list matches so moving down

	{

		find(key, currNode->below);

	}

	else if (currNode->below == nullptr && key < currNode->next->key)//will use for insert function
	{
		return currNode;
	}
}