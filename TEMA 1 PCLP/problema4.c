#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dec_to_bin(int n, char *s) {
    for(int i = 0; i < 8; i++) {
        s[8-i-1] = n % 2 + '0';
        n /= 2;
    }
    s[8] = '\0';
}

int bin_to_dec(char *s) {
    int n = 0;
    for(int i = 0; i < 8; i++)
        n += (s[i] - '0') << (8-i-1); // x << y muta toti bitii din x la stanga cu y pozitii, practic ridica la puteri de 2
    return n;
}

char min(char a, char b) {
    if(a < b)
        return a;
    return b;
}

void mul_mat(char m1[8][8], char m2[8][8], char res[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            res[i][j] = '0';
            for (int k = 0; k < 8; k++) {
                res[i][j] += (m1[i][k] - '0') * (m2[k][j] - '0');
                // pentru adunarea booleana 1 + 1 = 1, asa nu vom obtine nr mai mari de 1
                res[i][j] = min(res[i][j], '1');
            }
        }
    }
}

void transpose_mat(char m[8][8], char res[8][8]) {
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            res[i][j] = m[j][i];
}

int sum_X_0(char m[][8]) {
    int score = 0;
    // i1, j1 sunt colturile din stanga sus ale celor 4 submatrici
    for(int i1 = 0; i1 < 8; i1 += 4) {
        for(int j1 = 0; j1 < 8; j1 += 4) {
			// j1, j2 sunt culturile din dreapta jos
            int i2 = i1 + 3, j2 = j1 + 3;
            // verificam toate liniile
            for(int x = i1; x <= i2; x++) {
                int s = 0;
                for(int y = j1; y <= j2; y++)
                    s += m[x][y] - '0';
                if(s == 4)
                    score++;
            }
            // verificam toate coloanele
            for(int y = j1; y <= j2; y++) {
                int s = 0;
                for(int x = i1; x <= i2; x++)
                    s += m[x][y] - '0';
                if(s == 4)
                    score++;
            }
            // verificam diagonalele
            if(m[i1][i1] + m[i1+1][i1+1] + m[i1+2][i1+2] + m[i2][i2] == '1' * 4)
                score++;
            if(m[i1][j2] + m[i1+1][j2-1] + m[i1+2][j2-2] + m[i2][j1] == '1' * 4)
                score++;
        }
    }
    return score;
}

int main() {
	// at = A * At, aat = A * At, aa = A * A
    char a[8][8], at[8][8], aat[8][8], aa[8][8];
    for(int i = 0; i < 8; i++) {
        int x;
        scanf("%d", &x);
        dec_to_bin(x, a[i]);
    }
    // pentru a genera A * At mai intai avem nevoie de At
    transpose_mat(a, at);
    mul_mat(a, a, aa);
    mul_mat(a, at, aat);
    // calculam scorurile matricilor
    char s1 = sum_X_0(a), s2 = sum_X_0(aat), s3 = sum_X_0(aa);
	// afisam pe cea cu cel mai mare scor
    if(s1 >= s2 && s1 >= s3)
        for(int i = 0; i < 8; i++)
            printf("%d\n", bin_to_dec(a[i]));
    else if(s2 >= 1 && s2 >= s3)
        for(int i = 0; i < 8; i++)
            printf("%d\n", bin_to_dec(aat[i]));
    else
        for(int i = 0; i < 8; i++)
            printf("%d\n", bin_to_dec(aa[i]));
}
