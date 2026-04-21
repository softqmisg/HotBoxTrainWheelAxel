/*
 * Utility.cpp
 *
 *  Created on: Apr 20, 2026
 *      Author: mehdi
 */

#include <Utility.h>
#include <stdlib.h>
#include  "main.h"
#include <stdio.h>
// Implementation
int Utility::getDayOfWeek(uint16_t year, uint8_t month, uint8_t day) {
    if (!isValidDate(year, month, day)) {
        return -1;  // Invalid date
    }
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (month < 3) {
        year -= 1;
    }
    return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}

void Utility::getDayName(uint16_t year, uint8_t month, uint8_t day, char *name) {
    static const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                                  "Thursday", "Friday", "Saturday"};
    int dow = getDayOfWeek(year, month, day);
    sprintf(name,"%s",(dow >= 0) ? days[dow] : "Invalid Date");
}

void Utility::getDayNameShort(uint16_t year, uint8_t month, uint8_t day, char *name) {
    static const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    int dow = getDayOfWeek(year, month, day);
    sprintf(name,"%s",(dow >= 0) ? days[dow] : "Inv");
}

bool Utility::isLeapYear(uint16_t year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool Utility::isJalaliLeapYear(uint16_t year)
{
        int remainder = year % 33;
        return remainder == 1 || remainder == 5 || remainder == 9 || remainder == 13 ||
               remainder == 17 || remainder == 22 || remainder == 26 || remainder == 30;
}
bool Utility::isValidDate(uint16_t year, uint8_t month, uint8_t day) {
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year)) {
        return day <= 29;
    }
    return day <= days_in_month[month - 1];
}
 bool Utility::isValidJalaliDate(uint16_t year, uint8_t month, uint8_t day)
{
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    if (month < 7 && day > 31) {
        return false;
    }

    if (month > 6 && month < 12 && day > 30) {
        return false;
    }

    // Check for leap year in month 12
    if (month == 12) {
    	if(day > (isJalaliLeapYear(year)?30:29)){
    		return false;
    	}
//        int d_4 = (year + 1) % 4;
//        int d_33 = static_cast<int>(((year - 55) % 132) * 0.0305);
//        bool isLeap = (d_33 != 3 && d_4 <= d_33) ? 287 : 286;
//        if (day > (isLeap ? 30 : 29)) {
//            return false;
//        }
    }
    return true;
}

// Gregorian to Jalali conversion
 void Utility::gregorianToJalali(uint16_t year, uint8_t month, uint8_t day,uint16_t &jyear, uint8_t &jmonth, uint8_t &jday)
{
    long days;
    long gy2 = (month > 2) ? (year + 1) : year;
    long g_d_m[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    days = 355666 + (365 * year) + ((int)((gy2 + 3) / 4)) - ((int)((gy2 + 99) / 100)) + ((int)((gy2 + 399) / 400)) + day + g_d_m[month - 1];
    int jy = -1595 + (33 * ((int)(days / 12053)));
    days %= 12053;
    jy += 4 * ((int)(days / 1461));
    days %= 1461;
    if (days > 365) {
      jy += (int)((days - 1) / 365);
      days = (days - 1) % 365;
    }
    int jm, jd;
    jy = jy;
    if (days < 186) {
      jm = 1 + (int)(days / 31);
      jd= 1 + (days % 31);
    } else {
      jm = 7 + (int)((days - 186) / 30);
      jd = 1 + ((days - 186) % 30);
    }
    jyear=jy;
    jmonth=jm;
    jday=jd;

}
// Jalali to Gregorian conversion
 void Utility::jalaliToGregorian(uint16_t year, uint8_t month, uint8_t day,uint16_t &gyear, uint8_t &gmonth, uint8_t &gday)
{
    year += 1595;
    long days = -355668 + (365 * year) + (((int)(year / 33)) * 8) + ((int)(((year % 33) + 3) / 4)) + day + ((month < 7) ? (month - 1) * 31 : ((month - 7) * 30) + 186);
    long gy = 400 * ((int)(days / 146097));
    days %= 146097;
    if (days > 36524) {
      gy += 100 * ((int)(--days / 36524));
      days %= 36524;
      if (days >= 365) days++;
    }
    gy += 4 * ((int)(days / 1461));
    days %= 1461;
    if (days > 365) {
      gy += (int)((days - 1) / 365);
      days = (days - 1) % 365;
    }
    long gd = days + 1;
    long gm;
    long sal_a[13] = {0, 31, ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  	for (gm = 0; gm < 13 && gd > sal_a[gm]; gm++) gd -= sal_a[gm];

    gday=gd;
    gmonth=gm;
    gyear=gy;

}

 int16_t Utility::generateRandomInt(int16_t max, int16_t min)
 {
	uint32_t seed=0;
	seed+=SysTick->VAL;
	srand(seed);
	 return (rand() % (max - min + 1)) + min;
 }


 bool Utility::generateRandomBin() {
     return rand() < RAND_MAX / 2 ? false : true;
 }
