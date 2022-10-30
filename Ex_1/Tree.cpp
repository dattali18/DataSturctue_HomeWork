#include "Tree.h"
#include <queue>

// methods of the class Node

void Node::setValue(string v)
{
	this->content = v;
}

// methods of the class Tree

Node* Tree::search(string val)
{
	std::queue<Node*> queue;
	queue.push(root);

	while (!queue.empty()) {
		Node* currentNode = queue.front();
		queue.pop();

		if (currentNode->content == val) {
			return currentNode;
		}

		for (auto node = currentNode->responses.begin(); node != currentNode->responses.end(); node++)
		{
			queue.push(*node);
		}
	}
	return nullptr;
}

void Tree::deleteAllSubTree(Node* t)
{
	if (t->isLeaf) {
		delete t;
		return;
	}
	// for each childern of the subtree t delete all of their subtree
	for (auto node = t->responses.begin(); node  != t->responses.end(); node++)
	{
		deleteAllSubTree(*node);
		// after deleting all of the subtree of a certain child remove the ptr to the child from the list
		t->responses.erase(node);
	}
	// after deleting and removing all of the subtrees in the children remove the root itself
	delete t;
}

void Tree::addRoot(string newval)
{
	// creating a new node and giving it a string value
	Node* node = new Node(newval);
	// deleting the old tree
	this->deleteAllSubTree(root);
	// creating a new root
	root = node;
}

bool Tree::addSon(string fatherdiscussion, string newresponse)
{

	Node* p = search(fatherdiscussion);
	// if the dicussion doesn't exist return false
	if (p == nullptr) {
		return false;
	}
	// if the dicussion exist and we have the parent add to the response a new response
	p->responses.push_back(new Node(newresponse));
	// changing the value of is leaf since it has a son now
	p->isLeaf = false;
	// return true indicate the operation was a success
	return true;
}

bool Tree::printSubTree(string val)
{
	std::queue<Node*> queue;
	Node* p = search(val);
	if (p == nullptr) return false;

	queue.push(p);
	int level = 0;

	while (!queue.empty()) {
		Node* currentNode = queue.front();
		queue.pop();

		// printing the response
		// printing the \t to see the diferent levels
		for (size_t i = 0; i < level; i++)
		{
			std::cout << '\t';
		}
		std::cout << currentNode->content << std::endl;
		level++;

		for (auto node = currentNode->responses.begin(); node != currentNode->responses.end(); node++)
		{
			queue.push(*node);
		}
	}
	return true;
}

bool Tree::deleteSubTree(string val)
{
	Node* p = search(val);
	// there is no node with the value val so we return false to indicate that ther ewas a problame
	if (p == nullptr) {
		return false;
	}
	// if p is not null so we have the node so we can delete all the sub tree of the node
	deleteAllSubTree(p);
	
}


// methods of the class Treelist

void treeList::addNewTree(string s)
{
	// cerating a new tree with the root node with value s
	Tree* tree = new Tree();
	tree->addRoot(s);
	// pushing the new tree in the tree list
	trees.push_back(tree);
}

void treeList::deleteTree(Tree* tree)
{
	// finding the tree inside the list
	std::list<Tree*>::iterator itr = std::find(trees.begin(), trees.end(), tree);

	// the function find() return an itr to the element, but if it's not in the list the itr = list.end()
	if (itr != trees.end()) {
		// deleting the tree, will call the dtor
		delete *itr;
		// erasing the ptr of the tree from the list
		trees.erase(itr);
	}
}

bool treeList::addResponse(string rt, string prnt, string res)
{
	Tree* tree = searchTreeByRoot(rt);

	// if tree = nullptr so we didn't find a tree with the root value of rt so we return false to indicate the operation was unsuccessful
	if(tree == nullptr)
		return false;

	bool flag= tree->addSon(prnt, res);
	return flag;
}

bool treeList::delResponse(string rt, string res)
{
	Tree* tree = searchTreeByRoot(rt);

	// if tree = nullptr so we didn't find a tree with the root value of rt so we return false to indicate the operation was unsuccessful
	if (tree == nullptr)
		return false;

	bool flag = tree->deleteSubTree(res);
	return flag;
}


// the function will return a ptr to the tree if found, else will return nullptr
Tree* treeList::searchTreeByRoot(string rt)
{

	Tree* tree = nullptr;
	for (auto itr = trees.begin(); itr != trees.end(); itr++)
	{
		// if we have found the tree where the string value of the root = rt
		// point the ptr to the tree and exit the loop
		if ((*itr)->root->content == rt) {
			tree = *itr;
			break;
		}
	}

	return tree;
}