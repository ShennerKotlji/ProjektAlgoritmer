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
void PrintNotScheduled(List<SurgeryInfo> SurgeriesNotScheduled);

void Uppgift1(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ, List<SurgeryInfo> &SurgeriesNotScheduled);
void Uppgift1Stack(OperatingRoom *&roomArr, int amountOfORs, std::stack<helpStruct> &Q, List<SurgeryInfo> &SurgeriesNotScheduled);
void Uppgift2(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ, List<SurgeryInfo> &SurgeriesNotScheduled, int day);
void Uppgift2Stack(OperatingRoom *&roomArr, int amountOfORs, std::stack<helpStruct> &Q, List<SurgeryInfo> &SurgeriesNotScheduled, int day);




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

	////Uppgift1
	//readFromFile(aList, "Operationer_1a.txt");
	//readFromFile(aList, "Operationer_1b.txt");
	//AddToPQ(aList, PQ,Q);
	//start = clock();
	////Uppgift1(roomArr, amountOfORs, PQ,  SurgeriesNotScheduled);
	//Uppgift1Stack(roomArr, amountOfORs, Q, SurgeriesNotScheduled);
	//end = clock();
	////TIME
	//float time = 1.0f*(end - start)/CLOCKS_PER_SEC;
	//std::cout << time << endl;
	//std::cout << "" << endl;
	//PrintNotScheduled(SurgeriesNotScheduled);
	



	//UPPGIFT 2 MED PQ - MAX OCH MIN HEAP
	//readFromFile(aList,"Operationer_2.txt");
	//cout << "\nFor how many days do you want to book the OR?" << endl; 
	//int Days; 
	//cin >> Days; 
	//cin.ignore(); 

	//AddToPQ(aList, PQ, Q);
	//Uppgift2(roomArr, amountOfORs, PQ, SurgeriesNotScheduled,1);
	//PrintNotScheduled(SurgeriesNotScheduled);
	//for (int i = 0; i < Days - 1; i++)
	//{
	//	AddToPQ(SurgeriesNotScheduled, PQ, Q);
	//	for (int g = 0; g < SurgeriesNotScheduled.length(); g++)
	//	{
	//		SurgeriesNotScheduled.removeAt(g);
	//		g--;
	//	}
	//	Uppgift2(roomArr, amountOfORs, PQ, SurgeriesNotScheduled,i+2);
	//	PrintNotScheduled(SurgeriesNotScheduled);
	//}
	//	
	



	////UPPGIFT 2 med STACK
	/*readFromFile(aList, "Operationer_2.txt");
	cout << "\nFor how many days do you want to book the OR?" << endl;
	int Days;
	cin >> Days;
	cin.ignore();

	AddToPQ(aList, PQ, Q);
	Uppgift2Stack(roomArr, amountOfORs, Q, SurgeriesNotScheduled,1);
	PrintNotScheduled(SurgeriesNotScheduled);
	for (int i = 0; i < Days - 1; i++)
	{
		AddToPQ(SurgeriesNotScheduled, PQ, Q);
		for (int g = 0; g < SurgeriesNotScheduled.length(); g++)
		{
			SurgeriesNotScheduled.removeAt(g);
			g--;
		}
		Uppgift2Stack(roomArr, amountOfORs, Q, SurgeriesNotScheduled, i + 2);
		PrintNotScheduled(SurgeriesNotScheduled);
	}*/

	


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

}

void Uppgift1Stack(OperatingRoom *&roomArr, int amountOfORs,  std::stack<helpStruct> &Q, List<SurgeryInfo>& SurgeriesNotScheduled)
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

				if (Q.size() == 0)
				{
					i = amountOfORs;
					keepRunning = true;
				}
				else
				{
					highest = Q.top();
					i--;
					addedToOR = true;
				}
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

	for (int i = 0; i < amountOfORs; i++)
	{
		cout << "Operating Room " << i + 1 << endl;
		roomArr[i].PrintSchedule();
	}
	delete [] roomArr;
}
void Uppgift1(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ, List<SurgeryInfo> &SurgeriesNotScheduled)
{

	helpStruct highest = PQ.top();
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
				if (PQ.size() == 0)
				{
					i = amountOfORs;
					keepRunning = true;
				}
				else
				{
					highest = PQ.top();
					i--;
					addedToOR = true;
				}
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
		cout << "Operating Room " << i + 1 << endl;
		roomArr[i].PrintSchedule();
	}

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
}

void Uppgift2(OperatingRoom *&roomArr, int amountOfORs, std::priority_queue<helpStruct> &PQ, List<SurgeryInfo> &SurgeriesNotScheduled, int day)
{
	roomArr = new OperatingRoom[amountOfORs];
	helpStruct highest = PQ.top();
	int time = 0;
	
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

				if (PQ.size() == 0)
				{
					i = amountOfORs;
					keepRunning = true;
				}
				else
				{
					highest = PQ.top();
					i--;
					addedToOR = true;
				}
				
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

	cout << "DAY: " << day << endl;
	for (int i = 0; i < amountOfORs; i++)
	{
		cout << "Operating Room " << i+1 << endl;
		roomArr[i].PrintSchedule();
	}

	delete[] roomArr;

}

void PrintNotScheduled(List<SurgeryInfo> SurgeriesNotScheduled)
{
	if (SurgeriesNotScheduled.length() != 0)
	{
		int length = SurgeriesNotScheduled.length();
		SurgeryInfo* GetSurgeries = new SurgeryInfo[length];
		SurgeriesNotScheduled.getAll(GetSurgeries, length);
		cout << "SURGERIES NOT SCHEDULED" << endl;
		cout << "Amount of surgeries " << length << endl;
		for (int i = 0; i < length; i++)
		{
			cout << GetSurgeries[i].getID() << " " << GetSurgeries[i].getSubSpecialty() << " " << GetSurgeries[i].getTime() << endl;
		}

		delete[] GetSurgeries;
	}

	else
	{
		cout << "All surgeries was succesfully booked to the available OR:s " << endl;
	}

}

void Uppgift2Stack(OperatingRoom *&roomArr, int amountOfORs, std::stack<helpStruct> &Q, List<SurgeryInfo> &SurgeriesNotScheduled, int day)
{
	roomArr = new OperatingRoom[amountOfORs];
	helpStruct highest = Q.top();
	int time = 0;

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

	bool addedToOR = false;
	bool keepRunning = false;
	int countFilled = 0;

	while (keepRunning == false)
	{
		highest = Q.top();
		countFilled = 0;
		addedToOR = false;
		for (int i = 0; i < amountOfORs; i++)
		{
			if (roomArr[i].getTotalTime() >= highest.time)
			{
				roomArr[i].AddSurgeriesToOR(highest.ID, highest.subSpecialty, highest.time);
				roomArr[i].countTime(highest.time);
				Q.pop();

				if (Q.size() == 0)
				{
					i = amountOfORs;
					keepRunning = true;
				}
				else
				{
					highest = Q.top();
					i--;
					addedToOR = true;
				}

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

	}

	cout << "DAY: " << day << endl;
	for (int i = 0; i < amountOfORs; i++)
	{
		cout << "Operating Room " << i + 1 << endl;
		roomArr[i].PrintSchedule();
	}

	delete[] roomArr;
}
