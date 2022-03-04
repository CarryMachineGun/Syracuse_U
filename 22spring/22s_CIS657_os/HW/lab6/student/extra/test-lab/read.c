#include "syscall.h"

char data[2048];

int
main()
{
  OpenFileId input = ConsoleInput;

  char buffer[100];
  
  int i,j;
  for (i = 0; i < 5; i++)
  {
    Read(&buffer, 50, input);
    for (j = 0; j < 10000; j++);
  }

  Exit(0);
}
