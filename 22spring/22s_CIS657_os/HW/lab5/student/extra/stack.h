#ifndef STACK_H
#define STACK_H
#include "debug.h"
// stack.h
class Stack {
public:
   Stack(int sz); // Constructor: initialize variables, allocate space. 
   ~Stack(); // Destructor: deallocate space allocated above.
   void Push(int value); // Push an integer, checking for overflow. 
   bool Full(); // Returns TRUE if the stack if full, FALSE otherwise.
   void PopAndPrint(); // Iteratively pop & print the top. Calls Pop()
   int  Pop(); // Pop the top element in the stack

private:
   int size; // The maximum capacity of the stack.
   int top; // Index of the top of the stack.
   int *stack; // A pointer to an array that holds the contents.
};
#endif
