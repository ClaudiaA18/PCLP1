#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// rotire de matrice in sens ceasornic
void clockwise_rotation(int k, char r[7][3][3][33]) {
    char t[3][3][33];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            strcpy(t[i][j], r[k][3-j-1][i]);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            strcpy(r[k][i][j], t[i][j]);

}
// rotire de matrice in sens trigonometric
void anti_clockwise_rotation(int k, char r[7][3][3][33]) {
    char t[3][3][33];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            strcpy(t[i][j], r[k][j][3-i-1]);

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            strcpy(r[k][i][j], t[i][j]);
}
// dest = fata care se va modifica
// src  = fata de la care vom copia
// x, y = una dintre valoril FIRST_ROW, FIRST_COLUMN, LAST_ROW, LAST_COLUMN
// pe fata dest, linia/coloana x vom pune ce este pe fata src, linia/coloana y
// order este 1 sau -1, reprezinta modul in care elementele de pe o fata a cubului se aseaza pe cealalta
// daca este 1, atunci indicii de linie/coloana din {0, 1, 2} devin {0, 1, 2}, altfel din {0, 1, 2} devind {2, 1, 0}
void change(int dest, char *x, int src, char *y, int order, char r[7][3][3][33]) {
    int i1 = x[0] - 48, j1 = x[1] - 48;
    int i2 = y[0] - 48, j2 = y[1] - 48;
    // x, y sunt siruri de caractrede de lungime 2, de formatul {'0'/'2', '3'} sau {'3', '0'/'2'}
    // primul element reprezinta linia si al 2-lea coloana
    // daca un element este '0' sau '2' atunci stim ca chiar ne referim la acel numar de linie/coloana
    // dar daca este '3' clar nu este vorba de o linia/coloana pentru ca nu apartine din intervalul [0, 2]
    // daca este '3' inseamna ca in loc de '3', vom face un for de la 0 la 2 si vom pune in schimb acea valoare
    
    int oi1 = 0, oj1 = 0, oi2 = 0, oj2 = 0;
    for(int i = 0; i < 3; i++) {
        if(i1 > 2 || oi1)
            i1 = i, oi1 = 1;
        if(j1 > 2 || oj1)
            j1 = i, oj1 = 1;
        if(i2 > 2 || oi2)
            i2 = i, oi2 = 1;
        if(j2 > 2 || oj2)
            j2 = i, oj2 = 1;

        if(order == -1 && oi2)
            i2 = 3 - i - 1;
        if(order == -1 && oj2)
            j2 = 3 - i - 1;
        strcpy(r[dest][i1][j1], r[src][i2][j2]);
    }
}


