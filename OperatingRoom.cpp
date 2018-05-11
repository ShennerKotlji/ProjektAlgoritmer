#include "OperatingRoom.h"
#include <iostream>

OperatingRoom::OperatingRoom(int nrOfOperatingRooms, float startTime, float endTime)
{
	this->nrOfOperatingRooms = nrOfOperatingRooms;
	this->OperatingRooms = new List<SurgeryInfo>[nrOfOperatingRooms];
	this->startTime = startTime;
	this->endTime = endTime;
	

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
void OperatingRoom::AddSurgeriesToList(int ID, std::string subSpecialty, int time)
{
	SurgeryInfo toAdd(ID, subSpecialty, time);
	OperatingRooms[0].insertAt(0, toAdd);

}
void OperatingRoom::PrintSchedule() const
{
	for (int i = 0; i < nrOfOperatingRooms; i++)
	{
		int length = OperatingRooms[i].length();
		if (length != 0)
		{
			{
				for (int k = 0; k < length; k++)
				{
					std::cout << "ID: " << OperatingRooms[i].getAt(k).getID() << "  Surgery: " << OperatingRooms[i].getAt(k).getSubSpecialty() << " Time: " << OperatingRooms[i].getAt(k).getTime() << std::endl;
				}
			}

			std::cout << "" << std::endl;
		}
	}
}
