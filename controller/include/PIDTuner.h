#ifndef __PIDTUNER_H__
#define __PIDTUNER_H__

#include "db.h"
#include "PIDController.h"
#include "GzHelper.h"
#include "gz/msgs.hh"

namespace twip
{

class PIDRunner
{
protected:
    GzHelper* _pGz;
    PIDController* _pCtrl;
public:
    void runStep(gz::msgs::Twist t_in);
    void runLoop();
    PIDRunner(GzHelper* pGz, PIDController* pCtrl);
    ~PIDRunner(){}
};


class PIDTuner : PIDRunner
{
    DBWriter* _pDb;
public:
    PIDTuner(DBWriter* pDb, GzHelper* pGz, PIDController* pCtrl);
    ~PIDTuner(){};
    
    void runTrial();
    void runTrials();
};
    
} // namespace twip


#endif // __PIDTUNER_H__