/*
 * flashlib.c
 *
 *  Created on: Dec 9, 2020
 *      Author: Pasindu
 */

/* Includes ------------------------------------------------------------------*/
#include "flashlib.h"
#include <stdint.h>






/**
  * @brief  Perform a  erase the specified FLASH memory pages
  *
  * @param[in]  PageAdress: Initial FLASH page address to erase
  *             This parameter must be a number between
  *             Min_Data = 0x08000000 and Max_Data = FLASH_BANKx_END
  *             (x = 1 or 2 depending on devices)
  *
  * @param[in]  NbPages: Number of pagess to be erased.
  *             This parameter must be a value between
  *             Min_Data = 1 and Max_Data = (max number of pages - value of initial page)
  *

  *
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef FlashErasePages(uint32_t PageAddress,uint32_t NbPages)
{
  HAL_FLASH_Unlock();
  FLASH_EraseInitTypeDef FLASH_EraseInitStruct = {0};
  FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
  FLASH_EraseInitStruct.PageAddress = PageAddress;
  FLASH_EraseInitStruct.NbPages = NbPages;

  uint32_t  errorStatus = 0;

  HAL_StatusTypeDef statusErase = HAL_FLASHEx_Erase(&FLASH_EraseInitStruct,&errorStatus);

  HAL_FLASH_Lock();

  return statusErase;
}


/**
  * @brief  Program an array into the flash specified by the starting flash address.
  *         The array type can be either be word , halfword or doubleword
  *
  * @param  TypeProgram:  Indicate the way to program at a specified address.
  *                       This parameter can be a value of @ref FLASH_Type_Program
  *                       FLASH_TYPEPROGRAM_HALFWORD, FLASH_TYPEPROGRAM_WORD or FLASH_TYPEPROGRAM_DOUBLEWORD
  * 
  * @param  FlashAddress:      Specifies the starting address to be programmed.
  * 
  * @param  pData: Pointer to the array of data
  * 
  * @param sizeofarr: Use sizeof(pData) 
  *                   size of the array in bytes
  *
  */

HAL_StatusTypeDef FlashWriteArr(uint32_t TypeProgram , uint32_t FlashAddress , uint64_t *pData , uint32_t sizeofarr  )
{
  uint8_t index = 0;
  uint8_t fInc = 0;
  uint8_t nbiterations = 0;

  HAL_StatusTypeDef status = HAL_ERROR;

  HAL_FLASH_Unlock();

  if(TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
  {
	  uint16_t * pDataN = (uint16_t * )pData;
    nbiterations    = sizeofarr/2;
    fInc            = 1U;
    for (index = 0U; index < nbiterations; index++)
    {
    	status = HAL_FLASH_Program(TypeProgram,FlashAddress+index*2*fInc, *(pDataN ++));
    }
  }
  else if(TypeProgram == FLASH_TYPEPROGRAM_WORD)
  {
	  uint32_t * pDataN = (uint32_t * )pData;
    nbiterations    = sizeofarr/4;
    fInc            = 2U;
    for (index = 0U; index < nbiterations; index++)
    {
    	status = HAL_FLASH_Program(TypeProgram,FlashAddress+index*2*fInc, *(pDataN ++));
    }
  }
  else
  {
	  uint16_t * pDataN = (uint16_t * )pData;
    nbiterations    = sizeofarr/8;
    fInc            = 4U;
    for (index = 0U; index < nbiterations; index++)
    {
    	status = HAL_FLASH_Program(TypeProgram,FlashAddress+index*2*fInc, *(pDataN ++));
    }
  }



  HAL_FLASH_Lock();

  return status;

}


/**
  * @brief  Read an array of data from the flash specified by the starting flash address.
  *         The array type can be either be word , halfword or doubleword
  *
  * @param  TypeProgram:  Indicate the way to program at a specified address.
  *                       This parameter can be a value of @ref FLASH_Type_Program
  *                       FLASH_TYPEPROGRAM_HALFWORD, FLASH_TYPEPROGRAM_WORD or FLASH_TYPEPROGRAM_DOUBLEWORD
  * 
  * @param  FlashAddress:      Specifies the starting address to be programmed.
  * 
  * @param  pData: Pointer to the array of data
  * 
  * @param lenofarr: The size of the array.(Number of elements)
  *                   The number of @ref TypeProgram elements to be read from the flash
  *
  */
void FlashReadArr(uint32_t TypeProgram , uint32_t FlashAddress , uint64_t *pData , uint32_t lenofarr  )
{
  uint8_t index = 0;
  uint8_t fInc = 0;

  if(TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
  {
    uint16_t * pFlashAd = (uint16_t *) FlashAddress;
    uint16_t * pDataAd  = (uint16_t *) pData;


    for(index = 0U; index < lenofarr; index++)
    {
      *(pDataAd++) = *(pFlashAd++) ;
    }

  }
  else if(TypeProgram == FLASH_TYPEPROGRAM_WORD)
  {
    uint32_t * pFlashAd = (uint32_t *) FlashAddress;
    uint32_t * pDataAd  = (uint32_t *) pData;


    for(index = 0U; index < lenofarr; index++)
    {
      *(pDataAd++) = *(pFlashAd++) ;
    }
	  
  }
  else
  {
    uint64_t * pFlashAd = (uint64_t *) FlashAddress;
    uint64_t * pDataAd  = (uint64_t *) pData;


    for (index = 0U; index < lenofarr; index++)
    {
      *(pDataAd++) = *(pFlashAd++) ;
    }
	  
  }




}
