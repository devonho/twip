#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <thread>
#include <gz/msgs.hh>
#include <gz/transport.hh>

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

void writedb();

static std::atomic<bool> g_terminatePub(false);

void signal_handler(int _signal)
{
    if (_signal == SIGINT || _signal == SIGTERM)
        g_terminatePub = true;
}

float velocity = 0.0f;
float lasterr = 0.0f;
float cumerr = 0.0f;
gz::transport::Node node;
gz::transport::Node::Publisher pub;
gz::transport::Node::Publisher pub_ctrl;
gz::msgs::Twist msg;
gz::msgs::Vector3d v;
unsigned long itercount = 0;
log4cpp::Category& root = log4cpp::Category::getRoot();

void reset_world()
{
    gz::msgs::WorldControl req;
    gz::msgs::Boolean rep;
    bool res;
    req.mutable_reset()->set_all(true);
    node.Request("/world/empty/control", req, 100, rep, res);
    root << log4cpp::Priority::INFO << "world reset: " << std::boolalpha << res;
}

void cb(const gz::msgs::Pose &_msg)
{
    gz::msgs::Quaternion qm = _msg.orientation();
    gz::math::Quaternionf q;
    q.Set(qm.w(),qm.x(),qm.y(),qm.z());

    float err = q.Pitch();
    if (pub)
    {
        float P = err * 100;      
        float I = cumerr * 0.00;
        float D = (lasterr - err) * 10;         
        v.set_x(P + I + D);

        root << log4cpp::Priority::DEBUG << (P + I + D);

        *msg.mutable_linear() = v;
        pub.Publish(msg);
    }

    itercount++;
    if(itercount > 1000){
        reset_world();
        itercount=0;
    }

    lasterr = err;
    cumerr += err;
}

void setup_logging()
{
	log4cpp::Appender *appender = new log4cpp::FileAppender("default", "twip_controller.log");
	appender->setLayout(new log4cpp::BasicLayout());

	root.setPriority(log4cpp::Priority::INFO);
	root.addAppender(appender);
}

void setup_subscriptions()
{
    pub = node.Advertise<gz::msgs::Twist>("/cmd_vel");
    reset_world();
    if (!pub)
    {
        std::string msg = "Error advertising topic cmd_vel";
        root << log4cpp::Priority::ERROR << msg;
        throw msg;
    }

    if (!node.Subscribe("/world/empty/model/cart_rigid_suspension/pose", cb))
    {
        std::string msg = "Error subscribing to pose topic";
        root << log4cpp::Priority::ERROR << msg;
        throw msg;
    }
}

int main(int argc, char **argv)
{
    // Install a signal handler for SIGINT and SIGTERM.
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    setup_logging();
    setup_subscriptions();
   
    gz::transport::waitForShutdown();
    
    return 0;
}