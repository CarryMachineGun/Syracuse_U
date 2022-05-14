#include <fcntl.h>
#include <unistd.h>


int main(){
    open("foo", O_CREAT | O_RDWR | O_TRUNC);

    return 0;
}
