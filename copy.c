#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "error.h"

int main(int argc, char **argv)
{
  check(argc==3,"il faut trois arguments");
  int in=open(argv[1],O_RDONLY);
  check_syscall(in,"%s",argv[1]);
  int out=open(argv[2],O_CREAT|O_WRONLY|O_TRUNC,0640);
  check_syscall(out,"%s",argv[2]);

  char buffer;
  int r,w;
  while((r=read(in,&buffer,1))!=0){
    check_syscall(r,"read");
    w=write(out,&buffer,1);
    check_syscall(r,"write out ");
  }
  return 0;


  return EXIT_SUCCESS;
}
