#ifndef __GZ_HELPER__
#define __GZ_HELPER__

#include <gz/msgs.hh>
#include <gz/transport.hh>
#include <queue.h>

namespace twip 
{
class GzHelper
{   
    gz::transport::Node _node;
    gz::transport::Node::Publisher _pub;

    static void cb(const gz::msgs::Pose &_msg);
    static GzHelper* _pInstance;
    GzHelper();

public:
    twip::Queue _pose_mq;

    ~GzHelper(){};
    static GzHelper* getInstance();

    void reset_world();
    void send_command(gz::msgs::Twist cmd);
    gz::msgs::Pose get_pose();
};

}


#endif // __GZ_HELPER__