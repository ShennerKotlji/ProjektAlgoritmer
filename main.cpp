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
void AddToPQ(List<SurgeryInfo> aList, std::priority_queue<helpStruct> &PQ, std::stack<helpStruct> &Q);
void readFromFile(List<SurgeryInfo> &aList, const std::string & fileName);
void Uppgift1(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ, List<SurgeryInfo> &SurgeriesNotScheduled);
void Uppgift1del2(OperatingRoom *&roomArr, int amountOfORs, std::stack<helpStruct> &Q, List<SurgeryInfo> &SurgeriesNotScheduled);
void Uppgift2(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ, List<SurgeryInfo> &SurgeriesNotScheduled, bool k);
void resetArr(OperatingRoom*&roomArr,  int amountOfORs);


int main()

{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::priority_queue<helpStruct> PQ;
	std::stack<helpStruct> Q;

	clock_t start;
	clock_t end;


	std::cout << "Enter amount of operating rooms" << endl;
	int amountOfORs = 0;
	cin >> amountOfORs;
	cin.ignore();
	List<SurgeryInfo> aList;
	List<SurgeryInfo> SurgeriesNotScheduled;
	OperatingRoom * roomArr = nullptr;

	//Uppgift1
	//readFromFile(aList, "Operationer_1a.txt");
	//readFromFile(aList, "Operationer_1b.txt");
	//AddToPQ(aList, PQ,Q);
	//start = clock();
	//Uppgift1(roomArr, amountOfORs, PQ,  SurgeriesNotScheduled);
	////Uppgift1del2(roomArr, amountOfORs, Q, SurgeriesNotScheduled);
	//end = clock();
	////TIME
	//float time = 1.0f*(end - start)/CLOCKS_PER_SEC;
	//std::cout << time << endl;
	//std::cout << "" << endl;
	//// NOT SCHEDULED SURGERIES
	//int length = SurgeriesNotScheduled.length();
	//SurgeryInfo* GetSurgeries = new SurgeryInfo[length];
	//SurgeriesNotScheduled.getAll(GetSurgeries, length);
	//cout << "SURGERIES NOT SCHEDULED" << endl;
	//cout << length << endl;
	//for (int i = 0; i < length; i++)
	//{
	//	cout << GetSurgeries[i].getID() << " " << GetSurgeries[i].getSubSpecialty() << " " << GetSurgeries[i].getTime() << endl;
	//}
	//std::cin.get();


	//UPPGIFT 2
	readFromFile(aList,"Operationer_2.txt");
	cout << "\nFor how many days do you want to book the OR?" << endl; 
	int Days; 
	cin >> Days; 
	cin.ignore(); 

	bool k = true; 
	AddToPQ(aList, PQ, Q);
		cout << "Day: 1" << endl;
		Uppgift2(roomArr, amountOfORs, PQ, SurgeriesNotScheduled,k);
		AddToPQ(SurgeriesNotScheduled, PQ, Q);
		
		for (int i = 0; i < SurgeriesNotScheduled.length(); i++)
		{
			SurgeriesNotScheduled.removeAt(i);
			i--;
		}
	

		cout << "Day: 2" << endl;
		//OperatingRoom* newArr = nullptr;
		Uppgift2(roomArr, amountOfORs, PQ, SurgeriesNotScheduled,k);
	

	// NOT SCHEDULED SURGERIES
	int length = SurgeriesNotScheduled.length();
	SurgeryInfo* GetSurgeries = new SurgeryInfo[length];
	SurgeriesNotScheduled.getAll(GetSurgeries, length);
	cout << "SURGERIES NOT SCHEDULED" << endl;
	cout << length << endl;
	for (int i = 0; i < length; i++)
	{
		cout << GetSurgeries[i].getID() << " " << GetSurgeries[i].getSubSpecialty() << " " << GetSurgeries[i].getTime() << endl;
	}

	delete[] GetSurgeries;
	cin.get();
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

void Uppgift1del2(OperatingRoom *&roomArr, int amountOfORs,  std::stack<helpStruct> &Q, List<SurgeryInfo>& SurgeriesNotScheduled)
{
	
	helpStruct highest = Q.top();
	roomArr = new OperatingRoom[amountOfORs];
	int time = 0;

	for (int i = 0; i < amountOfORs; i++)
	{
		roomArr[i].setTime(08.00, 19.00);
	}

	bool addedToOR = false;
	bool keepRunning = false;
	int countFilled = 0;

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

		}
			if (addedToOR == false && Q.size() != 0)
			{
				SurgeryInfo add(highest.ID, highest.subSpecialty, highest.time);
				SurgeriesNotScheduled.insertAt(0, add);
				Q.pop();

			}

			if (Q.size() == 0)
			{
				keepRunning = true;
			}
	
		

		for (int i = 0; i < amountOfORs; i++)
		{
			if (roomArr[i].getTotalTime() == 0)
			{
				countFilled++;
			}
		}

		if (countFilled == amountOfORs)
		{
			keepRunning = true;
		}

	}

	/*for (int i = 0; i < amountOfORs; i++)
	{
		cout << i << " " << endl;
		roomArr[i].PrintSchedule();
	}*/

	delete [] roomArr;
}
void Uppgift1(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ, List<SurgeryInfo> &SurgeriesNotScheduled)
{

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
	int countFilled = 0;

	while (keepRunning == false)
	{
		highest = PQ.top();
		countFilled = 0;
		addedToOR = false;
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

		}
			if (addedToOR == false && PQ.size() != 0)
			{
				SurgeryInfo add(highest.ID, highest.subSpecialty, highest.time);
				SurgeriesNotScheduled.insertAt(0, add);
				PQ.pop();

			}

			if (PQ.size() == 0)
			{
				keepRunning = true;
			}

		
		/*for (int i = 0; i < amountOfORs; i++)
		{
			if (roomArr[i].getTotalTime() == 0)
			{
				countFilled++;
			}
		}

		if (countFilled == amountOfORs)
		{
			keepRunning = true;
		}*/
	
	}

	/*for (int i = 0; i < amountOfORs; i++)
	{
		cout << i << " " << endl;
		roomArr[i].PrintSchedule();
	}*/
	
		/*highest = PQ.top();
		cout << highest.time;*/
	delete[] roomArr;
	
}

