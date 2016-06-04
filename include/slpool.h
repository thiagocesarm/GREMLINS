/*!
 *	@file slpool.h
 *
 *  File with the SLPool class.
 */
 
#include <iostream>

#ifndef _SLPOOL_
#define _SLPOOL_

#include "storagepool.h"
#include "mempool_common.h"

// Definition of the raw area's size within the block.
#define SIZE 4

/*!
 *	@brief SLPool class.
 *	
 *	Class that creates and manages a memory pool. Inherits it's basic methods 
 *  from StoragePool, for more details check the "storagepool.h" file.
 */
class SLPool : public StoragePool
{
    public:
        //==================== STRUCT DEFINITION ====================
        
        // Simply keeps the length of an area.
        struct Header 
        {
            unsigned int mui_Length;
            Header() : mui_Length(0u) { /* Empty */ }
        };
        
        /* Contains either a pointer to the next free area or a raw area to be
         * allocated and store a variable.
         */
        struct Block : public Header 
        {
            enum { BlockSize = SIZE };
            union
            {
                Block * mp_Next;
                char mc_RawArea [ BlockSize - sizeof  (Header) ];
            };
            Block() : Header(), mp_Next( nullptr ) { /* Empty */ };
        };

    private:
        //======================== ATTRIBUTES =======================
    
        // Keeps the number of blocks minus the sentinel block
        unsigned int mui_NumberOfBlocks;
        
        // Pointer to an array of blocks allocated dinamically
        Block *mp_Pool; //!< Head of the list.
        
        /* Receive the address to the block responsible for being the "head" of
         * the list of free areas.
         */
        Block &mr_Sentinel; //!< End of the list.
        
    public:
        //====================== PUBLIC METHODS =====================

        // For detailed information, refer to the "slpool.inl" file

        // Class constructor, receives the number of bytes desired in the pool
        explicit SLPool( size_t );
        
        // Class destructor
        ~SLPool();
        
        /* Overwrites the << operator to exhibit the actual state of the pool,
         * showing free and allocated spaces.
         */
        friend std::ostream & operator<< ( std::ostream & _os, const SLPool & _pool )
        {
            auto i(0u);
    		Block * work = _pool.mr_Sentinel.mp_Next;
    		
    		_os << "\n";
    		
    		while( i < _pool.mui_NumberOfBlocks )
    		{
    		    if( work == &_pool.mp_Pool[i] )
    		    {
    		        for( auto j(0u); j < _pool.mp_Pool[i].mui_Length; j++)
    		            _os << "[ ]";
    		            work = work->mp_Next;
    		    }
    		    else
    		    {
    		        for( auto j(0u); j < _pool.mp_Pool[i].mui_Length; j++)
    		            _os << "[#]";
    		    }
    		    
                i += _pool.mp_Pool[i].mui_Length;
    		}
    
    		_os << "\n\n";
    		
    		return _os;
    	}
    	
        /* Searches within the pool for a free area that can receive a variable
         * with the size received as a parameter
         */
        void * Allocate( size_t );
        
        /* Frees the area designated by the pointer, merging it with any other
         * free area nearby.
         */
        void Free( void * );
        
        
        
};


// Includes the method implementation from "slpool.inl"
#include "slpool.inl"

#endif