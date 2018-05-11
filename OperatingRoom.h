#pragma once
#include "SurgeryInfo.h"
#include "List.h"

class OperatingRoom
{

public:
	OperatingRoom(int nrOfOperatingRooms= 0, float startTime = 0.0f, float endTime = 0.0f);
	~OperatingRoom();
	int getStartTime() const;
	int getEndTime() const;

	void setTimeForOR(float newStartTime, float newEndTime);
	void AddSurgeriesToList(int ID, std::string subSpecialty, int time);
	void PrintSchedule() const;





private:
	List<SurgeryInfo> * OperatingRooms;
	List<SurgeryInfo> Surgeries;
	int nrOfOperatingRooms;
	float startTime;
	float endTime; 


};
