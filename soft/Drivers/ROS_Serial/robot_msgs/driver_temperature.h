#ifndef _ROS_robot_msgs_driver_temperature_h
#define _ROS_robot_msgs_driver_temperature_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.hpp"

namespace robot_msgs
{

  class driver_temperature : public ros::Msg
  {
    public:
      typedef float _propulsion_type;
      _propulsion_type propulsion;
      typedef float _steering_type;
      _steering_type steering;

    driver_temperature():
      propulsion(0),
      steering(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_propulsion;
      u_propulsion.real = this->propulsion;
      *(outbuffer + offset + 0) = (u_propulsion.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_propulsion.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_propulsion.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_propulsion.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->propulsion);
      union {
        float real;
        uint32_t base;
      } u_steering;
      u_steering.real = this->steering;
      *(outbuffer + offset + 0) = (u_steering.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_steering.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_steering.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_steering.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->steering);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_propulsion;
      u_propulsion.base = 0;
      u_propulsion.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_propulsion.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_propulsion.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_propulsion.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->propulsion = u_propulsion.real;
      offset += sizeof(this->propulsion);
      union {
        float real;
        uint32_t base;
      } u_steering;
      u_steering.base = 0;
      u_steering.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_steering.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_steering.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_steering.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->steering = u_steering.real;
      offset += sizeof(this->steering);
     return offset;
    }

    const char * getType(){ return "robot_msgs/driver_temperature"; };
    const char * getMD5(){ return "71449fe200b97c98b46ce390f7dd4ba2"; };

  };

}
#endif
