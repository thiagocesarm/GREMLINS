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
 *	needed, then creates a dinamically allocated Block array at mp_Pool and 
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
 *  Simple class destructor which deletes the dinamically allocated array at mp_Pool
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
    
    #ifndef _BEST_FIT_
    /*    
     *  - First fit: if _BEST_FIT_ is undefined we run through the free areas' list
     *              searching for the first area with enough blocks to keep the size
     *              received. If the area found has the same size required, it just
     *              changes the pointer area to a raw data area and removes it from 
     *              the list. 
     */
     
    // Searching for first free area big enough to keep the size received.
    while(work != nullptr and work->mui_Length < numberOfBlocks)
    {
        work_prev = work;
        work = work->mp_Next;
    }
    
    // In case there's no area with enough size, bad_alloc exception is thrown.
    if(work == nullptr)
    {
        std::bad_alloc exception;
        throw exception;
    }
    
    // Case where the first big enough area found is exactly the size asked.
    if( work->mui_Length == numberOfBlocks )
    {
        work_prev->mp_Next = work->mp_Next;
    }
    // Case where the first big enough area found is bigger than the size asked.
    else
    {
        Block * work_next = work + numberOfBlocks; // Pointer to the new free area at the end of the block.
        work_next->mui_Length = (work->mui_Length) - numberOfBlocks; // The new free area length.
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
    
    Block * best_ptr (nullptr);
    Block * best_ptr_prev (work_prev);
    
    while(work != nullptr)
    {
        // Checks if the free area is big enough to fit the requisition.
        if(work->mui_Length >= numberOfBlocks)
        {
            // First condition checks if it is the first big enough area found;
            // second condition checks if its length is smaller than actual best area's length.
            if( (best_ptr_prev == &mr_Sentinel) or (work->mui_Length < best_ptr->mui_Length) )
            {
                best_ptr = work;
                best_ptr_prev = work_prev;
            
                if( work->mui_Length == numberOfBlocks )
                    break;
            }
        }
        work_prev = work;
        work = work->mp_Next;
    }
    
    // In case there's no area with enough size, bad_alloc exception is thrown.
    if(best_ptr == nullptr or best_ptr->mui_Length < numberOfBlocks)
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
        Block * best_ptr_next = best_ptr + numberOfBlocks; // Pointer to the new free area at the end of the block.
        best_ptr_next->mui_Length = (best_ptr->mui_Length) - numberOfBlocks; // The new free area length.
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
 *  for this to be done 4 cases must be analyzed.
 */
void SLPool::Free( void * ptDelete )
{
    Block * ptPrevReserved = &mr_Sentinel;
    Block * ptPostReserved = mr_Sentinel.mp_Next;
    Block * ptReserved = reinterpret_cast<Block*>(reinterpret_cast<char*>(ptDelete) - sizeof(Header));
    
    if(ptReserved == nullptr) return;
    
    // Goes through the Free Area list and searches for Free Area after
    while(ptPostReserved != nullptr and ptPostReserved < ptReserved)
    {
        ptPrevReserved = ptPostReserved;
        ptPostReserved = ptPostReserved->mp_Next;
    }
    
    // The area is directly between two free areas
    if (ptPrevReserved + ptPrevReserved->mui_Length == ptReserved 
        and ptReserved + ptReserved->mui_Length == ptPostReserved)
    {
        ptPrevReserved->mui_Length += ptPostReserved->mui_Length + ptReserved->mui_Length;
        ptPrevReserved->mp_Next = ptPostReserved->mp_Next;
    }
    // The area is not directly between any other free areas
    else if (ptPrevReserved + ptPrevReserved->mui_Length != ptReserved 
            and ptReserved + ptReserved->mui_Length != ptPostReserved)
    {
        ptPrevReserved->mp_Next = ptReserved;
        ptReserved->mp_Next = ptPostReserved;
    }
    // There is a free area directly before and no other
    else if (ptPrevReserved + ptPrevReserved->mui_Length == ptReserved 
            and ptReserved + ptReserved->mui_Length != ptPostReserved)
    {
        ptPrevReserved->mui_Length += ptReserved->mui_Length;
        ptPrevReserved->mp_Next = ptPostReserved;
    }
    // The area is a free area directly after and no other
    else
    {
        ptReserved->mui_Length += ptPostReserved->mui_Length;
        ptPrevReserved->mp_Next = ptReserved;
        ptReserved->mp_Next = ptPostReserved->mp_Next;
    }
}