#ifndef _ROS_robot_msgs_encoders_h
#define _ROS_robot_msgs_encoders_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.hpp"
#include "robot_msgs/encoder.h"

namespace robot_msgs
{

  class encoders : public ros::Msg
  {
    public:
      typedef robot_msgs::encoder _propulsion_type;
      _propulsion_type propulsion;
      typedef robot_msgs::encoder _steering_type;
      _steering_type steering;

    encoders():
      propulsion(),
      steering()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->propulsion.serialize(outbuffer + offset);
      offset += this->steering.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->propulsion.deserialize(inbuffer + offset);
      offset += this->steering.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "robot_msgs/encoders"; };
    const char * getMD5(){ return "d6ff90e96ffa7d67fd2af7908a7c42c7"; };

  };

}
#endif
