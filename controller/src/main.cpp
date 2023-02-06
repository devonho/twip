#include <csignal>
#include <iostream>
#include <string>
#include <thread>

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

#include "queue.h"
#include "PIDController.h"
#include "GzHelper.h"

static std::atomic<bool> g_terminatePub(false);
log4cpp::Category& root = log4cpp::Category::getRoot();

void signal_handler(int _signal)
{
    if (_signal == SIGINT || _signal == SIGTERM)
        g_terminatePub = true;
}

void setup_logging()
{
	log4cpp::Appender *appender = new log4cpp::FileAppender("default", "twip_controller.log");
	appender->setLayout(new log4cpp::BasicLayout());

	root.setPriority(log4cpp::Priority::INFO);
	root.addAppender(appender);
}

int main(int argc, char **argv)
{    
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    setup_logging();
   
    twip::GzHelper* pGz = twip::GzHelper::getInstance();
    twip::PIDController controller;
    unsigned long itercount = 0;

    while(!g_terminatePub) {

        
        pGz->send_command(controller.step(pGz->get_pose()));
        
        itercount++;
        if(itercount > 500){
            pGz->reset_world();
            itercount=0;
        }
        
    }
   
    return 0;
}