/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include <string.h>
#include <stdio.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef struct 
{
  uint8_t Payload[10];
  uint8_t len ;
}Cmd_t;

typedef enum
{
  MAIN_MENU_STATE,
  LED_EFFECT_STATE,
  RTC_MENU_STATE,
  RTC_TIME_CFG_STATE,
  RTC_DATE_CFG_STATE,
  RTC_REPORT_STATE
}State_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

extern State_t current_state ;

extern TaskHandle_t handle_menu_task;
extern TaskHandle_t handle_led_task;
extern TaskHandle_t handle_rtc_task;
extern TaskHandle_t handle_print_task;
extern TaskHandle_t handle_cmd_task;


extern QueueHandle_t   Q_print ;
extern QueueHandle_t   Q_data ;

extern TimerHandle_t handle_led_timer[4];

extern UART_HandleTypeDef huart2;

extern RTC_HandleTypeDef hrtc;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

void LedEffectAction1(void);
void LedEffectAction2(void);
void LedEffectAction3(void);
void LedEffectAction4(void);
void LedEffectStart(uint8_t effect_num);
void LedEffectStop(void);
void RTC_ShowTimeDate(void);
void RTC_ConfigTime(uint8_t hours , uint8_t min , uint8_t sec);
void RTC_ConfigDate(uint8_t day , uint8_t month , uint8_t year);
uint8_t RTC_ValidateRTCTimeConfig(uint8_t hour , uint8_t min , uint8_t sec);
uint8_t RTC_ValidateRTCDateConfig(uint8_t day , uint8_t month , uint8_t Year);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define LED1_PORT         GPIOC
#define LED2_PORT         GPIOC
#define LED3_PORT         GPIOC
#define LED4_PORT         GPIOA

#define LED1_PIN          GPIO_PIN_5
#define LED2_PIN          GPIO_PIN_6
#define LED3_PIN          GPIO_PIN_8
#define LED4_PIN          GPIO_PIN_12

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
