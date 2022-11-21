#pragma once

#include <iostream>
#include "HashTable.h"


class HashInt: public HashTable<typename int, typename int>
{
protected:

	int h1(int key);

	int h2(int key);

public:

	HashInt(int n) : HashTable<int, int>(n) {}

	void print();
};
