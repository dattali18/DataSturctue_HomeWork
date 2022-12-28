#include "HoffmanNode.h"
#include "vector"
#include "queue"

//HuffmanTree::

void HuffmanTree::encode(std::string sourceFileName, std::string destFileName){}

void HuffmanTree::decode(std::string sourceFileName, std::string destFileName){}

int* HuffmanTree::buildFrequencyTable(std::string text) {
	for (size_t i = 0; i < SYMBOLE_SIZE; i++)
	{
		frequencyTable[text[i]] += 1;
	}

	return frequencyTable;
}

void HuffmanTree::buildTree(int* frequencyTable){
	int n = 0;
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, compareNode> pQueue;
	// counting how much char do we have in our code
	// and creating the priority queue 
	for (int i = 0; i < SYMBOLE_SIZE; i++)
	{
		n = (frequencyTable[i] == 0) ? n : n + 1;
		if (frequencyTable[i] != 0) {
			pQueue.push(new HuffmanNode((std::to_string((char)i)), frequencyTable[i]));
		}
	}
	// now applying the algorithm
	for (int i = 1; i < n - 1; i++)
	{
		HuffmanNode* x = pQueue.top();
		pQueue.pop();
		HuffmanNode* y = pQueue.top();
		pQueue.pop();
		HuffmanNode* z = new HuffmanNode("", x->GetFrequency() + y->GetFrequency(), x, y);
		pQueue.push(z);
	}
	// at the end of the loop we should have only one node in the pQueue and we need to assigin it the root
	root = pQueue.top();
	
}

std::string* HuffmanTree::buildCodedTabe() {
	// we need the tree to allready be done when we call this function

	// scanning the tree
	//
	//std::queue<HuffmanNode*> queue;
	//queue.push(root);
	//while (!queue.empty()) {
	//	HuffmanNode* current = queue.front();
	//	queue.pop();

	//	//do the thing with the node

	//	queue.push(current->GetLeft());
	//	queue.push(current->GetRight());
	//}

	calcHuffmanCodeTable(root, "");
	return codedTable;
}

void HuffmanTree::calcHuffmanCodeTable(HuffmanNode* root, std::string str = "") {
	if (!root)
		return;

	if (root->GetStr() != "") {
		codedTable[root->GetStr()[0]] = str;
	}

	calcHuffmanCodeTable(root->GetLeft(), str + "0");
	calcHuffmanCodeTable(root->GetRight(), str + "1");
}

void HuffmanTree::buildTree(int n, std::string letters, std::string tree){
}

void HuffmanTree::encode(char letter, std::string* codedTable){}



