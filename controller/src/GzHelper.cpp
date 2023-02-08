#include "GzHelper.h"

namespace twip 
{

GzHelper* GzHelper::_pInstance = NULL;

GzHelper* GzHelper::getInstance()
{
    if(_pInstance == NULL)
    {
        _pInstance = new GzHelper();
    }
    return _pInstance;
}

void GzHelper::posecb(const gz::msgs::Pose &_msg)
{
    GzHelper::getInstance()->_pose_mq.push(_msg);
}

void GzHelper::keyboardcb(const gz::msgs::Int32 &_msg)
{
    GzHelper::getInstance()->_keyboard_mq.push(_msg);
}

GzHelper::GzHelper()
{
    _pub = _node.Advertise<gz::msgs::Twist>("/cmd_vel");
    reset_world();
    if (!_pub)
    {
        std::string msg = "Error advertising topic cmd_vel";
        throw msg;
    }

    if (!_node.Subscribe("/world/empty/model/cart_rigid_suspension/pose", this->posecb))
    {
        std::string msg = "Error subscribing to pose topic";
        throw msg;
    }

    if (!_node.Subscribe("/keyboard/keypress", this->keyboardcb))
    {
        std::string msg = "Error subscribing to keypress topic";
        //throw msg;
    }
}

void GzHelper::reset_world()
{
    gz::msgs::WorldControl req;
    gz::msgs::Boolean rep;
    bool res;
    req.mutable_reset()->set_all(true);
    _node.Request("/world/empty/control", req, 100, rep, res);
}

void GzHelper::send_command(gz::msgs::Twist cmd)
{
    _pub.Publish(cmd);
}

gz::msgs::Pose GzHelper::get_pose()
{
    gz::msgs::Pose pose;
    _pose_mq.pop_wait(pose);
    return pose;
}

GzKey GzHelper::get_key()
{
    gz::msgs::Int32 keymsg;
    GzKey key = GzKey::INVALID;
    if(_keyboard_mq.pop_wait(keymsg))
    {
        key = (GzKey)keymsg.data();
    }
    return key;
}


}