#include "syscall.h"

char data[2048];

int
main()
{
  OpenFileId output = ConsoleOutput;

  char* str = "Hello from Zhen Ren  \n";
  
  int i;
  for (i = 0; i < 10; i++)
  {
    Write(str, 23, output);
  }

  Exit(0);
}
