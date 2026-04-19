#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include  "main.h"

extern RTC_HandleTypeDef hrtc;
Model::Model() :
		modelListener(0),
		saveCarNumberValue(1),
		hours(0),
		minutes(0),
		seconds(0),
		day(1),
		month(1),
		year(2024),
		updateEnabled(false),
		tickCounter(0)
{

}

void Model::tick()
{
    // Called periodically by the framework

	    tickCounter++;
	    // Update clock every second (60 ticks = 1 second at 60 FPS)
	    if (tickCounter >= 60)
	    {
	        tickCounter = 0;
	 	   if (!updateEnabled)
	 	        return;
	        updateRTC();  // Read from hardware RTC
	    }
}

void Model::saveCarNumber(int carNum){
	saveCarNumberValue=carNum;
}
int  Model::getCarNumber() const{
	return saveCarNumberValue;
}

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
    // Notify listeners
    if (modelListener!=nullptr)
    {
    	modelListener->timeUpdated(day, month, year);
    }

}
