/****
	***********************************************************************************************************************************************************************************
	*	@file  	qspi_w25q64.c
	*	@version V1.0
	*  @date    2021-7-20
	* @author anti-customer technology
	* @brief QSPI driver W25Qxx related functions, the read and write functions provided are directly operated using HAL library functions
   ************************************************************************************************************************************************************************************
   *  @description
	*
	* Experimental platform: NANOFH743IIT6
	* Eshop: https://kavirelectronic.ir/eshop
	* TELEGRAM ID:   @kavirsupport
	*
>>>>> File description:
	*
	* 1. The routine is referred to the official driver file stm32h743i_eval_qspi.c
	* 2. The routine uses QUADSPI_BK1
	* 3. The read and write functions provided are all directly operated using HAL library functions, and DMA and interrupts are not used.
	* 4. The default configuration QSPI driver clock is 120M
	*
>>>>> Important Note:
	*
	* 1. The erase time of W25QXX is limited!!! The typical reference values ??given in the manual are: 4K-45ms, 32K-120ms, 64K-150ms, and the entire chip erases 20S
	*
	* 2. The writing time of W25QXX is limited!!! The typical reference value given in the manual is: 256 bytes-0.4ms, which is 1M bytes/s (the actual measurement is about 600K bytes/s)
	*
	* 3. If you use library functions to read directly, then whether to use DMA, whether to enable Cache, the optimization level of the compiler, and the location of the data storage area (internal TCM SRAM or AXI SRAM) will all affect the reading speed.
	*
	* 4. If memory mapping mode is used, the read performance is only related to the QSPI drive clock and whether the Cache is turned on
	*
	* 5. Use library functions for direct reading, keil version 5.30, compiler AC6.14, compilation level Oz image size, reading speed is 6.7M bytes/S, data is placed in TCM SRAM or AXI SRAM
	* All have similar results. If you directly use the HAL library to read, the speed will be very slow.
	*
	* 6. If MDMA is used for reading, it can reach 55.56M bytes/s. If memory mapping mode is used, it can reach 59.7M/s (working at 133M clock)
	*
	* 7. The maximum drive frequency allowed by W25Q64JV is 133MHz. The maximum drive frequency of 743 QSPI is also 133MHz. However, for direct reading of HAL library functions, there will be no performance improvement if the drive clock exceeds 15M.
	*
	* 8. For direct reading in memory mapped mode, there will be no performance improvement if the drive clock exceeds 127.5M. Because the QSPI core clock is limited to 250M, it is recommended that the actual QSPI drive clock not exceed 125M.
	*
	* 9. In actual use, when the data is relatively large, it is recommended to use 64K or 32K erase, the erase time is longer than the 4K erase block
	*
	****************************************************** ****************************************************** ****************************************************** **********************************FAN*****
***/

#include "W25Q64_QSPI.h"

extern QSPI_HandleTypeDef hqspi; // Define the QSPI handle. The variable naming generated using cubeMX is retained here to facilitate user reference and transplantation.

