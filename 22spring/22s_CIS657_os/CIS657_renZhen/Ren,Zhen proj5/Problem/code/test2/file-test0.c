#include "syscall.h"

char data[2048];

int
main()
{

  int i,j;
  char* str = "Hello from file-test0\n";
  OpenFileId output;

   if (Create("file-test0.txt"))
      {
      output = Open("file-test0.txt"); 
      }
   else 
      Exit(1);

  
  for (i = 0; i < 5; i++)
  {
    Write(str, 22, output);
    for (j = 0; j < 10000; j++);
  }

  Close(output);
  Exit(0);
}
