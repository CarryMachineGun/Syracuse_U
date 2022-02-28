#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "stack.h"

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
        printf("*** thread %d looped %d times\n", which, num);
        kernel->currentThread->Yield();
    }
}

void
ThreadTest()
{

/*
    Thread *t = new Thread("forked thread");
    t->Fork((VoidFunctionPtr) SimpleThread, (void *) 1);
    
    SimpleThread(0);
*/

Stack *s = new Stack(20); // ...
s->Push(17);
s->Push(16);
s->Push(15);
s->Push(14);
s->PopAndPrint();
delete s;
}
