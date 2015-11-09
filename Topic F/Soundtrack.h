/********************************************************************

Maximillian Brain
CSM20
Soundtrack.h
Compiling and Running

********************************************************************/

#ifndef _SOUND_TRACK
#define _SOUND_TRACK

#include <string>
#include <iostream>
#include <sstream>

#include "PrecondViolatedExcep.h"
using namespace std;

class soundtrack
{
	// Overloaded stream insertion and extraction operators
	friend std::ostream &operator<<(std::ostream &, const soundtrack &);
	friend std::istream &operator>>(std::istream&, soundtrack&);

private:
	string composer;
	string title;
	string label;
	string catalogNumber;
	string dateRecorded;
	string id;
	int dateReleased;

public:
	soundtrack();
	soundtrack(const string& theComposer, const string& theTitle, const string& theLabel,
		const string& theCatalogNumber, const string& theDateRecorded, const int& theDateReleased);
	soundtrack(const string& theComposer, const string& theTitle, const string& theLabel,
		const string& theCatalogNumber, const string& theDateRecorded, const int& theDateReleased, const string& theid);

	void setComposer(const string& theComposer) { composer = theComposer; }
	void setTitle(const string& theTitle) { title = theTitle; }
	void setLabel(const string& theLabel) { label = theLabel; }
	void setCatalogNumber(const string& theCatalogNumber) { catalogNumber = theCatalogNumber; }
	void setDateRecorded(const string& theDateRecorded) { dateRecorded = theDateRecorded; }
	void setDateReleased(const int& theDateReleased) { dateReleased = theDateReleased; }
	void setId(const string& theId) { id = theId; }

	string getComposer() const { return composer; }
	string getTitle() const { return title; }
	string getLabel() const { return label; }
	string getCatalogNumber() const { return catalogNumber; }
	string getDateRecorded() const { return dateRecorded; }
	string getId() const { return id; }
	int getDateReleased() const { return dateReleased; }

	bool operator==(const soundtrack& right) const{ return id == right.id; }
	bool operator>(const soundtrack& right) const { return id > right.id; }
	bool operator<(const soundtrack& right) const { return id < right.id; }

	bool operator==(const string& right) const { return right == id; }
	bool operator>(const string& right) const { return right > id; }
	bool operator<(const string& right) const { return right < id; }
}; // end soundtrack

#endif