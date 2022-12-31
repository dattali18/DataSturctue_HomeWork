#include "HoffmanNode.h"
#include <iostream>
#include "vector"
#include "queue"
#include <fstream>

//HuffmanTree::

void HuffmanTree::encode(std::string sourceFileName, std::string destFileName){
	// in the encodeing process in the source file we only have the string of char that need to encode
	// and in the destionation file we have 4 lines accroding to the question
	std::ifstream sourceFile(sourceFileName);
	std::ofstream destFile(destFileName);
	
	if (!sourceFile.is_open())
		std::cout << "Error opening source file" << std::endl;
	if (!destFile.is_open())
		std::cout << "Error opening destination file." << std::endl;

	// getting the string to encode
	std::string text;
	sourceFile >> text;

	// after this call the frequencyTable is built
	this->buildFrequencyTable(text);
	// after this call the tree is allready complete
	this->buildTree(this->frequencyTable);
	// after this call we have the coded table for each  character
	this->buildCodedTabe();
	std::string code;
	// now looping for each char in the string
	for (size_t i = 0; text[i] != 0; i++)
	{
		code += encode(text[i], this->codedTable);
	}
	// now we need to get n the amount of char in the code
	int n = 0;
	for (size_t i = 0; i < SYMBOLE_SIZE; i++)
	{
		n = (this->frequencyTable[i] != 0) ? n + 1 : n;
	}
	// call the function that returns the letters in the tree
	std::string letters = getLetterInTree(root, "");;
	
	// call the function the retuns the tree sturcture of the tree
	std::string codedTree = getCoddedTree(root, "");

	// putting the data in the file
	destFile << n;			// (1): the amount of char in the code
	destFile << letters;	// (2): the char in the code in the order they appear in the tree
	destFile << codedTree;	// (3): the coded tree
	destFile << code;		// (4): the coded text


	sourceFile.close();
	destFile.close();
}

void HuffmanTree::decode(std::string sourceFileName, std::string destFileName){
	// in the encodeing process in the source file we only have the string of char that need to encode
// and in the destionation file we have 4 lines accroding to the question
	std::ifstream sourceFile(sourceFileName);
	std::ofstream destFile(destFileName);

	int n;
	std::string letters, coddedTree, code;

	sourceFile >> n;
	sourceFile >> letters;
	sourceFile >> coddedTree;
	sourceFile >> code;

	this->buildTree(n, letters, coddedTree);

	std::string text = decode(code);

	// writing the decoded text into the dest file
	destFile << text;

	// call the function that decode the code with the tree

	sourceFile.close();
	destFile.close();
}

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

std::string HuffmanTree::getLetterInTree(HuffmanNode* root, std::string letters)
{
	if (!root)
		return letters;
	if (root->m_str != "") {
		letters += root->m_str;
	}
	return getLetterInTree(root->m_left, letters) + getLetterInTree(root->m_right, letters);
}

std::string HuffmanTree::getCoddedTree(HuffmanNode* root, std::string code)
{
	if (!root) return code;
	if (root->m_str != "")
		code += '1';
	if (root->m_left && root->m_right) {
		code += '0';
		return getCoddedTree(root->m_left, code) + getCoddedTree(root->m_right, code);
	}

}

void HuffmanTree::calcHuffmanCodeTable(HuffmanNode* root, std::string str = "") {
	if (!root)
		return;

	if (root->m_str != "") {
		codedTable[root->m_str[0]] = str;
	}

	if (root->m_left) {
		calcHuffmanCodeTable(root->m_left, str + "0");
	}
	if (root->m_right) {
		calcHuffmanCodeTable(root->m_right, str + "1");
	}
}

void HuffmanTree::buildTree(int n, std::string letters, std::string tree){
	// beafore building the tree we need to first calc the frequencyTable
	std::queue<HuffmanNode*> queue;
	queue.push(root);
	int i = -1;

	while (!queue.empty()) {
		HuffmanNode* current = queue.front();
		queue.pop();

		// do the thing
		i++;

		if (tree[i] == '0') {
			current->m_left = new HuffmanNode("", 0);
			current->m_right = new HuffmanNode("", 0);
		}
		else if (tree[i] == '1') {
			current->m_str = letters[i];
			current->m_frequency = frequencyTable[(char)letters[i]];
			continue;
		}
		//

		if (current->m_left) {
			queue.push(current->m_left);
		}
		if (current->m_right) {
			queue.push(current->m_right);
		}
	}

}

std::string HuffmanTree::encode(char letter, std::string* codedTable){
	// returning the code for the letter in the parameter
	return codedTable[letter];
}

std::string HuffmanTree::decode(std::string code)
{
	std::string text;
	HuffmanNode* current = root;
	for (size_t i = 0; code[i] == 0; i++)
	{
		if (current->m_str != "") {
			text += current->m_str;
			current = root;
		}
		else {
			if (code[i] == '0') current = current->m_left;
			else if (code[i] == '1') current = current->m_right;
		}

	}
	return text;
}




