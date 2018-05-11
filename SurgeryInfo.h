#pragma once
#include <string>
class SurgeryInfo

{

public:
	SurgeryInfo(int ID = -1, const std::string & subSpecialty = "", int time = -1);
	~SurgeryInfo();
	int getID() const;
	std::string getSubSpecialty() const;
	int getTime() const;

	


private:
	int ID;
	std::string subSpecialty;
	int time;


};
