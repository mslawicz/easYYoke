/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_stm.h
  * @author  MCD Application Team
  * @brief   Header for custom_stm.c module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#ifndef __CUSTOM_STM_H
#define __CUSTOM_STM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  /* Device_Information */
  CUSTOM_STM_MAN_NAME,
  CUSTOM_STM_MOD_NUMB,
  CUSTOM_STM_PNP_ID,
  /* Battery */
  CUSTOM_STM_BAT_LVL,
  /* Human_Interface_Device */
  CUSTOM_STM_HID_INFO,
  CUSTOM_STM_REP_MAP,
  CUSTOM_STM_REPORT,
} Custom_STM_Char_Opcode_t;

typedef enum
{
  /* Manufacturer_Name_String */
  CUSTOM_STM_MAN_NAME_READ_EVT,
  /* Model_Number_String */
  CUSTOM_STM_MOD_NUMB_READ_EVT,
  /* PnP_ID */
  CUSTOM_STM_PNP_ID_READ_EVT,
  /* Battery_Level */
  CUSTOM_STM_BAT_LVL_READ_EVT,
  CUSTOM_STM_BAT_LVL_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_BAT_LVL_NOTIFY_DISABLED_EVT,
  /* Human_Interface_Device_Information */
  CUSTOM_STM_HID_INFO_READ_EVT,
  /* Report_Map */
  CUSTOM_STM_REP_MAP_READ_EVT,
  /* Report */
  CUSTOM_STM_REPORT_READ_EVT,
  CUSTOM_STM_REPORT_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_REPORT_NOTIFY_DISABLED_EVT,

  CUSTOM_STM_BOOT_REQUEST_EVT
} Custom_STM_Opcode_evt_t;

typedef struct
{
  uint8_t * pPayload;
  uint8_t   Length;
} Custom_STM_Data_t;

typedef struct
{
  Custom_STM_Opcode_evt_t       Custom_Evt_Opcode;
  Custom_STM_Data_t             DataTransfered;
  uint16_t                      ConnectionHandle;
  uint8_t                       ServiceInstance;
} Custom_STM_App_Notification_evt_t;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
extern uint8_t SizeMan_Name;
extern uint8_t SizeMod_Numb;
extern uint8_t SizePnp_Id;
extern uint8_t SizeBat_Lvl;
extern uint8_t SizeHid_Info;
extern uint8_t SizeRep_Map;
extern uint8_t SizeReport;

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions ------------------------------------------------------- */
void SVCCTL_InitCustomSvc(void);
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification);
tBleStatus Custom_STM_App_Update_Char(Custom_STM_Char_Opcode_t CharOpcode,  uint8_t *pPayload);
/* USER CODE BEGIN EF */

/* USER CODE END EF */

#ifdef __cplusplus
}
#endif

#endif /*__CUSTOM_STM_H */
