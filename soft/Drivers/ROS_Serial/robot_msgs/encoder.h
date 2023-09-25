#ifndef _ROS_robot_msgs_encoder_h
#define _ROS_robot_msgs_encoder_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.hpp"

namespace robot_msgs
{

  class encoder : public ros::Msg
  {
    public:
      typedef float _degree_type;
      _degree_type degree;
      typedef uint32_t _cnt_type;
      _cnt_type cnt;
      typedef uint32_t _period_type;
      _period_type period;

    encoder():
      degree(0),
      cnt(0),
      period(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_degree;
      u_degree.real = this->degree;
      *(outbuffer + offset + 0) = (u_degree.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_degree.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_degree.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_degree.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->degree);
      *(outbuffer + offset + 0) = (this->cnt >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cnt >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->cnt >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->cnt >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cnt);
      *(outbuffer + offset + 0) = (this->period >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->period >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->period >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->period >> (8 * 3)) & 0xFF;
      offset += sizeof(this->period);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_degree;
      u_degree.base = 0;
      u_degree.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_degree.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_degree.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_degree.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->degree = u_degree.real;
      offset += sizeof(this->degree);
      this->cnt =  ((uint32_t) (*(inbuffer + offset)));
      this->cnt |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->cnt |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->cnt |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->cnt);
      this->period =  ((uint32_t) (*(inbuffer + offset)));
      this->period |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->period |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->period |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->period);
     return offset;
    }

    const char * getType(){ return "robot_msgs/encoder"; };
    const char * getMD5(){ return "58b711c9cf2faad2034161aaca997fd4"; };

  };

}
#endif
