/*
 * Logger.h
 *
 *  Created on: Apr 27, 2026
 *      Author: mehdi
 */

#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_
#include "rtc.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include "Utility.h"
extern RTC_HandleTypeDef hrtc;


struct LogData {
	uint8_t carNum;
    uint8_t sensorId;
    int16_t value;

    LogData() : carNum(0),sensorId(0), value(0) {}
    LogData(uint8_t u,uint8_t id,int16_t val)
        : carNum(u), sensorId(id), value(val) {}
};


// Log Entry Structure
struct LogEntry {
	LogData data;
    uint32_t timestamp; // Unix timestamp or RTC count
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    LogEntry() :timestamp(0),
        day(0), month(0), year(0), hour(0), minute(0), second(0) {}

};

// Main Logger Class
class Logger {
private:
    std::vector<LogEntry> logs;
    size_t maxSize;
    // Get current timestamp (implement based on your RTC)
   bool readHardwareRTC( RTC_TimeTypeDef *sTime,  RTC_DateTypeDef *sDate)
   {

	    // Read time and date from STM32 RTC
	    if (HAL_RTC_GetTime(&hrtc, sTime, RTC_FORMAT_BIN) == HAL_OK)
	    {
	        // Must call GetDate to unlock the RTC
	        HAL_RTC_GetDate(&hrtc, sDate, RTC_FORMAT_BIN);
	        return true;
	    }
	    return false;
   }
    uint32_t makeTimestamp(LogEntry &entry) const {
        // Replace with your RTC implementation
    	    // Month days in normal year
    	    const uint8_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    	    // Calculate days since 1970-01-01
    	    uint32_t days = 0;

    	    // Years from 2000 to year-1
    	    for (uint16_t y = 2000; y < entry.year; y++) {
    	        days += 365 + (Utility::isLeapYear(y) ? 1 : 0);
    	    }

    	    // Months from January to month-1
    	    for (uint8_t m = 1; m < entry.month; m++) {
    	        days += monthDays[m-1];
    	        if (m == 2 && Utility::isLeapYear(entry.year)) {
    	            days += 1;  // Add Feb 29 for leap year
    	        }
    	    }

    	    // Days in current month
    	    days += entry.day - 1;

    	    // Convert to seconds
    	    uint32_t timestamp = days * 86400;  // 86400 seconds in a day
    	    timestamp += entry.hour * 3600;
    	    timestamp += entry.minute * 60;
    	    timestamp += entry.second;

    	    return timestamp;
    }

    // Get current date/time (implement based on your RTC)
    void getCurrentDateTime(uint8_t& day, uint8_t& month, uint16_t& year,
                            uint8_t& hour, uint8_t& minute, uint8_t& second) {
        // Replace with your RTC implementation
        // Example using placeholder values
    	RTC_TimeTypeDef sTime;
    	RTC_DateTypeDef sDate;
    	readHardwareRTC(&sTime,&sDate);

        hour = sTime.Hours;
        minute = sTime.Minutes;
        second = sTime.Seconds;
        day = sDate.Date;
        month = sDate.Month;
        year = sDate.Year + 2000;  // RTC typically returns year 0-99
    }

    void saveToFlash();

public:
    Logger(size_t maxLogSize );


    ~Logger() {
        clear();
    }

    // Add Sensor Event
    bool addSensorEvent( const LogData& data) {
        if (logs.size() >= maxSize) {
            removeOldestLog();
        }

        LogEntry entry;
        getCurrentDateTime(entry.day, entry.month, entry.year,
                           entry.hour, entry.minute, entry.second);
        entry.data = data;
        entry.timestamp = makeTimestamp(entry);


        logs.push_back(entry);
        return true;
    }

    // Remove log by index
    bool removeLog(size_t index) {
        if (index < logs.size()) {
            logs.erase(logs.begin() + index);
            return true;
        }
        return false;
    }

    // Remove oldest log
    bool removeOldestLog() {
        if (!logs.empty()) {
            logs.erase(logs.begin());
            return true;
        }
        return false;
    }

    // Remove all logs
    void clear() {
        logs.clear();
    }


    // Get all logs
    const std::vector<LogEntry>& getAllLogs() const {
        return logs;
    }

    // Get log count
    size_t getLogCount() const {
        return logs.size();
    }

    // Get max size
    size_t getMaxSize() const {
        return maxSize;
    }

    // Change max size (will trim if smaller)
    void setMaxSize(size_t newSize) {
        maxSize = newSize;
        while (logs.size() > maxSize) {
            removeOldestLog();
        }
        logs.shrink_to_fit();
    }

};


#endif /* INC_LOGGER_H_ */
