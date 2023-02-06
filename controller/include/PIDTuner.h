#ifndef __PIDTUNER_H__
#define __PIDTUNER_H__

#include "db.h"
#include "PIDController.h"
#include "GzHelper.h"

namespace twip
{
class PIDTuner 
{
    DBWriter* _pDb;
    GzHelper* _pGz;
public:
    PIDTuner(DBWriter* pDb, GzHelper* pGz);
    ~PIDTuner(){};
    
    void runTrial(PIDController* pCtrl);
    void runTrials();
};
    
} // namespace twip


#endif // __PIDTUNER_H__