void AddToPQ(List<SurgeryInfo> aList, std::priority_queue<helpStruct> &PQ, std::stack<helpStruct> &Q)
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

void Uppgift2(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ, List<SurgeryInfo> &SurgeriesNotScheduled, bool k)
{
	roomArr = new OperatingRoom[amountOfORs];
	helpStruct highest = PQ.top();
	int time = 0;
	if(k == true)
	{
		for (int i = 0; i < amountOfORs; i++)
		{
		float start = 0;
		float end = 0;
		cout << "\nEnter the start time for Operation room " << i + 1 << endl;
		cin >> start;
		cin.ignore();
		cout << "\nEnter the end time for Operation room " << i + 1 << endl;
		cin >> end;
		cin.ignore();
		roomArr[i].setTime(start, end);
		}
	}


	bool addedToOR = false;
	bool keepRunning = false;
	int countFilled = 0;

	while (keepRunning == false)
	{
		highest = PQ.top();
		countFilled = 0;
		addedToOR = false;
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

		}
		if (addedToOR == false && PQ.size() != 0)
		{
			SurgeryInfo add(highest.ID, highest.subSpecialty, highest.time);
			SurgeriesNotScheduled.insertAt(0, add);
			PQ.pop();
		}

		if (PQ.size() == 0)
		{
			keepRunning = true;
		}

	}

	for (int i = 0; i < amountOfORs; i++)
	{
	cout << i << " " << endl;
	roomArr[i].PrintSchedule();
	}

	delete[] roomArr;

}
void resetArr(OperatingRoom*&roomArr, int amountOfORs)
{

}