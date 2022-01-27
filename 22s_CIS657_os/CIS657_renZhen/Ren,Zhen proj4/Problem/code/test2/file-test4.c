#include "syscall.h"

int
main()
{
  OpenFileId input;
  char buffer[100];
  int i,j;
  input = Open("file-test0.txt");

  for (i = 0; i < 2; i++)
  {
    Read(&buffer, 22, input);
    Write(buffer, 22, ConsoleOutput);
    for (j = 0; j < 10000; j++);
  }
  Close(input);
  Exit(0);
}

