#include "syscall.h"

int
main()
{

  int i,j;
  char* str = "Hello from file-test1\n";
  OpenFileId output;

   if (Create("file-test1.txt")) {
      output = Open("file-test1.txt"); 
      Write("Opened file-test1.txt\n", 22, ConsoleOutput);
   }
   else {
      Write("Problem Creating a file\n", 24, ConsoleOutput);
      Exit(1);
   }

   if (Open("nofile.txt") < 0) {
      Write("File doesn't exist\n", 19, ConsoleOutput);
      Exit(1);
   }

  
  for (i = 0; i < 5; i++)
  {
    Write(str, 22, output);
    for (j = 0; j < 10000; j++);
  }

  Close(output);
  Exit(0);
}
