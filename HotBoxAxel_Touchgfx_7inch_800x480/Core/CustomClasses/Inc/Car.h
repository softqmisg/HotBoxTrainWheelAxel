/*
 * Car.h
 *
 *  Created on: Apr 21, 2026
 *      Author: mehdi
 */

#ifndef INC_CAR_H_
#define INC_CAR_H_
#include <touchgfx/hal/Types.hpp>
#include "Utility.h"

class Car {
public:
    enum class TempState{NORMAL,ERROR};
    struct Sensor_t{
    	int16_t temperature;
    	TempState state;
    	uint8_t priority; //1=low,2=med,3=high
    };

	Car();
	virtual ~Car();
	void setCarID(uint8_t carID);
	uint8_t getCarID();
	void setTemperature(uint8_t sensorID,uint16_t temp,Car::TempState state);
	void setTemperature(uint8_t sensorID,Sensor_t temperature);
	Sensor_t getTemperature(uint8_t sensorID);

	void setPriority(uint8_t sensorID,uint8_t prio);
	uint8_t getPriority(uint8_t sensorID);

	void setShowDuration(uint16_t duration);
	void setShowDurationMS(uint16_t durationms);
	uint16_t getDuration();

private:
	uint8_t carID;
	Sensor_t sensor[MAX_SENSORNUM];
	uint16_t showDuration;
};

#endif /* INC_CAR_H_ */
