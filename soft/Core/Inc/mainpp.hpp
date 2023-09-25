/*
 * mainpp.h
 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */

#ifndef MAINPP_H_
#define MAINPP_H_

#ifdef __cplusplus
 extern "C" {
#endif

	#define pr_en_stuct htim3
	#define st_en_stuct htim2

	#define max_hurt_beat_period 1000 // ms

	enum motor_type{
		propulsion,
		steering,
	};

	enum service_msg{
		set_cnt_value_to_steering_encoder,		//0
		set_period_value_to_steering_encoder,
		save_settings_of_steering_encoder,

		set_cnt_value_to_propulsion_encoder,	//3
		set_period_value_to_propulsion_encoder,
		save_settings_of_propulsion_encoder,
	};


	void setup(void);
	void loop(void);


#ifdef __cplusplus
}
#endif


#endif /* MAINPP_H_ */
