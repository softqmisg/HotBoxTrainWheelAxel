/*
 * LedParam.cpp
 *
 *  Created on: Apr 21, 2026
 *      Author: mehdi
 */

#include <LedParam.h>

LedParam::LedParam(uint8_t id):
id(id),
//colorON(ColorState::OFF),
//colorOFF(ColorState::OFF),
currentColor(ColorState::COLORFIXED),
isBlinking(false),
periodOn(60),
periodOff(60),
currentMode(0),
timerCounter(0),
callback(nullptr)
{
	// TODO Auto-generated constructor stub
	updateOutput();
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

void LedParam::setPeriod(uint16_t pdon,uint16_t pdoff)
{
	periodOn=pdon;
	periodOff=pdoff;
	if(currentMode)
	{
		if(timerCounter>=pdon)
		{
			timerCounter=0;
		}
	}
	else
	{
		if(timerCounter>=pdoff)
			timerCounter=0;
	}
}

void LedParam::setPeriodMS(uint16_t pdmson,uint16_t pdmsoff)
{
    // Assuming 60fps = 16.67ms per frame
    int ticksOn = (pdmson * 60) / 1000;
    if (ticksOn < 1) ticksOn = 1;

    int ticksOff = (pdmsoff * 60) / 1000;
    if (ticksOff < 1) ticksOff= 1;


    setPeriod(ticksOn,ticksOff);
}
void LedParam::setFixed()
{
	if(!isBlinking)
		currentColor=ColorState::COLORFIXED;
	updateOutput();
}
void LedParam::startBlinking()
{
	isBlinking=true;
	timerCounter=0;
	currentMode=1;
	currentColor=ColorState::COLORBLINKOFF;
	updateOutput();
}
void LedParam::stopBlinking()
{
	isBlinking=false;
	currentColor=ColorState::COLORFIXED;
	updateOutput();
}
void LedParam::tick(){
	if(isBlinking)
	{
		timerCounter++;
		if(currentMode) //if(OnMode)
		{
			if(timerCounter>(int)periodOn)
			{
				timerCounter=0;
				currentColor=ColorState::COLORBLINKOFF;
				currentMode=0;
				updateOutput();
			}
		}
		else //if(OffMode)
		{
			if(timerCounter>(int)periodOff)
			{
				timerCounter=0;
				currentColor=ColorState::COLORBLINKON;
				currentMode=1;
				updateOutput();
			}

		}
	}
}
