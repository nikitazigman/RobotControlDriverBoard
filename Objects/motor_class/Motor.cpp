/*
 * Motor.cpp
 *
 *  Created on: Dec 7, 2020
 *      Author: nikita
 */
#include "math.h"

#include "../Core/Inc/main.h"
#include "tim.h"

#include <motor_class/Motor.h>

Motor::Motor(Peripheral* motor_peripheral){
	peripheral = motor_peripheral;
	direction = None;
}

void Motor::set_up_timer(){
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	peripheral->htim->Instance = TIM4;
	peripheral->htim->Init.Prescaler = 1199;
	peripheral->htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	peripheral->htim->Init.Period = 300;
	peripheral->htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	peripheral->htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_TIM_PWM_Init(&htim4) != HAL_OK){
		Error_Handler();
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	if (HAL_TIMEx_MasterConfigSynchronization(peripheral->htim, &sMasterConfig) != HAL_OK){
		Error_Handler();
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;

	if (HAL_TIM_PWM_ConfigChannel(peripheral->htim, &sConfigOC, peripheral->tim_channel) != HAL_OK){
		Error_Handler();
	}
}

void Motor::set_pwm_value(uint32_t speed){
	switch(peripheral->tim_channel){
	case TIM_CHANNEL_1:
		peripheral->htim->Instance->CCR1 = 2*speed;
	case TIM_CHANNEL_2:
		peripheral->htim->Instance->CCR2 = 2*speed;
	case TIM_CHANNEL_3:
		peripheral->htim->Instance->CCR3 = 2*speed;
	case TIM_CHANNEL_4:
		peripheral->htim->Instance->CCR4 = 2*speed;
	}
}

void Motor::init(){
	set_up_timer();
	HAL_TIM_PWM_Start(peripheral->htim, peripheral->tim_channel);
}

void Motor::stop(){
	HAL_GPIO_WritePin(peripheral->backward_direction.port, peripheral->backward_direction.pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(peripheral->forward_direction.port, peripheral->forward_direction.pin, GPIO_PIN_RESET);
}

void Motor::set_speed(int8_t speed){
	if(speed > 0){
		if(direction != forward){
			stop();
			HAL_Delay(100);
		}
		HAL_GPIO_WritePin(peripheral->forward_direction.port, peripheral->forward_direction.pin, GPIO_PIN_SET);
		set_pwm_value(0xff & (uint32_t)(fabs(speed)*2));
		direction = forward;
	}
	else if(speed < 0){
		if(direction != backward){
			stop();
			HAL_Delay(100);
		}
		HAL_GPIO_WritePin(peripheral->backward_direction.port, peripheral->backward_direction.pin, GPIO_PIN_SET);
		set_pwm_value(0xff & (uint32_t)(fabs(speed)*2));
		direction = backward;
	}
	else{
		stop();
		direction = None;
	}
}

