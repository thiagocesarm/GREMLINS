/*!
 *  @mainpage Project GREMLINS
 *  @authors Thiago Cesar Morais Diniz de Lucena
 *  @authors Yuri Reinaldo da Silva
 *  @date June, 2016
 *  @version Beta
 *
 *	@file gremlins.cpp
 *
 *  File with the main function, used mostly to test slpool implementation.
 */
 
#include <iostream>
#include "mempool_common.h"
#include "slpool.h"
#include "test.cpp"
// #include "storagepool.h"


int main()
{
    /*
    SLPool _pool(400);
    int * a = new (_pool) int [147];
    delete[] a;
    
    a = new (_pool) int [147];
    delete[] a;*/
    
    
    
 /*
    int * b = new (_pool) int;
 
    long int * c = new (_pool) long int;
 
    long long int * d = new (_pool) long long int;
    
    float * e = new (_pool) float;
    
    double * f = new (_pool)  double;
    
    long double * g = new (_pool) long double;
    
    char * h = new (_pool) char;
    
    std::string * i = new (_pool) std::string;
    
    std::cout << _pool;
    
    delete c;std::cout << _pool; 
    delete e;std::cout << _pool;
    delete d;std::cout << _pool;
    delete b;std::cout << _pool;
    delete f;std::cout << _pool;
    delete i;std::cout << _pool;
    delete g;std::cout << _pool;
    delete h;std::cout << _pool; */
    
    StoragePoolTest();
    
    /*
    
    TESTE DO BEST FIT 
    
    
    long long int * x = new (mem) long long int;
    std::cout << mem;
    
    int * y = new (mem) int[36];
    std::cout << mem;
    
    long long int * z = new (mem) long long int;
    std::cout << mem;
    
    delete [] y;
    std::cout << mem;
    
    int * w = new (mem) int[24];
    std::cout << mem;
    */
    
    
    
    
    /*
    std::cout << "inserindo um arranjo de doubles\n";
    double * double_arr2 = new (mem) double[5];
    std::cout << mem;
    
    std::cout << "inserindo um long long int\n";
    long long int * x = new (mem) long long int;
    *x = 1974;
    // std::cout << "o long long int é " << *x << std::endl;
    std::cout << mem;
    
    std::cout << "removendo um long long int\n";
    delete x;
    std::cout << mem;
    
    std::cout << "inserindo um double\n";
    double * z = new (mem) double;
    *z = 3.1417;
    std::cout << mem;
    std::cout << "o double é " << *z << std::endl;
    
    // std::cout << "removendo um double\n";
    // std::cout << mem;
    // delete z;
    
    
    std::cout << "inserindo um char\n";
    char * w = new (mem)char;
    std::cout << mem;    
    
    // std::cout << "inserindo uma string\n";
    // std::string * j = new (mem) std::string;
    // *j = "HO";
    // std::cout << mem;
    
    
    // std::cout << "removendo um char\n";
    // delete w;
    // std::cout << mem;
    
    std::cout << "inserindo um arranjo de ints\n";
    int * zelandia = new (mem) int[20];
    std::cout << mem;
    
    std::cout << "inserindo um float\n";
    float * k = new (mem) float;
    std::cout << mem;
    
    
    std::cout << "Deletando primeira posição\n";
    delete x;
    std::cout << mem;
    
    std::cout << "inserindo um arranjo de doubles\n";
    double * double_arr = new (mem) double[2];
    std::cout << mem;
    
    std::cout << "inserindo outro float\n";
    float * l = new (mem) float;
    std::cout << mem;
    
    std::cout << "inserindo outro double\n";
    double * m = new (mem) double;
    std::cout << mem;
    
    delete[] zelandia;
    std::cout << mem;
    */
    return EXIT_SUCCESS;
}