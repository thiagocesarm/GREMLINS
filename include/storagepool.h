/*!
 *	@file storagepool.h
 *
 *  File with the storage pool class template.
 */
#ifndef _STPOOL_
#define _STPOOL_


/*!
 *	@brief StoragePool class.
 *	
 *	An interface class that points the needed methods.
 */
class StoragePool 
{
    public:
        virtual ~StoragePool (){}
        virtual void * Allocate ( size_t ) = 0;
        virtual void Free ( void * ) = 0;
};

#endif