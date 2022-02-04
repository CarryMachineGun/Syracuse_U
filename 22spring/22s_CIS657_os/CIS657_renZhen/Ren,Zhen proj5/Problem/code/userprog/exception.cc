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
FILE *file[5];
Thread *thread[5];
int fileC = 2;
int threadC = 1;
Thread *joining;
int jointed;
int joinState = 0;


void
RunUserProg1(void *filename) {
    AddrSpace *space = new AddrSpace;
    ASSERT(space != (AddrSpace *)NULL);
    if (space->Load((char*)filename)) {  // load the program into the space
        space->Execute();         // run the program
    }
    ASSERTNOTREACHED();
}

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

void
ExceptionHandler(ExceptionType which)
{
  int type = kernel->machine->ReadRegister(2);
  
  DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");
  
  switch (which) {
    case SyscallException:
      switch(type) {
        case SC_Halt:
          DEBUG(dbgSys, "Shutdown, initiated by user program.\n");
          
          SysHalt();
          break;
          
        case SC_Add:
          DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
          
          /* Process SysAdd Systemcall*/
          int result;
          result = SysAdd(/* int op1 */(int)kernel->machine->ReadRegister(4),
                          /* int op2 */(int)kernel->machine->ReadRegister(5));
          
          DEBUG(dbgSys, "Add returning with " << result << "\n");
          /* Prepare Result */
          kernel->machine->WriteRegister(2, (int)result);
          
          
          break;
          
        case SC_Write:
        {
          int buf;
          int k;
          int id;
          k = kernel->machine->ReadRegister(5);
          id = kernel->machine->ReadRegister(6);
          
          //printf("In ExceptionHander, Write System call is made.The first parameter is %d the second parameter is %d the third parameter is %d\n",(int)kernel->machine->ReadRegister(4),(int)kernel->machine->ReadRegister(5),(int)kernel->machine->ReadRegister(6));
          if (id != 1){
            if (*(file+id) == NULL)
            {
              kernel->machine->WriteRegister(2, -1);
              break;
            }
            for (int i = 0; i < k; i++){
              kernel->machine->ReadMem(kernel->machine->ReadRegister(4)+i,1, &buf);
              fputc(buf, *(file+id));
            }
            kernel->machine->WriteRegister(2, k);
          }
          else{
            for (int i = 0; i < k; i++) {
              kernel->machine->ReadMem(kernel->machine->ReadRegister(4)+i,1, &buf);
              printf("%s", &buf);
            }
            kernel->machine->WriteRegister(2, k);
          }
          break;
        }
        case SC_Create:
        {
          char* name = (char*) malloc(sizeof(char)*50);
          int buf;
          char temp[1];
          int i = 0;
          while(true)
          {
            kernel->machine->ReadMem(kernel->machine->ReadRegister(4)+i,1,&buf);
            sprintf(temp, "%s",&buf);
            if (strcmp(temp, "") == 0)
            {
              name[i] = '\0';
              break;
            }
            name[i] = *temp;
            i++;
          }
          FILE *fp = fopen(name, "w");
          if (fp == NULL)
          {
            kernel->machine->WriteRegister(2, -1);
            break;
          }
          else{
            kernel->machine->WriteRegister(2, 1);
            break;
          }
        }  

        case SC_Open:
        {
          char* name = (char*) malloc(sizeof(char)*50);
          int buf;
          char temp[1];
          int i = 0;
          while(true)
          {
            kernel->machine->ReadMem(kernel->machine->ReadRegister(4)+i,1,&buf);
            sprintf(temp, "%s",&buf);
            if (strcmp(temp, "") == 0)
            {
              name[i] = '\0';
              break;
            }
            name[i] = *temp;
            i++;
          }
          FILE *open = fopen(name, "r+");
          if (open == NULL)
          {
            kernel->machine->WriteRegister(2, -1);
            break;
          }
          *(file+fileC) = open;
          kernel->machine->WriteRegister(2, fileC);
          fileC++;
          break;
        }
          

        case SC_Read:
        {
          int buf;
          int k;
          k = kernel->machine->ReadRegister(5);
          int id = kernel->machine->ReadRegister(6);
          for (int i = 0; i < k; i++)
          {
            buf = fgetc(*(file+id));
            kernel->machine->WriteMem(kernel->machine->ReadRegister(4)+i, 1, buf);
          }
          kernel->machine->WriteRegister(2, k);
          
          break;
        }
          

        case SC_Exit:
        {
          int k = kernel->machine->ReadRegister(4);
          if (k == 0)
          {
            printf("Process %s exited normally\n", kernel->currentThread->getName());
          }
          else{
            joinState = -1;
            printf("Process %s exited abnormally\n", kernel->currentThread->getName());
          } 
          if (joining != NULL && kernel->currentThread == *(thread + jointed))
          {
            kernel->interrupt->SetLevel(IntOff);
            kernel->scheduler->ReadyToRun(joining);
            joining = NULL;

            jointed = 0;
          }
          kernel->currentThread->Finish();
          break;
        }
        
        case SC_Join:
        {
          jointed = kernel->machine->ReadRegister(4);
          joining = kernel->currentThread;
          kernel->machine->WriteRegister(2, 0);
          kernel->interrupt->SetLevel(IntOff);
          kernel->currentThread->Sleep(FALSE);
          break;
        }

        case SC_Exec:
        {
          char* name = (char*) malloc(sizeof(char)*50);
          int buf;
          char temp[1];
          int i = 0;
          while(true)
          {
            kernel->machine->ReadMem(kernel->machine->ReadRegister(4)+i,1,&buf);
            sprintf(temp, "%s",&buf);
            if (strcmp(temp, "") == 0)
            {
              name[i] = '\0';
              break;
            }
            name[i] = *temp;
            i++;
          }
          kernel->machine->WriteRegister(2, threadC);
          Thread * t = new Thread(name);
          t->Fork((VoidFunctionPtr)RunUserProg1, name);
          *(thread+threadC) = t;
          
          threadC++;
          
          break;
        }

        case SC_Close:
        {
          int id = kernel->machine->ReadRegister(4);
          if (*(file+id) == NULL){
            kernel->machine->WriteRegister(2, -1);
            break;
          }
          fclose(*(file+id));
          kernel->machine->WriteRegister(2, 1);
          break;
        }
          
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
    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
  }
}