///*************************************************************************************************
//* Function name: HAL_QSPI_MspInit
//* Entry parameter: hqspi - variable defined by QSPI_HandleTypeDef, which represents the defined QSPI handle
//* Return value: None
//* Function: QSPI pin initialization function
//* Note: This function will be called by the MX_QUADSPI_Init function
//*************************************************************************************************/
//
//void HAL_QSPI_MspInit(QSPI_HandleTypeDef* hqspi)
//{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
//	if(hqspi->Instance==QUADSPI)
//	{
//		__HAL_RCC_QSPI_CLK_ENABLE(); // Enable QSPI clock
//
//		GPIO_QUADSPI_CLK_ENABLE; // Enable QUADSPI_CLK IO port clock
//		GPIO_QUADSPI_BK1_NCS_ENABLE; // Enable QUADSPI_BK1_NCS IO port clock
//		GPIO_QUADSPI_BK1_IO0_ENABLE; // Enable QUADSPI_BK1_IO0 IO port clock
//		GPIO_QUADSPI_BK1_IO1_ENABLE; // Enable QUADSPI_BK1_IO1 IO port clock
//		GPIO_QUADSPI_BK1_IO2_ENABLE; // Enable QUADSPI_BK1_IO2 IO port clock
//		GPIO_QUADSPI_BK1_IO3_ENABLE; // Enable QUADSPI_BK1_IO3 IO port clock
//
//		/******************************************************
//		PB2     ------> QUADSPI_CLK
//		PB6     ------> QUADSPI_BK1_NCS
//		PD11    ------> QUADSPI_BK1_IO0
//		PD12    ------> QUADSPI_BK1_IO1
//		PE2     ------> QUADSPI_BK1_IO2
//		PD13    ------> QUADSPI_BK1_IO3
//		*******************************************************/
//
//		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // Multiplex push-pull output mode
//		GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-down
//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // Super fast IO mouth speed
//
//		GPIO_InitStruct.Pin = QUADSPI_CLK_PIN; // QUADSPI_CLK pin
//		GPIO_InitStruct.Alternate = QUADSPI_CLK_AF; // QUADSPI_CLK multiplexing
//		HAL_GPIO_Init(QUADSPI_CLK_PORT, &GPIO_InitStruct); // Initialize the QUADSPI_CLK pin
//
//		GPIO_InitStruct.Pin = QUADSPI_BK1_NCS_PIN; // QUADSPI_BK1_NCS pin
//		GPIO_InitStruct.Alternate = QUADSPI_BK1_NCS_AF; // QUADSPI_BK1_NCS multiplexing
//		HAL_GPIO_Init(QUADSPI_BK1_NCS_PORT, &GPIO_InitStruct); // Initialize the QUADSPI_BK1_NCS pin
//
//		GPIO_InitStruct.Pin = QUADSPI_BK1_IO0_PIN; // QUADSPI_BK1_IO0 pin
//		GPIO_InitStruct.Alternate = QUADSPI_BK1_IO0_AF; // QUADSPI_BK1_IO0 multiplexing
//		HAL_GPIO_Init(QUADSPI_BK1_IO0_PORT, &GPIO_InitStruct); //Initialize QUADSPI_BK1_IO0 pin
//
//		GPIO_InitStruct.Pin = QUADSPI_BK1_IO1_PIN; // QUADSPI_BK1_IO1 pin
//		GPIO_InitStruct.Alternate = QUADSPI_BK1_IO1_AF; // QUADSPI_BK1_IO1 multiplexing
//		HAL_GPIO_Init(QUADSPI_BK1_IO1_PORT, &GPIO_InitStruct); //Initialize QUADSPI_BK1_IO1 pin
//
//		GPIO_InitStruct.Pin = QUADSPI_BK1_IO2_PIN; // QUADSPI_BK1_IO2 pin
//		GPIO_InitStruct.Alternate = QUADSPI_BK1_IO2_AF; // QUADSPI_BK1_IO2 multiplexing
//		HAL_GPIO_Init(QUADSPI_BK1_IO2_PORT, &GPIO_InitStruct); //Initialize QUADSPI_BK1_IO2 pin
//
//		GPIO_InitStruct.Pin = QUADSPI_BK1_IO3_PIN; // QUADSPI_BK1_IO3 pin
//		GPIO_InitStruct.Alternate = QUADSPI_BK1_IO3_AF; // QUADSPI_BK1_IO3 multiplexing
//		HAL_GPIO_Init(QUADSPI_BK1_IO3_PORT, &GPIO_InitStruct); //Initialize QUADSPI_BK1_IO3 pin
//	}
//}
//
///*************************************************************************************************
//* Function name: MX_QUADSPI_Init
//* Entry parameters: None
//* Return value: None
//* Function: Initialize QSPI configuration
//* Description: None
//**************************************************************************************************/
//
//void MX_QUADSPI_Init(void)
//{
//	hqspi.Instance = QUADSPI; // QSPI peripheral
//
//	HAL_QSPI_DeInit(&hqspi); //Reset QSPI
//
//	hqspi.Init.ClockPrescaler = 1; // Clock division value, divide the QSPI core clock by 1+1 to get the QSPI communication driver clock
//	hqspi.Init.FifoThreshold = 32; // FIFO threshold
//	hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE; // Sampling after half a CLK cycle
//	hqspi.Init.FlashSize = 22; // Flash size, number of bytes in FLASH = 2^[FSIZE+1], the core board uses 8M bytes W25Q64, here it is set to 22
//	hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE; // The time the chip select remains high
//	hqspi.Init.ClockMode = QSPI_CLOCK_MODE_3; // Mode 3
//	hqspi.Init.FlashID 				= QSPI_FLASH_ID_1;						// Ê¹ÓÃQSPI1
//	hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE; // Disable dual flash mode
//
//	HAL_QSPI_Init(&hqspi); // Initialization configuration
//}

