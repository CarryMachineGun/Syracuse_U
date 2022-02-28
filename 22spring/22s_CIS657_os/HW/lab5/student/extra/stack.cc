#include "stack.h"
#include "debug.h"

Stack::Stack(int sz) {
    size = sz;
    top = 0;
    stack = new int[size]; // an array of integers of size "size"
}

Stack::~Stack() {
    delete stack;
}

bool
Stack::Full() {
    return (top == size);
}


void
Stack::Push(int value) {
  ASSERT(!Full()); 
  stack[top++] = value; 
}



int 
Stack::Pop() {
  return stack[--top];
}

void
Stack::PopAndPrint(){
  while (top > 0) {
	printf("Element %d of the stack is %d\n", top, Pop());
  }
}


