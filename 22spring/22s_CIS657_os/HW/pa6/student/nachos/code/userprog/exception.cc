// exception.cc
//  Entry point into the Nachos kernel from user programs.
//  There are two kinds of things that can cause control to
//  transfer back to here from user code:
//
//  syscall -- The user code explicitly requests to call a procedure
//  in the Nachos kernel.  Right now, the only function we support is
//  "Halt".
//
//  exceptions -- The user code does something that the CPU can't handle.
//  For instance, accessing memory that doesn't exist, arithmetic errors,
//  etc.
//
//  Interrupts (which can also cause control to transfer from user
//  code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//----------------------------------------------------------------------
// ExceptionHandler
//  Entry point into the Nachos kernel.  Called when a user program
//  is executing, and either does a syscall, or generates an addressing
//  or arithmetic exception.
//
//  For system calls, the following is the calling convention:
//
//  system call code -- r2
//    arg1 -- r4
//    arg2 -- r5
//    arg3 -- r6
//    arg4 -- r7
//
//  The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//  "which" is the kind of exception.  The list of possible exceptions
//  is in machine.h.
//----------------------------------------------------------------------

void ExceptionHandler(ExceptionType which)
{
  int type = kernel->machine->ReadRegister(2);
  int result;
  int temp;

  DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

  switch (which)
  {
  case SyscallException:
    switch (type)
    {
    case SC_Halt:
      DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

      SysHalt();
      break;

    case SC_Add:
      DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

      /* Process SysAdd Systemcall*/
      result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
                      /* int op2 */ (int)kernel->machine->ReadRegister(5));

      DEBUG(dbgSys, "Add returning with " << result << "\n");
      /* Prepare Result */
      kernel->machine->WriteRegister(2, (int)result);

      break;

    case SC_Exit:
      // printf("Exit system call made by %s\n", kernel->currentThread->getName());

      DEBUG(dbgSys, "Exit " << kernel->machine->ReadRegister(4) << "\n");

      // Extract exit status
      temp = kernel->machine->ReadRegister(4);
      if (temp == 0)
        printf("Process exited normally\n");
      else
        cout << "Process exited abnormally with status " << temp << endl;

      // Let's finish this thread
      kernel->currentThread->Finish();
      break;

      /*======================================
       * TODO: Finish the implementations
       * for the following system calls
       * ====================================
       */
    case SC_Read:
      // printf("Read system call made by %s\n", kernel->currentThread->getName());
      {
        DEBUG(dbgSys, "Read " << kernel->machine->ReadRegister(4) << "; " << kernel->machine->ReadRegister(5) << "; " << kernel->machine->ReadRegister(6) << "\n");

        // char content[2048];
        int c;
        int size, id, buffer;
        char content[2048];

        buffer = (int)kernel->machine->ReadRegister(4);
        size = (int)kernel->machine->ReadRegister(5);
        id = (int)kernel->machine->ReadRegister(6);

        kernel->machine->WriteRegister(2, read(id, content, size));

        for (int i = 0; i < size; i++)
        {
          kernel->machine->WriteMem(buffer + i, 1, content[i]);
        }
      }

      break;

    case SC_Write:
    {
      // printf("Write system call made by %s\n", kernel->currentThread->getName());
      DEBUG(dbgSys, "Write " << kernel->machine->ReadRegister(4) << "; " << kernel->machine->ReadRegister(5) << "; " << kernel->machine->ReadRegister(6) << "\n");

      char content[2048];
      int c;
      int buffer, size, id;

      buffer = (int)kernel->machine->ReadRegister(4);
      size = (int)kernel->machine->ReadRegister(5);
      id = (int)kernel->machine->ReadRegister(6);

      for (int i = 0; i < size; i++)
      {
        kernel->machine->ReadMem(buffer + i, 1, &c);
        content[i] = (char)c;
      }

      kernel->machine->WriteRegister(2, write(id, content, size));
    }
    break;

    case SC_Create:
      // printf("Create() system call is called \n");
      {
        DEBUG(dbgSys, "Create " << kernel->machine->ReadRegister(4) << "\n");

        // Retrieve parameters
        int buffer, c;
        c = 'a';
        char name[1024];
        buffer = (int)kernel->machine->ReadRegister(4);

        // the file name
        for (int i = 0; ((char)c) != '\0'; i++)
        {
          kernel->machine->ReadMem(buffer + i, 1, &c);

          name[i] = (char)c;
        }

        // create the file
        int is_success = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);

        // returns 1 on success, and -1 on failure, to the user program
        kernel->machine->WriteRegister(2, is_success == -1 ? -1 : 1);
      }

      break;

    case SC_Open:
      // printf("Open() system call is called\n");
      {
        DEBUG(dbgSys, "Create " << kernel->machine->ReadRegister(4) << "\n");

        // Retrieve parameters
        int buffer, c;
        c = 'a';
        char name[1024];
        buffer = (int)kernel->machine->ReadRegister(4);

        // the file name
        for (int i = 0; ((char)c) != '\0'; i++)
        {
          kernel->machine->ReadMem(buffer + i, 1, &c);

          name[i] = (char)c;
        }

        // create the file
        // int file_description = open(("./%s", name), O_WRONLY);
        int file_description = open(name, O_RDWR, 0666);

        // returns 1 on success, and -1 on failure, to the user program
        kernel->machine->WriteRegister(2, file_description);
      }

      break;

    case SC_Close:
      // printf("Close() system call is called\n");
      {

        DEBUG(dbgSys, "Close " << kernel->machine->ReadRegister(4) << "\n");

        // Retrieve parameters
        int id;
        id = (int)kernel->machine->ReadRegister(4);

        kernel->machine->WriteRegister(2, close(id) == 0 ? 1 : -1);
      }
      break;

      // NOT REQUIRED FOR THIS PA
    case SC_Exec:
      printf("Exec() system call is called\n");
      break;

    case SC_Join:
      printf("Join() system call is called\n");
      break;

    default:
      cerr << "Unexpected system call " << type << "\n";
      break;
    }
    break;
  default:
    cerr << "Unexpected user mode exception" << (int)which << "\n";
    break;
  }

  /* Modify return point */
  {
    /* set previous programm counter (debugging only)*/
    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

    /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

    /* set next programm counter for brach execution */
    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
  }
}
