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
    assert(argc == 3);
    char buffer;

    // construire le chemin au fichier index
    int l = strlen(argv[1]);
    char idx_filename[l + strlen(SUFFIXE) + 1];

    strncpy(idx_filename, argv[1], l);
    strcpy(idx_filename + l, SUFFIXE);

    int fd_idx = open(idx_filename, O_RDONLY);
    check_syscall(fd_idx, "index file");

    int line = atoi(argv[2]);
    int index_position = (line - 1) * sizeof(int); // the index file stores the positions (offsets) of the newline characters as values of type int. Each int represents the byte offset of a newline in the original file.

    lseek(fd_idx, index_position, SEEK_SET);
    int start;

    int r = read(fd_idx, &start, sizeof(int));
    check_syscall(r, "first read");

    int fd = open(argv[1], O_RDONLY);
    check_syscall(fd, "%s", argv[1]);
    // we can basically obtain the size of the ine to be read
    //  by just calculating the size between the two indexes (ie the two offsets)in the idx file

    // Read and display the desired line from the input file
    lseek(fd, start, SEEK_SET);

    printf("%d\n", start);
    printf("%d\n", index_position);

    while (read(fd, &buffer, sizeof(char)) > 0 && (buffer != '\n'))
    {
        // printf("%s", &buffer);
        write(STDOUT_FILENO, &buffer, sizeof(char));
    }
    printf("\n");

    close(fd);
    close(fd_idx);

    return EXIT_SUCCESS;
}
