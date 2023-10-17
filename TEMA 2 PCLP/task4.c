#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// avem cele 2 functii care rotesc bitii dintr-un numar, ambele functioneaza la fel

int rotl(char x, int k) {
    // k devine k % 8 pentru ca char are 8 biti, si daca facem de exemplu 16 rotiri la stanga e ca si cum am face 0
    k %= 8;
    int bits[8], i, j;
    // punem bitii intr-un vector
    for (i = 7; i >= 0; i--) {
        bits[i] = x % 2;
        x /= 2;
    }
    // de k ori facem cate o permutare circulara
    for (i = 0; i < k; i++) {
        // salvam primul bit
        int aux = bits[0];
        // pe fiecare pozitie se va pune cel din fata lui
        for (j = 0; j < 7; j++) {
            bits[j] = bits[j + 1];

        }
        // pep ultima pozitie se puna ce era inainte pe prima
        bits[7] = aux;
    }
    // transformam la loc in baza 10
    int y = 0;
    for (i = 0; i < 8; i++) {
        y += bits[i] * (1 << (7 - i));
    }
    return y;
}
// la fel ca rotl dar in directia opusa
int rotr(char x, int k) {
    k %= 8;
    int bits[8], i, j;
    for (i = 7; i >= 0; i--) {
        bits[i] = x % 2;
        x /= 2;
    }
    for (i = 0; i < k; i++) {
        // salvam ultimul bit
        int aux = bits[7];
        // fiecare pozitie o primeste pe cea din spate
        for (j = 7; j > 0; j--) {
            bits[j] = bits[j - 1];

        }
        // pe prima pozitie punem ce era inainte pe ultima
        bits[0] = aux;
    }
    int y = 0;
    for (i = 0; i < 8; i++) {
        y += bits[i] * (1 << (7 - i));
    }
    return y;
}

int main(void) {
    read_data();
    char url[201];
    int i, j;
    // cititm tot de la stdin
    while (scanf("%s", url) != EOF) {
        // cod   = checksum-ul pe care il calculam
        // found = indicele site-ului care se cheama la fel ca ce scrie la stdin
        int cod = 0, found = -1;
        // trecem prin toate site-urile
        for (i = 0; i < size; i++) {
            // daca am gasit site-ul atunci calculam checksum-ul
            if (strcmp(websites[i].url, url) == 0) {
                for (j = 1; websites[i].continut[j] != '\0'; j++) {
                    // pornim de la j=1 pentru ca pe j=0 se afla newline si nu se ia in calcul
                    // conditia e inversata, si k = j-1, din aceeasi cauza ca j incepe de la 1
                    if (j % 2 == 1) {
                        cod ^= rotl(websites[i].continut[j], j-1);
                    }
                    else {
                        cod ^= rotr(websites[i].continut[j], j-1);
                    }
                }
                // tinem minte indicele site-ului si oprim for-ul
                found = i;
                break;
            }
        }
        // found ramane -1 daca nu s-a gasit un site care are url-ul identic cu ce s-a scris la stdin
        if (found == -1) {
            printf("Website not found!\n");
        }
        else {
            if (websites[found].checksum == cod) {
                printf("Website safe!\n");
            }
            else {
                printf("Malicious website! Official key: %d. Found key: %d\n", websites[found].checksum, cod);
            }

        }
    }
    // eliberam memoria
    free(websites);
}
