#include "PIDTuner.h"
#include <chrono>

extern std::atomic<bool> g_terminatePub;

namespace twip
{

PIDTuner::PIDTuner(DBWriter* pDb, GzHelper* pGz)
{
    _pDb = pDb;
    _pGz = pGz;
}

void PIDTuner::runTrial(PIDController* pCtrl)
{
    unsigned long itercount = 0;
    gz::msgs::Pose p;
    gz::msgs::Twist t;
    while(true)
    {
        p = _pGz->get_pose();
        t = pCtrl->step(p);        
        _pGz->send_command(t);
    
        itercount++;
        if(itercount > 500){
            _pGz->reset_world();
            break;
        }
    }
    unsigned long int ts = (unsigned long int)std::chrono::system_clock::now().time_since_epoch().count();
    PoseDBObject poserec(p, ts);
    PIDParamDBObject pidrec(pCtrl->Kp, pCtrl->Ki, pCtrl->Kd, ts);
    _pDb->open();
    _pDb->insert(&poserec);
    _pDb->insert(&pidrec);
    _pDb->close();
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
                PIDController ctrl;
                ctrl.Kd = i * 100;
                ctrl.Ki = j * 0.001;
                ctrl.Kd = k * 10;
                /*
                ctrl.Kd = 100;
                ctrl.Ki = 0.981;
                ctrl.Kd = 10;
                */
                runTrial(&ctrl);

                if(g_terminatePub) break;
            }

            if(g_terminatePub) break;
        }            

        if(g_terminatePub) break;
    }
    _pDb->close();

}

}
