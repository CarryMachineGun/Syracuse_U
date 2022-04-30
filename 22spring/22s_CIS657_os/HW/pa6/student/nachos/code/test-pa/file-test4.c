#include "syscall.h"

// convert an integer to a string. The code is available over the Internet
int tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    if (num > 0)
    {
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
    }
    else if (num < 0)
    {
        num = 0 - num;
        n = num;
        len++;
        str[0] = '-';

        while (n != 0)
        {
            len++;
            n /= 10;
        }
        for (i = 1; i < len; i++)
        {
            rem = num % 10;
            num = num / 10;
            str[len - (i + 1) + 1] = rem + '0';
        }
    }
    else
    {
        len = 1;
        str[len - 1] = '0';
    }

    str[len] = '\0';

    return len + 1;
}

int main()
{
    OpenFileId outfile0, input, not_exist_file;

    char *str = "Hello from file-test4\n";
    char num2stringBuffer[100];
    char buffer[100];
    int numWritten = 0;
    int length = 0;

    if (Create("file-test4.txt") == -1)
    {
        Exit(1);
    }

    outfile0 = Open("file-test4.txt");

    Write(str, 22, outfile0);

    Close(outfile0);

    input = Open("file-test2.txt");
    not_exist_file = input - 100;

    // – Print “Read(): Successful: read x bytes”, where x is the value returned by Read() on
    // success.
    numWritten = Read(&buffer, 22, input);
    Write("Read(): Successful: read ", 25, ConsoleOutput);
    length = tostring(&num2stringBuffer, numWritten);
    Write(&num2stringBuffer, length, ConsoleOutput);
    Write(" bytes\n", 7, ConsoleOutput);

    // – Print “Read(): Failed: returned y”, where y is the value returned by Read() on failure.
    numWritten = Read(&buffer, 22, not_exist_file);
    Write("Read(): Failed: returned ", 25, ConsoleOutput);
    length = tostring(&num2stringBuffer, numWritten);
    Write(&num2stringBuffer, length, ConsoleOutput);
    Write("\n", 1, ConsoleOutput);

    // – Print “Close(): Successful: returned x”, where x is the value returned by Close() on
    // success.
    numWritten = Close(input);
    Write("Close(): Successful: returned ", 30, ConsoleOutput);
    length = tostring(&num2stringBuffer, numWritten);
    Write(&num2stringBuffer, length, ConsoleOutput);
    Write("\n", 1, ConsoleOutput);

    // – Print “Close(): Failed: returned y”, where y is the value returned by Close() on failure.
    numWritten = Close(not_exist_file);
    Write("Close(): Failed: returned ", 26, ConsoleOutput);
    length = tostring(&num2stringBuffer, numWritten);
    Write(&num2stringBuffer, length, ConsoleOutput);
    Write("\n", 1, ConsoleOutput);

    Exit(0);
}
