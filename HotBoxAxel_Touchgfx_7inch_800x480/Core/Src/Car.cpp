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
void Car::setAxelTemperature(uint8_t axelID,uint16_t temp,Car::TempState state)
{
	tempAxel[axelID].state=state;
	tempAxel[axelID].temperature=temp;

}
void Car::setAxelTemperature(uint8_t axelID,TempAxel_t tempAxel)
{
	this->setAxelTemperature(axelID,tempAxel.temperature,tempAxel.state);
}
Car::TempAxel_t Car::getAxelTemperature(uint8_t axelID){
	return tempAxel[axelID];
}
