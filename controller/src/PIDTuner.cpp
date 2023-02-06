#include "PIDTuner.h"
#include <chrono>

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
    _pDb->insert(&poserec);
    _pDb->insert(&pidrec);
}

void PIDTuner::runTrials()
{
    _pDb->open();
    PoseDBObject obj1;
    PIDParamDBObject obj2;
    _pDb->create_table(&obj1);
    _pDb->create_table(&obj2);
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
        {
            for(int k=1;k<=10;k++)
            {
                PIDController ctrl;
                ctrl.Kd = i * 10;
                ctrl.Ki = j * 0.001;
                ctrl.Kd = k * 1;
                runTrial(&ctrl);
            }
        }            
    }
    _pDb->close();

}

}
