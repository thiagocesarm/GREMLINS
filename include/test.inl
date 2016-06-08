/*!
 *	@file test.inl
 *
 *  File with the the memory manager test procedures and functions.
 */
 
/*!
 *  @brief Generates random number to use as size.
 *  
 *  Uses time seed to generate a random number in the interval [100, 1999].
 *  This number is used as number of bytes to be allocated in a memory pool.
 *  
 *  @return Randomly generated size.
 */
size_t getRandomForSize()
{
    std::srand(std::time(0));
    size_t b_size = rand() % 1900 + 100;
    return b_size;
}

/*!
 *  @brief Generates random number to use as time interval.
 *  
 *  Uses time seed to generate a random number in the interval [1, 100].
 *  This number is used as a time-stamp associated with an Event object.
 *  
 *  @return Randomly generated time interval.
 */
std::time_t getRandomTimeInterval()
{
    std::srand(std::time(0));
    std::time_t b_seconds = rand() % 100 + 1;
    return b_seconds;
}

/*!
 *  @brief Tests the SLPool memory manager.
 *  
 *  @param _pool A pointer to the memory pool to be tested.
 *  @param _timeLimit Number of times the operations will be run.
 *  
 *  Uses a sequence of allocations and frees to test SLPool memory manager. The 
 *  allocations are associated with objects from the Event class, so each of them has
 *  a randomly generated time-stamp indicating when the allocated memory should be freed.
 *  The number os bytes of each allocation is also randomly generated. The allocate 
 *  and free operations are executed in a total of _timeLimit times, then the average time of
 *  of execution is calculated and printed on screen.
 */
void StoragePoolTest ( SLPool & _pool, std::time_t _timeLimit ) 
{
    std::cout << ">>> Beginning tests with a storage pool." << std::endl;
    std::cout << ">>> Tests will be executed for " << _timeLimit  << " rounds." << std::endl;
    
    // Priority queue to store each event.
    std::priority_queue<Event> pq;
    
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> mi_avg(0.0);
    
    for ( std::time_t t ( 0 ) ; t < _timeLimit ; ++ t )
    {  
        start = std::chrono::steady_clock::now();
        while ( !pq.empty() ) { // Run while we have events pending or time to run .
            Event ev = pq.top(); // Access the event with the smallest time - stamp .
            if ( ev.getTimeStamp() > t ) break ; // Still some time left ....
            // When we got here , the top event has run out of time .
            pq.pop(); // Remove event from priority queue .
            _pool.Free( ev.getMemoryPtr() ); // Calling free operator .
        }
        auto memSize = getRandomForSize();
        void * const add = _pool.Allocate ( memSize );
        end = std::chrono::steady_clock::now();
        auto elapsedTime = getRandomTimeInterval ();
        std::time_t releaseTime = t + elapsedTime; // Set time stamp some time from now 
        Event aux ( add, releaseTime );
        pq.push( aux ); // Creating a new simulation event.
        
        // Average calculated using progressive average.
        mi_avg = mi_avg + (end - start - mi_avg) / static_cast<double>(t+1);
    }
    
    std::cout << "Average time taken: " << std::chrono::duration <double, std::nano> (mi_avg).count() << "ns\n" <<std::endl;
}

/*!
 *  @brief Tests the standard system memory manager.
 *  
 *  @param _timeLimit Number of times the operations will be run.
 *  
 *  Uses a sequence of allocations and frees to test standard system memory manager. The 
 *  allocations are associated with objects from the Event class, so each of them has
 *  a randomly generated time-stamp indicating when the allocated memory should be freed.
 *  The allocate and free operations are executed in a total of _timeLimit times, 
 *  then the average time of execution is calculated and printed on screen.
 *  
 *  The allocations on this test are char arrays of randomly generated sizes.
 *
 */
