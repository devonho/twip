#include "PIDController.h"

namespace twip {

PIDController::PIDController(){}
PIDController::~PIDController(){}

gz::msgs::Twist PIDController::step(const gz::msgs::Pose &_msg, gz::msgs::Twist twist_in) {
    gz::msgs::Quaternion qm = _msg.orientation();
    gz::math::Quaternionf q;
    q.Set(qm.w(),qm.x(),qm.y(),qm.z());

    gz::msgs::Twist twist_out;
    gz::msgs::Vector3d v_out;

    float pitch = twist_in.mutable_linear()->y() > 0 ? 0.01f : -0.01f;

    float err = q.Pitch() + pitch;

    float P = err * Kp;      
    float I = _cumerr * Ki;
    float D = (_lasterr - err) * Kd;         
    v_out.set_x(P + I + D);

    //root << log4cpp::Priority::DEBUG << (P + I + D);

    *twist_out.mutable_linear() = v_out;
    *twist_out.mutable_angular() = *twist_in.mutable_angular();
    
    _lasterr = err;
    _cumerr += err;
    return twist_out;
}

}