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

    // Manage CarNumber
    void saveCarNumber(int carNum);
    int  getCarNumber() const;

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
     void startClockUpdates() { updateEnabled = true; }
     void stopClockUpdates() { updateEnabled = false; }

protected:

private:
    ModelListener* modelListener;
    //CarNumber Variable
    int saveCarNumberValue;

    // Time variables
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    bool updateEnabled;
    uint16_t tickCounter;

    //Reading hardware
    void readHardwareRTC();
};

#endif // MODEL_HPP
