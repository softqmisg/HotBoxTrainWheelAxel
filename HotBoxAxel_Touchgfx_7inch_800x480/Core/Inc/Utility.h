/*
 * Utility.h
 *
 *  Created on: Apr 20, 2026
 *      Author: mehdi
 */

#ifndef INC_UTILITY_H_
#define INC_UTILITY_H_
//#include <stddef.h>
#include <touchgfx/hal/Types.hpp>

#define MAX_LOG_SIZE (size_t)1000
#define MAX_CARNUM	10
#define MAX_SENSORNUM	9 //8+1
#define ERROR_TEMP 32767

class Utility {
public:
    // Basic day of week calculation
    static int getDayOfWeek(uint16_t year, uint8_t month, uint8_t day);
    // Returns name of day
    static void getDayName(uint16_t year, uint8_t month, uint8_t day, char *name);
    // Returns abbreviated name (Mon, Tue, etc.)
    static void getDayNameShort(uint16_t year, uint8_t month, uint8_t day, char *name);
    // Check if date is valid
    static bool isValidDate(uint16_t year, uint8_t month, uint8_t day);
    static bool isValidJalaliDate(uint16_t year, uint8_t month, uint8_t day);
    // Check if year is leap year
    static bool isLeapYear(uint16_t year);
    static bool isJalaliLeapYear(uint16_t year);
    // Gregorian to Jalali conversion
    static void gregorianToJalali(uint16_t year, uint8_t month, uint8_t day,uint16_t &jyear, uint8_t &jmonth, uint8_t &jday);
    // Jalali to Gregorian conversion
    static void jalaliToGregorian(uint16_t year, uint8_t month, uint8_t day,uint16_t &gyear, uint8_t &gmonth, uint8_t &gday);

    static int16_t generateRandomInt(int16_t max,int16_t min);
    static bool generateRandomBin();
};

#endif /* INC_UTILITY_H_ */
