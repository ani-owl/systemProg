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
#define BUF_SIZE 2048

int main(int argc, char *argv[])
{
  assert(argc == 2);
  // construire le chemin au fichier index
  int l = strlen(argv[1]); // length of the input file
  char idx_filename[l + strlen(SUFFIXE) + 1];
  strncpy(idx_filename, argv[1], l); // copies the input file name into the idx_filename array.
                                     // copy the first l characters from argv[1] (the input file name) to idx_filename
  strcpy(idx_filename + l, SUFFIXE); // This line appends the suffix ".idx" to the idx_filename array.

  int fd = open(argv[1], O_RDONLY);
  check_syscall(fd, "%s", argv[1]);

  int fd_idx = open(idx_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  check_syscall(fd_idx, "index file");

  char buffer[BUF_SIZE];
  int index_position = 0;
  int nb_bytes_read;
  int nb_bytes_written;
  // each time we go through the loop we increment the position of the index when \n is found we write that position into the file
  while ((nb_bytes_read = read(fd, buffer, BUF_SIZE)) > 0)
  {
    for (int i = 0; i < nb_bytes_read; i++)
    {
      if (buffer[i] == '\n')
      {
        printf("Newline found at position: %d\n", index_position);
        nb_bytes_written = write(fd_idx, &index_position, sizeof(int));
        check_syscall(nb_bytes_written, "write");
      }
      index_position += 1;
    }
  }
  check_syscall(nb_bytes_read, "read");
  close(fd);
  close(fd_idx);

  return 0;
}
