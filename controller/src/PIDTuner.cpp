#include "PIDTuner.h"
#include <chrono>

extern std::atomic<bool> g_terminatePub;

namespace twip
{

PIDRunner::PIDRunner(GzHelper* pGz, PIDController* pCtrl)
{
    _pGz = pGz;
    _pCtrl = pCtrl;
}

PIDTuner::PIDTuner(DBWriter* pDb, GzHelper* pGz, PIDController* pCtrl)
    : PIDRunner(pGz, pCtrl)
{
    _pDb = pDb;
}

void PIDRunner::runStep(gz::msgs::Twist t_in)
{
    gz::msgs::Pose p;
    gz::msgs::Twist t_out;
    p = _pGz->get_pose();
    t_out = _pCtrl->step(p, t_in);        
    _pGz->send_command(t_out);
}

void PIDRunner::runLoop()
{
    gz::msgs::Twist t_in;
    t_in.clear_linear();
    while(g_terminatePub != true)
    {
        switch(_pGz->get_key())
        {
            case GzKey::LEFT_ARROW:
                t_in.mutable_angular()->set_z((10*3.142/180));
                break;
            case GzKey::RIGHT_ARROW:
                t_in.mutable_angular()->set_z((-10*3.142/180));
                break;
            case GzKey::UP_ARROW:
                t_in.mutable_linear()->set_y(1);
                break;
            case GzKey::DOWN_ARROW:
                t_in.mutable_linear()->set_y(-1);
                break;
            default:  
                break;              
        }

        runStep(t_in);
    }
}

void PIDTuner::runTrial()
{
    unsigned long itercount = 0;
    gz::msgs::Twist t_in;
    t_in.clear_linear();

    while(true)
    {
        runStep(t_in);

        itercount++;
        if(itercount > 500){
            break;
        }
    }

    unsigned long int ts = (unsigned long int)std::chrono::system_clock::now().time_since_epoch().count();
    PoseDBObject poserec(_pGz->get_pose(), ts);
    PIDParamDBObject pidrec(_pCtrl->Kp, _pCtrl->Ki, _pCtrl->Kd, ts);

    _pDb->open();
    _pDb->insert(&poserec);
    _pDb->insert(&pidrec);
    _pDb->close();

    _pGz->reset_world();

}

void PIDTuner::runTrials()
{
    _pDb->open();
    PoseDBObject obj1;
    PIDParamDBObject obj2;
    _pDb->create_table(&obj1);
    _pDb->create_table(&obj2);
    _pDb->close();
    for(int i=1;i<=1;i++)
    {
        for(int j=1;j<=1000;j++)
        {
            for(int k=1;k<=1;k++)
            {
                _pCtrl->Kd = i * 100;
                _pCtrl->Ki = j * 0.001;
                _pCtrl->Kd = k * 10;
                /*
                _pCtrl->Kd = 100;
                _pCtrl->Ki = 0.981;
                _pCtrl->Kd = 10;
                */
                runTrial();

                if(g_terminatePub) break;
            }

            if(g_terminatePub) break;
        }            

        if(g_terminatePub) break;
    }
    _pDb->close();

}

}
