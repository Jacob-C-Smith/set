/** !
 * @file set/set.h 
 * 
 * @author Jacob Smith
 * 
 * Include header for set library
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// sync submodule
#include <sync/sync.h>

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Memory management macro
#ifndef SET_REALLOC
#define SET_REALLOC(p, sz) realloc(p,sz)
#endif

// Forward declarations
struct set_s;

// Type definitions
/** !
 *  @brief The type definition of a set struct
 */
typedef struct set_s set;

// Allocaters
/** !
 *  Allocate memory for a set
 *
 * @param pp_set return
 *
 * @sa set_destroy
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_create ( set **const pp_set );

// Constructors
/** !
 *  Construct a set with a specific number of elements
 *
 * @param pp_set return
 * @param size   number of set elements. 
 *
 * @sa set_create
 * @sa set_from_elements
 * @sa set_union
 * @sa set_difference
 * @sa set_intersection
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_construct ( set **const pp_set, size_t size );

/** !
 *  Construct a set from an array of elements
 *
 * @param pp_set      return
 * @param pp_elements pointer to array of elements
 * @param size        quantity of elements in element parameter. 
 *
 * @sa set_create
 * @sa set_construct
 * @sa set_union
 * @sa set_difference
 * @sa set_intersection
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_from_elements ( set **const pp_set, const void **const pp_elements, size_t size );

/** !
 *  Construct a set from the union of set A and set B
 *
 * @param pp_set return
 * @param p_a    pointer to set A
 * @param p_b    pointer to set B
 *
 * @sa set_create
 * @sa set_construct
 * @sa set_from_elements
 * @sa set_difference
 * @sa set_intersection
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_union ( set **const pp_set, const set *const p_a, const set *const p_b );

/** !
 *  Construct a set from the difference of set A and set B
 * 
 * @param pp_set return
 * @param p_a    set A
 * @param p_b    set B
 * 
 * @sa set_create
 * @sa set_construct
 * @sa set_from_elements
 * @sa set_union
 * @sa set_intersection
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int set_difference ( set **const pp_set, const set *const p_a, const set *const p_b );

/** !
 *  Construct a set from the intersection of set A and set B
 * 
 * @param pp_set return
 * @param p_a    set A
 * @param p_b    set B
 * 
 * @sa set_create
 * @sa set_construct
 * @sa set_from_elements
 * @sa set_union
 * @sa set_difference
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int set_intersection ( set **const pp_set, const set *const p_a, const set *const p_b );

// Accessors
/** !
 *  Test if set A and set B are disjoint
 * 
 * @param p_a set A
 * @param p_b set B
 * 
 * @sa set_issubset
 * @sa set_issuperset
 * 
 * @return true if set A is disjoint to set B else false
 */
DLLEXPORT bool set_isdisjoint ( const set *const p_a, const set *const p_b );

/** !
 *  Test if set A is a subset of set B
 * 
 * @param p_a set A
 * @param p_b set B
 * 
 * @sa set_isdisjoint
 * @sa set_issuperset
 * 
 * @return true if A is a subset of B else false
*/
DLLEXPORT bool set_issubset ( const set *const p_a, const set *const p_b );

/** !
 *  Test if set A is a superset of set B
 * 
 * @param p_a set A
 * @param p_b set B
 * 
 * @sa set_isdisjoint
 * @sa set_issubset
 * 
 * @return true if A is a superset of B else false
*/
DLLEXPORT bool set_issuperset ( const set *const p_a, const set *const p_b );

// Mutators
/** !
 *  Add an element to a set. 
 *
 * @param p_set   pointer to the set
 * @param p_value the element
 *
 * @sa set_discard
 * @sa set_difference_update
 * @sa set_intersection_update
 * @sa set_update
 * @sa set_pop
 * @sa set_remove
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_add ( set *const p_set, const void *p_element );

/** !
 *  Remove an element form an existing set
 *
 * @param pp_set return
 * @param size   number of set elements. 
 *
 * @sa set_add
 * @sa set_difference_update
 * @sa set_intersection_update
 * @sa set_update
 * @sa set_pop
 * @sa set_remove
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT void set_discard ( set *const p_set, void *p_element );

/** !
 *  Update an existing set with the difference of itself and another set 
 *
 * @param p_a an existing set
 * @param p_b another set
 *
 * @sa set_add
 * @sa set_discard
 * @sa set_intersection_update
 * @sa set_update
 * @sa set_pop
 * @sa set_remove
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_difference_update ( set *const p_a, const set *const p_b );

/** !
 *  Update an existing set with the intersection of itself and another set 
 *
 * @param p_a an existing set
 * @param p_b another set
 *
 * @sa set_add
 * @sa set_discard
 * @sa set_difference_update
 * @sa set_update
 * @sa set_pop
 * @sa set_remove
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_intersection_update ( set *const p_a, const set *const p_b );

/** !
 *  Update an existing set with the union of itself and another set 
 *
 * @param p_a an existing set
 * @param p_b another set
 *
 * @sa set_add
 * @sa set_discard
 * @sa set_difference_update
 * @sa set_intersection_update
 * @sa set_pop
 * @sa set_remove
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_update ( set *const p_a, const set *const p_b );

/** !
 *  Remove and return an element from a set
 *
 * @param p_set    the set
 * @param pp_value return
 *
 * @sa set_add
 * @sa set_discard
 * @sa set_difference_update
 * @sa set_intersection_update
 * @sa set_update
 * @sa set_remove
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_pop ( set *const p_set, void **const pp_value );

/** !
 *  Remove an element from a set.
 *
 * @param p_set   the set
 * @param p_value return
 *
 * @sa set_add
 * @sa set_discard
 * @sa set_difference_update
 * @sa set_intersection_update
 * @sa set_update
 * @sa set_pop
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_remove ( set *const p_set, void *const p_value );

// Clear elements
/** !
 *  Remove all elements from a set
 *
 * @param p_set set
 *
 * @sa set_free_clear
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_clear ( set *const p_set );

/** !
 *  Remove all elements from a set, and deallocate values with pfn_free_func
 *
 * @param p_set         the set
 * @param pfn_free_func pointer to deallocator function of type void (*)(void *)
 * 
 * @sa set_clear
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_free_clear ( set *const p_set, void (*pfn_free_func) );

// Shallow copy
/** !
 *  Make a shallow copy of a set
 *
 * @param p_set  the set
 * @param pp_set return
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_copy ( const set *const p_set, set **const pp_set );

// Destructors
/** !
 *  Destroy and deallocate a set 
 *
 * @param pp_set pointer to a set pointer
 *
 * @sa set_create
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int set_destroy ( set **const pp_set );
