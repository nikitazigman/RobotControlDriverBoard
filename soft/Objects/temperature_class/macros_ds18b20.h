/*
 * macros_ds18b20.h
 *
 *  Created on: Jan 19, 2021
 *      Author: nikita
 */

#ifndef MACROS_DS18B20_H_
#define MACROS_DS18B20_H_

#define DELAY_RESET           500
#define DELAY_WRITE_0         60
#define DELAY_WRITE_0_PAUSE   10
#define DELAY_WRITE_1         10
#define DELAY_WRITE_1_PAUSE   60
#define DELAY_READ_SLOT       10
#define DELAY_BUS_RELAX       10
#define DELAY_READ_PAUSE      50
#define DELAY_T_CONVERT       760000
#define DELAY_T_PROTECTION    5

#define SKIP_ROM              0xCC
#define CONVERT_T             0x44
#define READ_SCRATCHPAD       0xBE
#define WRITE_SCRATCHPAD      0x4E
#define TH_REGISTER           0x4B
#define TL_REGISTER           0x46
#define DQ_LOW(Port,Pin) CLEAR_BIT(Port->ODR, Pin);
#define DQ_HIGH(Port,Pin) SET_BIT(Port->ODR, Pin);
#define READ_1(Port,Pin,x) ((uint16_t)(READ_BIT(Port->IDR, Pin) ? 1 : 0) << x)

#endif /* MACROS_DS18B20_H_ */
