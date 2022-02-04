#include "syscall.h"

int
main()
{
    SpaceId newProc;
    OpenFileId input = ConsoleInput;
    OpenFileId output = ConsoleOutput;
    char prompt[7], ch, buffer[60];
    int i;


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
	
	do {
	
	    Read(&buffer[i], 1, input); 

	} while( buffer[i++] != '\n' );

	buffer[--i] = '\0';

	if( i > 0 ) {
		newProc = ExecUnixSys(buffer);
		// Join(newProc);
	}
    }
}

