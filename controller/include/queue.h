#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "db.h"
#include "pthread.h"
#include <list>
#include <gz/msgs.hh>
#include <unistd.h>

//#define USE_MUTEXES

namespace twip
{

template <typename T> class Queue {

    std::list<T> _array;
    pthread_mutex_t _mutex;
    unsigned int _timeoutms = 1000;
public:
    Queue();
    Queue(unsigned int timeoutms);
    ~Queue(){};

    void push(T item);
    bool pop_wait(T &item);
};


template<typename T>
Queue<T>::Queue() {
    _timeoutms = 5000;
}

template<typename T>
Queue<T>::Queue(unsigned int timeoutms) {
    _timeoutms = timeoutms;
}

template<typename T>
void Queue<T>::push(T item){
    #ifdef USE_MUTEXES
    pthread_mutex_lock(&_mutex);
    #endif

    _array.push_back(item);

    #ifdef USE_MUTEXES
    pthread_mutex_unlock(&_mutex);
    #endif
}

template<typename T>
bool Queue<T>::pop_wait(T &item){
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
            item = _array.front();
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
#endif // __QUEUE_H__