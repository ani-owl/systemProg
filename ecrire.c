#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[]){
int i, fd;

 if(argc != 2) {
 fprintf(stderr, "Usage: ecrire <position_depart>\n");
 exit(1);
 }

 fd = open("fich", O_WRONLY | O_CREAT, 0666);

 for(i = atoi(argv[1]); i < 10; i += 2) {
 lseek(fd, i*sizeof(int), SEEK_SET);
 write(fd, &i, sizeof(int));
 sleep(1);
 }

 close(fd);
 return 0;
//ECRIRE à  WRITES IN LES POSITIONS PAIRES  and ecrire 1 , writes in les positions impaires 
//3. deux tetes de lecture
}