/*************************************************************************************************
* Function name: QSPI_W25Qxx_Init
* Entry parameters: None
* Return value: QSPI_W25Qxx_OK - initialization successful, W25Qxx_ERROR_INIT - initialization error
* Function: Initialize QSPI configuration, read W25Q64ID
* Description: None
*************************************************************************************************/

int8_t QSPI_W25Qxx_Init(void)
{
	uint32_t Device_ID; // device ID

//	MX_QUADSPI_Init(); // Initialize QSPI configuration
	QSPI_W25Qxx_Reset(); //Reset device
	Device_ID = QSPI_W25Qxx_ReadID(); // Read device ID

	if( Device_ID == W25Qxx_FLASH_ID ) // Match
	{
//		printf ("W25Q64 OK,flash ID:%X\r\n",Device_ID); // Initialization successful
		return QSPI_W25Qxx_OK; // Return success flag
	}
	else
	{
//		printf ("W25Q64 ERROR!!!!! ID:%X\r\n",Device_ID); // Initialization failed
		return W25Qxx_ERROR_INIT; // Return error flag
	}
}

/*************************************************************************************************
* Function name: QSPI_W25Qxx_AutoPollingMemReady
* Entry parameters: None
* Return value: QSPI_W25Qxx_OK - communication ended normally, W25Qxx_ERROR_AUTOPOLLING - polling waiting for no response
* Function: Use the automatic polling flag to query and wait for the end of communication
* Note: This function should be called for every communication and wait for the communication to end to avoid wrong operations.
**************************************************************************************************/

int8_t QSPI_W25Qxx_AutoPollingMemReady(void)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration
	QSPI_AutoPollingTypeDef s_config; // Polling comparison related configuration parameters

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressMode = QSPI_ADDRESS_NONE; // No address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.DataMode = QSPI_DATA_1_LINE; // 1 line data mode
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.Instruction = W25Qxx_CMD_ReadStatus_REG1; // Read status information register

// Keep querying the W25Qxx_CMD_ReadStatus_REG1 register, and keep comparing W25Qxx_Status_REG1_BUSY in the read status byte with 0
//Read bit 0 of status register 1 (read-only), Busy flag, which will be set to 1 when erasing/writing data/writing commands, and is 0 when idle or the communication ends

	s_config.Match = 0; // Match value
	s_config.MatchMode = QSPI_MATCH_MODE_AND; // AND operation
	s_config.Interval = 0x10; // Polling interval
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE; // Automatic stop mode
	s_config.StatusBytesSize = 1; //Number of status bytes
	s_config.Mask = W25Qxx_Status_REG1_BUSY; // Mask the status byte received in polling mode and only compare the bits needed

	//Send polling wait command
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK; // Communication ends normally

}

/*************************************************************************************************
* Function name: QSPI_W25Qxx_Reset
* Entry parameters: None
* Return value: QSPI_W25Qxx_OK - reset successful, W25Qxx_ERROR_INIT - initialization error
* Function: Reset device
* Description: None
*************************************************************************************************/

