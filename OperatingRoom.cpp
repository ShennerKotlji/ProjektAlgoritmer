#include "OperatingRoom.h"

OperatingRoom::OperatingRoom(int nrOfOperatingRooms)
{
	this->nrOfOperatingRooms = nrOfOperatingRooms;
	this->Surgeries = new List<SurgeryInfo>[nrOfOperatingRooms];
	this->startTime = 0;
	this->endTime = 0;

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

void setTimeForOR(int roomNr, float startTime, float endTime)
{
	
}
