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
	if (t == nullptr) {
		return;
	}
	for (auto node = t->responses.begin(); node != t->responses.end(); node++)
	{
		deleteAllSubTree(*node);
	}
	delete t;
}

void Tree::addRoot(string newval)
{
	// creating a new node and giving it a string value
	Node* node = new Node(newval);
	// deleting the old tree
	deleteAllSubTree(root);
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
	Node* p = search(val);
	if (p == nullptr) return false;
	print(p);
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

void Tree::print(Node* p, int level)
{
	for (size_t i = 0; i < level; i++)
	{
		cout << "   ";
	}
	cout << p->content << endl;
	int nextLevel = level + 1;
	for (auto node = p->responses.begin(); node != p->responses.end(); node++)
	{
		print(*node, nextLevel);
	}

} 


bool Tree::searchAndPrintPath(Node* p, string val)
{
	if (val == p->content) {

	}
	return false;
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

void treeList::searchAndPrint(string val)
{
	for (auto itr = trees.begin(); itr != trees.end(); itr++)
	{
		// it will search in the current tree, and if it doesn't find it, it will search in the next tree etc...
		(*itr)->searchAndPrintPath(val);
	}

}

void treeList::printTree(string rt)
{
	// calling the methods that will find the right tree by searching the root node in each tree in the list
	Tree* tree = searchTreeByRoot(rt);

	// cheking if tree -> nullptr, we now the tree with root->content = rt doesn't exist
	if (tree != nullptr) {
		tree->printAllTree();
	}

}

void treeList::printAllTrees()
{
	for (auto itr = trees.begin(); itr != trees.end(); itr++)
	{
		(*itr)->printAllTree();
		std::cout << std::endl;
	}
}

void treeList::printSubTree(string rt, string s)
{
	// calling the methods that will find the right tree by searching the root node in each tree in the list
	Tree* tree = searchTreeByRoot(rt);

	// cheking if tree -> nullptr, we now the tree with root->content = rt doesn't exist
	if (tree != nullptr) {
		tree->printSubTree(s);
	}
}