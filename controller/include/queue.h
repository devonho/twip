#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "db.h"
#include "pthread.h"
#include <list>
#include <gz/msgs.hh>

namespace twip
{

class Queue {

    std::list<gz::msgs::Pose> _array;
    pthread_mutex_t _mutex;
    unsigned int _timeoutms = 1000;
public:
    Queue();
    Queue(unsigned int timeoutms);
    ~Queue(){};

    void push(gz::msgs::Pose pose);
    bool pop_wait(gz::msgs::Pose &pose);
};

}
#endif // __QUEUE_H__