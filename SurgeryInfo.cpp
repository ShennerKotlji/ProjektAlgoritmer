#include "SurgeryInfo.h"

SurgeryInfo::SurgeryInfo(int ID, const std::string & subSpecialty, int time)
{
	this->ID = ID;
	this->subSpecialty = subSpecialty;
	this->time;
}

SurgeryInfo::~SurgeryInfo()
{

}

int SurgeryInfo::getID() const
{
	return ID;
}

std::string SurgeryInfo::getSubSpecialty() const
{
	return subSpecialty;
}

int SurgeryInfo::getTime() const
{
	return time;
}