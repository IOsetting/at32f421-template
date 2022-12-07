#ifndef __AT32F421_DELAY_H
#define __AT32F421_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "at32f421.h"

/* exported functions ------------------------------------------------------- */
/**
  * @brief  initialize delay function
  * @param  none
  * @retval none
  */
void delay_init(void);

/**
  * @brief  inserts a delay time.
  * @param  nus: specifies the delay time length, in microsecond.
  * @retval none
  */
void delay_us(uint32_t nus);

/**
  * @brief  inserts a delay time.
  * @param  nms: specifies the delay time length, in milliseconds.
  * @retval none
  */
void delay_ms(uint16_t nms);


#ifdef __cplusplus
}
#endif

#endif /* __AT32F421_DELAY_H */

