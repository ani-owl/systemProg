#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

#include "error.h"

int main(int argc, char*argv[]){
    if (fork()==0){
        execlp(argv[1],argv+1);//ARGV[1]

        perror("");
        exit(1);
    }
    int status;
    wait(&status);
    printf("code de retour:%d",status);
    return 0;


}
