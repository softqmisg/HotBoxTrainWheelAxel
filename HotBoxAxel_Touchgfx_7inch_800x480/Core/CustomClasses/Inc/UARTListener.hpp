/*
 * UARTListener.h
 *
 *  Created on: Sep 20, 2026
 *      Author: mehdi
 */

#ifndef CUSTOMCLASSES_INC_UARTLISTENER_HPP_
#define CUSTOMCLASSES_INC_UARTLISTENER_HPP_
#include "UARTBuffer.hpp"
#include <rtc.h>
#include <stdbool.h>
#include <cstdint>
#include "Utility.h"
class Model;
class UARTListener {
public:
	enum MessageType {TIMEDATE=0xF8,TEMPERATURE=0x44};
	enum SeedValue {SEED_TIMEDATE=0x23,SEED_TEMPERATURE=0x3A};
    static UARTListener& getInstance();      // ◀── the clean access point
    static void handleRxInterrupt(UART_HandleTypeDef* huart);
    // Call once at startup — starts the first interrupt reception
    void start();
    // Call every frame from Model::tick() (or main loop)
    void poll();

    // Optional: send a packet back to the sensor
    volatile int8_t* getTemperature(uint8_t &car)  { car=carNumber; return temperature; }
   bool  hasNewReading()  const { return newReading; }
   void  clearNewReading()      { newReading = false; }
   void sendTimeDateRequest(RTC_TimeTypeDef sTime,RTC_DateTypeDef sDate);
   void sendTimeDateRequest(uint8_t s,uint8_t m,uint8_t h,uint8_t d,uint8_t mo,uint8_t y);
   uint8_t isrByte = 0;

private:

    uint8_t packet[200];
	uint8_t counter_bytes=0;

    UARTListener() {}
	UARTListener(const UARTListener&)            = delete;
	UARTListener& operator=(const UARTListener&) = delete;

    void onByteReceived(uint8_t b) { rx.push(b); }

    UARTBuffer rx;

    enum State { WAIT_FF0, WAIT_FF1, WAIT_FD, WAIT_FE,READ_ADDR,READ_TYPE,
    	READ_FIXED_TEMP,READ_BYTES_TEMP,READ_ENDFIXED_TEMP,
		READ_TRAIL_FF,READ_TRAIL_CRC };
    State   state    = WAIT_FF0;


    bool parseByte(uint8_t b,int8_t *tmp,uint8_t *car);

    volatile int8_t temperature[MAX_SENSORNUM];
    volatile uint8_t carNumber;
    volatile bool  newReading  = false;

    uint8_t crc8_maxim(const uint8_t *buf, size_t len, uint8_t seed);
    void sendUartData(uint8_t *data,int len,MessageType msgType);

};

#endif /* CUSTOMCLASSES_INC_UARTLISTENER_HPP_ */