int8_t QSPI_W25Qxx_Reset(void)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressMode = QSPI_ADDRESS_NONE; // No address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.DataMode = QSPI_DATA_NONE; // No data mode
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.Instruction = W25Qxx_CMD_EnableReset; // Execute reset enable command

	//Send reset enable command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_INIT; // If the sending fails, return error message
	}
	//Use the automatic polling flag and wait for the communication to end
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}

	s_command.Instruction = W25Qxx_CMD_ResetDevice; // Reset device command

	//Send reset device command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_INIT; // If the sending fails, return error message
	}
	//Use the automatic polling flag and wait for the communication to end
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK; // Reset successful
}

/*************************************************************************************************
* Function name: QSPI_W25Qxx_ReadID
* Entry parameters: None
* Return value: W25Qxx_ID - read device ID, W25Qxx_ERROR_INIT - communication and initialization error
* Function: Initialize QSPI configuration, read device ID
* Description: None
**************************************************************************************************/

uint32_t QSPI_W25Qxx_ReadID(void)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration
	uint8_t QSPI_ReceiveBuff[3]; // Store the data read by QSPI
	uint32_t W25Qxx_ID; // Device ID

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS; // 24-bit address
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.AddressMode = QSPI_ADDRESS_NONE; // No address mode
	s_command.DataMode = QSPI_DATA_1_LINE; // 1 line data mode
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.NbData = 3; //The length of the transmitted data
	s_command.Instruction = W25Qxx_CMD_JedecID; // Execute the read device ID command

	//Send command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
// return W25Qxx_ERROR_INIT; // If sending fails, return error message
	}
	// Receive data
	if (HAL_QSPI_Receive(&hqspi, QSPI_ReceiveBuff, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
// return W25Qxx_ERROR_TRANSMIT; // If reception fails, return error message
	}
	// Combine the obtained data into ID
	W25Qxx_ID = (QSPI_ReceiveBuff[0] << 16) | (QSPI_ReceiveBuff[1] << 8 ) | QSPI_ReceiveBuff[2];

	return W25Qxx_ID; // Return ID
}



/*************************************************************************************************
* Function name: QSPI_W25Qxx_MemoryMappedMode
* Entry parameters: None
* Return value: QSPI_W25Qxx_OK - write enable successful, W25Qxx_ERROR_WriteEnable - write enable failed
* Function: Set QSPI to memory mapping mode
* Note: When set to memory mapping mode, it can only be read, not written! ! !
**************************************************************************************************/

int8_t QSPI_W25Qxx_MemoryMappedMode(void)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration
	QSPI_MemoryMappedTypeDef s_mem_mapped_cfg; // Memory mapping access parameters

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS; // 24-bit address
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.AddressMode = QSPI_ADDRESS_4_LINES; // 4-line address mode
	s_command.DataMode = QSPI_DATA_4_LINES; // 4-line data mode
	s_command.DummyCycles = 6; // Number of dummy cycles
	s_command.Instruction = W25Qxx_CMD_FastReadQuad_IO; // In 1-4-4 mode (1 line instruction, 4 lines address, 4 lines data), fast read instructions

	s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE; // Disable timeout counter, nCS remains active
	s_mem_mapped_cfg.TimeOutPeriod = 0; // Timeout judgment period

	QSPI_W25Qxx_Reset(); //Reset W25Qxx

	if (HAL_QSPI_MemoryMapped(&hqspi, &s_command, &s_mem_mapped_cfg) != HAL_OK) // Configure
	{
		return W25Qxx_ERROR_MemoryMapped; // Error setting memory mapping mode
	}

	return QSPI_W25Qxx_OK; // Configuration successful
}

/*************************************************************************************************
* Function name: QSPI_W25Qxx_WriteEnable
* Entry parameters: None
* Return value: QSPI_W25Qxx_OK - write enable successful, W25Qxx_ERROR_WriteEnable - write enable failed
* Function: Send write enable command
* Description: None
**************************************************************************************************/

