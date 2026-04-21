/*
 * LedParam.cpp
 *
 *  Created on: Apr 21, 2026
 *      Author: mehdi
 */

#include <LedParam.h>

LedParam::LedParam(uint8_t id):
id(id),
colorON(ColorState::OFF),
colorOFF(ColorState::OFF),
currentColor(ColorState::OFF),
isBlinking(false),
period(60),
timerCounter(0),
callback(nullptr)
{
	// TODO Auto-generated constructor stub

}

LedParam::~LedParam() {
	// TODO Auto-generated destructor stub
}
void LedParam::setCallback(StateChangeCallback cb){
	callback=cb;
}
void LedParam::updateOutput()
{
	if(callback!=nullptr)
		callback(id,currentColor);
}

void LedParam::setPeriod(uint16_t pd)
{
	period=pd;
	if(timerCounter>=pd)
		timerCounter=0;
}

void LedParam::setPeriodMS(uint16_t ms)
{
    // Assuming 60fps = 16.67ms per frame
    int ticks = (ms * 60) / 1000;
    if (ticks < 1) ticks = 1;
    setPeriod(ticks);
}
void LedParam::setBlinking(ColorState stateon,ColorState stateoff)
{
	colorON=stateon;
	colorOFF=stateoff;
	if(isBlinking)
		currentColor=colorOFF;
	updateOutput();
}
void LedParam::setFixed(ColorState colorfixed)
{
	colorFixed=colorfixed;
	if(!isBlinking)
		currentColor=colorFixed;
	updateOutput();
}
void LedParam::startBlinking()
{
	isBlinking=true;
	timerCounter=0;
	currentColor=colorOFF;
	updateOutput();
}
void LedParam::stopBlinking()
{
	isBlinking=false;
	currentColor=colorFixed;
	updateOutput();
}
void LedParam::tick(){
	if(isBlinking)
	{
		timerCounter++;
		if(timerCounter>period)
		{
			timerCounter=0;
			if(currentColor==colorOFF)
				currentColor=colorON;
			else
				currentColor=colorOFF;
		}
	}
}
