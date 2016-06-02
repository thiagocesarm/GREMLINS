#ifndef _SLPOOL_
#define _SLPOOL_

#include "storagepool.h"
#include "mempool_common.h"

#define SIZE 16

class SLPool : public StoragePool
{
    public:
    
        struct Header 
        {
            unsigned int mui_Length;
            Header() : mui_Length(0u) { /* Empty */ }
        };
        
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
    
        unsigned int mui_NumberOfBlocks;
        Block *mp_Pool; //!< Head of the list.
        Block &mr_Sentinel; //!< End of the list.
        
    public:

        explicit SLPool( size_t );
        ~SLPool();
        void * Allocate( size_t );
        void Free( void * );
};

#include "slpool.inl"

#endif