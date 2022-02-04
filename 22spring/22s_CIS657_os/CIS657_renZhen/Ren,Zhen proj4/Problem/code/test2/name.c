#include "syscall.h"

char data[2048];

int
main()
{
  OpenFileId output = ConsoleOutput;

  char* str = "Peilin Li 2021/11/23\n";
  
  int i,j;
  for (i = 0; i < 10; i++)
  {
    Write(str, 22, output);
    for (j = 0; j < 10000; j++);
  }

  Exit(0);
}
