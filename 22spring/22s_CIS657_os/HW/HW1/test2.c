#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        printf("fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        close(STDOUT_FILENO);
        int ret = open("./out.log", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        if (ret == -1)
        {
            printf("Failed to open file for stdout redirection\n");
            exit(1);
        }
        char *myargs[2];
        myargs[0] = strdup("ls"); // execute ls command
        myargs[1] = NULL;
        int status = execvp(myargs[0], myargs);
        if (status == -1)
        {
            printf("execvp: failed");
            exit(1);
        }
        printf("Child: Finished\n");
    }
    else
    {
        wait(NULL);
        printf("Parent: Finished\n");
    }
    return 0;
}