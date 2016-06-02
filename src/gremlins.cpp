// #include "header.h"

#include <iostream>
#include "mempool_common.h"
// #include "storagepool.h"
#include "slpool.h"


int main ()
{
    SLPool mem(110);
    
    // auto my_mem = mem.Allocate(100);
    
    
    std::cout << "1\n";
    long long int * x = new long long int;
    *x = 1974;
    std::cout << "x é " << *x << std::endl;
    delete x;
    
    
    std::cout << "e 3?\n";
    double * z = new (mem) double;
    *z = 3.1417;
    std::cout << "z é " << *z << std::endl;
    delete z;
    
    std::cout << "e 4?\n";
    long long int * w = new (mem) long long int;
    std::cout << "e 5?\n";
    long long int * k = new (mem) long long int;
    

    return EXIT_SUCCESS;
}

