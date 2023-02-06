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

#include "queue.h"
#include "PIDController.h"

static std::atomic<bool> g_terminatePub(false);
log4cpp::Category& root = log4cpp::Category::getRoot();
gz::transport::Node node;
gz::transport::Node::Publisher pub;
twip::Queue pose_mq;

void signal_handler(int _signal)
{
    if (_signal == SIGINT || _signal == SIGTERM)
        g_terminatePub = true;
}

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
    pose_mq.push(_msg);
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
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    setup_logging();
    setup_subscriptions();
   
    twip::PIDController controller;
    unsigned long itercount = 0;

    while(!g_terminatePub) {

        gz::msgs::Pose pose;
        gz::msgs::Twist twist;
        pose_mq.pop_wait(pose);        
        twist = controller.step(pose);
        pub.Publish(twist);
        
        itercount++;
        if(itercount > 500){
            reset_world();
            itercount=0;
        }
    }

    //gz::transport::waitForShutdown();
    
    return 0;
}