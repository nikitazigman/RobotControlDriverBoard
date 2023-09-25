/*
 * Motor.h
 *
 *  Created on: Dec 7, 2020
 *      Author: nikita
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "tim.h"
#include "gpio.h"
#include "main.h"

class Peripheral{
private:
	typedef struct{
		GPIO_TypeDef * port;
		uint16_t pin;
	}GPIO;
public:
	TIM_HandleTypeDef* htim;
	uint32_t tim_channel;
	GPIO forward_direction;
	GPIO backward_direction;

	Peripheral(TIM_HandleTypeDef* htim_t, uint32_t tim_channel_t,
			GPIO_TypeDef * forward_port, uint16_t forward_pin,
			GPIO_TypeDef * backward_port, uint16_t backward_pin){
		htim = htim_t;
		tim_channel = tim_channel_t;
		forward_direction.port = forward_port;
		forward_direction.pin = forward_pin;
		backward_direction.port = backward_port;
		backward_direction.pin = backward_pin;
	}
};

class Motor {
private:
	enum motor_direction{
		None,
		forward,
		backward,
	};

	motor_direction direction;

	Peripheral* peripheral;

	void set_up_timer();
	void set_pwm_value(uint32_t speed);

public:
	Motor(Peripheral* motor_peripheral);
	void init();
	void stop();
	void set_speed(int8_t speed);
};

#endif /* MOTOR_H_ */
