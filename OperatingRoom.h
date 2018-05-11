#pragma once
#include "SurgeryInfo.h"
#include "List.h"

class OperatingRoom
{

public:
	OperatingRoom(int nrOfOperatingRooms);
	~OperatingRoom();
	int getStartTime() const;
	int getEndTime() const;

	void setTimeForOR(int roomNr, float startTime, float endTime);




private:
	List<SurgeryInfo> * Surgeries;
	int nrOfOperatingRooms;
	float startTime;
	float endTime; 


};
