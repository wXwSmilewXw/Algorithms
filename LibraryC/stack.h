#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "vector.h"

// Stack
// Stores pointer to custom user data
typedef void* Data;
// Custom function to free user pointers on delete
typedef void (FFree)(void*);

typedef struct Stack Stack;

#ifdef __cplusplus
extern "C" {
#endif

// Creates empty stack
Stack *stack_create();

Vector *stack_get_vector(Stack *stack);

// Deletes the stack
void stack_delete(Stack *stack);

// Pushes data on top of the stack
// Should be O(1) on average
void stack_push(Stack *stack, Data data);

// Retrives the last element from the stack
Data stack_get(const Stack *stack, size_t index);

// Removes the last element from the stack
// Should be O(1)
Data stack_pop(Stack *stack);

// Returns true if the stack is empty
bool stack_empty(const Stack *stack);

#ifdef __cplusplus
}
#endif

#endif
