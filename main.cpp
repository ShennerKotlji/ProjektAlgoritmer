#include "OperatingRoom.h"
#include <fstream>
#include "SurgeryInfo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>
#include <stack>

using namespace std;

struct helpStruct
{
	int ID;
	std::string subSpecialty;
	int time;

	bool operator<(const helpStruct& other) const
	{
		return time < other.time;
	}
};
void BinPacking(List<SurgeryInfo> aList, std::priority_queue<helpStruct> &PQ, std::stack<helpStruct> &Q);
void readFromFile(List<SurgeryInfo> &aList, const std::string & fileName);
void Uppgift1(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ);
void Uppgift1del2(OperatingRoom *&roomArr, int amountOfORs, std::stack<helpStruct> &Q);


int main()

{
	std::priority_queue<helpStruct> PQ;
	std::stack<helpStruct> Q;

	clock_t start;
	clock_t end;

	std::cout << "Enter amount of operating rooms" << endl;
	int amountOfORs = 0;
	cin >> amountOfORs;
	cin.ignore();
	List<SurgeryInfo> aList;
	OperatingRoom * roomArr = nullptr;
	readFromFile(aList, "Operationer_1a.txt");
	readFromFile(aList, "Operationer_1b.txt");
	
	BinPacking(aList, PQ,Q);
	start = clock();
	Uppgift1(roomArr, amountOfORs, PQ);
	//Uppgift1del2(roomArr, amountOfORs, Q); 
	end = clock();
	float time = 1.0f*(end - start);/*/CLOCKS_PER_SEC;*/
	std::cout << time << endl;
	std::cin.get();
	return 0;

}

void readFromFile(List<SurgeryInfo> &aList, const std::string & fileName)
{

	ifstream fileIn(fileName);
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
			aList.insertAt(0, toAdd);
		}

	}

	/*int length = aList.length();
	SurgeryInfo*GetAll = new SurgeryInfo[length];
	aList.getAll(GetAll, length);
	for (int i = 0; i < length; i++)
	{
		cout << GetAll[i].getID()  <<  " " <<  GetAll[i].getSubSpecialty() << " " << GetAll[i].getTime() << endl;
	}

	delete[] GetAll;*/
}

void Uppgift1del2(OperatingRoom *&roomArr, int amountOfORs,  std::stack<helpStruct> &Q)
{
	
	helpStruct highest = Q.top();
	
	roomArr = new OperatingRoom[amountOfORs];
	int time = 0;

	//UPPGIFT 1
	for (int i = 0; i < amountOfORs; i++)
	{
		roomArr[i].setTime(08.00, 19.00);
	}

	bool addedToOR = false;
	bool keepRunning = false;
	int totlaTimeForall = roomArr[0].getTotalTime();
	while (keepRunning == false)
	{
		addedToOR = false;
		highest = Q.top();
		for (int i = 0; i < amountOfORs; i++)
		{
			if (roomArr[i].getTotalTime() >= highest.time)
			{
				roomArr[i].AddSurgeriesToOR(highest.ID, highest.subSpecialty, highest.time);
				roomArr[i].countTime(highest.time);
				Q.pop();
		
				highest = Q.top();
				i--;
				addedToOR = true;
			}

			if (addedToOR == false && Q.size() != 0)
			{
				Q.pop();

			}

			else if (Q.size() == 0)
			{
				keepRunning = true;
			}
	
		}
	}


	for (int i = 0; i < amountOfORs; i++)
	{
		cout << i << " " << endl;
		roomArr[i].PrintSchedule();
	}
}
void Uppgift1(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ)
{
	/*bool *Arr = new bool[amountOfORs]; 
	for (int i = 0; i < amountOfORs; i++)
	{
		Arr[i] = false; 
	}*/

	helpStruct highest = PQ.top();
	roomArr = new OperatingRoom[amountOfORs];
	int time = 0;

	//UPPGIFT 1
	for (int i = 0; i < amountOfORs; i++)
	{
		roomArr[i].setTime(08.00, 19.00);
	}

	bool addedToOR = false;
	bool keepRunning = false; 
	int totlaTimeForall = roomArr[0].getTotalTime();


	while(keepRunning == false)
	{
		addedToOR = false;
		highest = PQ.top();
		for (int i = 0; i < amountOfORs; i++)
		{
			if (roomArr[i].getTotalTime() >= highest.time)
			{
				roomArr[i].AddSurgeriesToOR(highest.ID, highest.subSpecialty, highest.time);
				roomArr[i].countTime(highest.time);
				PQ.pop();
				highest = PQ.top();
				i--;
				addedToOR = true;
			}

			if (addedToOR == false && PQ.size() != 0)
			{
				PQ.pop();
				
			}

			else if(PQ.size() == 0)
			{
				keepRunning = true;
			}
		/*	if (roomArr[i].getTotalTime() == totlaTimeForall)
			{
				Arr[i] = true; 
			}*/
		}
		
		
	}

	



	for (int i = 0; i < amountOfORs; i++)
	{
		cout << i << " " << endl;
		roomArr[i].PrintSchedule();
	}
	
		/*highest = PQ.top();
		cout << highest.time;*/
	
	
}


void BinPacking(List<SurgeryInfo> aList, std::priority_queue<helpStruct> &PQ, std::stack<helpStruct> &Q)
{
	int listLength = aList.length();
	for (int i = 0; i < listLength; i++)
	{

		helpStruct addToPQ = { aList.getAt(i).getID(), aList.getAt(i).getSubSpecialty(), aList.getAt(i).getTime() };
		Q.push(addToPQ);
		PQ.push(addToPQ);

	}
	/*helpStruct highest = PQ.top();*/
	// topInQueue = Q.front();
	

	//std::cout << highest.time << endl;
}
