# README

## Description

This board was designed to controll delivery robot. 
The robot has 2 motors: one for propultion and one for sterring. 

The board communicates with the main PC trough COM Port interface using ROS serial commuication protocol. 
The software you can find [here](https://github.com/nikitazigman/RobotControlBoard_soft) 

The board contains: 
* two H bridges to operate DC motors ( you can also use it to controll LED strips). Theoretically the board can operate 30A and 30V. 
* the H bridges is controlled by MC STM32F446RET6 using PWM 
* COM Port interface to communicate with the PC or something. (We used it to communicate trough ROS serial with PC board)
* two connectors for temperature sensors db18b20 (one wire interface). We used them for monitoring temperature of the drivers. 
* two connectors for encoders. We used it for provideing odometry messages to ROS.
* micro USB connector. You can use it to power the board or you can use an other one 5V connector.   

## Project structure

The Altium project consist of 6 lists of cuircuit and one PCB files. 
In the Doc foled I put excel table with the list of all used components. 

Each of the lists except of [MAIN](MAIN.SchDoc) contains "independent" block. 

1. [MCU](MCU.SchDoc) I used the STM32F446RET6 microcontroller. Sheet also includes connectors that directely connected to it.
2. [H bridge](H_bridge.SchDoc) contains Full H bridge circuit. The Circuit was based on BTS7970B microchip, and totaly repeats circuit from the datasheet.
3. [COM Port](com_port.SchDoc) I used the UART-USB converter CP2102-GMR.
4. [Power supply](power_supply.SchDoc) in the project I used ADP3338AKCZ-3.3RL7 LDO to convert 5V to 3.3V 
5. [Cooler](Radiator.SchDoc) I used the sk68-75-sa radiator and fan for cooling the drivers  

## Errata note

1. I forgot to separate Power and digital GND and in case of high load you can have big noise in digital lines. I solved this problem using non galvanic isolation USB-USB board [ICQUANZX ADUM3160 ADUM3160 USB to USB](https://www.amazon.de/-/en/gp/product/B07Z21RKMN/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1)
2. The ground plane of drivers not wide enough to provide continuous 30A current
3. I didn't use protection stuff on my board beacause I have them outside of the board. I suggest to use some supressors and fuses for the protection :)