int8_t QSPI_W25Qxx_WriteEnable(void)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration
	QSPI_AutoPollingTypeDef s_config; // Polling comparison related configuration parameters

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressMode = QSPI_ADDRESS_NONE; // No address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.DataMode = QSPI_DATA_NONE; // No data mode
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.Instruction = W25Qxx_CMD_WriteEnable; //Send write enable command

	//Send write enable command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_WriteEnable;	//
	}

// Keep querying the W25Qxx_CMD_ReadStatus_REG1 register, and keep comparing W25Qxx_Status_REG1_WEL in the read status byte with 0x02
// Read the first bit of status register 1 (read-only), WEL write enable flag bit. When the flag bit is 1, it means that write operations can be performed.

	s_config.Match = 0x02; // Match value
	s_config.Mask = W25Qxx_Status_REG1_WEL; // Read the first bit of status register 1 (read-only), WEL write enable flag bit. When the flag bit is 1, it means that write operations can be performed.
	s_config.MatchMode = QSPI_MATCH_MODE_AND; // AND operation
	s_config.StatusBytesSize = 1; //Number of status bytes
	s_config.Interval = 0x10; // Polling interval
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE; // Automatic stop mode

	s_command.Instruction = W25Qxx_CMD_ReadStatus_REG1; // Read status information register
	s_command.DataMode = QSPI_DATA_1_LINE; // 1 line data mode
	s_command.NbData = 1; // Data length

	//Send polling wait command
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK; // Communication ends normally
}

/*************************************************************************************************
*
* Function name: QSPI_W25Qxx_SectorErase
*
* Entry parameters: SectorAddress - the address to be erased
*
* Return value: QSPI_W25Qxx_OK - erasure successful
* W25Qxx_ERROR_Erase - Erase failed
* W25Qxx_ERROR_AUTOPOLLING - Polling waiting for no response
*
* Function: Perform sector erasure operation, erasing 4K bytes each time
*
* Note: 1. According to the erase reference time given in the W25Q64JV data sheet, the typical value is 45ms and the maximum value is 400ms.
*2. The actual erasing speed may be greater than 45ms or less than 45ms
*3.The longer the flash is used, the longer it will take to erase it.
*
**************************************************************************************************/

int8_t QSPI_W25Qxx_SectorErase(uint32_t SectorAddress)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS; // 24-bit address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.AddressMode = QSPI_ADDRESS_1_LINE; // 1-line address mode
	s_command.DataMode = QSPI_DATA_NONE; // No data
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.Address = SectorAddress; // The address to be erased
	s_command.Instruction = W25Qxx_CMD_SectorErase; // Sector erase command

	//Send write enable
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable; // Write enable failed
	}
	//Issue an erase command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase; // Erase failed
	}
	//Use the automatic polling flag and wait for the end of erasure
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK; // Erase successful
}

/*************************************************************************************************
*
* Function name: QSPI_W25Qxx_BlockErase_32K
*
* Entry parameters: SectorAddress - the address to be erased
*
* Return value: QSPI_W25Qxx_OK - erasure successful
* W25Qxx_ERROR_Erase - Erase failed
* W25Qxx_ERROR_AUTOPOLLING - Polling waiting for no response
*
* Function: Perform block erasure operation, erasing 32K bytes each time
*
* Note: 1. According to the erasure reference time given in the W25Q64JV data sheet, the typical value is 120ms and the maximum value is 1600ms.
*2. The actual erasing speed may be greater than 120ms or less than 120ms
*3.The longer the flash is used, the longer it will take to erase it.
*
*************************************************************************************************/

int8_t QSPI_W25Qxx_BlockErase_32K (uint32_t SectorAddress)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS; // 24-bit address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.AddressMode = QSPI_ADDRESS_1_LINE; // 1-line address mode
	s_command.DataMode = QSPI_DATA_NONE; // No data
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.Address = SectorAddress; // The address to be erased
	s_command.Instruction = W25Qxx_CMD_BlockErase_32K; // Block erase command, erase 32K bytes each time

	//Send write enable
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable; // Write enable failed
	}
	//Issue an erase command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase; // Erase failed
	}
	//Use the automatic polling flag and wait for the end of erasure
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK; // Erase successful
}

