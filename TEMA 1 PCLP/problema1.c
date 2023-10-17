#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// verificam daca 2 cuvinte sunt anagrame folosind vectori de frecventa
// daca cei 2 vectori de frecventa sunt identici inseamna ca avem aceleasi caractere, deci anagrame
int is_anagram(char *s1, char *s2) {
    int f1[26] = {0}, f2[26] = {0}, ok = 1;
    if(strlen(s1) != strlen(s2))
        return 0;
    for(int i = 0; s1[i]; i++)
        f1[s1[i]-'a']++;
    for(int i = 0; s2[i]; i++)
        f2[s2[i]-'a']++;

    for(int i = 0; i < 26; i++) {
        if(f1[i] != f2[i]) {
            ok = 0;
            break;
        }
    }
    return ok;
}
// numaram cate caractere din s1 sunt situate diferit fata de s2, impartim la lungime
double compute_grade(char *s1, char *s2) {
    double k = 0;
    for(int i = 0; s1[i]; i++)
        if(s1[i] != s2[i])
            k++;
    return k / strlen(s1);

}

int main () {
    char x[1001][51], y[1001][51];
    double v[1001];
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%s %s", x[i], y[i]); 
        if(!is_anagram(x[i], y[i]))
            v[i] = -1; // daca nu sunt anagrame au scorul -1
        else
            v[i] = compute_grade(x[i], y[i]); // altfel calculam scorul [0, 1]
    }
    // selection sort bazat pe gradul anagramelor
    // daca gradele sunt egale atunci comparam lexicografic primele cuvinte
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(v[i] < v[j] || (v[i] == v[j] && strcmp(x[i], x[j]) < 0)) {
                char aux1[51], aux2[51];
                double aux3;
                strcpy(aux1, x[i]);
                strcpy(x[i], x[j]);
                strcpy(x[j], aux1);

                strcpy(aux2, y[i]);
                strcpy(y[i], y[j]);
                strcpy(y[j], aux2);

                aux3 = v[i];
                v[i] = v[j];
                v[j] = aux3;
            }
        }
    }
    // afisam cuvintele in ordinea gradelor
    for(int i = 0; i < n; i++)
        printf("%s %s\n", x[i], y[i]);
}

