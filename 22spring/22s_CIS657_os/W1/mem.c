#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// #include "common.h"

int main(int argc, char *argv[]) {
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) address of p: %08x\n", getpid(), (unsigned) p); // a2: print out the address of the memory
    *p = 0; // a3: put zero into the first slot of the memory 
    while (1) {
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p); // a4
    }
    return 0;
}