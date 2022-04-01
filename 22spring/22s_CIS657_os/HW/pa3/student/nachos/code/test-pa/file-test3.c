#include "syscall.h"

// convert an integer to a string. The code is available over the Internet
int tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
  return len+1;
}
 

int
main()
{
  OpenFileId outfile0; 

 char* str = "Hello from file-test3\n";
 char num2stringBuffer[100];
 int i,j;
 int numWritten = 0;
 int length = 0;


  if (Create("file-test3.txt") == -1) {
     Exit(1);
  }

  outfile0 = Open("file-test3.txt");

  for (i = 0; i < 5; i++)
  {
    numWritten = Write(str, 22, outfile0);
    Write("Number of Characters Written is ", 32, ConsoleOutput);
    length = tostring(&num2stringBuffer, numWritten);
    Write(&num2stringBuffer, length, ConsoleOutput);
    Write("\n", 1, ConsoleOutput);
  }

  Close(outfile0);

  Exit(0);
}

