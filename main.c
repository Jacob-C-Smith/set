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
    if ( set_construct(&p_set, 4, (set_equal_fn *)strcmp) == 0 ) goto failed_to_construct_set;

    // Add elements to the set
    set_add(p_set, "Hi");
    set_add(p_set, "Hello");
    set_add(p_set, "Hola");
    set_add(p_set, &z);

    // Destruct the set
    if ( set_destroy(&p_set) == 0 ) goto failed_to_destroy_set;

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {

        // Set errors
        {
            failed_to_construct_set:
                printf("Failed to construct set!\n");

                // Error
                return EXIT_FAILURE;

            failed_to_destroy_set:
                printf("Failed to destroy set!\n");

                // Error
                return EXIT_FAILURE;
        }
    }
}