#include "HSubject.h"

void HSubject::printS(string ky)
{
	int idx = search(ky);
	if (idx == -1 ) {
		cout << "ERROR" << endl;
		return;
	}
	else if (arr[idx].flag != full)
	{
		cout << "ERROR" << endl;
		return;
	}

	cout << "Subject " << ky << " " << arr[idx].data.size() << " topics: " << endl;
	for (auto sub = arr[idx].data.rbegin(); sub != arr[idx].data.rend(); ++sub)
	{
		cout << *sub << " ";
	}
	cout << endl;
}

void HSubject::printN(string ky, int N)
{
	int idx = search(ky);
	if (idx == -1) {
		cout << "ERROR" << endl;
		return;
	}
	else if (arr[idx].flag != full)
	{
		cout << "ERROR" << endl;
		return;
	}
	if (N > arr[idx].data.size()) {
		for (auto sub = arr[idx].data.rbegin(); sub != arr[idx].data.rend(); ++sub)
		{
			cout << *sub << " ";
		}
		return;
	}
	auto sub = arr[idx].data.rbegin();
	for (int i = 0; i < N; ++i)
	{
		cout << *sub << " ";
		sub++;
	}
	cout << endl;
}

void HSubject::print()
{
	cout << "All subjects and titles: " << endl;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i].flag == full) {
			cout << arr[i].key << ": ";
			for (auto sub = arr[i].data.rbegin(); sub != arr[i].data.rend(); ++sub)
			{
				cout << *sub << " ";
			}
			cout << endl;
		}

	}
}

void HSubject::startNewTable()
{
	for (size_t i = 0; i < size; i++)
	{
		arr[i].flag = empty;
	}
}

void HSubject::addSubjectAndTitle(string s, string t)
{

	int idx = search(s);
	// if idx = -1 so subject is not in the table yet
	if (idx == -1) {
		// if the amount of place in use is equal to the size we don't have anymore space left so we don't do anything
		if (inUse >= size)
			return;
		int num = 0;
		int i = 0;
		// getting the right index for the key
		// while the place at current index is full redo the hashing
		do
		{
			i = hash(s, num++);
		} while (arr[i].flag == full);

		inUse++;
		idx = i;
		arr[i].flag = full;
		arr[i].key = s;
	}
	arr[idx].data.push_back(t);
}
