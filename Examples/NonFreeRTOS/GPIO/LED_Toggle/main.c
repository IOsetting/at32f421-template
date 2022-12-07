/**
  **************************************************************************
  * @file     main.c
  * @version  v2.0.9
  * @date     2022-09-28
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f421_clock.h"
#include "at32f421_delay.h"

typedef enum
{
  LED2                                   = 0,
  LED3                                   = 1,
  LED4                                   = 2
} led_type;

#define LED_NUM                          3

#define LED2_PIN                         GPIO_PINS_6
#define LED2_GPIO                        GPIOF
#define LED2_GPIO_CRM_CLK                CRM_GPIOF_PERIPH_CLOCK

#define LED3_PIN                         GPIO_PINS_2
#define LED3_GPIO                        GPIOB
#define LED3_GPIO_CRM_CLK                CRM_GPIOB_PERIPH_CLOCK

#define LED4_PIN                         GPIO_PINS_13
#define LED4_GPIO                        GPIOC
#define LED4_GPIO_CRM_CLK                CRM_GPIOC_PERIPH_CLOCK


gpio_type *led_gpio_port[LED_NUM]        = {LED2_GPIO, LED3_GPIO, LED4_GPIO};
uint16_t led_gpio_pin[LED_NUM]           = {LED2_PIN, LED3_PIN, LED4_PIN};
crm_periph_clock_type led_gpio_crm_clk[LED_NUM] = {LED2_GPIO_CRM_CLK, LED3_GPIO_CRM_CLK, LED4_GPIO_CRM_CLK};

/**
  * @brief  configure led gpio
  * @param  led: specifies the led to be configured.
  * @retval none
  */
void at32_led_init(led_type led)
{
  gpio_init_type gpio_init_struct;

  /* enable the led clock */
  crm_periph_clock_enable(led_gpio_crm_clk[led], TRUE);

  /* set default parameter */
  gpio_default_para_init(&gpio_init_struct);

  /* configure the led gpio */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = led_gpio_pin[led];
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(led_gpio_port[led], &gpio_init_struct);
}

/**
  * @brief  turns selected led toggle.
  * @param  led: specifies the led to be set off.
  *   this parameter can be one of following parameters:
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval none
  */
void at32_led_toggle(led_type led)
{
  if(led > (LED_NUM - 1))
    return;
  if(led_gpio_pin[led])
    led_gpio_port[led]->odt ^= led_gpio_pin[led];
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  sclk_120m_hext_config();

  delay_init();

  at32_led_init(LED2);
  at32_led_init(LED3);
  at32_led_init(LED4);

  while(1)
  {
    at32_led_toggle(LED2);
    delay_ms(200);
    at32_led_toggle(LED3);
    delay_ms(200);
    at32_led_toggle(LED4);
    delay_ms(200);
  }
}
