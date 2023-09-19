/** !
 * set library
 *
 * @file set.c
 *
 * @author Jacob Smith
 */

// Headers
#include <set/set.h>

// Structure definitions
struct set_s
{
    void   **elements;
    size_t   max;
    size_t   count;
    mutex    _lock;
};

int set_create ( set **const pp_set )
{

    // Argument check
    if ( pp_set == (void *) 0 ) goto no_set;

    // Initialized data
    set *p_set = SET_REALLOC(0, sizeof(set));

    // Error checking
    if ( p_set == (void *) 0 ) goto no_mem;

    // Zero set
    memset(p_set, 0, sizeof(set));

    // Return the allocated memory
    *pp_set = p_set;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_set:
                #ifndef NDEBUG
                    printf("[set] Null pointer provided for parameter \"pp_set\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {
            no_mem:
                #ifndef NDEBUG
                    printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

// TODO: Implement these functions
/*
int  set_construct           ( set       **const pp_set, size_t             size );
int  set_from_elements       ( set       **const pp_set, const void **const pp_elements, size_t            size );
int  set_union               ( set       **const pp_set, const set   *const p_a        , const  set *const p_b );
int  set_difference          ( set       **const pp_set, const set   *const p_a        , const  set *const p_b );
int  set_intersection        ( set       **const pp_set, const set   *const p_a        , const  set *const p_b );
bool set_isdisjoint          ( const set  *const p_a   , const set   *const p_b );
bool set_issubset            ( const set  *const p_a   , const set   *const p_b );
bool set_issuperset          ( const set  *const p_a   , const set   *const p_b );
int  set_add                 ( set        *const p_set , const void  *      p_element );
void set_discard             ( set        *const p_set , void        *      p_element );
int  set_difference_update   ( set        *const p_a   , const set   *const p_b );
int  set_intersection_update ( set        *const p_a   , const set   *const p_b );
int  set_update              ( set        *const p_a   , const set   *const p_b );
int  set_pop                 ( set        *const p_set , void       **const pp_value );
int  set_remove              ( set        *const p_set , void        *const p_value );
int  set_clear               ( set        *const p_set );
int  set_free_clear          ( set        *const p_set , void       (*pfn_free_func) );
int  set_copy                ( const set  *const p_set , set        **const pp_set );
int  set_destroy             ( set       **const pp_set );
*/