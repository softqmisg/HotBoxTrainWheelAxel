#ifndef W25Q64_QSPI_H
#define W25Q64_QSPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#define W25Qxx_FlashSize       				0x800000		// W25Q64´óÐ¡£¬8M×Ö½Ú
#define W25Qxx_BlockSize_32k				0x8000
#define W25Qxx_BlockSize_64k				0x10000
#define W25Qxx_PageSize       				0x100			// Ò³´óÐ¡£¬256×Ö½Ú
#define W25Qxx_Mem_Addr						0x90000000 	// ÄÚ´æÓ³ÉäÄ£Ê½µÄµØÖ·

#define W25Qxx_FLASH_ID           			0xef4017    // W25Q64 JEDEC ID
#define W25Qxx_ChipErase_TIMEOUT_MAX		100000U		// ³¬Ê±µÈ´ýÊ±¼ä£¬W25Q64ÕûÆ¬²Á³ýËùÐè×î´óÊ±¼äÊÇ100S

#define W25Qxx_CMD_EnableReset  		0x66		//RESET_ENABLE_CMD// Ê¹ÄÜ¸´Î»
#define W25Qxx_CMD_ResetDevice   		0x99		//RESET_MEMORY_CMD// ¸´Î»Æ÷¼þ
#define W25Qxx_CMD_JedecID 				0x9F		//READ_ID_CMD2// JEDEC ID
#define W25Qxx_CMD_WriteEnable			0x06		//WRITE_ENABLE_CMD// Ð´Ê¹ÄÜ

#define W25Qxx_CMD_SectorErase 			0x20		//SECTOR_ERASE_CMD// ÉÈÇø²Á³ý£¬4K×Ö½Ú£¬ ²Î¿¼²Á³ýÊ±¼ä 45ms
#define W25Qxx_CMD_BlockErase_32K 		0x52		// ¿é²Á³ý£¬  32K×Ö½Ú£¬²Î¿¼²Á³ýÊ±¼ä 120ms
#define W25Qxx_CMD_BlockErase_64K 		0xD8		//BLOCK_ERASE_CMD// ¿é²Á³ý£¬  64K×Ö½Ú£¬²Î¿¼²Á³ýÊ±¼ä 150ms
#define W25Qxx_CMD_ChipErase 			0xC7		//CHIP_ERASE_CMD// ÕûÆ¬²Á³ý£¬²Î¿¼²Á³ýÊ±¼ä 20S

#define W25Qxx_CMD_QuadInputPageProgram 0x32  		//QUAD_IN_FAST_PROG_CMD// 1-1-4Ä£Ê½ÏÂ(1ÏßÖ¸Áî1ÏßµØÖ·4ÏßÊý¾Ý)£¬Ò³±à³ÌÖ¸Áî£¬²Î¿¼Ð´ÈëÊ±¼ä 0.4ms
#define W25Qxx_CMD_FastReadQuad_IO      0xEB  		//QUAD_INOUT_FAST_READ_CMD// 1-4-4Ä£Ê½ÏÂ(1ÏßÖ¸Áî4ÏßµØÖ·4ÏßÊý¾Ý)£¬¿ìËÙ¶ÁÈ¡Ö¸Áî

#define W25Qxx_CMD_ReadStatus_REG1		0x05		//READ_STATUS_REG1_CMD	// ¶Á×´Ì¬¼Ä´æÆ÷1
#define W25Qxx_Status_REG1_BUSY  		0x01		//WRITE_STATUS_REG1_CMD	// ¶Á×´Ì¬¼Ä´æÆ÷1µÄµÚ0Î»£¨Ö»¶Á£©£¬Busy±êÖ¾Î»£¬µ±ÕýÔÚ²Á³ý/Ð´ÈëÊý¾Ý/Ð´ÃüÁîÊ±»á±»ÖÃ1
#define W25Qxx_Status_REG1_WEL  		0x02		//PAGE_PROG_CMD	// ¶Á×´Ì¬¼Ä´æÆ÷1µÄµÚ1Î»£¨Ö»¶Á£©£¬WELÐ´Ê¹ÄÜ±êÖ¾Î»£¬¸Ã±êÖ¾Î»Îª1Ê±£¬´ú±í¿ÉÒÔ½øÐÐÐ´²Ù×÷

#define QSPI_W25Qxx_OK           		0		// W25QxxÍ¨ÐÅÕý³£
#define W25Qxx_ERROR_INIT         		-1		// ³õÊ¼»¯´íÎó
#define W25Qxx_ERROR_WriteEnable       -2		// Ð´Ê¹ÄÜ´íÎó
#define W25Qxx_ERROR_AUTOPOLLING       -3		// ÂÖÑ¯µÈ´ý´íÎó£¬ÎÞÏìÓ¦
#define W25Qxx_ERROR_Erase         		-4		// ²Á³ý´íÎó
#define W25Qxx_ERROR_TRANSMIT         	-5		// ´«Êä´íÎó
#define W25Qxx_ERROR_MemoryMapped		-6    // ÄÚ´æÓ³ÉäÄ£Ê½´íÎó


/*----------------------------------------------- º¯ÊýÉùÃ÷ ---------------------------------------------------*/

int8_t	QSPI_W25Qxx_Init(void);// W25Qxx³õÊ¼»¯
int8_t 	QSPI_W25Qxx_Reset(void);					// ¸´Î»Æ÷¼þ
uint32_t QSPI_W25Qxx_ReadID(void);					// ¶ÁÈ¡Æ÷¼þID
int8_t 	QSPI_W25Qxx_MemoryMappedMode(void);		// ½øÈëÄÚ´æÓ³ÉäÄ£Ê½

int8_t 	QSPI_W25Qxx_SectorErase(uint32_t SectorAddress);		// ÉÈÇø²Á³ý£¬4K×Ö½Ú£¬ ²Î¿¼²Á³ýÊ±¼ä 45ms
int8_t 	QSPI_W25Qxx_BlockErase_32K (uint32_t SectorAddress);	// ¿é²Á³ý£¬  32K×Ö½Ú£¬²Î¿¼²Á³ýÊ±¼ä 120ms
int8_t 	QSPI_W25Qxx_BlockErase_64K (uint32_t SectorAddress);	// ¿é²Á³ý£¬  64K×Ö½Ú£¬²Î¿¼²Á³ýÊ±¼ä 150ms£¬Êµ¼ÊÊ¹ÓÃ½¨ÒéÊ¹ÓÃ64K²Á³ý£¬²Á³ýµÄÊ±¼ä×î¿ì
int8_t 	QSPI_W25Qxx_ChipErase (void);                         // ÕûÆ¬²Á³ý£¬²Î¿¼²Á³ýÊ±¼ä 20S

int8_t	QSPI_W25Qxx_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);	// °´Ò³Ð´Èë£¬×î´ó256×Ö½Ú
int8_t	QSPI_W25Qxx_WriteBuffer(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);				// Ð´ÈëÊý¾Ý£¬×î´ó²»ÄÜ³¬¹ýflashÐ¾Æ¬µÄ´óÐ¡
int8_t 	QSPI_W25Qxx_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);	// ¶ÁÈ¡Êý¾Ý£¬×î´ó²»ÄÜ³¬¹ýflashÐ¾Æ¬µÄ´óÐ¡


#ifdef __cplusplus
}
#endif

#endif


