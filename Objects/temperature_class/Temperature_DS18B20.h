/*
 * Temperature.h
 *
 *  Created on: Jan 19, 2021
 *      Author: nikita
 */

#ifndef TEMPERATURE_CLASS_TEMPERATURE_H_
#define TEMPERATURE_CLASS_TEMPERATURE_H_

#include "main.h"

typedef enum {
	DS18B20_RESOLUTION_9_BIT  = 0x1F,
	DS18B20_RESOLUTION_10_BIT = 0x3F,
	DS18B20_RESOLUTION_11_BIT = 0x5F,
	DS18B20_RESOLUTION_12_BIT = 0x7F
} DS18B20_RESOLUTION_t;

class Temperature_DS18B20 {
private:
	DS18B20_RESOLUTION_t resolution;

	TIM_TypeDef * TIM = {0};

	GPIO_TypeDef * Port = {0};
	uint16_t Pin = 0;

	uint32_t DELAY_WAIT_CONVERT = 0;
	uint32_t start_us = 0;

	void write_byte(uint8_t data);
	void write_bit(uint8_t bit);
	void reset(void);
	void delay_us(uint32_t n);


	uint32_t is_busy(void);
	void convert_t(void);
	uint8_t get_devider(DS18B20_RESOLUTION_t resolution);
	float obtain_temperature(void);

public:
	Temperature_DS18B20(TIM_TypeDef * tim, GPIO_TypeDef * port, uint16_t Pin);
	virtual ~Temperature_DS18B20();

	float get_data();

	void set_resolution(DS18B20_RESOLUTION_t resolution);
	DS18B20_RESOLUTION_t get_resolution();
};

#endif /* TEMPERATURE_CLASS_TEMPERATURE_H_ */