/*************************************************************************************************
*
* Function name: QSPI_W25Qxx_BlockErase_64K
*
* Entry parameters: SectorAddress - the address to be erased
*
* Return value: QSPI_W25Qxx_OK - erasure successful
* W25Qxx_ERROR_Erase - Erase failed
* W25Qxx_ERROR_AUTOPOLLING - Polling waiting for no response
*
* Function: Perform block erasure operation, erasing 64K bytes each time
*
* Note: 1. According to the erasure reference time given in the W25Q64JV data sheet, the typical value is 150ms and the maximum value is 2000ms.
*2. The actual erasing speed may be greater than 150ms or less than 150ms
*3.The longer the flash is used, the longer it will take to erase it.
* 4. In actual use, it is recommended to use 64K erasing, which has the fastest erasing time.
*
**************************************************************************************************/

int8_t QSPI_W25Qxx_BlockErase_64K (uint32_t SectorAddress)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS; // 24-bit address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.AddressMode = QSPI_ADDRESS_1_LINE; // 1-line address mode
	s_command.DataMode = QSPI_DATA_NONE; // No data
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.Address = SectorAddress; // The address to be erased
	s_command.Instruction = W25Qxx_CMD_BlockErase_64K; // Block erase command, each erase 64K bytes

	//Send write enable
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable; // Write enable failed
	}
	//Issue an erase command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase; // Erase failed
	}
	//Use the automatic polling flag and wait for the end of erasure
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK; // Erase successful
}

/*************************************************************************************************
*
* Function name: QSPI_W25Qxx_ChipErase
*
* Entry parameters: None
*
* Return value: QSPI_W25Qxx_OK - erasure successful
* W25Qxx_ERROR_Erase - Erase failed
* W25Qxx_ERROR_AUTOPOLLING - Polling waiting for no response
*
* Function: Perform entire chip erase operation
*
* Note: 1. According to the erasure reference time given in the W25Q64JV data sheet, the typical value is 20s and the maximum value is 100s.
*2. The actual erasing speed may be greater than 20s or less than 20s
*3.The longer the flash is used, the longer it will take to erase it.
*
*************************************************************************************************/

int8_t QSPI_W25Qxx_ChipErase (void)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration
	QSPI_AutoPollingTypeDef s_config; //Polling waiting for configuration parameters

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS; // 24-bit address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.AddressMode = QSPI_ADDRESS_NONE; // No address
	s_command.DataMode = QSPI_DATA_NONE; // No data
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.Instruction = W25Qxx_CMD_ChipErase; // Erase command to erase the entire chip

	//Send write enable
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable; // Write enable failed
	}
	//Issue an erase command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase; // Erase failed
	}

// Keep querying the W25Qxx_CMD_ReadStatus_REG1 register, and keep comparing W25Qxx_Status_REG1_BUSY in the read status byte with 0
//Read bit 0 of status register 1 (read-only), Busy flag, which will be set to 1 when erasing/writing data/writing commands, and is 0 when idle or the communication ends

	s_config.Match = 0; // Match value
	s_config.MatchMode = QSPI_MATCH_MODE_AND; // AND operation
	s_config.Interval = 0x10; // Polling interval
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE; // Automatic stop mode
	s_config.StatusBytesSize = 1; //Number of status bytes
	s_config.Mask = W25Qxx_Status_REG1_BUSY; // Mask the status byte received in polling mode and only compare the bits needed

	s_command.Instruction = W25Qxx_CMD_ReadStatus_REG1; // Read status information register
	s_command.DataMode = QSPI_DATA_1_LINE; // 1 line data mode
	s_command.NbData = 1; // Data length

	//The typical reference time for W25Q64 whole chip erasure is 20s, the maximum time is 100s, the timeout waiting value here W25Qxx_ChipErase_TIMEOUT_MAX is 100S
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, W25Qxx_ChipErase_TIMEOUT_MAX) != HAL_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK;
}

