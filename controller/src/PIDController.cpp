#include "PIDController.h"

namespace twip {

PIDController::PIDController(){}
PIDController::~PIDController(){}

gz::msgs::Twist PIDController::step(const gz::msgs::Pose &_msg) {
    gz::msgs::Quaternion qm = _msg.orientation();
    gz::math::Quaternionf q;
    q.Set(qm.w(),qm.x(),qm.y(),qm.z());

    gz::msgs::Twist twist;
    gz::msgs::Vector3d v;

    float err = q.Pitch();

    float P = err * Kp;      
    float I = _cumerr * Ki;
    float D = (_lasterr - err) * Kd;         
    v.set_x(P + I + D);

    //root << log4cpp::Priority::DEBUG << (P + I + D);

    *twist.mutable_linear() = v;
    //pub.Publish(msg);
    
    _lasterr = err;
    _cumerr += err;
    return twist;
}

}