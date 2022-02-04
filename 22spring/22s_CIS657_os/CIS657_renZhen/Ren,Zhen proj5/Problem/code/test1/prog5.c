#include "syscall.h"

char data[2048];

int
main()
{
  int i,j;
  OpenFileId output;
  char* str = "Hello from prog5\n";
  output = Open("testfile.txt");

  for (i = 0; i < 5; i++)
  {
    Write(str, 18, output);
    for (j = 0; j < 10000; j++);
  }
  Close(output);

  Exit(0);
}
