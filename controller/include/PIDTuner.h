#ifndef __PIDTUNER_H__
#define __PIDTUNER_H__

#include "db.h"
#include "PIDController.h"
#include "GzHelper.h"

namespace twip
{
class PIDTuner 
{
public:
    PIDTuner(DBWriter* pDb, GzHelper* pGz);
    ~PIDTuner(){};
    
    void runTrial();
};
    
} // namespace twip


#endif // __PIDTUNER_H__