int main () {
    int n, FRONT = 0, BACK = 1, UP = 2, DOWN = 3, LEFT = 4, RIGHT = 5, AUX = 6;
    char FIRST_ROW[] = "03", LAST_ROW[] = "23", FIRST_COLUMN[] = "30", LAST_COLUMN[] = "32";
    char c[6][11], r[7][3][3][33], s[33], *p;
    for(int i = 0; i < 6; i++)
        scanf("%s", c[i]);
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 3; j++) {

            scanf("%s", s); // folosim strtok ca sa ignoram punctele
            p = strtok(s, ".");
            for(int k = 0; k < 3; k++) {
                strcpy(r[i][j][k], p);
                p = strtok(NULL, ".");
            }
        }
    }

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%s", s); 
        // pentru fiecare miscare rotim fata principala
        // dupa apelam change de 5 ori pentru a schimba culorile de pe fetele adiacente (4 + 1 ca salvam partea de sus in AUX)
        if(!strcmp(s, "F")) {
            clockwise_rotation(FRONT, r);
            change(AUX, FIRST_ROW, UP, LAST_ROW, 1, r);
            change(UP, LAST_ROW, LEFT, LAST_COLUMN, -1, r);
            change(LEFT, LAST_COLUMN, DOWN, FIRST_ROW, 1, r);
            change(DOWN, FIRST_ROW, RIGHT, FIRST_COLUMN, -1, r);
            change(RIGHT, FIRST_COLUMN, AUX, FIRST_ROW, 1, r);

        }
        if(!strcmp(s, "F'")) {
            anti_clockwise_rotation(FRONT, r);
            change(AUX, FIRST_ROW, UP, LAST_ROW, 1, r);
            change(UP, LAST_ROW, RIGHT, FIRST_COLUMN, 1, r);
            change(RIGHT, FIRST_COLUMN, DOWN, FIRST_ROW, -1, r);
            change(DOWN, FIRST_ROW, LEFT, LAST_COLUMN, 1, r);
            change(LEFT, LAST_COLUMN, AUX, FIRST_ROW, -1, r);
        }
        if(!strcmp(s, "B")) {
            clockwise_rotation(BACK, r);
            change(AUX, FIRST_ROW, UP, FIRST_ROW, 1, r);
            change(UP, FIRST_ROW, RIGHT, LAST_COLUMN, 1, r);
            change(RIGHT, LAST_COLUMN, DOWN, LAST_ROW, -1, r);
            change(DOWN, LAST_ROW, LEFT, FIRST_COLUMN, 1, r);
            change(LEFT, FIRST_COLUMN, AUX, FIRST_ROW, -1, r);
        }
        if(!strcmp(s, "B'")) {
            anti_clockwise_rotation(BACK, r);
            change(AUX, FIRST_ROW, UP, FIRST_ROW, 1, r);
            change(UP, FIRST_ROW, LEFT, FIRST_COLUMN, -1, r);
            change(LEFT, FIRST_COLUMN, DOWN, LAST_ROW, 1, r);
            change(DOWN, LAST_ROW, RIGHT, LAST_COLUMN, -1, r);
            change(RIGHT, LAST_COLUMN, AUX, FIRST_ROW, 1, r);
        }
        if(!strcmp(s, "U")) {
            clockwise_rotation(UP, r);
            change(AUX, FIRST_ROW, BACK, FIRST_ROW, 1, r);
            change(BACK, FIRST_ROW, LEFT, FIRST_ROW, 1, r);
            change(LEFT, FIRST_ROW, FRONT, FIRST_ROW, 1, r);
            change(FRONT, FIRST_ROW, RIGHT, FIRST_ROW, 1, r);
            change(RIGHT, FIRST_ROW, AUX, FIRST_ROW, 1, r);
        }
        if(!strcmp(s, "U'")) {
            anti_clockwise_rotation(UP, r);
            change(AUX, FIRST_ROW, BACK, FIRST_ROW, -1, r);
            change(BACK, FIRST_ROW, RIGHT, FIRST_ROW, 1, r);
            change(RIGHT, FIRST_ROW, FRONT, FIRST_ROW, 1, r);
            change(FRONT, FIRST_ROW, LEFT, FIRST_ROW, 1, r);
            change(LEFT, FIRST_ROW, AUX, FIRST_ROW, -1, r);
        }
        if(!strcmp(s, "D")) {
            clockwise_rotation(DOWN, r);
            change(AUX, FIRST_ROW, FRONT, LAST_ROW, 1, r);
            change(FRONT, LAST_ROW, LEFT, LAST_ROW, 1, r);
            change(LEFT, LAST_ROW, BACK, LAST_ROW, 1, r);
            change(BACK, LAST_ROW, RIGHT, LAST_ROW, 1, r);
            change(RIGHT, LAST_ROW, AUX, FIRST_ROW, 1, r);
        }
        if(!strcmp(s, "D'")) {
            anti_clockwise_rotation(DOWN, r);
            change(AUX, FIRST_ROW, FRONT, LAST_ROW, 1, r);
            change(FRONT, LAST_ROW, RIGHT, LAST_ROW, 1, r);
            change(RIGHT, LAST_ROW, BACK, LAST_ROW, 1, r);
            change(BACK, LAST_ROW, LEFT, LAST_ROW, 1, r);
            change(LEFT, LAST_ROW, AUX, FIRST_ROW, 1, r);
        }
        if(!strcmp(s, "L")) {
            clockwise_rotation(LEFT, r);
            change(AUX, FIRST_ROW, UP, FIRST_COLUMN, 1, r);
            change(UP, FIRST_COLUMN, BACK, LAST_COLUMN, -1, r);
            change(BACK, LAST_COLUMN, DOWN, FIRST_COLUMN, -1, r);
            change(DOWN, FIRST_COLUMN, FRONT, FIRST_COLUMN, 1, r);
            change(FRONT, FIRST_COLUMN, AUX, FIRST_ROW, 1, r);
        }
        if(!strcmp(s, "L'")) {
            anti_clockwise_rotation(LEFT, r);
            change(AUX, FIRST_ROW, UP, FIRST_COLUMN, 1, r);
            change(UP, FIRST_COLUMN, FRONT, FIRST_COLUMN, 1, r);
            change(FRONT, FIRST_COLUMN, DOWN, FIRST_COLUMN, 1, r);
            change(DOWN, FIRST_COLUMN, BACK, LAST_COLUMN, -1, r);
            change(BACK, LAST_COLUMN, AUX, FIRST_ROW, -1, r);
        }
        if(!strcmp(s, "R")) {
            clockwise_rotation(RIGHT, r);
            change(AUX, FIRST_ROW, UP, LAST_COLUMN, 1, r);
            change(UP, LAST_COLUMN, FRONT, LAST_COLUMN, 1, r);
            change(FRONT, LAST_COLUMN, DOWN, LAST_COLUMN, 1, r);
            change(DOWN, LAST_COLUMN, BACK, FIRST_COLUMN, -1, r);
            change(BACK, FIRST_COLUMN, AUX, FIRST_ROW, 1, r);
        }
        if(!strcmp(s, "R'")) {
            anti_clockwise_rotation(RIGHT, r);
            change(AUX, FIRST_ROW, UP, LAST_COLUMN, 1, r);
            change(UP, LAST_COLUMN, BACK, FIRST_COLUMN, -1, r);
            change(BACK, FIRST_COLUMN, DOWN, LAST_COLUMN, -1, r);
            change(DOWN, LAST_COLUMN, FRONT, LAST_COLUMN, 1, r);
            change(FRONT, LAST_COLUMN, AUX, FIRST_ROW, 1, r);
        }
    }
    // afisam cubul rubik
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                printf("%s", r[i][j][k]);
                if(k < 2)
                    printf(".");
            }
            printf("\n");
        }
    }
}

