/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_app.c
  * @author  MCD Application Team
  * @brief   Custom Example Application (Server)
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "batt_api.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* Device_Information */
  /* Battery */
  uint8_t               Bat_lvl_Notification_Status;
  /* Human_Interface_Device */
  uint8_t               Report_Notification_Status;
  /* USER CODE BEGIN CUSTOM_APP_Context_t */

  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */
typedef struct
{
  int16_t X;
  int16_t Y;
  int16_t Z;
  int8_t HAT;
  int8_t buttons;
} joystick_report_t;
/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

PLACE_IN_SECTION("BLE_APP_CONTEXT") static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

uint8_t UpdateCharData[247];
uint8_t NotifyCharData[247];

/* USER CODE BEGIN PV */
static uint8_t joystick_report[JOYSTICK_REPORT_SIZE] =
{
  /* joystick report */
  0x05, 0x01,                    /* USAGE_PAGE (Generic Desktop) */
  0x09, 0x04,                    /* USAGE (Joystick) */
  0xa1, 0x01,                    /* COLLECTION (Application) */
  0x09, 0x01,                    /*   USAGE (Pointer) */
  0xa1, 0x00,                    /*   COLLECTION (Physical) */
  0x75, 0x10,                    /*     REPORT_SIZE (16) */
  0x16, 0x01, 0x80,              /*     LOGICAL_MINIMUM (-32767) */
  0x26, 0xff, 0x7f,              /*     LOGICAL_MAXIMUM (32767) */
  0x09, 0x30,                    /*     USAGE (X) */
  0x09, 0x31,                    /*     USAGE (Y) */
  0x09, 0x32,                    /*     USAGE (Z) */
  0x95, 0x03,                    /*     REPORT_COUNT (3) */
  0x81, 0x02,                    /*     INPUT (Data,Var,Abs) */
  0xc0,                          /*   END_COLLECTION (Physical) */
  0x09, 0x39,                    /*   USAGE (Hat switch) */
  0x15, 0x01,                    /*   LOGICAL_MINIMUM (1) */
  0x25, 0x08,                    /*   LOGICAL_MAXIMUM (8) */
  0x35, 0x00,                    /*   PHYSICAL_MINIMUM (0) */
  0x46, 0x3b, 0x01,              /*   PHYSICAL_MAXIMUM (315) */
  0x65, 0x14,                    /*   UNIT (Eng Rot:Angular Pos) */
  0x75, 0x04,                    /*   REPORT_SIZE (4) */
  0x95, 0x01,                    /*   REPORT_COUNT (1) */
  0x81, 0x42,                    /*   INPUT (Data,Var,Abs, Null) */
  0x75, 0x04,                    /*   REPORT_SIZE (4) */
  0x95, 0x01,                    /*   REPORT_COUNT (1) */
  0x81, 0x41,                    /*   INPUT (Cnst,Ary,Abs,Null) */
  0x05, 0x09,                    /*   USAGE_PAGE (Button) */
  0x19, 0x01,                    /*   USAGE_MINIMUM (Button 1) */
  0x29, 0x08,                    /*   USAGE_MAXIMUM (Button 8) */
  0x15, 0x00,                    /*   LOGICAL_MINIMUM (0) */
  0x25, 0x01,                    /*   LOGICAL_MAXIMUM (1) */
  0x75, 0x01,                    /*   REPORT_SIZE (1) */
  0x95, 0x08,                    /*   REPORT_COUNT (8) */
  0x55, 0x00,                    /*   UNIT_EXPONENT (0) */
  0x65, 0x00,                    /*   UNIT (None) */
  0x81, 0x02,                    /*   INPUT (Data,Var,Abs) */
  0xc0                           /* END_COLLECTION (Application) */
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* Device_Information */
/* Battery */
static void Custom_Bat_lvl_Update_Char(void);
static void Custom_Bat_lvl_Send_Notification(void);
/* Human_Interface_Device */
static void Custom_Report_Update_Char(void);
static void Custom_Report_Send_Notification(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */

  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* Device_Information */
    case CUSTOM_STM_MAN_NAME_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MAN_NAME_READ_EVT */

      /* USER CODE END CUSTOM_STM_MAN_NAME_READ_EVT */
      break;

    case CUSTOM_STM_MOD_NUMB_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MOD_NUMB_READ_EVT */

      /* USER CODE END CUSTOM_STM_MOD_NUMB_READ_EVT */
      break;

    case CUSTOM_STM_PNP_ID_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_PNP_ID_READ_EVT */

      /* USER CODE END CUSTOM_STM_PNP_ID_READ_EVT */
      break;

    /* Battery */
    case CUSTOM_STM_BAT_LVL_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_BAT_LVL_READ_EVT */

      /* USER CODE END CUSTOM_STM_BAT_LVL_READ_EVT */
      break;

    case CUSTOM_STM_BAT_LVL_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_BAT_LVL_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_BAT_LVL_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_BAT_LVL_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_BAT_LVL_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_BAT_LVL_NOTIFY_DISABLED_EVT */
      break;

    /* Human_Interface_Device */
    case CUSTOM_STM_HID_INFO_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_HID_INFO_READ_EVT */

      /* USER CODE END CUSTOM_STM_HID_INFO_READ_EVT */
      break;

    case CUSTOM_STM_REP_MAP_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_REP_MAP_READ_EVT */

      /* USER CODE END CUSTOM_STM_REP_MAP_READ_EVT */
      break;

    case CUSTOM_STM_REPORT_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_REPORT_READ_EVT */

      /* USER CODE END CUSTOM_STM_REPORT_READ_EVT */
      break;

    case CUSTOM_STM_REPORT_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_REPORT_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_REPORT_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_REPORT_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_REPORT_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_REPORT_NOTIFY_DISABLED_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */

      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */
    tBleStatus result = BLE_STATUS_INVALID_PARAMS;

    /*UTIL_SEQ_RegTask( 1<< CFG_TASK_HID_UPDATE_REQ_ID, UTIL_SEQ_RFU, HIDSAPP_Profile_UpdateChar );*/

    result = Custom_STM_App_Update_Char(CUSTOM_STM_REP_MAP, (uint8_t *)joystick_report);

    if( result == BLE_STATUS_SUCCESS )
    {
      BLE_DBG_APP_MSG("Report Map Successfully Sent\n");
    }
    else
    {
      BLE_DBG_APP_MSG("Sending of Report Map Failed error 0x%X\n", result);
    }
  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/* Device_Information */
/* Battery */
void Custom_Bat_lvl_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Bat_lvl_UC_1*/
  static uint8_t previousBatLvl = 0;
  if(UpdateCharData[0] != previousBatLvl)
  {
      previousBatLvl = UpdateCharData[0];
      updateflag = 1;
  }
  /* USER CODE END Bat_lvl_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_BAT_LVL, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Bat_lvl_UC_Last*/

  /* USER CODE END Bat_lvl_UC_Last*/
  return;
}

void Custom_Bat_lvl_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Bat_lvl_NS_1*/
  static uint8_t previousBatLvl = 0;
  if(NotifyCharData[0] != previousBatLvl)
  {
      previousBatLvl = NotifyCharData[0];
      updateflag = 1;
  }
  /* USER CODE END Bat_lvl_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_BAT_LVL, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Bat_lvl_NS_Last*/

  /* USER CODE END Bat_lvl_NS_Last*/

  return;
}

/* Human_Interface_Device */
void Custom_Report_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Report_UC_1*/
  joystick_report_t joystick_report = {1,2,3,4,5};
  memcpy(UpdateCharData, &joystick_report, sizeof(joystick_report_t));
  updateflag = 1;
  /* USER CODE END Report_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_REPORT, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Report_UC_Last*/

  /* USER CODE END Report_UC_Last*/
  return;
}

void Custom_Report_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Report_NS_1*/

  /* USER CODE END Report_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_REPORT, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Report_NS_Last*/

  /* USER CODE END Report_NS_Last*/

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/

void updateBatteryLevel(uint8_t level)
{
    UpdateCharData[0] = level;
    Custom_Bat_lvl_Update_Char();
}

void notifyBatteryLevel(uint8_t level)
{
    NotifyCharData[0] = level;
    Custom_Bat_lvl_Send_Notification();
}

/* USER CODE END FD_LOCAL_FUNCTIONS*/