/**********************************************************************************************************
*
* Function name: QSPI_W25Qxx_WritePage
*
* Entry parameter: pBuffer - the data to be written
* WriteAddr - the address to write to W25Qxx
* NumByteToWrite - data length, up to 256 bytes
*
* Return value: QSPI_W25Qxx_OK - data written successfully
* W25Qxx_ERROR_WriteEnable - Write enable failed
* W25Qxx_ERROR_TRANSMIT - Transmission failed
* W25Qxx_ERROR_AUTOPOLLING - Polling waiting for no response
*
* Function: Write by page, up to 256 bytes only. Please be sure to complete the erase operation before data is written.
*
* Note: 1. The write time of Flash is the same as the erase time, which is limited. It does not mean that QSPI drive clock 133M can write at this speed.
* 2. According to the page (256 bytes) writing reference time given in the W25Q64JV data sheet, the typical value is 0.4ms and the maximum value is 3ms.
* 3. The actual writing speed may be greater than 0.4ms or less than 0.4ms
* 4. The longer the Flash is used, the longer it takes to write.
*5.Be sure to complete the erase operation before data writing
*
***********************************************************************************************************/

int8_t QSPI_W25Qxx_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS; // 24-bit address
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.AddressMode = QSPI_ADDRESS_1_LINE; // 1-line address mode
	s_command.DataMode = QSPI_DATA_4_LINES; // 4-line data mode
	s_command.DummyCycles = 0; //Number of dummy cycles
	s_command.NbData = NumByteToWrite; // Data length, up to 256 bytes
	s_command.Address = WriteAddr; //The address to be written to W25Qxx
	s_command.Instruction = W25Qxx_CMD_QuadInputPageProgram; // In 1-1-4 mode (1 line instruction, 1 line address, 4 lines data), page programming instruction

	// write enable
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable; // Write enable failed
	}
	//Write command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT; //Transmission data error
	}
	//Start transmitting data
	if (HAL_QSPI_Transmit(&hqspi, pBuffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT; //Transmission data error
	}
	// Use the automatic polling flag to wait for the end of writing
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK; // Data written successfully
}

/**********************************************************************************************************
*
* Function name: QSPI_W25Qxx_WriteBuffer
*
* Entry parameter: pBuffer - the data to be written
* WriteAddr - the address to write to W25Qxx
* NumByteToWrite - data length, the maximum size cannot exceed the size of the flash chip
*
* Return value: QSPI_W25Qxx_OK - data written successfully
* W25Qxx_ERROR_WriteEnable - Write enable failed
* W25Qxx_ERROR_TRANSMIT - Transmission failed
* W25Qxx_ERROR_AUTOPOLLING - Polling waiting for no response
*
* Function: Write data, the maximum size cannot exceed the size of the flash chip, please be sure to complete the erase operation
*
* Note: 1. The writing time of Flash is the same as the erasing time, which is limited. It does not mean that QSPI drive clock 133M can write at this speed.
* 2. According to the page write reference time given in the W25Q64JV data sheet, the typical value is 0.4ms and the maximum value is 3ms.
* 3. The actual writing speed may be greater than 0.4ms or less than 0.4ms
* 4. The longer the Flash is used, the longer it takes to write.
*5.Be sure to complete the erase operation before data writing
* 6. This function is transplanted from stm32h743i_eval_qspi.c
*
**********************************************************************************************************/

