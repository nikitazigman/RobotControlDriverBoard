/*
 * main.cpp

 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */
#include <mainpp.hpp>
#include <ros.hpp>
#include "main.h"
#include "tim.h"

#include "../Objects/encoder_class/Encoder.h"
#include "../Objects/motor_class/Motor.h"
#include "../Objects/temperature_class/Temperature_DS18B20.h"
#include "../Objects/button_class/Button.h"

#include <std_msgs/Float32.h>
#include <std_msgs/Int8MultiArray.h>
#include <std_msgs/UInt8.h>

#include <robot_msgs/encoders.h>
#include <robot_msgs/driver_settings.h>
#include <robot_msgs/motors.h>
#include <robot_msgs/driver_temperature.h>

void motor_control(const robot_msgs::motors& msg);
void serviceCallBack(const robot_msgs::driver_settings& ros_service_msg);

int timer_for_publisher = 0;
int emergency_timer_hurt_beat = 0;

ros::NodeHandle nh;

robot_msgs::encoders robot_odometry_msg;
robot_msgs::driver_temperature temperature_msg;

ros::Publisher robot_odometry_pub("encoders", &robot_odometry_msg);
ros::Publisher robot_temperature_pub("drivers_temp", &temperature_msg);

ros::Subscriber <robot_msgs::motors> motors("motors",&motor_control);
ros::Subscriber <robot_msgs::driver_settings> service("driver_settings",&serviceCallBack);

Encoder encoder_sterring(&st_en_stuct);
Encoder encoder_propulsion(&pr_en_stuct);

Peripheral steering_peripheral(
		&htim4,
		TIM_CHANNEL_2,
		steering_forward_enable_GPIO_Port,
		steering_forward_enable_Pin,
		steering_backward_enable_GPIO_Port,
		steering_backward_enable_Pin
);

Peripheral propulsion_peripheral(
		&htim4,
		TIM_CHANNEL_1,
		propulsion_forward_enable_GPIO_Port,
		propulsion_forward_enable_Pin,
		propulsion_backward_enable_GPIO_Port,
		propulsion_backward_enable_Pin
);

Motor steering_motor(&steering_peripheral);
Motor propulsion_motor(&propulsion_peripheral);

Temperature_DS18B20 propulsion_temperature(TIM5, temp_propulsion_GPIO_Port, temp_propulsion_Pin);
Temperature_DS18B20 steering_temperature(TIM5, temp_steering_GPIO_Port, temp_steering_Pin);

Button emergency_btn(emergency_btn_GPIO_Port, emergency_btn_Pin);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void emergency_handler(){
	if(emergency_btn.state_update()==false){
		propulsion_motor.set_speed(0);
		steering_motor.set_speed(0);
	}
	if((HAL_GetTick() - emergency_timer_hurt_beat) >= max_hurt_beat_period){
		propulsion_motor.set_speed(0);
		steering_motor.set_speed(0);
	}
}

void serviceCallBack(const robot_msgs::driver_settings& ros_service_msg){
	service_msg command = (service_msg) ros_service_msg.command;
	float data = ros_service_msg.data;

	switch(command){
		case set_cnt_value_to_steering_encoder:
			encoder_sterring.set_cnt(data);
			break;
		case set_cnt_value_to_propulsion_encoder:
			encoder_propulsion.set_cnt(data);
			break;
		case set_period_value_to_steering_encoder:
			encoder_sterring.set_period(data);
			break;
		case set_period_value_to_propulsion_encoder:
			encoder_propulsion.set_period(data);
			break;
		case save_settings_of_steering_encoder:
			encoder_sterring.save();
			break;
		case save_settings_of_propulsion_encoder:
			encoder_sterring.save();
			break;
	}
}

void motor_control(const robot_msgs::motors& msg){
	emergency_timer_hurt_beat = HAL_GetTick();
	if(emergency_btn.get_state()==true){
		propulsion_motor.set_speed(msg.propulsion);
		steering_motor.set_speed(msg.steering);
	}
}

void publish_encoders_data(){
	robot_odometry_msg.propulsion.degree = encoder_propulsion.get_current_angle();
	robot_odometry_msg.propulsion.cnt = encoder_propulsion.get_cnt_value();
	robot_odometry_msg.propulsion.period = encoder_propulsion.get_cnt_period();

	robot_odometry_msg.steering.degree = encoder_sterring.get_current_angle();
	robot_odometry_msg.steering.cnt = encoder_sterring.get_cnt_value();
	robot_odometry_msg.steering.period = encoder_sterring.get_cnt_period();

	robot_odometry_pub.publish(&robot_odometry_msg);
}

void publish_temperature_data(){
	temperature_msg.propulsion = propulsion_temperature.get_data();
	temperature_msg.steering = steering_temperature.get_data();

	robot_temperature_pub.publish(&temperature_msg);
}

void setup(void){
	nh.initNode();

	nh.advertise(robot_odometry_pub);
	nh.advertise(robot_temperature_pub);

  	nh.subscribe(motors);
  	nh.subscribe(service);

  	encoder_sterring.init();
  	encoder_propulsion.init();

  	steering_motor.init();
  	propulsion_motor.init();

  	propulsion_temperature.set_resolution(DS18B20_RESOLUTION_12_BIT);
  	steering_temperature.set_resolution(DS18B20_RESOLUTION_12_BIT);

	timer_for_publisher = HAL_GetTick();

	emergency_btn.set_filter_time(10); //ms
}


void loop(void){
	if(HAL_GetTick() - timer_for_publisher > 500){
		timer_for_publisher = HAL_GetTick();
		publish_encoders_data();
		publish_temperature_data();
	}
	emergency_handler();


	nh.spinOnce();
}


