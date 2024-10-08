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
  FILE * in=fopen(argv[1],"r");
  check_syscall(in!=NULL,"%s",argv[1]);
  FILE * out=fopen(argv[2],"w+");
  check_syscall(out!=NULL,"%s",argv[2]);

  char buffer;
  int r,w;
  while((r=fread(&buffer,sizeof buffer,1,in))!=0){
    check_syscall(r==1,"read");
    w=fwrite(&buffer,1,1,out);
    check_syscall(w==1,"write out ");
  }
    fclose(in);
    fclose(out);


  return EXIT_SUCCESS;
}