int8_t QSPI_W25Qxx_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size)
{
	uint32_t end_addr, current_size, current_addr;
	uint8_t *write_data; //Data to be written

	current_size = W25Qxx_PageSize - (WriteAddr % W25Qxx_PageSize); // Calculate the remaining space of the current page

	if (current_size > Size) // Determine whether the remaining space of the current page is enough to write all data
	{
		current_size = Size; // If enough, get the current length directly
	}

	current_addr = WriteAddr; // Get the address to be written
	end_addr = WriteAddr + Size; // Calculate the end address
	write_data = pBuffer; // Get the data to be written

	do
	{
		//Write data by page
		if(QSPI_W25Qxx_WritePage(write_data, current_addr, current_size) != QSPI_W25Qxx_OK)
		{
			return W25Qxx_ERROR_TRANSMIT;
		}

		else // Successfully write data on a page basis, prepare for the next write of data
		{
			current_addr += current_size; // Calculate the address to be written next
			write_data += current_size; // Get the address of the data storage area to be written next
			// Calculate the length of the next written data
			current_size = ((current_addr + W25Qxx_PageSize) > end_addr) ? (end_addr - current_addr) : W25Qxx_PageSize;
		}
	}
	while (current_addr < end_addr); // Determine whether all data has been written

	return QSPI_W25Qxx_OK; // Data written successfully

}

/**********************************************************************************************************************************
*
* Function name: QSPI_W25Qxx_ReadBuffer
*
* Entry parameter: pBuffer - the data to be read
* ReadAddr - the address of W25Qxx to be read
* NumByteToRead - data length, the maximum size cannot exceed the size of the flash chip
*
* Return value: QSPI_W25Qxx_OK - read data successfully
* W25Qxx_ERROR_TRANSMIT - Transmission failed
* W25Qxx_ERROR_AUTOPOLLING - Polling waiting for no response
*
* Function: Read data, the maximum size cannot exceed the size of the flash chip
*
* Note: 1. The reading speed of Flash depends on the QSPI communication clock, and the maximum cannot exceed 133M
* 2. What is used here is the 1-4-4 mode (1 line instruction, 4 lines address, 4 lines data), fast read instruction Fast Read Quad I/O
* 3. There is a free cycle when using the fast read instruction. For details, refer to the W25Q64JV manual Fast Read Quad I/O (0xEB) instruction.
* 4. In actual use, whether DMA is used, the optimization level of the compiler, and the location of the data storage area (internal TCM SRAM or AXI SRAM) will all affect the reading speed.
* 5. In this routine, library functions are used for direct reading and writing, keil version 5.30, compiler AC6.14, compilation level Oz image size, reading speed is 7M bytes/S,
* The results are similar if the data is placed in TCM SRAM or AXI SRAM.
* 6. Directly use the HAL library for reading and writing, which is very slow. Using MDMA for reading can reach 58M bytes/S.
* 7. The maximum driving frequency allowed by W25Q64JV is 133MHz, and the maximum driving frequency of QSPI of 743 is also 133MHz. However, for direct reading by HAL library function,
* Driving clocks exceeding 15M will not improve performance. MDMA can be used in situations where speed requirements are high.
*
****************************************************** ****************************************************** **************FAN************/

int8_t QSPI_W25Qxx_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	QSPI_CommandTypeDef s_command; // QSPI transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1-line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS; // 24-bit address
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // No alternate bytes
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE; // Disable DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // Data delay in DDR mode, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD; // Send instructions every time data is transmitted
	s_command.AddressMode = QSPI_ADDRESS_4_LINES; // 4-line address mode
	s_command.DataMode = QSPI_DATA_4_LINES; // 4-line data mode
	s_command.DummyCycles = 6; // Number of dummy cycles
	s_command.NbData = NumByteToRead; // Data length, the maximum size cannot exceed the size of the flash chip
	s_command.Address = ReadAddr; // The address of W25Qxx to be read
	s_command.Instruction = W25Qxx_CMD_FastReadQuad_IO; // In 1-4-4 mode (1 line instruction, 4 lines address, 4 lines data), fast read instructions

	//Send read command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT; //Transmission data error
	}

	// Receive data

	if (HAL_QSPI_Receive(&hqspi, pBuffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT; //Transmission data error
	}

	//Use the automatic polling flag and wait for the end of reception
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting for no response
	}
	return QSPI_W25Qxx_OK; //Read data successfully
}


// Experimental platform: Anti-customer STM32H743VBT6 core board

/************************************************ ****************************************************** ****************************************************** ****************************************************** *FAN************/
