/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"


void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

/**
 * Syswrite - the internal Write system call 
 * @param 
 *  addr - read from this address
 *  size - read this amount of bytes
 *  fp   - write to this file descriptor
 */
int SysWrite(int addr, int size, int fp)
{
  int ch; 
  int i = -1;

  if (fp == ConsoleOutput)
  {
    for (i = 0; i < size; i++)
    {
      // read 1 byte from memory
      if (kernel->machine->ReadMem(addr, 1, &ch) == FALSE)
      {
        DEBUG(dbgSys, "Machine::ReadMem returned false\n");
        return i;
      }

      // write 1 byte to console
      //printf ("%c", ch); 
      cout << (char) ch;

      // XXX: Instead of simple printf() or cout,
      // let's use already implemented SynchConsoleOutput
      // class that can handle concurrency
      // kernel->synchConsoleOut->PutChar(ch);


      // increment addr
      addr = addr + 1 /* one byte */;
    }
  }
  else {
    cout << "Unsupported file descriptor" << endl;
  }

  return i; /* either -1 or bytes written so far */
}



#endif /* ! __USERPROG_KSYSCALL_H__ */
