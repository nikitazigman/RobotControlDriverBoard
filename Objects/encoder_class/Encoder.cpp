/*
 * Encoder.cpp
 *
 *  Created on: Dec 7, 2020
 *      Author: nikita
 */
#include <../Core/Inc/main.h>
#include "memory_map.hpp"
#include <encoder_class/Encoder.h>

//Encoder::Encoder() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Encoder::~Encoder() {
//	// TODO Auto-generated destructor stub
//}

Encoder::Encoder(TIM_HandleTypeDef *handler){
	htim = handler;
	address = ADDR_FLASH_SECTOR_7;
	settings_flash = (Settings *)address;
}

void Encoder::save(uint32_t period, uint32_t cnt){
	settings.origin_value = cnt;
	settings.period_value = period;
	store_in_flash();
}

void Encoder::set_cnt(uint32_t cnt){
	settings.origin_value = cnt;
	setup_timer();
}

uint32_t Encoder::get_cnt_period(){
	return settings.period_value;
}

uint32_t Encoder::get_cnt_value(){
	return htim->Instance->CNT;
}

void Encoder::set_period(uint32_t period){
	settings.period_value = period;
	setup_timer();
}

void Encoder::restart_counter(){
	settings.origin_value = 0;
	setup_timer();
}

void Encoder::setup_timer(){
	HAL_TIM_Encoder_Stop(htim,TIM_CHANNEL_ALL);


	htim->Init.Prescaler = 0;
	htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	htim->Init.Period = settings.period_value;
	htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 10;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 10;

	HAL_TIM_Encoder_Init(htim, &sConfig);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig);

	HAL_TIM_Encoder_Start(htim,TIM_CHANNEL_ALL);
	htim->Instance->CNT = settings.origin_value;
}

float Encoder::get_current_angle(){
	return ((float)htim->Instance->CNT * get_degree_per_value());
}

float Encoder::get_degree_per_value(){
	return 360.0/((float)settings.period_value);
}

void Encoder::get_settings(){
	if(settings_flash->origin_value == 0xFFFFFFFF){
		settings.origin_value = 0;
	}
	else{
		settings.origin_value = settings_flash->origin_value;
	}

	if(settings_flash->period_value == 0xFFFFFFFF){
		settings.period_value = 2400;
	}
	else{
		settings.period_value = settings_flash->period_value;
	}
}

void Encoder::erase_sector(){
	uint32_t SECTORError = 0;
	FLASH_EraseInitTypeDef EraseInitStruct;

	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector        = FLASH_SECTOR_7;
	EraseInitStruct.NbSectors     = 1;
	HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
}
void Encoder::store_in_flash(){
	HAL_FLASH_Unlock();
	erase_sector();
	for(uint32_t i=0; i< sizeof(settings); i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,address + i,(int8_t)*((int8_t*)&settings+i));
	}
	HAL_FLASH_Lock();
}

// public:
void Encoder::save(){
	store_in_flash();
}

void Encoder::init(){
	get_settings();
	setup_timer();
}
