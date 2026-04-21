#ifndef MODEL_HPP
#define MODEL_HPP
#include <touchgfx/hal/Types.hpp>
#include <rtc.h>
#include "Car.h"
#include "LedParam.h"
class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void startRefreshingMain() { refreshingMainEnabled = true; }
    void stopRefreshinMain() { refreshingMainEnabled = false; }
    //Manage Time/Date
    enum class CalenderType{GEORGIAN,JALALI};
    void updateRTC();  // Read from hardware RTC
    void setRTCTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void setRTCDate(uint8_t day, uint8_t month, uint16_t year);

     uint8_t getHours() const { return hours; }
     uint8_t getMinutes() const { return minutes; }
     uint8_t getSeconds() const { return seconds; }
     uint8_t getDay() const { return day; }
     uint8_t getMonth() const { return month; }
     uint16_t getYear() const { return year; }

     void setCalenderType(Model::CalenderType type);
     Model::CalenderType getCalenderType() const {return calenderType;}
     //Manage EnvTemp
     void updateEnvTemperature();
    // Manage CarNumber
    void saveCarNumber(uint8_t carNum);
    int  getCarNumber() const;
    // Manage AxelTemperature
    void updateAxelTemperature(uint8_t carNum);
    //Manage Leds
    void updateLed(int ledId, LedParam::ColorState state);
protected:

private:
    ModelListener* modelListener;
    uint16_t tickCounter;
    bool refreshingMainEnabled;

    // Time variables
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    Model::CalenderType  calenderType;
    // envTemp variable
    int16_t envTemperature;
    //CarNumber Variable
    uint8_t carNumber;
    Car cars[MAX_CARNUM];
    //Leds Variable
    LedParam ledMain;
    LedParam ledAlarm;
    LedParam ledComm;
    //Reading hardware
    void readHardwareRTC();
};

#endif // MODEL_HPP
