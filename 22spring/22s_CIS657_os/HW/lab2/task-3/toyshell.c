/* The skeleton code for task-3 */

/**
 * You have to add your code to the places where it shows
 * <<YOUR CODE GOES HERE>> 
 *
 * You do not need to modify/edit/remove the existing code.
 *
 * The source file contains additional comments to explain the code 
 * or provide hint that you can leverage while completing the code.
 **/

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <assert.h>

// Some Macros for convenience
#define LINESZ 1024 
#define PRINT_ERROR_PARENT printf("Parent: An error has occurred\n")
#define PRINT_ERROR_CHILD  printf("Child: An error has occurred\n")


int main()
{
  // line holds the entire input string (including white spaces)
  char line[LINESZ+2]; 

  // cmdargs holds all the tokens of the given input string.
  // The size of cmdargs[] is 4, because
  // cmdargs[0] is expected to hold the given Linux command,
  // the next two elements are expected to hold 2 arguments for the given command,
  // and the final element of cmdargs is to store NULL. 
  char *cmdargs[4] ; 


  // a temporary pointer
  char *p ; 

  // the index counter
  int idx;


  
  while(1){
    /* Print a prompt for user */
    printf("Type your command: ");
    fflush(stdout);

    /* Keep reading user input from stdin line-by-line */
    if(fgets(line, 1024, stdin) == NULL){
      printf("Exiting...\n");
      break;
    }
    // strtok is a C library function to 
    // tokenize a string based on the delimiters
    // provided as the second argument.
    p = strtok(line, " \t\n"); 

    idx = 0; // re-initialize to 0

    while(p)
    {
      // cmdargs array holds each token of the user input (i.e., line)
      cmdargs[idx++] = p ;

      // extract the next token
      p = strtok(NULL, " \t\n"); 
      
      /* Right now, this program does not like any command with 
       * more than 2 args */
      if(idx > 3 /* 1 for the command + 2 for two args */)
      {
        PRINT_ERROR_PARENT;
        break; // we should stop processing tokens any more
      }
    }

    if (idx > 3)
      continue; // don't execute the given command, instead start over
		
    cmdargs[idx] = NULL ; // last element of cmdargs should be NULL

    //
    //<YOUR CODE GOES HERE>
    //
    // Pseudocode:
    // 1. Fork the process. 
    int rc = fork();
    // 2. If fork failed, then print error message (using PRINT_ERROR_PARENT) 
    //    and exit.
    if(rc < 0){
      PRINT_ERROR_PARENT;
      exit(1);
    // 3. If fork was successful, then
    // 3a. Is this child? If so, then 
    //      - Invoke execvp() to execute the command available in `cmdargs[]`.
    //      - Check if execvp() failed, then print error message 
    //          (using PRINT_ERROR_CHILD) and exit.
    }else if(rc == 0){
      execvp(cmdargs[0], cmdargs);
      PRINT_ERROR_CHILD;
    // 3b. Is this parent? If so, then
    //      - wait for the child process to finish. Use wait()/waitpid().
    //      - ** note: Once child is done, parent will continue the while loop
    //      for the next iteration. **
    //
    // 
    }else{
      int wc = wait(NULL);
    }     
  } // end of while(1)
	
  return 0 ; // exit with SUCCESS
}
