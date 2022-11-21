#pragma once

#include <iostream>
#include <string>
using namespace std;



template <typename T, typename K>
class HashTable
{
protected:

	enum state { empty, full, deleted };
	class Item
	{
	public:
		T data;
		K key;
		state flag;
		Item() {}
		Item(T d, K k, state f) { data = d; key = k; flag = f; }
	};


	int size;

	int inUse = 0;

	Item* arr;

	bool prime(int n);

	int hash(K key, int i);

	virtual int h1(K key) = 0;

	virtual int h2(K key) = 0;

public:

	HashTable(int m = 10);

	~HashTable();

	void add(K key, T dat);

	int remove(K key);

	int search(K key);

	T* entryData(K i)
	{
		int ind = search(i);
		if (ind == -1)
			return NULL;
		else
			return &(arr[ind].data);
	}

	void print();
};

template<typename T, typename K>
inline bool HashTable<T, K>::prime(int n)
{
	// using the Sieve of Eratosthenes to create all the prime up to n + 100
	// I'm assuming that we will not use n so big that the next prime is more the 100 number farther up
	// for info p(10000001) - p(10000000) = 18 , means that for number in the 10^9 range the difference between two prime is only 18
	// p(n) the n'th prime
	const int SIZE = n + 100;
	bool* prime = new bool[SIZE];
	// putting true in the array
	for (size_t i = 0; i < SIZE; i++)
	{
		prime[i] = true;
	}

	for (int p = 2; p * p <= SIZE; p++) {
		// If prime[p] is not changed, then it is a prime
		if (prime[p]) {
			// Update all multiples of p greater than or
			// equal to the square of it numbers which are
			// multiple of p and are less than p^2 are
			// already been marked.
			for (int i = p * p; i <= (SIZE - 1); i += p)
				prime[i] = false;
		}
	}
	// now that we have the list of all the prime number till n + 100 we will search for the nearest prime to n
	int k = n;
	// while k is not a prime
	while (!prime[k]) {
		k++;
	}
	// now k is the closet prime to n
	size = k;
	delete[]prime;
	return true;
}

template<typename T, typename K>
inline int HashTable<T, K>::hash(K key, int i)
{
	return (h1(key) + i * h2(key)) % size;

}

template<typename T, typename K>
inline HashTable<T, K>::HashTable(int m)
{
	prime(m);
	// now size is the nearest prime to m
	arr = new Item[size];
}

template<typename T, typename K>
inline HashTable<T, K>::~HashTable()
{
	delete[]arr;
}

template<typename T, typename K>
inline void HashTable<T, K>::add(K key, T dat)
{
	// if the amount of place in use is equal to the size we don't have anymore space left so we don't do anything
	if (inUse >= size)
		return;
	int num = 0;
	int i = 0;
	// getting the right index for the key
	// while the place at current index is full redo the hashing
	do
	{
		i = hash(key, num++);
	} while (arr[i].flag == full);
	// putting the data in
	arr[i].data = dat;
	arr[i].key = key;
	arr[i].flag = full;

	inUse++;
}

template<typename T, typename K>
inline int HashTable<T, K>::remove(K key)
{
	int i = search(key);
	// if i == -1 the key isn't in the table so we return also -1 to indicate the key isn't in the table
	if (i == -1)
		return -1;

	// updating the state of the current item
	arr[i].flag = deleted;
	// removeing 1 form the amount of place in use
	inUse--;
	return 0;
}

template<class T, class K>
inline int HashTable<T, K>::search(K key)
{
	int i;
	int n = 0;
	do
	{
		i = hash(key, n++);
	} while (arr[i].key != key && n <= size);
	// while the key of the current index is not equal the key we are searching for continue hashing
	// of if the amount of time we looped is bigger or equal size the key isn't in the table
	if (n >= size)
		return -1;
	return i;
}
