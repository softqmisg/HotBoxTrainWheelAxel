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
volatile uint8_t dummy_packet[500];
volatile uint16_t dummy_counter=0;
extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	UARTListener& uart=UARTListener::getInstance();
 	dummy_packet[dummy_counter]=uart.isrByte;
 	dummy_counter++;
 	if(dummy_counter>100)
 	{
 		dummy_counter=0;

 	}
    UARTListener::handleRxInterrupt(huart);
}
void UARTListener::handleRxInterrupt(UART_HandleTypeDef* huart)
{
	 if (huart->Instance != USART2)
	        return;
	 	UARTListener& uart=getInstance();

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
    uint8_t b;
    int8_t tmp[MAX_SENSORNUM];
    uint8_t car;
    while (rx.pop(b))
    {
        if (parseByte(b,tmp,&car))
        {
//        	carNumber=car;
//        	for(uint8_t t=0;t<MAX_SENSORNUM;t++) temperature[t]=tmp[t];
        	newReading=true;

        }
    }
}

// ------------------------------------------------------------------
//Date Time form Master BoradCast
//offset:0    1    2    3    4     5     6 .. 18          19    20
//       FF   FF   FD   FE   ADDR  TYPE   payload (13)     FF    CRC8
//       └      sync	 ┘                                └ trailer
//ADDR: 0x01->0x0A :car number/ 0x0b=Boroad cast Master
//Type:0x044=Temperature/0xF8=DateTime
//payload for Temperature:
//     6  7  8      9 .. 17       18
//     10 00 00    c1 .. c9       00
//     └ fixed ┘  └ 9 routes ┘  └fixed┘

// ------------------------------------------------------------------
bool UARTListener::parseByte(uint8_t b,int8_t *tmp,uint8_t *carvalue)
{
    switch (state)
    {
    case WAIT_FF0:
    	counter_bytes=0;
        state = (b == 0xFF) ? WAIT_FF1 : WAIT_FF0;
        break;
    case WAIT_FF1:
    	counter_bytes=1;
        state = (b == 0xFF) ? WAIT_FD : WAIT_FF0;
        break;
    case WAIT_FD:
    	counter_bytes=2;
        state = (b == 0xFD) ? WAIT_FE : WAIT_FF0;
        break;
    case WAIT_FE:
    	counter_bytes=3;
    	state = (b == 0xFE) ? READ_ADDR : WAIT_FF0;
        break;
    case READ_ADDR:
    	counter_bytes=4;
    	carNumber=b-1;
    	state=READ_TYPE;
    	break;
    case READ_TYPE:
    	counter_bytes=5;
//    	if (b == (uint8_t)MessageType::TEMPERATURE){
//    		state =  READ_FIXED_TEMP;
//    	}
//    	else
//    	{
//    		state=WAIT_FD;
//    	}
		state =  READ_FIXED_TEMP;

    	break;
    case READ_FIXED_TEMP:
    		counter_bytes++;

    		if(counter_bytes==6)
    		{
    			state = (b == 0x10) ? READ_FIXED_TEMP : WAIT_FF0;
    		}
    		else if(counter_bytes==7)
    		{
    			state = (b == 0x00) ? READ_FIXED_TEMP : WAIT_FF0;
    		}
    		else if (counter_bytes==8)
			{
    			state = (b == 0x00) ? READ_BYTES_TEMP : WAIT_FF0;
			}
    		else
    		{
    			state=WAIT_FF0;
    		}
    	break;
    case READ_BYTES_TEMP:

    	counter_bytes++;
    	temperature[counter_bytes-9]=b;
    	if(counter_bytes>=17)
    	{
    		state=READ_ENDFIXED_TEMP;
    	}
    	break;
    case READ_ENDFIXED_TEMP:
    	counter_bytes=18;
//    	state = (b == 0x00) ? READ_BYTES_TEMP : WAIT_FF0;
    	state=READ_TRAIL_FF;
    	break;
    case READ_TRAIL_FF:
    	counter_bytes=19;
    	state = (b == 0xFF) ? READ_TRAIL_CRC : WAIT_FF0;
    	break;
    case READ_TRAIL_CRC:
    	counter_bytes=20;
    	packet[counter_bytes]=b;
    	uint8_t calc_crc=crc8_maxim(packet, 20, (uint8_t)SeedValue::SEED_TEMPERATURE);
    	state=WAIT_FF0;
//    	if(calc_crc==b)
    		return true;
    	break;
    }
	packet[counter_bytes]=b;
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
        for (int b = 0; b < 8; b++)
            crc = (crc & 1) ? (uint8_t)((crc >> 1) ^ 0x8C) : (uint8_t)(crc >> 1);
    }
    return crc;
//    uint8_t crc = seed;
//    for (size_t i = 0; i < len; i++) {
//        crc ^= buf[i];
//        for (int b = 0; b < 8; b++) {
//            if (crc & 0x01)
//                crc = (uint8_t)((crc >> 1) ^ 0x8C);
//            else
//                crc = (uint8_t)(crc >> 1);
//        }
//    }
//    return crc;
}

void UARTListener::sendUartData(uint8_t *data,int len,MessageType msgType) //0=time send
{
	switch(msgType)
	{
		case MessageType::TIMEDATE: //time
		{
			uint8_t pData[21]={0xff,0xff,0xfd,0xfe,0x0b,(uint8_t)msgType,0x00,0x00,0x00,
					0,0,0,0,0,0,
					0x00,0x00,0x00,0x00,0xFF,0
			};
			int totalLen=21;
			for(uint8_t i=0;i<6;i++)
				pData[9+i]=data[i];
			pData[20]=crc8_maxim(pData, 20, (uint8_t)SeedValue::SEED_TIMEDATE);
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
    sendUartData(timeDate, 6,MessageType::TIMEDATE);
}
void UARTListener::sendTimeDateRequest(uint8_t s,uint8_t m,uint8_t h,uint8_t d,uint8_t mo,uint8_t y) //y=0-99 ~2000~2099
{
	   RTC_TimeTypeDef sTime={.Hours=h,.Minutes=m,.Seconds=s};
	    RTC_DateTypeDef sDate={.Month=mo,.Date=d,.Year=y};
	    sendTimeDateRequest(sTime,sDate);
}
