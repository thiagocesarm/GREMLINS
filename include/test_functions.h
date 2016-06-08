/*!
 *	@file test_functions.h
 *
 *  File with the Event class implementation.
 */

#ifndef _TEST_
#define _TEST_

#include "header.h"
#include "slpool.h"

/*!
 *	@brief Event class
 *
 *  Event class which creates a pair of a SLPool adress and a time stamp. It is basically
 *  a memory pool which has a time-stamp indicating how many seconds after its allocation
 *  the pool shall be freed.
 */
class Event
{
    public:
        // Class constructor. It receives a SLPool addres and a time-stamp
        Event(void * _mem, std::time_t _time):
            timeStamp(_time),
            memoryPtr(_mem)
        {}
        //Class destructor.
        ~Event(){}
        
        // Getter methods
        std::time_t getTimeStamp(){ return timeStamp; }
        char * getMemoryPtr() { return reinterpret_cast<char*>(memoryPtr); }
        
        // Overload of operator <, used to compare events by their time-stamps
        inline friend bool operator< (const Event & lhs, const Event & rhs)
        { return lhs.timeStamp < rhs.timeStamp; }
        
    
    private:
        std::time_t timeStamp;
        void * memoryPtr;
};

#include "test.inl"

#endif