#include "syscall.h"

char data[2048];

int
main()
{
  OpenFileId output = ConsoleOutput;

  char* str = "Hello from prog1\n";
  
  int i,j;
  for (i = 0; i < 5; i++)
  {
    Write(str, 18, output);
    for (j = 0; j < 10000; j++);
  }

  Exit(0);
}
