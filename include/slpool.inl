/*!
 *	@file slpool.h
 *
 *  File with the SLPool class' methods implementation.
 */
 
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <new>
#include "slpool.h"


/*!
 *	@brief Class constructor
 *	@param poolSz number of bytes designated to fit in the memory pool
 *
 *	First, it checks how many blocks of size SIZE ("defined in slpool.h") are
 *	needed, then creates an dinamically allocated Block array at mp_Pool and 
 *  sets the last block (an extra) to the be the "head" of a free area list.
 */
SLPool::SLPool( size_t poolSz ) :
    mui_NumberOfBlocks( ceil( poolSz / static_cast<float>(SIZE) ) ),
    mp_Pool ( new Block[mui_NumberOfBlocks + 1] ),
    mr_Sentinel ( mp_Pool[mui_NumberOfBlocks] )
{
    mp_Pool[0].mui_Length = mui_NumberOfBlocks;
    mp_Pool[0].mp_Next = nullptr;
    
    mr_Sentinel.mp_Next = &mp_Pool[0];
    mr_Sentinel.mui_Length = 0;
}

/*!
 *	@brief Class destructor
 *
 *  Simple class destructor who deletes the dinamically allocated array at mp_Pool
 */
SLPool::~SLPool()
{ delete[] mp_Pool; }

/*!
 *	@brief Looks for a free area that can fit de received number of bytes
 *	@param numberOfBytes the size of the variable to fit in the memory pool
 *
 *	There are two possibles strategies in this method, it depends whether _BEST_FIT_
 *  is defined or not
 *
 *  @return A void type pointer to the beginning of the raw area 
 */
void * SLPool::Allocate( size_t numberOfBytes )
{ 
    size_t numberOfBlocks = ceil( (numberOfBytes + sizeof( Header) ) / static_cast<float>(sizeof(Block)) );
    Block * work = mr_Sentinel.mp_Next;
    Block * work_prev = &mr_Sentinel;
    
    // #define _BEST_FIT_
    
    #ifndef _BEST_FIT_
/*    
 *  - First fit: if _BEST_FIT_ is undefined we run through the free areas' list
 *              searching for the first area with enough blocks to keep the size
 *              received. If the area found has the same size required, it just
 *              changes the pointer area to a raw data area and removes it from 
 *              the list. 
 */
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
        Block * work_next = work + numberOfBlocks;
        work_next->mui_Length = (work->mui_Length) - numberOfBlocks;
        work_next->mp_Next = work->mp_Next;
        work_prev->mp_Next = work_next;
        work->mui_Length = numberOfBlocks;
    }
    
    return reinterpret_cast<void*>(reinterpret_cast<char*>(work) + sizeof(Header));
    
    #endif
    
    #ifdef _BEST_FIT_
/*    
 *  - Best fit: if _BEST_FIT_ is defined we do a complete run through the free 
 *              areas' list searching for the area with enough or the closest 
 *              higher amount of blocks to keep the size received. If the area 
 *              found has the same size required, it just changes the pointer to 
 *              a raw data area and removes it from the list.
 */ 
    Block * best_ptr (work);
    Block * best_ptr_prev (&mr_Sentinel);
    
    while(work != nullptr)
    {
        if(work->mui_Length < best_ptr->mui_Length and work->mui_Length >= numberOfBlocks)
        {
            best_ptr = work;
            best_ptr_prev = work_prev;
            
            if( work->mui_Length == numberOfBlocks )
                break;
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
        Block * best_ptr_next = best_ptr + numberOfBlocks;
        best_ptr_next->mui_Length = best_ptr->mui_Length - numberOfBlocks;
        best_ptr_next->mp_Next = best_ptr->mp_Next;
        best_ptr_prev->mp_Next = best_ptr_next;
        best_ptr->mui_Length = numberOfBlocks;
    }

    return reinterpret_cast<void*>(reinterpret_cast<char*>(best_ptr) + sizeof(Header));
    
    #endif
}

/*!
 *	@brief Sets an occupied area to a free area
 *	@param ptDelete a pointer to the area to be deleted
 *
 *	The area that needs to be freed gets merged with any other free area nearby,
 *  for this to be done 4 cases must be analyzed:
 *      - The area is directly between two free areas
 *      - The area is not directly between other free areas
 *      - The area is a free area directely before and no other
 *      - The area is a free area directely after and no other
 */
void SLPool::Free( void * ptDelete )
{
    std::cout << "entrei free\n";
    Block * ptPrevReserved = &mr_Sentinel;
    Block * ptPostReserved = mr_Sentinel.mp_Next;
    Block * ptReserved = reinterpret_cast<Block*>(reinterpret_cast<char*>(ptDelete) - sizeof(Header));

    while(ptPostReserved != nullptr and ptPostReserved < ptReserved)
    {
        std::cout << "entrei no laço\n";
        ptPrevReserved = ptPostReserved;
        ptPostReserved = ptPostReserved->mp_Next;
    }
    
    if (ptPrevReserved + ptPrevReserved->mui_Length == ptReserved 
        and ptReserved + ptReserved->mui_Length == ptPostReserved)
    {
        std::cout << "entrei no caso 1\n";
        ptPrevReserved->mui_Length += ptPostReserved->mui_Length + ptReserved->mui_Length;
        ptPrevReserved->mp_Next = ptPostReserved->mp_Next;
    }
    else if (ptPrevReserved + ptPrevReserved->mui_Length != ptReserved 
            and ptReserved + ptReserved->mui_Length != ptPostReserved)
    {
        std::cout << "entrei no caso 2\n";
        ptPrevReserved->mp_Next = ptReserved;
        ptReserved->mp_Next = ptPostReserved;
    }
    else if (ptPrevReserved + ptPrevReserved->mui_Length == ptReserved 
            and ptReserved + ptReserved->mui_Length != ptPostReserved)
    {
        std::cout << "entrei no caso 3\n";
        ptPrevReserved->mui_Length += ptReserved->mui_Length;
        ptPrevReserved->mp_Next = ptPostReserved;
    }
    else
    {
        std::cout << "entrei no caso 4\n";
        ptReserved->mui_Length += ptPostReserved->mui_Length;
        ptPrevReserved->mp_Next = ptReserved;
        ptReserved->mp_Next = ptPostReserved->mp_Next;
    }
}