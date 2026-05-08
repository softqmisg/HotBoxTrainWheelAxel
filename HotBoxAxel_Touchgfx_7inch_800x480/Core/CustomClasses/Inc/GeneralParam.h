/*
 * GeneralParam.h
 *
 *  Created on: May 7, 2026
 *      Author: mehdi
 */

#ifndef CUSTOMCLASSES_SRC_GENERALPARAM_H_
#define CUSTOMCLASSES_SRC_GENERALPARAM_H_
#include <touchgfx/hal/Types.hpp>

class GeneralParam {
public:
	GeneralParam();
	virtual ~GeneralParam();
	void setLocoNum(uint16_t num);
	uint16_t getLocoNum(){return locoNum;}
	void setLanguage(bool isEN);
	bool getIsLanguageEN(){return isLanguageEn;}
	void setVolume(uint8_t vol);
	uint8_t getVolume(){return volume;}
	void setBrightness(uint8_t bri);
	uint8_t getBrightness(){return brightness;}
	void setDelayBetweenCarChange(uint32_t delay);
	uint32_t getDelayBetweenCarChange(){return delayBetweenCarChange; }
	void setDelayBetweenAutoHiding(uint32_t delay);
	uint32_t getDelayBetweenAutoHiding(){return delayBetweenAutoHiding;}
	void setDelayTurningOffLCD(uint32_t delay);
	uint32_t getDelayTurningOffLCD(){return delayTurningOffLCD;}

	void applyDefaults();

private:
	uint16_t locoNum;
	bool isLanguageEn;
	uint8_t volume;
	uint8_t brightness;
	uint32_t delayBetweenCarChange;
	uint32_t delayBetweenAutoHiding;
	uint32_t delayTurningOffLCD;

	const uint16_t defaultLocoNum=12345;
	const bool defaultIsLanguageEn=true;
	const uint8_t defaultVolume=5;		//
	const uint8_t defaultBrighness=10; //MAX-MIN:10~1
	const uint32_t defaultDelayBetweenCarChange=10000; //ms:MAX-MIN=20000~3000
	const uint32_t defaultDelayBetweenAutoHiding=10000;
	const uint32_t defaultDelayTurningOffLCD=0; //0=NEVER, MAX-MIN:100000-20000

};

#endif /* CUSTOMCLASSES_SRC_GENERALPARAM_H_ */