void SystemTest (time_t _timeLimit)
{
    std::cout << ">>> Beginning tests with system management" << std::endl;
    std::cout << ">>> Tests will be ran for " << _timeLimit  << " rounds." << std::endl;
    
    // Priority queue to store each event.
    std::priority_queue<Event> pq;
    
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> sys_avg(0.0);

    for ( std::time_t t ( 0 ) ; t < _timeLimit ; ++ t )
    {  
        start = std::chrono::steady_clock::now();
        while ( !pq.empty() ) { // Run while we have events pending or time to run .
            Event ev = pq.top(); // Access the event with the smallest time - stamp .
            if ( ev.getTimeStamp() > t ) break ; // Still some time left ....
            // When we got here , the top event has run out of time .
            pq.pop(); // Remove event from priority queue .
            delete[]  ev.getMemoryPtr(); // Calling free operator .
        }
        auto memSize = getRandomForSize();
        char * const add = new char[memSize];
        end = std::chrono::steady_clock::now();
        auto elapsedTime = getRandomTimeInterval ();
        std::time_t releaseTime = t + elapsedTime; // Set time stamp some time from now 
        Event aux ( reinterpret_cast<void*>(add), releaseTime );
        pq.push( aux ); // Creating a new simulation event .
        
        // Average calculated using progressive average.
        sys_avg = sys_avg + (end - start - sys_avg) / static_cast<double>(t+1);
    }
    
    // There are still some allocated blocks when the number of rounds is reached.
    // They have to be freed from memory.
    while ( !pq.empty() ) 
    {
        Event ev = pq.top();
        pq.pop();
        delete[]  ev.getMemoryPtr(); // Calling free operator.
    }
    
    std::cout << "Average time taken: " << std::chrono::duration <double, std::nano>(sys_avg).count() << "ns\n" <<std::endl;
}

/*!
 *  @brief Showcases a the memory pool state in a sequence of allocations e frees
 *  
 *  Through printing on terminal, checks the behavior of the memory pool by showing
 *  it's state in three types of situations.    
 */
void ShowPoolExample ()
{
    SLPool ex (350);
    
    // The first situation is for affirming that the memory pool can contain a number
    // of different variable types altogether.
    std::cout << "\n> Allocating simple variables" << std::endl;
    
    std::cout << "Allocating int" << std::endl;
    int * ptr_a = new (ex) int;
    std::cout << ex;
    
    std::cout << "Allocating long int" << std::endl;
    long int * ptr_b = new (ex) long int;
    std::cout << ex;
    
    std::cout << "Allocating float" << std::endl;
    float * ptr_c = new (ex) float;
    std::cout << ex;
    
    std::cout << "Allocating char" << std::endl;
    char * ptr_d = new (ex) char;
    std::cout << ex;
    
    std::cout << "Allocating double" << std::endl;
    double * ptr_e = new (ex) double;
    std::cout << ex;
    
    std::cout << "Allocating long double" << std::endl;
    long double * ptr_f = new (ex) long double;
    std::cout << ex;
    
    std::cout << "Allocating std::string" << std::endl;
    std::string * ptr_g = new (ex) std::string;
    std::cout << ex;
    
    std::cout << "Allocating long long int" << std::endl;
    long long int * ptr_h = new (ex) long long int;
    std::cout << ex;
    
    // The second case displays how the process of freeing variables merges the 
    // free areas nearby
    std::cout << "> Freeing..." << std::endl;
    
    delete ptr_b;
    std::cout << ex;
    delete ptr_d;
    std::cout << ex;
    delete ptr_c;
    std::cout << ex;
    delete ptr_a;
    std::cout << ex;
    delete ptr_e;
    std::cout << ex;
    delete ptr_g;
    std::cout << ex;
    delete ptr_h;
    std::cout << ex;
    delete ptr_f;
    std::cout << ex;
    
    // The third situation displays the pool allocation behavior when receiving bigger 
    // variables and dealing with having fragmented areas, showing how different are
    // best fit and first fit
    
    std::cout << "> Allocating bigger variables (arrays)" << std::endl;

    int * a = new (ex) int [24];
    int * b = new (ex) int;
    
    int * c = new (ex) int [19];
    int * d = new (ex) int;
    
    int * e = new (ex) int [14];
    int * f = new (ex) int;
    
    delete[] a;
    delete[] c;
    delete[] e;
    
    std::cout << "Memory pool after some allocations and frees.";
    std::cout << ex;
    
    std::cout << "Allocating 3 blocks of memory." << std::endl;
    int * g = new (ex) int [14];
    std::cout << ex;
    
    std::cout << "Allocating 4 blocks of memory." << std::endl;
    int * h = new (ex) int [19];
    std::cout << ex;
    
    std::cout << "Allocating 5 blocks of memory." << std::endl;
    int * i = new (ex) int [24];
    std::cout << ex;
}

