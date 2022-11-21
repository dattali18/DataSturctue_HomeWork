#include "HashInt.h"

int HashInt::h1(int key)
{
    return key % size;
}

int HashInt::h2(int key)
{
    return (key % (size - 1) + 1) % size;
}

void HashInt::print()
{
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i].flag == full) {
			cout << arr[i].key << ": " << arr[i].data << endl;
		}
	}
}
