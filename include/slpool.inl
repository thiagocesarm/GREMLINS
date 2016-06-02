#include <cmath>
#include <iostream>
#include "slpool.h"

SLPool::SLPool( size_t poolSz ) :
    mui_NumberOfBlocks( ceil( (poolSz + sizeof(Header) ) / static_cast<float>(SIZE) ) ),
    mp_Pool ( new Block[mui_NumberOfBlocks + 1] ),
    mr_Sentinel ( mp_Pool[mui_NumberOfBlocks] )
{
    mp_Pool[0].mui_Length = mui_NumberOfBlocks;
    mp_Pool[0].mp_Next = nullptr;
    
    mr_Sentinel.mp_Next = &mp_Pool[0];
    mr_Sentinel.mui_Length = 0;
    
    std::cout << "Número de blocos: " << mui_NumberOfBlocks << "\n";
    std::cout << "sizeof dos blocos: " << SIZE << "\n";
}


SLPool::~SLPool()
{ delete[] mp_Pool; }

void * SLPool::Allocate( size_t )
{ return nullptr; }

void SLPool::Free( void * )
{}