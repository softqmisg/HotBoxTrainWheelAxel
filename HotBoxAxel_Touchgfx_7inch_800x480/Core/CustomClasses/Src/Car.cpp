/*
 * Car.cpp
 *
 *  Created on: Apr 21, 2026
 *      Author: mehdi
 */

#include "Car.h"

Car::Car():carID(0) {
	// TODO Auto-generated constructor stub
	for(int i=0;i<MAX_SENSORNUM;i++)
	{
		sensor[i].temperature=0;
		sensor[i].state=Car::TempState::NORMAL;
		sensor[i].priority=1;
	}

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
void Car::setTemperature(uint8_t sensorID,uint16_t temp,Car::TempState state)
{
	if(sensorID<MAX_SENSORNUM)
	{
		sensor[sensorID].state=state;
		sensor[sensorID].temperature=temp;
	}
}
void Car::setTemperature(uint8_t sensorID,Sensor_t temperature)
{
	this->setTemperature(sensorID,temperature.temperature,temperature.state);
}
Car::Sensor_t Car::getTemperature(uint8_t sensorID){
	if(sensorID<MAX_SENSORNUM)
		return sensor[sensorID];
}
void Car::setPriority(uint8_t sensorID,uint8_t prio)
{
	sensor[sensorID].priority=prio;
}
uint8_t Car::getPriority(uint8_t sensorID)
{
	return sensor[sensorID].priority;
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
