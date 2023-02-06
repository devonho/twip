#ifndef __PIDCONTROLLER_H__
#define __PIDCONTROLLER_H__

#include <gz/msgs.hh>
#include <gz/transport.hh>

namespace twip {

class PIDController {

    float _lasterr = 0.0f;
    float _cumerr = 0.0f;
public:
    PIDController();
    ~PIDController();
    gz::msgs::Twist step(const gz::msgs::Pose &_msg);
    float Kp = 100.0;
    float Ki = 0.0;
    float Kd = 10.0;
};

}


#endif // __PIDCONTROLLER_H__