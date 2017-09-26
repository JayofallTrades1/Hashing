#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<ctime>
#include<algorithm>
#define BUFFER 2000
#define SIZE 10

using namespace std;
const int TABLE_SIZE = 511;

int Hash(int value)
{
	return value / TABLE_SIZE;
}

/*
* HashNode Class Declaration
*/
class HashNode
{
public:
	int key;
	int value;
	HashNode* next;
	HashNode(int key, int value)
	{
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
};

/*
* HashMap Class Declaration
*/
class HashMap
{
private:
	HashNode** htable;
public:
	HashMap()
	{
		htable = new HashNode*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
			htable[i] = NULL;
	}
	~HashMap()
	{
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			HashNode* entry = htable[i];
			while (entry != NULL)
			{
				HashNode* prev = entry;
				entry = entry->next;
				delete prev;
			}
		}
		delete[] htable;
	}
	/*
	* Hash Function
	*/
	int HashFunc(int key)
	{
		return key % TABLE_SIZE;
	}

	/*
	* Insert Element at a key
	*/
	void Insert(int key, int value)
	{
		int hash_val = Hash(value);
		HashNode* prev = NULL;
		HashNode* entry = htable[hash_val];
		while (entry != NULL)
		{
			prev = entry;
			entry = entry->next;
		}
		if (entry == NULL)
		{
			entry = new HashNode(key, value);
			if (prev == NULL)
			{
				htable[hash_val] = entry;
			}
			else
			{
				prev->next = entry;
			}
		}
		else
		{
			entry->value = value;
		}
	}
	/*
	* Remove Element at a key
	*/
	void Remove(int key)
	{
		int hash_val = HashFunc(key);
		HashNode* entry = htable[hash_val];
		HashNode* prev = NULL;
		if (entry == NULL || entry->key != key)
		{
			cout << "No Element found at key " << key << endl;
			return;
		}
		while (entry->next != NULL)
		{
			prev = entry;
			entry = entry->next;
		}
		if (prev != NULL)
		{
			prev->next = entry->next;
		}
		delete entry;
		cout << "Element Deleted" << endl;
	}
	/*
	* Search Element at a key
	*/
	int Search(int key)
	{
		bool flag = false;
		int hash_val = HashFunc(key);
		HashNode* entry = htable[hash_val];
		while (entry != NULL)
		{
			if (entry->key == key)
			{
				cout << entry->value << " ";
				flag = true;
			}
			entry = entry->next;
		}
		if (!flag)
			return -1;
	}
};


int main(void)
{
	HashMap hash;
	int key;
	int array[BUFFER];
	srand((unsigned int)time(NULL));    // seed rand() with system time

	for (int i = 0; i < BUFFER; i++)   //random numbers stored into an array of size BUFFER
	{
		array[i]= (int)(rand() % 10000);  // limit data to 0 to 9999.
	}
	sort(array, array + BUFFER);
	for (int i = 0; i < BUFFER; i++)
	{
		hash.Insert(Hash(array[i]), array[i]);
	}
	return 0;
}
