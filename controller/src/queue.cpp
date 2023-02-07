#include "queue.h"
#include <unistd.h>

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
        /*
        try {
            pthread_mutex_lock(&_mutex);
        }
        catch(std::exception e)
        {
            std::cout << e.what() <<std::endl;
        }*/
        
        if(_array.size() > 0)
        {
            pose = _array.front();
            _array.pop_front();
            //pthread_mutex_unlock(&_mutex);
            return true;
        } else {
            //pthread_mutex_unlock(&_mutex);
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