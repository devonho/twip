#ifndef __GZ_HELPER__
#define __GZ_HELPER__

#include <gz/msgs.hh>
#include <gz/transport.hh>
#include <queue.h>

namespace twip 
{

typedef enum GzKey {
    LEFT_ARROW = 16777234,
    UP_ARROW = 16777235,
    RIGHT_ARROW = 16777236,
    DOWN_ARROW = 16777237,
    INVALID = 1,
    UNKNOWN = 0
} GzKey;

class GzHelper
{   
    gz::transport::Node _node;
    gz::transport::Node::Publisher _pub;

    static void posecb(const gz::msgs::Pose &_msg);
    static void keyboardcb(const gz::msgs::Int32 &_msg);
    static GzHelper* _pInstance;
    GzHelper();

public:
    twip::Queue<gz::msgs::Pose> _pose_mq;
    twip::Queue<gz::msgs::Int32> _keyboard_mq{0};

    ~GzHelper(){};
    static GzHelper* getInstance();

    void reset_world();
    void send_command(gz::msgs::Twist cmd);
    gz::msgs::Pose get_pose();
    GzKey get_key();
};

}


#endif // __GZ_HELPER__