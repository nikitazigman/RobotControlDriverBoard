# SOFTWARE PART

## ROS TOPICS

### Published Topics

1. **/encoders** [robot_msgs::encoders](#defined-msgs)
2. **/drivers_temp** [robot_msgs::driver_temperature](#defined-msgs)

### Subsribed Topics

1. **/motors** [robot_msgs::motors](#defined-msgs)
2. **/driver_settings** [robot_msgs::driver_settings](#defined-msgs) (see [posible commands](#comands))

## Defined msgs

robot_msgs::encoder

    float32 degree // value of encoder in degeree
    uint32 cnt // value of encoder's counter register TIMx -> CNT
    uint32 period // value of encoder's period register TIMx -> ARR

robot_msgs::encoders

    encoder steering
    encoder propulsion

robot_msgs::driver_settings

    uint8 command // comand to the device
    std_msgs/Float32MultiArray data // data of comand 

robot_msgs::motors

    int8 propulsion
    int8 steering

robot_msgs::temperature_msg

    float32 propulsion
    float32 steering

## COMANDS

topic [\driver_settings](#subscribed-topics) was defined for sending settings comands to the device. Msg of this topics includes fields of comand and data.

- The **comand** field is needed to send type of command ([see Supported Comands](#supported-comands)).
- The **data** field is needed to send related to command data ([see Example](#example-of-comand))

### Supported Comands

| name                                   | command | data           |
|----------------------------------------|---------|----------------|
|set_cnt_value_to_steering_encoder       |0        | [0:0xFFFFFFFF] |
|set_period_value_to_steering_encoder    |1        | [0:0xFFFFFFFF] |
|save_settings_of_steering_encoder       |2        | -              |
|set_cnt_value_to_propulsion_encoder     |3        | [0:0xFFFFFFFF] |
|set_period_value_to_propulsion_encoder  |4        | [0:0xFFFFFFFF] |
|save_settings_of_propulsion_encoder     |5        | -              |

### Examples

#### Example of set_cnt_value_to_steering_encoder comand

write in CNT value of steering encoder 10

    ~$ rostopic pub /service robot_control/service "command: 0
    data: 10"

#### Example of save_settings_of_propulsion_encoder comand

save porpulsion encoder's values of period and CNT in an internal FLASH of the device

    ~$ rostopic pub /service robot_control/service "command: 5
    data: 0"

#### How device pars it ([see source code here](Core/Src/maincpp.cpp) line 49)

```C++
enum service_msg{
  set_cnt_value_to_steering_encoder,
  set_period_value_to_steering_encoder,
  save_settings_of_steering_encoder,

  set_cnt_value_to_propulsion_encoder,
  set_period_value_to_propulsion_encoder,
  save_settings_of_propulsion_encoder,
};

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
```

## MOTORS

**NOTICE**: you should send this message with the rate higher than 1 hz (e.g. -r 100). If the frequency is less the program will stop the motors.  

**robot_control::motors** is used for controling the motors.
For sending command to motors 2 bytes is used:

- **propulsion** for propulsion motor [-127..127]
- **steering** for steering motor [-127..127]

To send msg to motors type

    $ rostopic pub /motors robot_control/motors "propulsion: <propulsion_motor_byte>
      steering: <steering_motor_byte>

to stop motors just send to the topic [0,0]

    $ rostopic pub /motors robot_control/motors "propulsion: 0
      steering:  0

## FLOW HOW TO WORK  

For starting work with the device you need to start roscore and launch rosserial

    $roscore

In second terminal

    $rosrun rosserial_python serial_node.py

then In third terminal check rostopic. You should see [these topics](#ros-topics)

    $rostopic list

if you don't see the topics, check the USB COM (I use default value, maybe you need to send your com port to rosserial)

Device UART settings:

- baud rate **57600**
- word length **8 bits**
- stop bits **1**
- parity **none**

## CODE STRUCTURE

- [Core](Core) - Here are core source files. They describe main flow of programm.
- [Drivers](Drivers) - Here are [CMSIS](Drivers\CMSIS), [HAL](Drivers\STM32F4xx_HAL_Driver) and [ROS_Serial](Drivers\ROS_Serial) libraries
- [Objects](Objects) - Here are my classes of device's objects (e.g. encoder class)

I hope other folders you will never need

## HARDWARE PART
  
you can find it [here](https://github.com/nikitazigman/RobotControlBoard_hard)

### P.S

Hope you won't burn my board :))
