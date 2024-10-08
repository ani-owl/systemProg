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
    int r, w;

    int a;
    char c;

    int index = open("test.idx", O_RDONLY);
    check_syscall(index, "%s", "test.idx");

    int file = open(argv[1], O_RDONLY);
    check_syscall(file, "%s", argv[1]);

    int number_line = atoi(argv[2]);

    lseek(index, ((number_line - 1) * sizeof(int)), SEEK_SET);
    r = read(index, &a, sizeof(int));




    lseek(file, a, SEEK_SET);

    while (r = read(file, &c, sizeof(char) != 0 && c != '\n'))
    {
        write(STDOUT_FILENO, &c, sizeof(char));
    }

    close(file);
    close(index);

    return EXIT_SUCCESS;
}
