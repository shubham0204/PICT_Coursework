/*
Name: Shubham Panchal
Roll no: 21356 - G3
Consider telephone book database of N clients. Make use of a hash
table implementation to quickly look up client’s telephone number.
Make use of two collision handling techniques and compare them using
number of comparisons required to find a set of telephone numbers
(Note: Use linear probing with replacement and without replacement)
 */

#include <iostream>
#include <ios>
#include <cstring>
using namespace std;

// Represents an entry in the HashTable
// Each key will be mapped to a Record
class Record
{

	string clientName;
	int telephone;

public:
	Record()
	{
		// Created empty record with default values
		clientName = "----";
		telephone = 0;
	}

	Record(string name, int telephone)
	{
		clientName = name;
		this->telephone = telephone;
	}

	void printRecord()
	{
		cout.width(20);
		cout << clientName << " ";
		cout.width(20);
		cout << telephone << "\n";
	}

	bool isEmpty()
	{
		// Check if current record is default or populated
		return telephone == 0;
	}

	friend class HashTable;
};

class HashTable
{

	int tableSize;
	Record *records;

	// Hash function which maps clientName to a unique integer
	// Defined by hash( clientName ) = SUM mod TABLESIZE
	// where  SUM -> Sum of all ASCII values of chars in clientName
	//        TABLESIZE -> Size of the HashTable
	int hash(string clientName)
	{
		int asciiSum = 0;
		for (int i = 0; i < clientName.length(); i++)
		{
			asciiSum += int(clientName[i]);
		}
		return asciiSum % tableSize;
	}

	bool checkOriginal(int index)
	{
		return hash(records[index].clientName) == index;
	}

public:
	HashTable(int tableSize)
	{
		this->tableSize = tableSize;
		records = new Record[tableSize];
	}

	void createTable()
	{
		for (int i = 0; i < (this->tableSize); i++)
		{
			records[i] = Record();
		}
	}

	void displayTable()
	{
		cout.width(20);
		cout << "Client Name  ";
		cout.width(20);
		cout << "Telephone  \n";
		for (int i = 0; i < (this->tableSize); i++)
		{
			cout << i << " ";
			records[i].printRecord();
		}
	}

	void insertRecordNotReplacement(Record newRecord)
	{
		int index = hash(newRecord.clientName);
		cout << index << "\n";
		if (records[index].isEmpty())
		{
			records[index] = newRecord;
		}
		else
		{
			// Handle Collision with linear probing technique
			// Increment a counter `currentIndex` which searchs for the
			// next empty record
			// Chaining without replacement
			cout << "Collision occurred at loc=" << index << " \n";
			int currentIndex = index;
			while (!records[currentIndex].isEmpty())
			{
				currentIndex = (currentIndex + 1) % tableSize;
			}
			records[currentIndex] = newRecord;
		}
	}

	void insertRecordReplacement(Record newRecord)
	{
		int index = hash(newRecord.clientName);
		if (records[index].isEmpty())
		{
			// If location at `index` is empty, place record
			records[index] = newRecord;
		}
		else
		{
			cout << "Collision occurred at loc=" << index << " \n";
			// Check if record at `index` belongs to that position
			if (checkOriginal(index))
			{
				// The record belongs to `index`, newRecord will be placed at the next
				// empty location
				int currentIndex = index;
				while (!records[currentIndex].isEmpty())
				{
					currentIndex = (currentIndex + 1) % tableSize;
				}
				records[currentIndex] = newRecord;
			}
			else
			{
				// The record does not belong to `index`, add `newRecord` to `index`
				// and place `existingRecord` to next empty location
				Record existingRecord = records[index];
				records[index] = newRecord;
				int currentIndex = index;
				while (!records[currentIndex].isEmpty())
				{
					currentIndex = (currentIndex + 1) % tableSize;
				}
				records[currentIndex] = existingRecord;
			}
		}
	}

	void searchRecord(string clientName)
	{
		int index = hash(clientName);
		int numComparisons = 1;
		if (records[index].clientName == clientName)
		{
			records[index].printRecord();
		}
		else
		{
			// Search sequentially in next locations
			// and maintain a count for number of comparisons
			int currentIndex = index;
			int passes = 0;
			while ((records[currentIndex].clientName != clientName) && passes != tableSize)
			{
				currentIndex = (currentIndex + 1) % tableSize;
				passes++;
				numComparisons++;
			}
			if (passes != tableSize)
			{
				records[currentIndex].printRecord();
			}
			else
			{
				cout << "No record found for " << clientName << "\n";
			}
		}
		cout << "No. of comparisons are: " << numComparisons << "\n";
	}
};

int main()
{

	HashTable table(10);
	table.createTable();
	table.insertRecordNotReplacement(Record("abcd", 10002));
	table.insertRecordNotReplacement(Record("zdfg", 10003));
	table.insertRecordNotReplacement(Record("asdf", 10004));
	table.insertRecordNotReplacement(Record("dbca", 10005));
	table.insertRecordNotReplacement(Record("qwer", 10006));
	table.insertRecordNotReplacement(Record("rtyu", 10006));
	table.insertRecordNotReplacement(Record("ergh", 10006));
	table.insertRecordNotReplacement(Record("fghj", 10006));
	table.insertRecordNotReplacement(Record("zasd", 10006));
	table.insertRecordNotReplacement(Record("dfgh", 10006));
	table.displayTable();
	table.searchRecord("abcd");
	table.searchRecord("zdfg");
	table.searchRecord("asdf");
	table.searchRecord("dbca");
	table.searchRecord("qwer");
	table.searchRecord("rtyu");
	table.searchRecord("ergh");
	table.searchRecord("fghj");
	table.searchRecord("zasd");
	table.searchRecord("dfgh");

	HashTable table2(10);
	table2.createTable();
	table2.insertRecordReplacement(Record("abcd", 10002));
	table2.insertRecordReplacement(Record("zdfg", 10003));
	table2.insertRecordReplacement(Record("asdf", 10004));
	table2.insertRecordReplacement(Record("dbca", 10005));
	table2.insertRecordReplacement(Record("qwer", 10006));
	table2.insertRecordReplacement(Record("rtyu", 10006));
	table2.insertRecordReplacement(Record("ergh", 10006));
	table2.insertRecordReplacement(Record("fghj", 10006));
	table2.insertRecordReplacement(Record("zasd", 10006));
	table2.insertRecordReplacement(Record("dfgh", 10006));
	table2.displayTable();
	table2.searchRecord("abcd");
	table2.searchRecord("zdfg");
	table2.searchRecord("asdf");
	table2.searchRecord("dbca");
	table2.searchRecord("qwer");
	table2.searchRecord("rtyu");
	table2.searchRecord("ergh");
	table2.searchRecord("fghj");
	table2.searchRecord("zasd");
	table2.searchRecord("dfgh");

	return 0;
}
