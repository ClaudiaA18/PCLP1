#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    read_data();
    char s[256], c;
    int n = 0, * f, i, j;
    // la fel ca la task2, facem un sir de frecventa, unde f[i] = 1, daca site-ul i respecta criteriile de search
    f = (int*)malloc(sizeof(int) * size);
    for (i = 0; i < size; i++) {
        f[i] = 0;
    }
    // citim tot de la stdin
    while (scanf("%c", &c) != EOF) {
        if (c == '\n') {
            break;
        }
        s[n++] = c;
    }
    s[n] = '\0';
    // facem si un sir de caractere pt cuvantul care nu se vrea, cel care incepe cu -
    char* p = strtok(s, " "), words[100][201], interzis[201];
    int w = 0;
    while (p != NULL) {
        // daca primul caracter e -, atunci il copiem in sirul interzis
        if (p[0] == '-') {
            strcpy(interzis, p + 1);
        }
        // altfel il copiem in sirul obisnuit
        else {
            strcpy(words[w], p);
            w++;
        }
        p = strtok(NULL, " ");
    }
    // trecem prin toate site-urile
    for (i = 0; i < size; i++) {
        char temp[201];
        strcpy(temp, websites[i].continut);
        p = strtok(temp, " \n");
        int cuvant_cautat = 0, cuvant_interzis = 0;
        // despartim continutul site-ului in cuvinte
        while (p != NULL) {
            for (j = 0; j < w; j++) {
                // daca e la fel cu oricare dintre cuvintele cautate, atunci punem cuvant_cautat = 1
                if (strcmp(words[j], p) == 0) {
                    cuvant_cautat = 1;
                }
            }
            // daca e la fel ca si cuvantul interzis, atunci punem cuvant_interzis = 1
            if (strcmp(interzis, p) == 0) {
                cuvant_interzis = 1;
            }
            p = strtok(NULL, " \n");
        }
        // daca s-a gasit macar un cuvant cerut si nu s-a gasit cuvantul cu - atunci f[i] = 1
        if (cuvant_cautat == 1 && cuvant_interzis == 0) {
            f[i] = 1;
        }
    }
    // un nou sir de site-uri
    struct website* tmp_websites = (struct website*)malloc(sizeof(struct website) * capacity);
    int k = 0;
    // adaugam in sir toate site-urile care au respectat criteriile de cautare
    for (i = 0; i < size; i++) {
        if (f[i] == 1) {
            add_website(websites[i].url, websites[i].nr_accesari, websites[i].checksum, websites[i].titlu,
                websites[i].continut, websites[i].text, websites[i].background, &tmp_websites, k);
            k++;
        }
    }
    // sortam sirul dupa functia de sortare compare2
    sort(tmp_websites, k, compare2);
    // afisam
    for (i = 0; i < k; i++) {
        printf("%s\n", tmp_websites[i].url);
    }
    // eliberam memoria
    free(tmp_websites);
    free(websites);
}
