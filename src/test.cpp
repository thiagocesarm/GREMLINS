#include <random>
#include <chrono>
#include <queue>
#include <string>
#include <ctime>
#include "mempool_common.h"
#include "slpool.h"

void SLPoolAllocate (SLPool & _pool)
{
    int * a = new (_pool) int [147];
    delete[] a;
 
    int * b = new (_pool) int;
 
    long int * c = new (_pool) long int;
 
    long long int * d = new (_pool) long long int;
    
    float * e = new (_pool) float;
    
    double * f = new (_pool)  double;
    
    long double * g = new (_pool) long double;
    
    char * h = new (_pool) char;
    
    std::string * i = new (_pool) std::string;
    
    delete b;
    delete c; 
    delete d;
    delete e;
    delete f;
    delete g;
    delete i;
    delete h; 
    
    char * H = new (_pool) char[60];
 
    long int * C = new (_pool) long int[3];
 
    float * E = new (_pool) float[12];
    
    std::string * I = new (_pool) std::string[5];
    delete[] E;
    delete[] C; 
    
    int * B = new (_pool) int[10];
    delete[] H; 
    
    double * F = new (_pool)  double[2];
    delete[] F;
    
    long double * G = new (_pool) long double[4];
    delete[] I;
    
    long long int * D = new (_pool) long long int[3];
    delete[] B;
    delete[] G;
    
    delete[] D;
}

void SystemAllocate ()
{
    int * a = new int [147];
    delete[] a;
 
    int * b = new int;
 
    long int * c = new long int;
 
    long long int * d = new long long int;
    
    float * e = new float;
    
    double * f = new  double;
    
    long double * g = new long double;
    
    char * h = new char;
    
    std::string * i = new std::string;
    
    delete b;
    delete c; 
    delete d;
    delete e;
    delete f;
    delete g;
    delete i;
    delete h; 
    
    char * H = new char[60];
 
    long int * C = new long int[3];
 
    float * E = new float[12];
    
    std::string * I = new std::string[5];
    delete[] E;
    delete[] C; 
    
    int * B = new int[10];
    delete[] H; 
    
    double * F = new  double[2];
    delete[] F;
    
    long double * G = new long double[4];
    delete[] I;
    
    long long int * D = new long long int[3];
    delete[] B;
    delete[] G;
    
    delete[] D;
}

void StoragePoolTest ( /*const StoragePool & _pool*/ ) 
{
    std::srand(std::time(0));
    // Generating values between 200 and 500
    size_t poolSz = rand() % 300 + 500;
    
    // Instatiating a pool for testing purposes
    SLPool poolToTest(poolSz);
    
    size_t _nTest;
    
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> mi_avg(0.0);
    std::chrono::duration<double> sys_avg(0.0);
    
    std::cout << "For how many tests do you wish to run?" << std::endl;
    std::cin >> _nTest;
    
    for ( size_t i( 0u ) ; i < _nTest ; ++i )
    {
        // Custom memory manager test
        start = std::chrono::steady_clock::now();
        SLPoolAllocate(poolToTest);
        end = std::chrono::steady_clock::now();
        mi_avg = mi_avg + (end - start - mi_avg) / static_cast<double>(i+1);
        
        // System memory manager test
        start = std::chrono::steady_clock::now();
        SystemAllocate();
        end = std::chrono::steady_clock::now();
        sys_avg = sys_avg + (end - start - sys_avg) / static_cast<double>(i+1);
        
    }
    std::cout << "Testing with memory pool size: " << poolSz << std::endl;
    std::cout << "SLPool's average time (nanoseconds): " << std::chrono::duration <double, std::milli> (mi_avg).count() << "\n";
    std::cout << "System memory manager average time (nanoseconds): " << std::chrono::duration <double, std::milli> (sys_avg).count() << "\n";
}


/*
void
medeTempo(  vector<long int>& V, const long int &x, long int first, long int last, int k,
    int (*_funcoesBusca) ( vector<long int>&, const long int &, long int, long int, int) )
{

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> media(0.0);

    for (int i = 0; i < 100; ++i)
    {
        start = std::chrono::steady_clock::now();
        _funcoesBusca( V, x, first, last, k );
        end = std::chrono::steady_clock::now();
        media = media + (end - start - media) / static_cast<double>(i+1);
    }

    output_file << (last - first) + 1 << " " << std::chrono::duration <double, std::milli> (media).count() << "\n";
    output_file.close();
}
*/