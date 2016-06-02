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

}

void SLPool::Free( void * )
{
    
}