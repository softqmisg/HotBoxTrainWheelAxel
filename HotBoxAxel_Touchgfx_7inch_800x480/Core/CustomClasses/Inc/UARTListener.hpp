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

class Model;
class UARTListener {
public:
	enum PacketType {TIMEDATE=0};
    static UARTListener& getInstance();      // ◀── the clean access point
    static void handleRxInterrupt(UART_HandleTypeDef* huart);
    // Call once at startup — starts the first interrupt reception
    void start();
    // Call every frame from Model::tick() (or main loop)
    void poll();

    // Optional: send a packet back to the sensor
    float getTemperature() const { return temperature; }
   bool  hasNewReading()  const { return newReading; }
   void  clearNewReading()      { newReading = false; }

    void sendTimeDateRequest(RTC_TimeTypeDef sTime,RTC_DateTypeDef sDate);
private:
    UARTListener() {}
	UARTListener(const UARTListener&)            = delete;
	UARTListener& operator=(const UARTListener&) = delete;

    void onByteReceived(uint8_t b) { rx.push(b); }
    uint8_t isrByte = 0;

    UARTBuffer rx;

//    enum State { WAIT_AA, WAIT_55, READ_H, READ_L, READ_CRC };
//    State   state    = WAIT_AA;
//    uint8_t highByte = 0;
//    uint8_t lowByte = 0;
//
//    uint8_t crc      = 0;

    // ISR ⇄ class glue

    bool parseByte(uint8_t b, float& out);

    volatile float temperature = 0.0f;
    volatile bool  newReading  = false;

    uint8_t crc8_maxim(const uint8_t *buf, size_t len, uint8_t seed);
    void sendUartData(uint8_t *data,int len,PacketType packetType);

};

#endif /* CUSTOMCLASSES_INC_UARTLISTENER_HPP_ */
