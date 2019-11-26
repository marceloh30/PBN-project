#include <stdio.h>
#include <unistd.h>

int main(){
    int pid = getpid();
    int a = 0;
    for(a = 0; a < 20; a++){
        printf("\n[%d]-%d",pid,a);
        sleep(1);
    }
    return a;
}
