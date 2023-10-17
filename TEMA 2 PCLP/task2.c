#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    read_data();
    char s[256], c;
    int n = 0, * f, i, j;
    // facem un sir de frecventa, unde f[i] = 1, daca site-ul i respecta criteriile de cautare
    f = (int*)malloc(sizeof(int) * size);
    for (i = 0; i < size; i++) {
        f[i] = 0;
    }
    // citim pana la '\n'
    while (scanf("%c", &c) != EOF) {
        if (c == '\n') {
            break;
        }
        s[n++] = c;
    }
    s[n] = '\0';
    char* p = strtok(s, " "), words[100][201];
    int w = 0;
    // facem un vector de cuvinte cu ce s-a scris la stdin
    while (p != NULL) {
        strcpy(words[w], p);
        w++;
        p = strtok(NULL, " ");
    }
    // trecem prin toate site-urile
    for (i = 0; i < size; i++) {
        char temp[201];
        // copiem continutul in alt sir, pentru a nu modifica sirul original
        strcpy(temp, websites[i].continut);
        p = strtok(temp, " \n");
        // trecem prin toate cuvintele din continutul site-ului
        while (p != NULL) {
            // daca vreun cuvant de la stdin se afla in continutul site-ului, atunci f[i] devine 1
            for (j = 0; j < w; j++) {
                if (strcmp(words[j], p) == 0) {
                    f[i] = 1;
                }
            }

            p = strtok(NULL, " \n");
        }
    }
    // facem un nou sir de site-uri
    struct website* tmp_websites = (struct website*)malloc(sizeof(struct website) * capacity);
    int k = 0;
    // pt fiecare site la care am spus ca f[i] = 1, vom adauga acel site in noul sir de site-uri
    for (i = 0; i < size; i++) {
        if (f[i] == 1) {
            add_website(websites[i].url, websites[i].nr_accesari, websites[i].checksum, websites[i].titlu,
                websites[i].continut, websites[i].text, websites[i].background, &tmp_websites, k);
            k++;
        }
    }
    // sortam sirul de site-uri de lungime k, dupa criteriul de sortare dat din functia compare1
    sort(tmp_websites, k, compare1);
    // afisam 
    for (i = 0; i < k; i++) {
        printf("%s\n", tmp_websites[i].url);
    }
    // eliberam memoria
    free(tmp_websites);
    free(websites);
}
