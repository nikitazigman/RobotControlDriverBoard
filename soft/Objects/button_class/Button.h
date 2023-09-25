/*
 * Button.h
 *
 *  Created on: Jan 21, 2021
 *      Author: nikita
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"
#include "stdbool.h"

class Button {
private:
 GPIO_TypeDef* port = {0};
 uint16_t pin = 0;

 bool state = 0;
 bool enter_trigger = 0;
 bool temproary_state = 0;

 uint32_t filter_time = 0;

 uint32_t tick=0;

public:
	Button(GPIO_TypeDef* port, uint16_t pin);
	virtual ~Button();

	void set_filter_time(int ms);
	int get_filter_time(void);
	bool get_state(void);

	bool state_update(void);
};

#endif /* BUTTON_H_ */
