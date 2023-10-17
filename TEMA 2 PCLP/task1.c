#include "util.h"
#include <stdio.h>
#include <stdlib.h>

// la toate task-urile citim datele, rezolvam task-ul, si la final eliberam memoria

int main(void) {
    int i;
    read_data();
    // trecem prin toate site-urile si afisam url-ul, numarul de vizite, si titlul
    for (i = 0; i < size; i++) {
        printf("%s %d %s\n", websites[i].url, websites[i].nr_accesari, websites[i].titlu);
    }
    free(websites);
}
