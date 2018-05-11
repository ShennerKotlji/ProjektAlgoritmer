#include "OperatingRoom.h"
#include <fstream>
#include "SurgeryInfo.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readFromFile(OperatingRoom aList);

int main()

{

	OperatingRoom aList(1);
	readFromFile(aList);




	std::cin.get();
	return 0;

}

void readFromFile(OperatingRoom aList)
{

	ifstream fileIn("Operationer_1a.txt");
	if (fileIn.is_open())
	{
		int ID = 0;
		std::string subSpecialty;
		int time;
		std::string textLine;
		while (!fileIn.eof())
		{
			fileIn >> ID;
			fileIn.ignore();
			getline(fileIn, textLine);
			int pos = textLine.find(",");
			subSpecialty = textLine.substr(0, pos);
			string intAsString = textLine.substr(pos + 1);
			time = stoi(intAsString);
			SurgeryInfo toAdd(ID, subSpecialty, time);
			aList.AddSurgeriesToList(ID, subSpecialty, time);
		}

	}

	aList.PrintSchedule();

}

	
	