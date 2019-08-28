#pragma once
#include <ctime>    
#include <climits>
#include <cstdlib>



class SkipList

{

public:

	class Node

	{



	public:

		Node(int boundries)//MIN/MAX constructor

		{

			key = boundries;

		};

		Node(int value, Node* left, Node* right, Node* up = nullptr, Node* down = nullptr)
		{
			key = value;
			prev = left;
			below = down;
			next = right;
			above = up;

		};



		int key;

		int listLevel = 1;

		Node * next = nullptr;

		Node * prev = nullptr;

		Node * above = nullptr;

		Node * below = nullptr;



		//add any public NODE functions & data

	};



	SkipList();

	Node * find(const int key);

	void print();

	bool insert(const int value);

	bool remove(const int key);

	void addLevel(Node* currNode);

	void removeLevels();

	void printLevels();

	int maxLevel = 0;

	Node* head = nullptr;
	void testConnections();



private:

	Node * find(const int key, Node * currNode);

	void printLevel(int level);



};