/********************************************************************

Maximillian Brain
CSM20
TopicF.cpp
Compiling and Running

********************************************************************/

#pragma warning( disable: 4290 )

#include "Soundtrack.h"
#include "AVL.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readFromFile(vector<soundtrack> & soundtrackVector, AvlTree <soundtrack, string> soundtrackAVL, vector<string> uniqueSoundtrackKeys);
void sortDuplicates(vector<string>& soundtrackIDs, vector<soundtrack>& soundtrackVector, 
	AvlTree <soundtrack, string>& soundtrackAVL, vector<string> uniqueSoundtrackKeys);

void findDates(vector<string>& soundtrackIDs, vector<string>& matchingIDs);

int main()
{
	cout << "Create and populate AVL tree\n\n";
	AvlTree<soundtrack, string> soundtrackAVL;
	vector<soundtrack> soundtrackVector;
	vector<string> uniqueSoundtrackKeys;
	soundtrack tempSoundtrack;

	readFromFile(soundtrackVector, soundtrackAVL, uniqueSoundtrackKeys);

	cin.ignore(cin.rdbuf()->in_avail());
	cout << "************************************ Press Enter to continue  --> ";
	cin.ignore();

	cout << "Get item with key \"FSMBox 03 Disc 8\": \n\n";
	string tempKey = "FSMBox 03 Disc 8";

	bool success = soundtrackAVL.Retrieve(tempKey, tempSoundtrack);
	if (success)
		cout << "found " << tempSoundtrack << " with key " << tempKey << endl << endl;
	else
		cout << "No items found with key\"" << tempKey << "\"\n\n";


	cout << "\nGet item with key \"FSMBox 08 Disc 8\": \n\n";

	tempKey = "FSMBox 08 Disc 8";
	success = soundtrackAVL.Retrieve(tempKey, tempSoundtrack);
	if (success)
		cout << "found " << tempSoundtrack << " with key " << tempKey << endl << endl;
	else
		cout << "No items found with key\"" << tempKey << "\"\n\n";

	cin.ignore(cin.rdbuf()->in_avail());
	cout << "************************************ Press Enter to continue  --> ";
	cin.ignore();

	cout << "Listing of all items in the tree: (There are" << soundtrackAVL.Count() << "items in the table)\n";
	//cout << soundtrackAVL;


	cin.ignore(cin.rdbuf()->in_avail());
	cout << "************************************ Press Enter to continue  --> ";
	cin.ignore();

	cout << "\n\nList all soundtracks recorded in the 1950s:\n";
	vector<string> containsDates;
	findDates(uniqueSoundtrackKeys, containsDates);

	for (unsigned int i = 0; i < containsDates.size(); i++)
	{
		soundtrackAVL.Retrieve(containsDates[i], tempSoundtrack);
		cout << tempSoundtrack;
	}

	cin.ignore(cin.rdbuf()->in_avail());
	cout << "\n************************************ Press Enter to continue  --> ";
	cin.ignore();

	cout << "\nDelete all items with key \"FSM V8N11\":\n\n";

	tempKey = "FSM V8N1";
	soundtrackAVL.Retrieve(tempKey, tempSoundtrack);
	success = soundtrackAVL.Delete(tempKey);

	if (success)
	{
		cout << tempSoundtrack << "\nhas been deleted\n";
	}
	else
		cout << "NO items for \"FSM V8N11\"\n\n";

	cout << "\nAgain delete all items with key \"FSM V8N11\":\n\n";
	soundtrackAVL.Retrieve(tempKey, tempSoundtrack);
	success = soundtrackAVL.Delete(tempKey);

	if (success)
	{
		cout << tempSoundtrack << "\nhas been deleted\n";
	}
	else
		cout << "NO items for \"FSM V8N11\"\n\n";

	cin.ignore(cin.rdbuf()->in_avail());
	cout << "\n************************************ Press Enter to continue  --> ";
	cin.ignore();
	cout << "Listing of all items in the tree: (There are" << soundtrackAVL.Count() << "items in the table)\n";
	//cout << soundtrackAVL <<endl;

	cout << "\nProgram Ending \n";
	cin.ignore(cin.rdbuf()->in_avail());
	cout << "\nPress Enter to end --> ";
	cin.ignore();
}

void readFromFile(vector<soundtrack> & soundtrackVector, AvlTree <soundtrack, string> soundtrackAVL, vector<string> uniqueSoundtrackKeys)
{
	vector<string >soundtrackKeys;
	ifstream inputFile;
	string fileName = "Topic F Soundtrack.txt";
	inputFile.open(fileName);
	while (!inputFile.eof())
	{
		soundtrack* temp = new soundtrack;
		try
		{
			inputFile >> *temp;
			soundtrackVector.push_back(*temp);
			soundtrackKeys.push_back(temp->getId());
			sortDuplicates(soundtrackKeys, soundtrackVector, soundtrackAVL, uniqueSoundtrackKeys);
		}
		catch (exception e)
		{
			cout << e.what() << ", ignoring " << *temp << endl ;
		}
		delete temp;
		temp = nullptr;
	}
}

void sortDuplicates(vector<string>& soundtrackIDs, vector<soundtrack>& soundtrackVector, AvlTree <soundtrack, string>& soundtrackAVL,
	vector<string> uniqueSoundtrackKeys)
{
	bool unique = 1;
	for (unsigned  int i = 0; i < soundtrackIDs.size() - 1; i++) // gets latest element of soundtrackVector and checks it all previous ids
	{
		if (soundtrackVector[soundtrackVector.size() - 1].getId() == soundtrackIDs[i])
			unique = 0;
	}
	if (unique) // if it's unique insert it on to the AVL and insert the key into a unique key vector
	{
		soundtrackAVL.Insert(soundtrackVector[soundtrackVector.size() - 1]);
		uniqueSoundtrackKeys.push_back(soundtrackVector[soundtrackVector.size() - 1].getId());
	}
	else
		cout << soundtrackVector[soundtrackVector.size() - 1] << " is a duplicate \n";
}

void findDates(vector<string>& soundtrackIDs, vector<string>& matchingIDs)
{
	vector<string> dates = { "1950", "1951", "1952", "1953", "1954", "1955", "1956", "1956", "1957", "1958", "1959" };

	//checks each Id for the dates stated above and if it contains it pushes onto the matchingID vector

	for (unsigned int i = 0; i < soundtrackIDs.size(); i++) 
		for (unsigned int j = 0; j < dates.size(); j++)
			if (soundtrackIDs[i].find(dates[j]))
				matchingIDs.push_back(soundtrackIDs[i]);
}

