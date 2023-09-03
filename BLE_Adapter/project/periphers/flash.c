#include "string.h"

#include "flash.h"


uint32_t GetPage(uint32_t Addr)
{
  if(!IS_ADDR_ALIGNED_32BITS(Addr)){
    while(1);
  }
  uint32_t offset = Addr - FLASH_START_ADDR;
	uint32_t page = offset / FLASH_PAGE_SIZE;
  if(!IS_FLASH_PAGE(page)){
    while(1);
  }
  return page;
}


void read_flash(uint32_t start_address_offset, uint8_t *read_buff, uint32_t buff_size)
{
	uint32_t i;
	uint32_t word;

	for (i=0; i<buff_size; i+=4)
	{
		word = *(__IO uint32_t *)(FLASH_USER_START_ADDR + start_address_offset + i);
		memcpy((uint8_t*)&read_buff[i], (uint8_t*)&word, 4);
	}
}


void erase_flash(uint32_t start_address_offset, uint32_t buff_len)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t first_page = GetPage(FLASH_USER_START_ADDR + start_address_offset);
	uint32_t num_of_page = GetPage(FLASH_USER_START_ADDR + start_address_offset + buff_len) - first_page + 1;
	
	uint32_t PageError;
	EraseInitStruct.TypeErase   = FLASH_TYPE_ERASE_PAGES;
  EraseInitStruct.Page        = first_page;
  EraseInitStruct.NbPages     = num_of_page;
	
	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
}


void program_flash(uint32_t start_address_offset, uint8_t *program_buff, uint32_t buff_size)
{
	uint32_t word;
	uint32_t i;
	
	for (i=0; i<buff_size; i+=4)
	{
		memcpy((uint8_t*)&word, (uint8_t*)&program_buff[i], 4);
		if (HAL_FLASH_Program(FLASH_USER_START_ADDR + start_address_offset + i, word) != HAL_OK)
		{}
	}
}
