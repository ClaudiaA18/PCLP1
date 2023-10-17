#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// acesst fisier contine functii, variabile si structuri de date utile pt toate fisierele

// enum pentru toate culorile
enum color { white, black, red, green, blue, yellow };

// structura cu toate datele unui site
struct website {
    char url[201];
    int nr_accesari;
    int checksum;
    char titlu[201];
    char* continut;
    enum color text;
    enum color background;
};

// sirul de site-uri, care initial va avea lungimea 3
struct website* websites;
int size, capacity = 3;
// functia care primeste ca parametru toate datele despre un nou site, si il adauga in sir
void add_website(char url[201], int nr_accesari, int checksum, char titlu[201], char* continut, enum color text, enum color background, struct website** websites, int size) {
    // daca verificam daca e nevoie sa mai alocam memorie
    if (size >= capacity) {
        capacity += 3;
        // alocam memoria in alt pointer si dupa o punem in websites, pentru a evita pierderi in cauzl in care realloc esueaza
        struct website* temp;
        temp = (struct website*)realloc(*websites, sizeof(struct website) * capacity);
        if (temp != NULL) {
            *websites = temp;
        }
    }
    // copiem toate datele din parametri
    strcpy((*websites)[size].url, url);
    (*websites)[size].nr_accesari = nr_accesari;
    (*websites)[size].checksum = checksum;
    strcpy((*websites)[size].titlu, titlu);
    (*websites)[size].continut = (char*)malloc(strlen(continut) + 1);
    if ((*websites)[size].continut != NULL) {
        strcpy((*websites)[size].continut, continut);
    }
    (*websites)[size].text = text;
    (*websites)[size].background = background;
}
// functie care returneaza o culoare din enum pentru prima litera ex: 'r' -> red
enum color get_color(char c) {
    if (c == 'w')
        return white;
    if (c == 'b')
        return black;
    if (c == 'r')
        return red;
    if (c == 'g')
        return green;
    if (c == 'b')
        return blue;
    if (c == 'y')
        return yellow;
    return white;
}
// functie care citeste toate site-urile din master.txt
void read_data(void) {
    websites = (struct website*)malloc(sizeof(struct website) * capacity);
    char s[31] = { 0 };
    // deschidem master.txt
    FILE* fin = fopen("master.txt", "r");
    while (fscanf(fin, "%s", s) != EOF) {
        FILE* fp = fopen(s, "r");
        char url[201] = { 0 };
        int bytes;
        int nr_accesari;
        int checksum;
        char titlu[201] = { 0 };
        char c;
        char* continut;
        // citim toate datele despre fiecare site
        fscanf(fp, "%s %d %d %d", url, &bytes, &nr_accesari, &checksum);
        continut = (char*)malloc(bytes * 2);
        int k = 0;
        // citim continutul, caracter cu caracter
        while (fscanf(fp, "%c", &c) != EOF) {
            continut[k] = c;
            k++;
        }
        // punem NULL la final
        continut[k] = '\0';
        // vedem unde incepe tagul de titlu si unde se termina, intre acestea se afla titlul efectiv
        char* p1 = strstr(continut, "<title>"), * p2 = strstr(continut, "</title");
        strncpy(titlu, p1 + 7, p2 - continut - 15);
        // cautam atributul de css color
        char* p3 = strstr(continut, "color"), * p4;
        // default, culorile sunt negru si alb
        enum color text = black, background = white;
        if (p3 != NULL) {
            p4 = strstr(p3 + 1, "color");
            // daca are '-' inainte atunci era backgroind-color
            if (p3[-1] == '-') {
                background = get_color(p3[6]);
            }
            else {
                text = get_color(p3[6]);
            }
            // mai verificam o data acelasi lucru, pentru ca poate exista si color, si background-color
            if (p4 != NULL) {
                if (p4[-1] == '-') {
                    background = get_color(p4[6]);
                }
                else {
                    text = get_color(p4[6]);
                }
            }
        }
        //adaugam site-ul la sir
        add_website(url, nr_accesari, checksum, titlu, continut, text, background, &websites, size);
        size++;
        // inchidem fisierul site-ului
        fclose(fp);
        // eliberam memoria pt continut
        free(continut);
    }
    // inchidem fisierul maser.txt
    fclose(fin);
}
// functie de comparare pt task2
int compare1(struct website a, struct website b) {
    if (strcmp(a.titlu, b.titlu) != 0) {
        if(strcmp(a.titlu, b.titlu) < 0)
            return 1;
        else
            return 0;
    }
    return a.nr_accesari > b.nr_accesari;
}
// functie de comparare pt task3
int compare2(struct website a, struct website b) {
    return a.nr_accesari > b.nr_accesari;
}
// sortare prin selectie, ce ce se foloseste de un pointer la o functie de comparare
void sort(struct website* websites, int n, int (*func)(struct website, struct website)) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (func(websites[i], websites[j])) {
                struct website aux = websites[i];
                websites[i] = websites[j];
                websites[j] = aux;
            }
        }
    }
}

