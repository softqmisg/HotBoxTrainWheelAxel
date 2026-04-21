/*
 * Car.h
 *
 *  Created on: Apr 21, 2026
 *      Author: mehdi
 */

#ifndef INC_CAR_H_
#define INC_CAR_H_
#include <touchgfx/hal/Types.hpp>
#define MAX_CARNUM	10
#define MAX_AXELNUM	8
class Car {
public:
    enum class TempState{NORMAL,ERROR};
    struct TempAxel_t{
    	int16_t temperature;
    	TempState state;
    };

	Car();
	virtual ~Car();
	void setCarID(uint8_t carID);
	uint8_t getCarID();
	void setAxelTemperature(uint8_t axelID,uint16_t temp,Car::TempState state);
	void setAxelTemperature(uint8_t axelID,TempAxel_t tempAxel);
	TempAxel_t getAxelTemperature(uint8_t axelID);


private:
	uint8_t carID;
	TempAxel_t tempAxel[MAX_AXELNUM];
};

#endif /* INC_CAR_H_ */
