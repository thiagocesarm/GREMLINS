#ifndef _STPOOL_
#define _STPOOL_

class StoragePool 
{
    public:
        virtual ~StoragePool (){}
        virtual void * Allocate ( size_t ) = 0;
        virtual void Free ( void * ) = 0;
};

#endif