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
  if(Close(input)){
    Write("close correctly\n",20,ConsoleOutput);
  }else{
    Write("close wrongly \n",20,ConsoleOutput);
  }
  Exit(0);
}