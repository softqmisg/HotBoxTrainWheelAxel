/*
 * EventLogger.h
 *
 *  Created on: Apr 27, 2026
 *      Author: mehdi
 */

#ifndef INC_EVENTLOGGER_H_
#define INC_EVENTLOGGER_H_
#include "rtc.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include "Utility.h"

extern RTC_HandleTypeDef hrtc;


// Event Types
enum class EventType {
    SYSTEM,
    SENSOR
};

// Event Subtypes
enum class SystemSubtype {
    SYSTEM_POWERON,
    SYSTEM_FLASHOVERFLOW,
    SYSTEM_RTCBATTERY,
	SYSTEM_FSKERROR

};

enum class SensorSubtype {
    SENSOR_TEMPOUTRANGE,
    SENSOR_TEMPNOTRECEIVED
};

enum class AlarmPriority{
	PRIORITY_LOW=0,
	PRIORITY_MED,
	PRIORITY_HIGH,
};
// Event-specific data structures
struct SystemData {
    uint16_t errorCode;

    SystemData() : errorCode(0) {}
    SystemData(uint32_t err)
        : errorCode(err) {}
};

struct SensorData {
	uint8_t carNum;
    uint8_t sensorId;

    SensorData() : carNum(0), sensorId(0){}
    SensorData(uint8_t num,uint8_t id)
        : carNum(num), sensorId(id) {}
};


// Union for polymorphic event data
union EventData {
    SystemData system;
    SensorData sensor;

    EventData() {}
    ~EventData() {}
};

// Log Entry Structure
struct EventEntry {
    EventType type;
    uint16_t subtype; // Store as uint16_t for flexibility
    AlarmPriority priority; // 1-3 (1=low, 3=critical)
    EventData data;
    uint32_t timestamp; // Unix timestamp or RTC count
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    bool navigate;

    EventEntry() : type(EventType::SYSTEM), subtype(0),priority(AlarmPriority::PRIORITY_LOW),
    	timestamp(0), day(0), month(0), year(0), hour(0), minute(0), second(0),
		navigate(false) {}

    // Helper to get subtype as enum
    SystemSubtype getSystemSubtype() const {
        return static_cast<SystemSubtype>(subtype);
    }

    SensorSubtype getSensorSubtype() const {
        return static_cast<SensorSubtype>(subtype);
    }

};

// Main Logger Class
class EventLogger {
private:
    std::vector<EventEntry> logs;
    std::vector<size_t> sortedIndices;
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
    uint32_t makeTimestamp(EventEntry &entry) const {
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

    // Get sorted indices (references to original positions)
    std::vector<size_t> getSortedIndices() const {
        std::vector<size_t> indices;
        for (size_t i = 0; i < logs.size(); ++i) {
            if (!logs[i].navigate) {
                indices.push_back(i);
            }
        }

        std::sort(indices.begin(), indices.end(),
                  [this](size_t a, size_t b) {
                      if ((int)logs[a].priority != (int)logs[b].priority)
                          return (int)logs[a].priority > (int)logs[b].priority;
                      return logs[a].timestamp > logs[b].timestamp;
                  });

        return indices;
    }



    void saveToFlash();


public:
    EventLogger(size_t maxLogSize );


    ~EventLogger() {
        clear();
    }

    // Add System Event
    bool addSystemEvent(SystemSubtype subtype,AlarmPriority prio, const SystemData& data) {
        if (logs.size() >= maxSize) {
            removeOldestLog();
        }

        EventEntry entry;
        getCurrentDateTime(entry.day, entry.month, entry.year,
                           entry.hour, entry.minute, entry.second);
        entry.type = EventType::SYSTEM;
        entry.subtype = static_cast<uint16_t>(subtype);
        entry.priority=prio;
        entry.data.system = data;
        entry.timestamp = makeTimestamp(entry);
        entry.navigate=false;
        logs.push_back(entry);
        return true;
    }

    // Add Sensor Event
    bool addSensorEvent(SensorSubtype subtype,AlarmPriority prio, const SensorData& data) {
        if (logs.size() >= maxSize) {
            removeOldestLog();
        }

        EventEntry entry;
        getCurrentDateTime(entry.day, entry.month, entry.year,
                           entry.hour, entry.minute, entry.second);
        entry.type = EventType::SENSOR;
        entry.subtype = static_cast<uint16_t>(subtype);
        entry.priority=prio;
        entry.data.sensor = data;
        entry.timestamp = makeTimestamp(entry);
        entry.navigate=false;
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

    // Count logs with same type and subtype in last 24 hours
    size_t countEventsInLast24Hours(EventType type, uint16_t subtype) const  {
        size_t count = 0;
        uint32_t currentTime ;
        bool isFirstLog=true;
        for (const auto& log : logs) {
            if (log.type == type && log.subtype == subtype) {
            	if(isFirstLog)
            	{
            		isFirstLog=false;
            		currentTime = makeTimestamp((EventEntry &)log);
            	}
            	else
				{
					if ((currentTime - log.timestamp) <= (24 * 60 * 60)) {
						count++;
					}
				}
            }
        }
        return count;
    }

    // Overloaded convenience methods for counting
    size_t countSystemEventsInLast24Hours(SystemSubtype subtype) const {
        return countEventsInLast24Hours(EventType::SYSTEM,
                                        static_cast<uint16_t>(subtype));
    }

    size_t countSensorEventsInLast24Hours(SensorSubtype subtype) const {
        return countEventsInLast24Hours(EventType::SENSOR,
                                        static_cast<uint16_t>(subtype));
    }

    // Get all logs
    const std::vector<EventEntry>& getAllLogs() const {
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

    // Get logs by type
    std::vector<EventEntry> getLogsByType(EventType type) const {
        std::vector<EventEntry> result;
        for (const auto& log : logs) {
            if (log.type == type) {
                result.push_back(log);
            }
        }
        return result;
    }

    // Access entry by index (for modification)
    EventEntry& getEntry(size_t index) {
        return logs[index];
    }

    const EventEntry& getEntry(size_t index) const {
        return logs[index];
    }

    void setNavigateHighestPriority(bool stat){
        if(sortedIndices.size()>0)
        {
			 size_t firstIndex = sortedIndices[0];
			 getEntry(firstIndex).navigate = stat;
        }

    }
    EventEntry* getHighestPriority() {
        sortedIndices = getSortedIndices();
        if (sortedIndices.size() > 0) {
            size_t firstIndex = sortedIndices[0];
            return &getEntry(firstIndex);
        }
        return nullptr;  // Safe: return null pointer
    }
};

#endif /* INC_EVENTLOGGER_H_ */
