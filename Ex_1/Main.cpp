#include <iostream>
#include "Tree.h"

using std::cout;
using std::cin;

int main() {
	Tree tree;

	tree.addRoot("root");
	tree.addSon("root", "child-1");
	tree.addSon("root", "child-2");
	tree.addSon("root", "child-3");
	tree.addSon("child-1", "child-1.1");
	tree.addSon("child-1", "child-1.2");
	tree.addSon("child-1", "child-1.3");
	
	tree.addSon("child-2", "child-2.1");
	tree.addSon("child-2.1", "child-2.1.1");
	tree.addSon("child-2.1.1", "child-2.1.1.1");
	
	tree.printAllTree();
	
	
	//tree.deleteSubTree("child-2");
	
	tree.printAllTree();

	return 0;
}