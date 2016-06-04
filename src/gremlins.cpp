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
// #include "storagepool.h"
#include "slpool.h"

int main ()
{
    SLPool mem(30);
    
    std::cout << "inserindo um long long int\n";
    long long int * x = new (mem) long long int;
    *x = 1974;
    std::cout << "o long long int é " << *x << std::endl;
    std::cout << mem;
    
    std::cout << "removendo um long long int\n";
    delete x;
    std::cout << mem;
    
    std::cout << "inserindo um double\n";
    double * z = new (mem) double;
    *z = 3.1417;
    std::cout << mem;
    std::cout << "o double é " << *z << std::endl;
    
    /*std::cout << "removendo um double\n";
    std::cout << mem;
    delete z;*/
    
    
    std::cout << "inserindo um char\n";
    char * w = new (mem)char;
    std::cout << mem;    
    
    // std::cout << "inserindo uma string\n";
    // std::string * j = new (mem) std::string;
    // *j = "HO";
    // std::cout << mem;
    
    
    /*std::cout << "removendo um char\n";
    delete w;
    std::cout << mem;*/
    
    
    std::cout << "inserindo um float\n";
    float * k = new (mem) float;
    std::cout << mem;
    
    
     std::cout << "Deletando primeira posição\n";
     delete x;
     std::cout << mem;
    
    std::cout << "inserindo outro float\n";
    float * l = new (mem) float;
    std::cout << mem;
    

    return EXIT_SUCCESS;
}

