## GREMLINS
### A Memory Manager using simple linked lists

##### Version 1.0.0 - Wednesday June 8th 2016

by Thiago Cesar Morais Diniz de Lucena & Yuri Reinaldo da Silva  

Can be found at: https://github.com/thiagocesarm/GREMLINS

Introduction
--------------------------------------------------------------------------------------

GREMLINS, is a memory manager developed in C++ devised to increase the performance
of continuous allocations and frees. It separates preemptively a quantity of memory 
with the size set by the user. GREMLINS can be used in a wide variety of applications
who desire to have control of it's memory management and better results.

Instalation and running
--------------------------------------------------------------------------------------

To install and execute the program, follow these steps: 

1. The file must be extracted from the accompanying zip folder 
  "Project_Gremlins.zip", it should come with all the files necessary.
2. Open your terminal and navigate to the folder where the files where extracted
   to.
3. Simply input the __make__ command.
..* Instead of make, another way to do it is by inputting the following command 
	at the terminal:

    *g++ -std=c++11 -I include src/gremlins.cpp -o bin/drive_gremlins -O3*
    
    3.1 If you want to test the Best Fit allocation method, input the following 
    command at the terminal:
    
    *g++ -std=c++11 -I include src/gremlins.cpp -o bin/drive_gremlins -O3 -D_BEST_FIT*


Then, to execute the program, you just run it by inputting the following command:
	
	*bin/drive_gremlins*

A reminder: To test the Best Fit allocation method, you have to compile the program
via the terminal command shown above. Best Fit allocation method does not work when
compiling with _make_ command.

Creating a memory pool
--------------------------------------------------------------------------------------

To use GREMLINS you must declare a memory within your code by inputting the following
at the header of your code:

#include "slpool.h"

Then you must declare a memory pool variable with the following structure:

SLPool *name* (*size_in_number_of_bytes*);

with this you have your memory pool ready to be used

Using your memory pool
--------------------------------------------------------------------------------------

In order to use your own memory pool you can use the _new_,_new[]_,_delete_ and 
_delete[]_ commands, but inputting _new_ or _new[]_ with the syntax below:

new (*your_pool*) *variable_type_you_want_to_allocate*

or 

new[] (*your_pool*) *variable_type_you_want_to_allocate*

Be wary: If the variable you want to allocate is bigger then any free area within the 
pool a std::bad_alloc exception will be thrown.

_delete_ and _delete[]_ can be used normally and has no changes with it's syntax.

Efficiency comparison test
--------------------------------------------------------------------------------------

The program provides a comparison test between memory pool's allocate and free
operations and standard _new_ and _delete_ operations. The test will ask for the
number of rounds the client wish to run the test. For best expected results, the
number of tests must be greater than 1000.

Recommendations
--------------------------------------------------------------------------------------

- A memory manager is very efficient at what it does, but it is better to be used if
many allocations are to be expected.

- If you expect to allocate mostly small variables, the first fit strategy will probably
be more efficient and quicker.

- If you are allocationg bigger memory sizes and freeing often, the best fit strategy 
will ensure less fragmenting and consequentially more free areas within the pool.

Bugs and limitations
--------------------------------------------------------------------------------------

No memory leaks were detected while executing the program. However, running the 
efficiency comparison test while checking for memory leaks might reduce drastically
the memory pool test efficiency. Thus, it is not recommended to run memory leak
check tools, eg. Valgrind, while running the comparison test.

When running the efficiency comparison test there is a possibility of the memory pool 
to not be able to contain all allocations, throwing a std::bad_alloc and exiting 
the program. In order to prevent this, for a higher number of tests, it's recommended 
to increase the size of the memory pool to be tested, respecting the memory limits
of the computer in which the test will be run. In the development tests, comparison
tests using a memory pool of size 2^29 were able to run up to 500000 round tests.