/*
 * Car.cpp
 *
 *  Created on: Apr 21, 2026
 *      Author: mehdi
 */

#include <Car.h>

Car::Car():carID(0) {
	// TODO Auto-generated constructor stub
	for(int i=0;i<MAX_AXELNUM;i++)
	{
		tempAxel[i].temperature=0;
		tempAxel[i].state=Car::TempState::NORMAL;
	}
	tempEnv.temperature=0;
	tempEnv.state=Car::TempState::NORMAL;
}

Car::~Car() {
	// TODO Auto-generated destructor stub
}

void Car::setCarID(uint8_t carID){
	carID=carID;
}
uint8_t Car::getCarID()
{
	return carID;
}
void Car::setTemperature(uint8_t axelID,uint16_t temp,Car::TempState state)
{
	if(axelID<MAX_AXELNUM)
	{
		tempAxel[axelID].state=state;
		tempAxel[axelID].temperature=temp;
	}
	else if(axelID==MAX_AXELNUM)
	{
		tempEnv.state=state;
		tempEnv.temperature=temp;
	}


}
void Car::setTemperature(uint8_t axelID,Temp_t tempAxel)
{
	this->setTemperature(axelID,tempAxel.temperature,tempAxel.state);
}
Car::Temp_t Car::getTemperature(uint8_t axelID){
	if(axelID<MAX_AXELNUM)
		return tempAxel[axelID];
	else
		return tempEnv;
}

void Car::setShowDuration(uint16_t duration)
{
	showDuration=duration;
}
void Car::setShowDurationMS(uint16_t durationms)
{
    // Assuming 60fps = 16.67ms per frame
    uint16_t ticks = (durationms * 60) / 1000;
    if (ticks < 1) ticks = 1;
	showDuration=ticks;
}
uint16_t Car::getDuration()
{
	return showDuration;
}
