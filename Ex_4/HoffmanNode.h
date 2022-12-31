#include <string>
#define SYMBOLE_SIZE 256
#pragma once

class compareNod;
class HuffmanTree;
class HuffmanNode
{
private:
	std::string m_str;

	int m_frequency;

	HuffmanNode* m_left;

	HuffmanNode* m_right;

	friend class compareNod;

	friend class HuffmanTree;
	
public:
	HuffmanNode(std::string str, int frequency, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr) : m_str(str), m_frequency(frequency), m_left(left), m_right(right) {}

	// getter for the children
	HuffmanNode* GetLeft() { return m_left; }

	HuffmanNode* GetRight() { return m_right; }

	std::string GetStr() { return m_str; }

	int GetFrequency() { return m_frequency; }

	// setter for the children

	void SetLeft(HuffmanNode* left) { m_left = left; }

	void SetRight(HuffmanNode* right) { m_right = right; }

	void SetStr(std::string str) { m_str = str; }

	void SetFrequency(int frequency) { m_frequency = frequency; }
};

class compareNode {
public:
	bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2)
	{
		return n1->GetFrequency() > n2->GetFrequency();
	}
};


class HuffmanTree {

private:
	HuffmanNode* root;

	int* frequencyTable;

	std::string* codedTable;

public:
	HuffmanTree() {
		root = nullptr;
		// now we will init the arrays

		for (size_t i = 0; i < SYMBOLE_SIZE; i++)
		{
			frequencyTable[i] = 0;
			codedTable[i] = "";
		}
	}

	void encode(std::string sourceFileName, std::string destFileName);

	void decode(std::string sourceFileName, std::string destFileName);

	int* buildFrequencyTable(std::string text);

	std::string* buildCodedTabe();

	std::string getLetterInTree(HuffmanNode* root, std::string letters);

	std::string getCoddedTree(HuffmanNode* root, std::string code);

	void buildTree(int* frequencyTable);

	void buildTree(int n, std::string letters, std::string tree);

	void calcHuffmanCodeTable(HuffmanNode* root, std::string str);

	std::string encode(char letter, std::string* codedTable);

	std::string decode(std::string code);


};


