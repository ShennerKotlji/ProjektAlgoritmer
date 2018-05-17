#include "OperatingRoom.h"
#include <iostream>
#include <queue>
#include <functional>

OperatingRoom::OperatingRoom(float startTime, float endTime)
{
	
	this->startTime = startTime;
	this->endTime = endTime;
	this->TimeLeft = (this->endTime - this->startTime) * 60;;
	

}
OperatingRoom::~OperatingRoom()
{

}

int OperatingRoom::getStartTime() const
{
	return startTime;
}
int OperatingRoom::getEndTime() const
{
	return endTime;
}

void OperatingRoom::setTimeForOR(float newStartTime, float newEndTime)
{
	this->startTime = newStartTime;
	this->endTime = newEndTime;
}
void OperatingRoom::AddSurgeriesToOR( int ID, std::string subSpecialty, int time)
{
	SurgeryInfo toAdd(ID, subSpecialty, time);
	ORoom.insertAt(0, toAdd);

}
void OperatingRoom::PrintSchedule() 
{
	int length = ORoom.length();
		if (length != 0)
		{
			SurgeryInfo * GetAll = new SurgeryInfo[length];
			ORoom.getAll(GetAll, length); 
			for (int i = 0; i < length; i++)
			{
				std::cout << "ID: " << GetAll[i].getID() << " " << "Surgery : " << GetAll[i].getSubSpecialty() << " Time :" <<  GetAll[i].getTime() << std::endl;
			}
			std::cout << "" << std::endl;
			delete[] GetAll;
		}
	
		
}

OperatingRoom::helpStruct OperatingRoom::BinPacking(List<SurgeryInfo> &aList, int &time) const
{
	std::priority_queue<helpStruct> PQ;
	int listLength = aList.length();
	for (int i = 0; i < listLength; i++)
	{
		
		helpStruct addToPQ = { aList.getAt(i).getID(), aList.getAt(i).getSubSpecialty(), aList.getAt(i).getTime() };
		PQ.push(addToPQ);

	}


	helpStruct highest = PQ.top();
	 
//	std::cout <<"\n"<< highest.ID << " " << highest.subSpecialty << " " << highest.time << std::endl;
	PQ.pop(); 
	highest.ID, highest.subSpecialty, highest.time;
	//std::cout << "\n" << highest.ID << " " << highest.subSpecialty << " " << highest.time << std::endl;


	return highest;

}

int OperatingRoom::getTotalTime() const
{
	return this->TimeLeft; 
}

void OperatingRoom::countTime(const int time)
{
	TimeLeft = TimeLeft - time;
}

void OperatingRoom::setTime(const float start, const float end)
{
	this->startTime = start;
	this->endTime = end;
	this->TimeLeft = (end - start) * 60;
}
