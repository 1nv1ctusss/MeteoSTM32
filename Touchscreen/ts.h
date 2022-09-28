/*
 ******************************************************************************
 * @file    ts.h
 * @author  MCD Application Team
 * @version V4.0.1
 * @date    21-July-2015
 * @brief   This file contains all the functions prototypes for the Touch Screen driver.
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TS_H
#define __TS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h> 

typedef struct {
	void       (*Init)(uint16_t);
	uint8_t   (*ReadID)(uint16_t);
	void       (*Start)(uint16_t);
	uint8_t    (*DetectTouch)(uint16_t, uint16_t*, uint16_t*);
}TS_DrvTypeDef;

#ifdef __cplusplus
}
#endif

#endif /* __TS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
