// Standard library
#include <stdio.h>
#include <stdlib.h>

// Include
#include <set/set.h>

// Entry point
int main ( int argc, const char* argv[] )
{

    // Initialized data
    set *p_set = (void *) 0;
    char z[3] = { 'H', 'i', 0x0 };

    // Construct a set with 4 elements
    set_construct(&p_set, 4, (set_equal_fn *)strcmp);

    // Add elements to the set
    set_add(p_set, "Hi");
    set_add(p_set, "Hello");
    set_add(p_set, "Hola");
    set_add(p_set, &z);

    // Success
    return EXIT_SUCCESS;
}