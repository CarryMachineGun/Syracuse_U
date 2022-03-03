#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0)
        return 1;
    else if (rc == 0)
    {
        printf("ola!");
        execvp("./a.out", argv);
    }
    else
        waitpid(rc, NULL, 0);

    return 0;
}