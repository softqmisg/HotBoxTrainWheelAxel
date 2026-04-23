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
    struct Temp_t{
    	int16_t temperature;
    	TempState state;
    };

	Car();
	virtual ~Car();
	void setCarID(uint8_t carID);
	uint8_t getCarID();
	void setTemperature(uint8_t axelID,uint16_t temp,Car::TempState state);
	void setTemperature(uint8_t axelID,Temp_t tempAxel);
	Temp_t getTemperature(uint8_t axelID);

	void setShowDuration(uint16_t duration);
	void setShowDurationMS(uint16_t durationms);
	uint16_t getDuration();

private:
	uint8_t carID;
	Temp_t tempAxel[MAX_AXELNUM];
	Temp_t tempEnv;
	uint16_t showDuration;
};

#endif /* INC_CAR_H_ */
