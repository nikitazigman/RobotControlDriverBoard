/*
 * Button.cpp
 *
 *  Created on: Jan 21, 2021
 *      Author: nikita
 */

#include "Button.h"

Button::Button(GPIO_TypeDef* port, uint16_t pin) {
	this->port = port;
	this->pin = pin;
}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

bool Button::get_state(){
	return this->state;
}

void Button::set_filter_time(int ms){
	this->filter_time = ms;
}

int Button::get_filter_time(void){
	return this->filter_time;
}

bool Button::state_update(void){
	GPIO_PinState gpio_state = HAL_GPIO_ReadPin(this->port, this->pin);

	if(gpio_state == this->temproary_state){
		if((HAL_GetTick() - this->tick) >= this->filter_time){
			this->state = gpio_state;
		}
	}
	else{
		this->temproary_state = gpio_state;
		this->tick = HAL_GetTick();
	}

	return this->state;
}
