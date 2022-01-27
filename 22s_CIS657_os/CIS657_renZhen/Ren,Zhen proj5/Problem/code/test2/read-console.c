#include "syscall.h"

int
main()
{
    SpaceId newProc;
    OpenFileId input = ConsoleInput;
    OpenFileId output = ConsoleOutput;
    char prompt[7], ch, buffer[60];
    int i, count;

    prompt[0] = 'N';
    prompt[1] = 'A';
    prompt[2] = 'C';
    prompt[3] = 'H';
    prompt[4] = 'O';
    prompt[5] = 'S';
    prompt[6] = '>';

    while( 1 )
    {
	Write(prompt, 7, output);

	i = 0;
	count = 0;

	do {
	
	    Read(&buffer[i], 1, input); 
	    count++;

	} while( buffer[i++] != '\n' );

	buffer[--i] = '\0';

    Write("I just read ", 12, ConsoleOutput);
    Write(&buffer, count, ConsoleOutput);
    Write("\n", 1, ConsoleOutput);

    }
}

