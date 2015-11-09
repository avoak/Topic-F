/********************************************************************

Maximillian Brain
CSM20
Soundtrack.cpp
Compiling and Running

********************************************************************/
#include "Soundtrack.h"

soundtrack::soundtrack() :
	composer(""), title(""), label(""), catalogNumber(""), dateRecorded(""), dateReleased(1900)
{
} 

soundtrack::soundtrack(const string& theComposer, const string& theTitle, const string& theLabel, const string& theCatalogNumber,
	const string& theDateRecorded, const int& theDateReleased) :
	composer(theComposer), title(theTitle), label(theLabel), catalogNumber(theCatalogNumber),
	dateRecorded(theDateRecorded), dateReleased(theDateReleased)
{
	id = theLabel + theCatalogNumber;
}

soundtrack::soundtrack(const string& theComposer, const string& theTitle, const string& theLabel, const string& theCatalogNumber, 
	const string& theDateRecorded, const int& theDateReleased, const string& theid) :
	composer(theComposer), title(theTitle), label(theLabel), catalogNumber(theCatalogNumber),
	dateRecorded(theDateRecorded), dateReleased(theDateReleased), id(theid)
{
}

ostream &operator<<(ostream& out, const soundtrack& cd)
{
	out << cd.getComposer() << "   " << cd.getTitle() << "   " << cd.getLabel() << "   " << cd.getCatalogNumber() << "   " << cd.getDateRecorded() << "   " << cd.getDateReleased() << endl;
	return out;
} 

istream &operator>>(istream &in, soundtrack &val)
{
	string buff;
	string delim = " \t"; 

	getline(in, buff, '\n');

	// first 24 characters for composer
	string tempComposer;
	tempComposer = buff.substr(0, 24);
	string composer = tempComposer.substr(0, tempComposer.find_last_not_of(delim) + 1);
	val.setComposer(composer);

	// next 40 characters for title
	string tempTitle;
	tempTitle = buff.substr(24, 40);
	string title = tempTitle.substr(0, tempTitle.find_last_not_of(delim) + 1);
	val.setTitle(title);

	//  next 16 for label
	string tempLabel;
	tempLabel = buff.substr(64, 16);
	string label = tempLabel.substr(0, tempLabel.find_last_not_of(delim) + 1);
	val.setLabel(label);

	// 4 next 24 characters for catalogNumber
	string tempCatalogNumber;
	tempCatalogNumber = buff.substr(80, 24);
	string catalogNumber = tempCatalogNumber.substr(0, tempCatalogNumber.find_last_not_of(delim) + 1);
	val.setCatalogNumber(catalogNumber);

	//  next 8 characters for dateRecorded
	string tempDateRecorded;
	tempDateRecorded = buff.substr(104, 8);
	string dateRecorded = tempDateRecorded.substr(0, tempDateRecorded.find_last_not_of(delim) + 1);
	val.setDateRecorded(dateRecorded);

	// next 4 characters for dateReleased 
	int intBuff;
	intBuff = stoi(buff.substr(112, 4));
	val.setDateReleased(intBuff);
	
	val.setId(val.getLabel() + val.getCatalogNumber()); // sets the id
	
	return in;
} // end overloaded >> operator