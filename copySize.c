#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "error.h"

int main(int argc, char **argv)
{
  check(argc==4,"il faut trois arguments");
  int in=open(argv[1],O_RDONLY);
  check_syscall(in,"%s",argv[1]);
  int out=open(argv[2],O_CREAT|O_WRONLY|O_TRUNC|O_SYNC,0640);
  check_syscall(out,"%s",argv[2]);
  int buffer=atoi(argv[3]);
  char c[buffer];
  int r,w;
  while((r=read(in,c,buffer))>0){
    check_syscall(r,"read");
    w=write(out,c,r);
    check_syscall(r,"write out ");
  }
  return 0;


  return EXIT_SUCCESS;
}
