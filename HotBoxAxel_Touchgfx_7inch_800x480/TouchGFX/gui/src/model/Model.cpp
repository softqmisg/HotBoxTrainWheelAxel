#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include  "main.h"
#include <stdlib.h>
#include "Utility.h"

extern RTC_HandleTypeDef hrtc;

Model::Model() :
modelListener(0),
tick1sCounter(0),
refreshingMainEnabled(false),
sensorLogger(MAX_LOG_SIZE),
eventLogger(MAX_LOG_SIZE),
hours(0),
minutes(0),
seconds(0),
day(1),
month(1),
year(2000),
calenderType(CalenderType::GEORGIAN),
carNumber(0),
ledMain(0),
ledAlarm(1),
ledComm(2)
{
	for(int i=0;i<MAX_CARNUM;i++)
	{
		cars[i].setCarID(i);
		cars[i].setShowDurationMS(10000);
		for(int axel=0;axel<MAX_SENSORNUM;axel++)
			cars[i].setTemperature(axel,0,Car::TempState::NORMAL);
	}

	ledMain.setCallback([this](uint8_t ledId,LedParam::ColorState colorState){
		this->colorLedChanged(ledId,colorState);
	});
	ledAlarm.setCallback([this](uint8_t ledId,LedParam::ColorState colorState){
		this->colorLedChanged(ledId,colorState);
	});
	ledComm.setCallback([this](uint8_t ledId,LedParam::ColorState colorState){
		this->colorLedChanged(ledId,colorState);
	});

	generalParam.setBrightness(8);

}

void Model::tick()
{
    // Called periodically by the framework
		ledMain.tick();
		ledAlarm.tick();
		ledComm.tick();
		//////ShowCar change///////////////
		tickCounter++;
		if(tickCounter>=cars[carNumber].getDuration())
		{
			tickCounter=0;
			carNumber++;
			if(carNumber>=MAX_CARNUM)
				carNumber=0;
			saveCarNumber(carNumber);
		}
		////////////////////////////////////
	    tick1sCounter++;
	    // Update clock every second (60 ticks = 1 second at 60 FPS)
	    if (tick1sCounter >= 60)
	    {
	        tick1sCounter = 0;
 		   updateRTC();  // Read from hardware RTC
	 	   if (refreshingMainEnabled)
	 	   {
	 		   updateLedMain();
	 		   updateLedAlarm();
	 		   updateLedComm();
	 	   }
 		   updateCarTemperatures(carNumber);

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
//Manage CarNumber
void Model::saveCarNumber(uint8_t carNum){
	tickCounter=0;
	carNumber=carNum;
	if(modelListener!=nullptr)
	{
		modelListener->carNumberUpdated(carNum);
	}
}
int  Model::getCarNumber() const{
	return carNumber;
}
//manage Axel Temperature & //Manage EnvTemp
void Model::updateCarTemperatures(uint8_t carNum)
{


	for(int i=0;i<MAX_SENSORNUM;i++)
	{
		int16_t temp;
		if(i==(MAX_SENSORNUM-1))
			temp = Utility::generateRandomInt(99, -40);
		else
			temp=(int16_t)(carNum+1)*10+Utility::generateRandomInt(9, 0);
		Car::TempState state;
		if(minutes%2==0 && seconds==0)
			state=Car::TempState::ERROR;
		else
			state=Car::TempState::NORMAL;

		cars[carNum].setTemperature(i,temp, state);
		if(state==Car::TempState::NORMAL)
		{
			LogData sensor;
			sensor.carNum=carNum;
			sensor.sensorId=i;
			sensor.value=temp;
			sensorLogger.addSensorLog(sensor);
			if(sensor.value>125 || sensor.value<-45)
			{
				SensorData alarm;
				alarm.carNum=carNum;
				alarm.sensorId=i;

				eventLogger.addSensorEvent(SensorSubtype::SENSOR_TEMPOUTRANGE,
											AlarmPriority::PRIORITY_HIGH,
											alarm);
			}
		}
		else
		{
			SensorData alarm;
			alarm.carNum=carNum;
			alarm.sensorId=i;
			eventLogger.addSensorEvent(SensorSubtype::SENSOR_TEMPNOTRECEIVED,
									(AlarmPriority)cars[carNum].getPriority(i),
									alarm);
		}
	}
	if(modelListener!=nullptr && refreshingMainEnabled)
	{
		modelListener->carTempUpdated(cars[carNum]);
		getWarning();
	}
}
//manage Leds
void Model::updateLedMain()
{
	if(!ledMain.getBlinking()){
		ledMain.setPeriodMS(1000,9000);
		ledMain.startBlinking();
	}

}
void Model::updateLedAlarm()
{
	if(!ledAlarm.getBlinking()){

		ledAlarm.setPeriodMS(4000,4000);
		ledAlarm.startBlinking();
	}
}
void Model::updateLedComm()
{
	ledComm.setFixed();
}
void Model::colorLedChanged(uint8_t ledId, LedParam::ColorState colorState)
{
	if(modelListener!=nullptr && refreshingMainEnabled)
	{
		modelListener->ledColorUpdated(ledId, colorState);
	}
}
//manage warning
void Model::getWarning(){
	updateWarning(eventLogger.getHighestPriority());
}
void Model::updateWarning(EventEntry *entry){
	if(modelListener!=nullptr){
		modelListener->warnigTextUpdated(entry);
	}
}
void Model::navigateWarning(){
	eventLogger.setNavigateHighestPriority(true);
	getWarning();
}
