/*
 * flashlib.h
 *
 *  Created on: Dec 9, 2020
 *      Author: Pasindu
 */

#ifndef INC_FLASHLIB_H_
#define INC_FLASHLIB_H_


#include "stm32f1xx_hal.h"



HAL_StatusTypeDef FlashErasePages(uint32_t PageAddress,uint32_t NbPages);
HAL_StatusTypeDef FlashWriteArr(uint32_t TypeProgram , uint32_t FlashAddress , uint64_t *pData , uint32_t sizeofarr  );
void FlashReadArr(uint32_t TypeProgram , uint32_t FlashAddress , uint64_t *pData , uint32_t lenofarr  );




#endif /* INC_FLASHLIB_H_ */
