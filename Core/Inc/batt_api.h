/*
 * batt_api.h
 *
 *  Created on: 31 lip 2022
 *      Author: marci
 */

#ifndef INC_BATT_API_H_
#define INC_BATT_API_H_

#include "stm32wbxx_hal.h"

void updateBatteryLevel(uint8_t level);
void notifyBatteryLevel(uint8_t level);

#ifdef __cplusplus
extern "C"
{
#endif

/*
void setBatteryLevel(void);
*/

#ifdef __cplusplus
}
#endif

#endif /* INC_BATT_API_H_ */
