#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main()
{
    printf("hello "); // printf is buffered, meaning it may not immediately flush its output to the terminal.
    // On the other hand, write is unbuffered and writes directly to the file descriptor
     fflush(stdout);
    write(1, "world", 5);

    return 1;
}
// printf("hello ") : Cette fonction est une fonction de la bibliothèque standard 
//qui écrit dans la sortie standard (stdout). Elle est mise en tampon (buffered), 
//ce qui signifie que le texte n'est pas immédiatement envoyé au terminal, 
//mais stocké dans un tampon en mémoire jusqu'à ce qu'il soit vidé (flushé),
// soit automatiquement (lorsqu'un caractère de nouvelle ligne \n est rencontré),
// soit manuellement via un appel à fflush(stdout).

// write(1, "world", 5) : La fonction write est un appel système direct qui écrit 
//immédiatement les données sur le descripteur de fichier 1 (qui est stdout).
// Elle n'utilise pas de tampon.
