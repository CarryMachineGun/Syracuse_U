#include "syscall.h"

int 
itoa(SpaceId id, char* str)
{
  int nid = (int)id;
  int tmp = nid;
  int div = 1;
  int len = 0;
  while (tmp > 0) {
    tmp /= 10;
    div *= 10;
  }
  while (div > 1) {
    str[len++] = (char)((nid % div) / (div / 10)) + '0';
    div /= 10;
  }
  str[len] = '\0';
  return len;
}

int
strcpy(char* dst, char* src)
{
  int len = 0;
  while (*src != '\0') {
    *dst++ = *src++;
    ++len;
  }
  *dst = '\0';
  return len;
}

int
main()
{
  OpenFileId output = ConsoleOutput;

  SpaceId id = Exec("../test/prog4");

  if (Join(id) == 0) {
    char str[100];
    char* prefix = "Hello from prog3b. Child process id: ";
    int len = strcpy(str, prefix);
  
    int nid = (int)id;
    len += itoa(nid, str + len);
    str[len++] = '\n';
    
    Write(str, len, output);
  } else {
    char* str = "Failed to Join\n";
    Write(str, 15, output);
  }

  Exit(0);
}
