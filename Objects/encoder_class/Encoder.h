/*
 * Encoder.h
 *
 *  Created on: Dec 7, 2020
 *      Author: nikita
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "tim.h"

class Encoder {
private:

	TIM_HandleTypeDef *htim;
	TIM_Encoder_InitTypeDef sConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	typedef struct{
		uint32_t origin_value;
		uint32_t period_value;
	}Settings;

	Settings *settings_flash;
	Settings settings;

	uint32_t address;

	void setup_timer();
	void get_settings();
	void store_in_flash();
	void erase_sector();

	float get_degree_per_value();

public:
	Encoder(TIM_HandleTypeDef *handler);

	void init();
	void save();
	void save(uint32_t period, uint32_t cnt);
	void restart_counter();
	void set_period(uint32_t period);
	void set_cnt(uint32_t cnt);

	uint32_t get_cnt_period();
	uint32_t get_cnt_value();
	float get_current_angle();
};

#endif /* ENCODER_H_ */
