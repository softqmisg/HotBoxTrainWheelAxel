/*
 * UARTListener.cpp
 *
 *  Created on: Sep 20, 2026
 *      Author: mehdi
 */
#include "UARTListener.hpp"
#include "usart.h"


UARTListener& UARTListener::getInstance()
{
    static UARTListener theInstance;         //
    return theInstance;
}
// ------------------------------------------------------------------
// HAL callback — runs in ISR context
// ------------------------------------------------------------------
extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    UARTListener::handleRxInterrupt(huart);
}
void UARTListener::handleRxInterrupt(UART_HandleTypeDef* huart)
{
	 if (huart->Instance != USART2)
	        return;

	    UARTListener& uart = UARTListener::getInstance();   // ◀── reference

	    uart.onByteReceived(uart.isrByte);                  // ◀── dot, not arrow
	    HAL_UART_Receive_IT(huart, &uart.isrByte, 1);       // ◀── &uart.isrByte, not &instance->isrByte

}
// ------------------------------------------------------------------
void UARTListener::start()
{
    HAL_UART_Receive_IT(&huart2, &isrByte, 1);
}

// ------------------------------------------------------------------
// Called from the GUI loop / Model::tick()
// ------------------------------------------------------------------
void UARTListener::poll()
{
//    uint8_t b;
//    float   temp;
//
//    while (rx.pop(b))
//    {
//        if (parseByte(b, temp))
//        {
//            model.setTemperature(temp);
//        }
//    }
}

// ------------------------------------------------------------------
// Packet: 0xAA 0x55 H L CRC   (CRC = H ^ L)
// ------------------------------------------------------------------
bool UARTListener::parseByte(uint8_t b, float& out)
{
//    switch (state)
//    {
//    case WAIT_AA:
//        if (b == 0xAA) state = WAIT_55;
//        break;
//
//    case WAIT_55:
//        state = (b == 0x55) ? READ_H : WAIT_AA;
//        break;
//
//    case READ_H:
//        highByte = b;
//        crc      = b;
//        state    = READ_L;
//        break;
//
//    case READ_L:
//        crc      ^= b;
//        highByte  = static_cast<uint8_t>(highByte);   // keep for CRC
//        // store low byte separately
//        state     = READ_CRC;
//        lowByte    = b;
//        break;
//
//    case READ_CRC:
//        state = WAIT_AA;
//        if (b == crc) {
//            int16_t raw = static_cast<int16_t>(
//                              (static_cast<uint16_t>(highByte) << 8) | lowByte);
//            out = raw / 10.0f;                    // 0.1 °C → °C
//            return true;
//        }
//        break;
//    }
    return false;
}

// ------------------------------------------------------------------
// Transmit — request a fresh reading
// ------------------------------------------------------------------
uint8_t UARTListener::crc8_maxim(const uint8_t *buf, size_t len, uint8_t seed)
{
    uint8_t crc = seed;
    for (size_t i = 2; i < len; i++) {
        crc ^= buf[i];
        for (int b = 0; b < 8; b++) {
            if (crc & 0x01)
                crc = (uint8_t)((crc >> 1) ^ 0x8C);
            else
                crc = (uint8_t)(crc >> 1);
        }
    }
    return crc;
}

void UARTListener::sendUartData(uint8_t *data,int len,PacketType packetType) //0=time send
{
	switch(packetType)
	{
		case PacketType::TIMEDATE: //time
		{
			uint8_t pData[21]={0xff,0xff,0xfd,0xfe,0x0b,0xf8,0x00,0x00,0x00,
					0,0,0,0,0,0,
					0x00,0x00,0x00,0x00,0xFF,0
			};
			int totalLen=21;
			for(uint8_t i=0;i<6;i++)
				pData[9+i]=data[i];
			pData[20]=crc8_maxim(pData, 20, 0x23);
			HAL_GPIO_WritePin(FSK_RT_GPIO_Port, FSK_RT_Pin, GPIO_PIN_RESET);
			HAL_Delay(2);
//			HAL_HalfDuplex_EnableTransmitter(&huart2);
			HAL_UART_Transmit(&huart2, pData, totalLen, 1000);
//			HAL_HalfDuplex_EnableReceiver(&huart2);
			HAL_Delay(2);
			HAL_GPIO_WritePin(FSK_RT_GPIO_Port, FSK_RT_Pin, GPIO_PIN_SET);
		}
		break;
		default:
			break;
	}

}

void UARTListener::sendTimeDateRequest(RTC_TimeTypeDef sTime,RTC_DateTypeDef sDate)
{
    // Example command: 0xAA 0x55 0x01 0xFE
//    static uint8_t cmd[4] = { 0xAA, 0x55, 0x01, 0xFE };
//
//    // Blocking transmit is fine in a superloop if the packet is short.
//    // For non-blocking, use HAL_UART_Transmit_IT + a TxCpltCallback.
//    HAL_UART_Transmit(&huart2, cmd, sizeof(cmd), 10);

	uint8_t timeDate[6]={0,0,0,0,0,0};
    timeDate[0]=RTC_ByteToBcd2(sDate.Year);
    timeDate[1]=RTC_ByteToBcd2(sDate.Month);
    timeDate[2]=RTC_ByteToBcd2(sDate.Date);
    timeDate[3]=RTC_ByteToBcd2(sTime.Hours);
    timeDate[4]=RTC_ByteToBcd2(sTime.Minutes);
    timeDate[5]=RTC_ByteToBcd2(sTime.Seconds);
    sendUartData(timeDate, 6,PacketType::TIMEDATE);
}
