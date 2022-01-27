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
    OpenFileId outfile;
    char buffer[100];
    char* str = "Hello from file-test4\n";
    int i,j;
    char num2stringBuffer[100];
    int numWritten = 0;
    int length = 0;
    outfile = Open("file-test4.txt");
    for (i = 0; i < 5; i++)
    {
        numWritten = Read(&buffer, 30, outfile);
        Write(buffer, numWritten, ConsoleOutput);
        Write("Number of Characters Written is ", 32,
        ConsoleOutput);
        length = tostring(&num2stringBuffer, numWritten);
        Write(&num2stringBuffer, length, ConsoleOutput);
        Write("\n", 1, ConsoleOutput);
        for (j = 0; j < 10000; j++);
    }
    if (Close(outfile)){
    Write("close file correctly\n", 22 , ConsoleOutput);
    }else{
    Write("close file fail\n", 17 , ConsoleOutput);
    }
Exit(0);
}