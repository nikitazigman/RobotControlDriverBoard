/*
 * Temperature.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: nikita
 */

#include <temperature_class/Temperature_DS18B20.h>
#include <temperature_class/macros_ds18b20.h>

Temperature_DS18B20::Temperature_DS18B20(TIM_TypeDef * tim, GPIO_TypeDef * port, uint16_t pin) {
	this->TIM = tim;
	this->Port = port;
	this->Pin = pin;
}

Temperature_DS18B20::~Temperature_DS18B20() {
	// TODO Auto-generated destructor stub
}

void Temperature_DS18B20::convert_t(void) {
	reset();
	write_byte(SKIP_ROM);
	write_byte(CONVERT_T);
	start_us = HAL_GetTick();
}


uint32_t Temperature_DS18B20::is_busy(void) {
	return (HAL_GetTick() - start_us) > DELAY_WAIT_CONVERT;
}

void Temperature_DS18B20::delay_us(uint32_t n) {
	TIM->ARR = n - 1;
	TIM->CNT = TIM->ARR;
	TIM->CR1 |= TIM_CR1_CEN; // start the timer
	while (TIM->CNT != 0);
	TIM->CR1 &= ~TIM_CR1_CEN; // stop the timer
}

void Temperature_DS18B20::reset(void) {
	DQ_LOW(Port,Pin);
	delay_us(DELAY_RESET);
	DQ_HIGH(Port,Pin);
	delay_us(DELAY_RESET);
}

void Temperature_DS18B20::write_bit(uint8_t bit) {
	DQ_LOW(Port,Pin);
	delay_us(bit ? DELAY_WRITE_1 : DELAY_WRITE_0);
	DQ_HIGH(Port,Pin);
	delay_us(bit ? DELAY_WRITE_1_PAUSE : DELAY_WRITE_0_PAUSE);
}

void Temperature_DS18B20::write_byte(uint8_t data) {
	for (uint8_t i = 0; i < 8; i++) {
		write_bit(data >> i & 1);
		delay_us(DELAY_T_PROTECTION);
	}
}

uint8_t Temperature_DS18B20::get_devider(DS18B20_RESOLUTION_t resolution) {
	if (resolution == DS18B20_RESOLUTION_9_BIT) {
		return 8;
	} else if (resolution == DS18B20_RESOLUTION_10_BIT) {
		return 4;
	} else if (resolution == DS18B20_RESOLUTION_11_BIT) {
		return 2;
	} else { // DS18B20_RESOLUTION_12_BIT
		return 1;
	}
}

float Temperature_DS18B20::obtain_temperature(void) {
	int temperature=0;

	reset();
	write_byte(SKIP_ROM);
	write_byte(READ_SCRATCHPAD);

	for (uint8_t i = 0; i < 16; i++) {
		DQ_LOW(Port,Pin);
		delay_us(DELAY_READ_SLOT);

		DQ_HIGH(Port,Pin);
		delay_us(DELAY_BUS_RELAX);

		temperature += READ_1(Port,Pin,i);
		delay_us(DELAY_READ_PAUSE);
	}

	return ((float)temperature / 16.0f);
}

float Temperature_DS18B20::get_data(void){
	float temperature = 0;
	__disable_irq();

	this->convert_t();
	while(is_busy());
	temperature = this->obtain_temperature();

	__enable_irq();

	return temperature;
}

void Temperature_DS18B20::set_resolution(DS18B20_RESOLUTION_t resolution) {

	reset();
	write_byte(SKIP_ROM);
	write_byte(WRITE_SCRATCHPAD);
	write_byte(TH_REGISTER);
	write_byte(TL_REGISTER);
	write_byte(resolution);
	DELAY_WAIT_CONVERT = DELAY_T_CONVERT / get_devider(resolution);

}
