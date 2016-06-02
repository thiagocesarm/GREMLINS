#include <cmath>
#include <iostream>
#include <stdexcept>
#include <new>
#include "slpool.h"

SLPool::SLPool( size_t poolSz ) :
    mui_NumberOfBlocks( ceil( (poolSz + sizeof( Header) ) / static_cast<float>(SIZE) ) ),
    mp_Pool ( new Block[mui_NumberOfBlocks + 1] ),
    mr_Sentinel ( mp_Pool[mui_NumberOfBlocks] )
{
    mp_Pool[0].mui_Length = mui_NumberOfBlocks;
    mp_Pool[0].mp_Next = nullptr;
    
    mr_Sentinel.mp_Next = &mp_Pool[0];
    mr_Sentinel.mui_Length = 0;
    
    // std::cout << "Número de blocos: " << mui_NumberOfBlocks << "\n";
    // std::cout << "sizeof dos blocos: " << SIZE << "\n";
}


SLPool::~SLPool()
{ delete[] mp_Pool; }

void * SLPool::Allocate( size_t numberOfBytes)
{ 
    size_t numberOfBlocks = ceil( (numberOfBytes + sizeof( Header) ) / static_cast<float>(sizeof(Block)) );
    Block * work = mr_Sentinel.mp_Next;
    Block * work_prev = &mr_Sentinel;
    
    #ifndef _BEST_FIT_
    
    while(work != nullptr and work->mui_Length < numberOfBlocks)
    {
        work_prev = work;
        work = work->mp_Next;
    }
    
    if(work == nullptr)
    {
        std::bad_alloc exception;
        throw exception;
    }
    
    
    if( work->mui_Length == numberOfBlocks )
    {
        work_prev->mp_Next = work->mp_Next;
    }
    else
    {
        Block * work_next = work + ( sizeof(Block) * numberOfBlocks );
        work_next->mui_Length = work->mui_Length - numberOfBlocks;
        work_next->mp_Next = work->mp_Next;
        work_prev->mp_Next = work_next;
        work->mui_Length = numberOfBlocks;
    }
    
    return work + sizeof(Header);
    
    #endif
    
    #ifdef _BEST_FIT_
    
    Block * best_ptr (work);
    Block * best_ptr_prev (&mr_Sentinel);
    
    while(work != nullptr)
    {
        if(work->mui_Length < best_ptr->mui_Length and work->mui_Length >= numberOfBlocks)
        {
            best_ptr = work;
            best_ptr_prev = work_prev;
        }
        work_prev = work;
        work = work->mp_Next;
    }
    
    if(best_ptr->mui_Length < numberOfBlocks)
    {
        std::bad_alloc exception;
        throw exception;
    }
    
    if( best_ptr->mui_Length == numberOfBlocks )
    {
        best_ptr_prev->mp_Next = best_ptr->mp_Next;
    }
    else
    {
        Block * best_ptr_next = best_ptr + ( sizeof(Block) * numberOfBlocks );
        best_ptr_next->mui_Length = best_ptr->mui_Length - numberOfBlocks;
        best_ptr_next->mp_Next = best_ptr->mp_Next;
        best_ptr_prev->mp_Next = best_ptr_next;
        best_ptr->mui_Length = numberOfBlocks;
    }

    return best_ptr + sizeof(Header);
    
    #endif
}

void SLPool::Free( void * ptDelete )
{
    Block * ptPrevReserved = &mr_Sentinel;
    Block * ptPostReserved = mr_Sentinel.mp_Next;
    Block * ptReserved = reinterpret_cast<Block*> (ptDelete);
    while(ptPostReserved != nullptr and ptPostReserved < ptReserved)
    {
        ptPrevReserved = ptPostReserved;
        ptPostReserved = ptPostReserved->mp_Next;
    }
    if (ptPrevReserved + (sizeof(Block) * ptPrevReserved->mui_Length) == ptReserved 
        and ptReserved + (sizeof(Block) * ptReserved->mui_Length) == ptPostReserved)
    {
        ptPrevReserved->mui_Length += ptPostReserved->mui_Length + ptReserved->mui_Length;
        ptPrevReserved->mp_Next = ptPostReserved->mp_Next;
    }
    else if (ptPrevReserved + (sizeof(Block) * ptPrevReserved->mui_Length) != ptReserved 
            and ptReserved + (sizeof(Block) * ptReserved->mui_Length) != ptPostReserved)
    {
        ptPrevReserved->mp_Next = ptReserved;
        ptReserved->mp_Next = ptPostReserved;
    }
    else if (ptPrevReserved + (sizeof(Block) * ptPrevReserved->mui_Length) == ptReserved 
            and ptReserved + (sizeof(Block) * ptReserved->mui_Length) != ptPostReserved)
    {
        ptPrevReserved->mui_Length += ptReserved->mui_Length;
        ptPrevReserved->mp_Next = ptPostReserved;
    }
    else
    {
        ptReserved->mui_Length += ptPostReserved->mui_Length;
        ptPrevReserved->mp_Next = ptReserved;
        ptReserved->mp_Next = ptPostReserved->mp_Next;
    }
}