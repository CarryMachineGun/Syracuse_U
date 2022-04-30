#include "syscall.h"

int
main()
{
  OpenFileId output = ConsoleOutput;

  char* str = "Yuchen Wang, 04/28/22\n";
  
  int i,j;
  for (i = 0; i < 10; i++)
  {
    Write(str, 22, output);
    for (j = 0; j < 10000; j++);
  }

  Exit(0);
}
