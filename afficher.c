#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "error.h"

#define SUFFIXE ".idx"

int main(int argc, char *argv[])
{
  assert(argc == 3);

  // construire le chemin au fichier index
  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1];

  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  int fd = open(argv[1], O_RDONLY);
  check_syscall(fd, "%s", argv[1]);

  int fd_idx = open(idx_filename, O_RDONLY);
  check_syscall(fd_idx, "index file");

  int line = atoi(argv[2]);
  int start;
  int end;
  int r;
  int w;
  // int file_size = lseek(fd, 0, SEEK_END);

  if (line > 0)
  {
    int index_position = (line - 1) * sizeof(int); // the index file stores the positions (offsets) of the newline characters as values of type off_t OR INT. Each int represents the byte offset of a newline in the original file.
    // printf("%d",index_position);                      //line-1 cuz we start counting from 0

    lseek(fd_idx, index_position, SEEK_SET);

    r = read(fd_idx, &start, sizeof(int));
    check_syscall(r, "start read");
    r = read(fd_idx, &end, sizeof(int));

    // handling the case where we want to read the last line but the last line doesn't end with a newline character
    //  if (r == 0) {//if number of bytes read is 0 then it means we reached the end of the file where there is no newline character
    //    end = file_size;
    //  }

    check_syscall(r, "end read");
    start += 1; // it keeps printing a newline before the desired line unless i add +1 to start because it counts the newline chaaracter bytes in the size between the end and the start
  }
  else
  { // handling the first line
    if (line == 0)
    {
      start = 0; // start from index 0 of the file
      r = read(fd_idx, &end, sizeof(int));
      check_syscall(r, "first line end read");
    }
  }

  int size = end - start; // we can basically obtain the size of the line to be read(the number of bytes there is between the two indexes in the idx file)
                          //  by just calculating the size between the two indexes (ie the two offsets)in the idx file

  lseek(fd, start, SEEK_SET);
  char buffer[size];
  r = read(fd, buffer, size);
  check_syscall(r, "read");
  // printf("%s",buffer);
  w = write(STDOUT_FILENO, buffer, size);
  check_syscall(w, "write");
  write(STDOUT_FILENO, "\n", 1);

  close(fd);
  close(fd_idx);

  return EXIT_SUCCESS;
}
