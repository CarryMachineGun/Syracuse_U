/** 
 * The solution of the faulty program for Lab-c. 
 *
 * Author: Endadul Hoque
 */
#include <stdio.h>

// PRINT_ERROR macro prints the underlying error messaage
// by using the `perror` library function.
// This is a simple macro. But C macros can be used 
// to write complex constructs.
#define PRINT_ERROR(x) perror(x)

int main(int argc, char **argv) {
  for(int i = 0; i < 10; i++)
     printf("%d: Hello world!\n", i);

  // Open a file 
  const char *filename = "README.md";
  FILE *fp = fopen(filename, "r");
  if (!fp){
    PRINT_ERROR("Failed to open the file");
  }

  // so the file is open now
  int retval = fseek(fp, 0, SEEK_END);
  if(retval == -1){
    PRINT_ERROR("fseek");
  }
  else {
    int size = ftell(fp);
    printf("size of \'%s\":  %d\n", filename, size);
  }
    
  return 0;
}
