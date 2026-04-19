#ifndef MODEL_HPP
#define MODEL_HPP
#include <touchgfx/hal/Types.hpp>
#include <rtc.h>

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
    //Manage Time/Date
    void updateRTC();  // Read from hardware RTC
    void setRTCTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void setRTCDate(uint8_t day, uint8_t month, uint16_t year);

     uint8_t getHours() const { return hours; }
     uint8_t getMinutes() const { return minutes; }
     uint8_t getSeconds() const { return seconds; }
     uint8_t getDay() const { return day; }
     uint8_t getMonth() const { return month; }
     uint16_t getYear() const { return year; }
     void startClockUpdates() { updateRTCEnabled = true; }
     void stopClockUpdates() { updateRTCEnabled = false; }
     //Manage EnvTemp
     void updateEnvTemperature();
    // Manage CarNumber
    void saveCarNumber(int carNum);
    int  getCarNumber() const;


protected:

private:
    ModelListener* modelListener;
    uint16_t tickCounter;
    // Time variables
    bool updateRTCEnabled;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day;
    uint8_t month;
    uint16_t year;

    // envTemp variable
    int16_t envTemperature;
    //CarNumber Variable
    int carNumber;


    //Reading hardware
    void readHardwareRTC();
};

#endif // MODEL_HPP
