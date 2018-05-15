#pragma once
#include "SurgeryInfo.h"
#include "List.h"
#include <functional>
#include <queue>
#include <iostream>
#include <fstream>

class OperatingRoom
{

public:

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

	OperatingRoom(float startTime = 0.0f, float endTime = 0.0f);
	~OperatingRoom();
	int getStartTime() const;
	int getEndTime() const;

	void setTimeForOR(float newStartTime, float newEndTime);
	void AddSurgeriesToOR(int ID, std::string subSpecialty, int time);
	int getTotalTime() const; 
	void setTime(float start, float end); 
	
	void countTime(const int time);
	struct helpStruct BinPacking(List<SurgeryInfo>& aList, int &time) const;
	void PrintSchedule() ;



private:
	List<SurgeryInfo> ORoom;
	//int nrOfOperatingRooms;
	float startTime;
	float endTime; 
	int TimeLeft;
	struct helpStruct;

	/*struct helpStruct
	{
		int ID;
		std::string subSpecialty;
		int time;

		bool operator<(const helpStruct& other) const
		{
			return time < other.time;
		}
	};*/


};
