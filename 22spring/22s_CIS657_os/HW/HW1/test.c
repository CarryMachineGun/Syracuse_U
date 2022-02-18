#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    int ret = open("./a/test.log", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    // int ret = open("./logdir/test.log", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if(ret == -1) printf("FUCK");

    return 0;
}


