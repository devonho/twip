#include <csignal>
#include <iostream>
#include <string>
#include <unistd.h>

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

#include "queue.h"
#include "PIDController.h"
#include "PIDTuner.h"
#include "GzHelper.h"

std::atomic<bool> g_terminatePub(false);
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
    std::string dbpath = "./pidtune.db";
    extern char *optarg;
    int f;
    while((f = getopt(argc, argv, "f:")) != -1) {
        switch(f){
            case 'f':
                dbpath = optarg;
        }
    }
    
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    setup_logging();
   
    std::remove(dbpath.c_str());
    twip::DBWriter db(dbpath);
    twip::GzHelper* pGz = twip::GzHelper::getInstance();
    twip::PIDController controller;

    twip::PIDTuner tuner(&db, pGz);
    tuner.runTrials();
    
    return 0;
}