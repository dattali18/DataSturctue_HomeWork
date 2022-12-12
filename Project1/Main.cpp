#include <iostream>
#include <list>
#include <string>
#include "Trie.h"

using namespace std;
// Daniel Attali 328780879

int main()
{

	char ch;
	string wrd;
	Trie tr;
	int comp;

	cout << "\nTRIE PROGRAM" << endl;
	cout << "\nChoose one of the following" << endl;
	cout << "a: add a new word" << endl;
	cout << "d: delete an word" << endl;
	cout << "s: check if an word exists " << endl;
	cout << "c: complete the possible word name " << endl;
	cout << "p: print trie" << endl;
	cout << "e: exit " << endl;
	do
	{
		cin >> ch;

		switch (ch)
		{
		case 'a':
			cout << "Enter a word to insert " << endl;
			cin >> wrd;
			if (tr.insert(wrd) == false)
				cout << "ERROR\n";
			break;
		case 'd':
			cout << "Enter a word to del " << endl;
			cin >> wrd;
			if (!tr.delW(wrd)) cout << "ERROR\n";
			break;
		case 's':
			cout << "Enter a word to search " << endl;
			cin >> wrd;
			if (tr.search(wrd))
				cout << "exists\n";
			else
				cout << "does not exist\n";
			break;

		case 'c':
			cout << "Enter a prefix to complete " << endl;
			cin >> wrd;
			comp = tr.printAutoSuggestions(wrd);

			if (comp == 0)
				cout << "No string exist with this prefix\n";
			break;
		case 'p': tr.printTrie(); break;
		case 'e':cout << "bye " << endl; break;
		default: cout << "ERROR " << endl;  break;
		}//switch
	} while (ch != 'e');

}

// ran test 4 on my maching and there was no error
/*
TRIE PROGRAM

Choose one of the following
a: add a new word
d: delete an word
s: check if an word exists
c: complete the possible word name
p: print trie
e: exit
a
Enter a word to insert
abcd
a
Enter a word to insert
acde
a
Enter a word to insert
abcdef
c
Enter a prefix to complete
d
No string exist with this prefix
a
Enter a word to insert
dabc
a
Enter a word to insert
dda
c
Enter a prefix to complete
d
dabc
dda
c
Enter a prefix to complete
dfg
No string exist with this prefix
p
a:
  b:
    c:
      d:
        e:
          f:
  c:
    d:
      e:
d:
  a:
    b:
      c:
  d:
    a:
d
Enter a word to del
dfg
ERROR
p
a:
  b:
    c:
      d:
        e:
          f:
  c:
    d:
      e:
d:
  a:
    b:
      c:
  d:
    a:
d
Enter a word to del
dfg
ERROR
p
a:
  b:
    c:
      d:
        e:
          f:
  c:
    d:
      e:
d:
  a:
    b:
      c:
  d:
    a:
d
Enter a word to del
ab
ERROR
d
Enter a word to del
abcdef
p
a:
  b:
    c:
      d:
  c:
    d:
      e:
d:
  a:
    b:
      c:
  d:
    a:
e
bye

C:\Users\danie\source\repos\dattali18\DataSturctue_HomeWork\x64\Release\Ex_3.exe (process 12256) exited with code 0.
Press any key to close this window . . .
*/