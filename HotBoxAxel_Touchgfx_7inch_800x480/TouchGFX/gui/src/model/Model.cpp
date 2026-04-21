#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include  "main.h"
#include <stdlib.h>
#include "Utility.h"

extern RTC_HandleTypeDef hrtc;
Model::Model() :
modelListener(0),
tickCounter(0),
refreshingMainEnabled(false),
hours(0),
minutes(0),
seconds(0),
day(1),
month(1),
year(2000),
calenderType(CalenderType::GEORGIAN),
envTemperature(0),
carNumber(0),
ledMain(0),
ledAlarm(1),
ledComm(2)
{
	for(int i=0;i<MAX_CARNUM;i++)
	{
		cars[i].setCarID(i);
		for(int axel=0;axel<MAX_AXELNUM;axel++)
			cars[i].setAxelTemperature(axel,0,Car::TempState::NORMAL);
	}

	ledMain.setCallback([this](int ledId,LedParam::ColorState state){
		updateLed(ledId,state);
	});
	ledAlarm.setCallback([this](int ledId,LedParam::ColorState state){
		updateLed(ledId,state);
	});
	ledComm.setCallback([this](int ledId,LedParam::ColorState state){
		updateLed(ledId,state);
	});
}

void Model::tick()
{
    // Called periodically by the framework
		ledMain.tick();
		ledAlarm.tick();
		ledComm.tick();

	    tickCounter++;
	    // Update clock every second (60 ticks = 1 second at 60 FPS)
	    if (tickCounter >= 60)
	    {
	        tickCounter = 0;
	 	   if (refreshingMainEnabled)
	 	   {
	 		   updateRTC();  // Read from hardware RTC
	 		   updateEnvTemperature();
	 	   }
 		   updateAxelTemperature(carNumber);

	    }
}
//Manage Time/Date
void Model::updateRTC(){
	readHardwareRTC();
	if(modelListener!=nullptr)
	{
		modelListener->timeUpdated(hours, minutes, seconds);
		modelListener->dateUpdated(day, month, year);
	}
}
void Model::readHardwareRTC(){
	   RTC_TimeTypeDef sTime;
	    RTC_DateTypeDef sDate;

	    // Read time and date from STM32 RTC
	    if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK)
	    {
	        // Must call GetDate to unlock the RTC
	        HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	        hours = sTime.Hours;
	        minutes = sTime.Minutes;
	        seconds = sTime.Seconds;
	        day = sDate.Date;
	        month = sDate.Month;
	        year = sDate.Year + 2000;  // RTC typically returns year 0-99
	    }
}
void Model::setRTCTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    RTC_TimeTypeDef sTime;

    sTime.Hours = hours;
    sTime.Minutes = minutes;
    sTime.Seconds = seconds;
    sTime.SubSeconds = 0;
    sTime.TimeFormat = RTC_HOURFORMAT_24;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    // Write to hardware RTC
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    {
        // Handle error
        Error_Handler();
    }

    // Update local variables
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;

    // Notify listeners
    if (modelListener!=nullptr)
    {
    	modelListener->timeUpdated(hours, minutes, seconds);
    }
}
void Model::setRTCDate(uint8_t day, uint8_t month, uint16_t year)
{

    RTC_DateTypeDef sDate;

    sDate.Date = day;
    sDate.Month = month;
    sDate.Year = year-2000;  // RTC typically returns year 0-99
    sDate.WeekDay=Utility::getDayOfWeek(year, month, day);
    // Write to hardware RTC
    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
        // Handle error
        Error_Handler();
    }

    // Update local variables
    this->year = year;
    this->month = month;
    this->day = day;

    // Notify listeners
    if (modelListener!=nullptr)
    {
    	modelListener->dateUpdated(day, month, year);
    }

}
void Model::setCalenderType(Model::CalenderType type)
{
	calenderType=type;
}
//Manage EnvTemp
void Model::updateEnvTemperature(){
	envTemperature = Utility::generateRandomInt(99, -40);

	if(modelListener!=nullptr)
	{
		modelListener->envTempUpdated(envTemperature);
	}
}
//Manage CarNumber
void Model::saveCarNumber(uint8_t carNum){
	carNumber=carNum;
	if(modelListener!=nullptr)
	{
		modelListener->carNumberUpdated(carNum);
	}
}
int  Model::getCarNumber() const{
	return carNumber;
}
//manage Axel Temperature
void Model::updateAxelTemperature(uint8_t carNum)
{

	for(int i=0;i<MAX_AXELNUM;i++)
	{
//		int16_t temp=Utility::generateRandomInt(125, -45);
		int16_t temp=(int16_t)carNum*10+Utility::generateRandomInt(9, 0);
		Car::TempState state=(Utility::generateRandomBin())?Car::TempState::NORMAL:Car::TempState::ERROR;
		cars[carNum].setAxelTemperature(i,temp, state);
	}
	if(modelListener!=nullptr && refreshingMainEnabled)
	{
		modelListener->carTempUpdated(cars[carNum]);
	}
}
//manage Leds
void Model::updateLed(int ledId, LedParam::ColorState state)
{

}
