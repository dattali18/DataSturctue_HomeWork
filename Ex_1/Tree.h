#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Node;

//Node: each Node in the discussion tree
class Node
{
	void setValue(string v);
public:
	list<Node*> responses;

	string content;

	bool isLeaf;

	Node(string v) { isLeaf = true;  content = v; }

	friend class Tree;
};


//Tree: the discussion Tree
class Tree
{
	Node* root;

	Node* search(string val);


	bool searchAndPrintPath(Node* p, string val);

	void print(Node* p, int level = 0);

public:

	Tree() { root = NULL; }

	~Tree() {
		deleteAllSubTree(root);
		root = 0;
	}

	// cuation!! there may be a problam with deleteing the node t itself
	void deleteAllSubTree(Node* t);

	void addRoot(string newval);

	bool addSon(string fatherdiscussion, string newresponse);

	bool searchAndPrintPath(string val)
	{
		bool flag = searchAndPrintPath(root, val);
		return flag;
	}

	void printAllTree() { print(root); }

	void printSubTreeroot(string val, int _= 0) { printSubTree(root->content); }

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

	~treeList();

	void addNewTree(string s);

	void deleteTree(Tree* tree);

	void searchAndPrint(string val);

	bool addResponse(string rt, string prnt, string res);

	bool delResponse(string rt, string res);

	void printTree(string rt);

	void printAllTrees();

	void printSubTree(string rt, string s);
};



