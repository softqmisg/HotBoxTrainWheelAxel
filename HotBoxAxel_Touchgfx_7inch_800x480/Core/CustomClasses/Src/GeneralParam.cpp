/*
 * GeneralParam.cpp
 *
 *  Created on: May 7, 2026
 *      Author: mehdi
 */

#include "GeneralParam.h"
#include<texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Texts.hpp>
#include "tim.h"
extern TIM_HandleTypeDef htim3;

GeneralParam::GeneralParam():
locoNum(defaultLocoNum),
isLanguageEn(defaultIsLanguageEn),
volume(defaultVolume),
brightness(defaultBrighness),
delayBetweenCarChange(defaultDelayBetweenCarChange),
delayBetweenAutoHiding(defaultDelayBetweenAutoHiding),
delayTurningOffLCD(defaultDelayTurningOffLCD)
{
	// TODO Auto-generated constructor stub

}

GeneralParam::~GeneralParam() {
	// TODO Auto-generated destructor stub
}
void GeneralParam::setLocoNum(uint16_t num){
	locoNum=num;
}
void GeneralParam::setLanguage(bool isEN){
	isLanguageEn=isEN;
}
void GeneralParam::setVolume(uint8_t vol){
	volume=vol;
}
void GeneralParam::setBrightness(uint8_t bri){
	if(bri>10 ||bri<1) return;
	brightness=bri;
	uint32_t period=__HAL_TIM_GET_AUTORELOAD(&htim3);
	  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,period*brightness/10);
}
void GeneralParam::setDelayBetweenCarChange(uint32_t delay){
	delayBetweenCarChange=delay;
}
void GeneralParam::setDelayBetweenAutoHiding(uint32_t delay){
	delayBetweenAutoHiding=delay;
}
void GeneralParam::setDelayTurningOffLCD(uint32_t delay){
	delayTurningOffLCD=delay;
}

