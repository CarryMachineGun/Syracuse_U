#include "syscall.h"

int
main()
{
  OpenFileId output = ConsoleOutput;
  char* str = "Hello from prog4\n"; 
  char *bye = "Bye from prog4\n";

  int i,j;

  for (i = 0; i < 5; i++)
  {
    Write(str, 17, output);
    for (j = 0; j < 10000; j++);
  }
  
  Write(bye, 15, output);

  Exit(0);
}
