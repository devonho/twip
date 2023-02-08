#include "queue.h"
#include <unistd.h>

#define USE_MUTEXES

namespace twip
{
Queue::Queue() {
    _timeoutms = 5000;
}

Queue::Queue(unsigned int timeoutms) {
    _timeoutms = timeoutms;
}

void Queue::push(gz::msgs::Pose pose){
    //pthread_mutex_lock(&_mutex);
    _array.push_back(pose);
    //pthread_mutex_unlock(&_mutex);
}

bool Queue::pop_wait(gz::msgs::Pose &pose){
    unsigned int count = 0;
    while(true){
        
        #ifdef USE_MUTEXES
        try {
            pthread_mutex_lock(&_mutex);
        }
        catch(std::exception e)
        {
            std::cout << e.what() <<std::endl;
        }
        #endif //USE_MUTEXES
        
        if(_array.size() > 0)
        {
            pose = _array.front();
            _array.pop_front();
            #ifdef USE_MUTEXES
            pthread_mutex_unlock(&_mutex);
            #endif
            return true;
        } else {
            #ifdef USE_MUTEXES
            pthread_mutex_unlock(&_mutex);
            #endif
            timespec req, rem;
            req.tv_nsec = 1000000;
            req.tv_sec = 0;
            rem.tv_nsec = 0;
            rem.tv_sec = 0;
            do {
                nanosleep(&req, &rem);
                req = rem;
            } while(rem.tv_nsec > 0);            
            count++;
            if(count >= _timeoutms) return false;
        }        
    }
    
}

}