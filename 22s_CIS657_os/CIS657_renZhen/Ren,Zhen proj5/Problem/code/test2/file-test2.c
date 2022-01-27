#include "syscall.h"

int
main()
{
  OpenFileId input;
  OpenFileId outfile0; 
  OpenFileId outfile1; 

 char buffer[100];
 char* str = "Hello from file-test2\n";
 int i,j;

  if (Create("file-test2.txt") == -1) {
     Exit(1);
  }

  outfile0 = Open("file-test2.txt");

  for (i = 0; i < 5; i++)
  {
    Write(str, 22, outfile0);
    for (j = 0; j < 10000; j++);
  }

  Close(outfile0);

  input = Open("file-test2.txt");

  if (Create("fiale-test2a.txt") == -1) 
     {
     Exit(1);
     }

  if ((outfile1 = Open("file-test2a.txt")) == -1)
	Exit(1);
  for (i = 0; i < 5; i++)
  {
    Read(&buffer, 22, input);
    Write(buffer, 22, outfile1);
    for (j = 0; j < 10000; j++);
  }
  Close(input);
  Exit(0);
}

