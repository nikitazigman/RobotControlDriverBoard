#ifndef _ROS_robot_msgs_motors_h
#define _ROS_robot_msgs_motors_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.hpp"

namespace robot_msgs
{

  class motors : public ros::Msg
  {
    public:
      typedef int8_t _propulsion_type;
      _propulsion_type propulsion;
      typedef int8_t _steering_type;
      _steering_type steering;

    motors():
      propulsion(0),
      steering(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_propulsion;
      u_propulsion.real = this->propulsion;
      *(outbuffer + offset + 0) = (u_propulsion.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->propulsion);
      union {
        int8_t real;
        uint8_t base;
      } u_steering;
      u_steering.real = this->steering;
      *(outbuffer + offset + 0) = (u_steering.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->steering);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_propulsion;
      u_propulsion.base = 0;
      u_propulsion.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->propulsion = u_propulsion.real;
      offset += sizeof(this->propulsion);
      union {
        int8_t real;
        uint8_t base;
      } u_steering;
      u_steering.base = 0;
      u_steering.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->steering = u_steering.real;
      offset += sizeof(this->steering);
     return offset;
    }

    const char * getType(){ return "robot_msgs/motors"; };
    const char * getMD5(){ return "68667b4cd86d6cd8a15cd6ef5be7e069"; };

  };

}
#endif
