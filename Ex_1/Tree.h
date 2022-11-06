#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

// Daniel Attali 328780879 data sturcture2 ex1

class Node;

//Node: each Node in the discussion tree
class Node
{
	void setValue(string v);
public:

	list<Node*> responses;

	string content;

	bool isLeaf;

	Node* parent;

	Node(string v) { isLeaf = true;  content = v; parent = nullptr; }

	~Node() {
		responses.clear();
		parent = nullptr;
	}

	friend class Tree;
};


//Tree: the discussion Tree
class Tree
{
	Node* root;

	void print(Node* p, int level=0);

	Node* search(string val);

public:

	Tree() { root = nullptr; }

	~Tree() {
		deleteAllSubTree(root);
		root = 0;
	}

	void deleteAllSubTree(Node* t);

	void addRoot(string newval);

	bool addSon(string fatherdiscussion, string newresponse);

	bool searchAndPrintPath(string val);

	void printAllTree() { print(root); }

	bool printSubTree(string val);

	bool deleteSubTree(string val);

	friend class treeList;
};


class treeList
{
private:

	list<Tree*> trees;

	Tree* searchTreeByRoot(string rt);

public:
	treeList() {}

	~treeList() {
		// by calling clear on a list of tree it will call the dtor on each tree in the list
		trees.clear();
	}

	void addNewTree(string s);

	void deleteTree(Tree* tree);

	void searchAndPrint(string val);

	bool addResponse(string rt, string prnt, string res);

	bool delResponse(string rt, string res);

	void printTree(string rt);

	void printAllTrees();

	void printSubTree(string rt, string s);
};



