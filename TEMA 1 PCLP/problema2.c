#include <stdio.h>
#include <stdlib.h>

int main () {
    int d1[201] = {0}, d2[201] = {0};
    // k = nr perechi de nebuni care se ataca intre ei
    // p = raspunsul cerintei 2
    int m, n, x, y, k = 0, p = 1;
    scanf("%d %d", &m, &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        // incrementam coordonatele, pentru ca indexam de la 1
        ++x; ++y;
        // spunem ca avem un nebun in plus pe primul tip de diagonala
        d1[x + y - 1]++;
        // spunem ca avem un nebun in plus pe al 2-lea tip de diagonala
        d2[x + m - y]++;
    }
    // trecem prin toate diagonalele (exista mereu 2*m-1 diagonale pentru oricare m)
    for(int i = 1; i <= 2 * m - 1; i++) {
		// daca avem doar un nebun pe o diagonala inseamna ca e singur deci nu poate ataca pe altcineva
		// facem combinari de d[i] luate cate 2, pentru ca se ataca intre ei 2 cate 2
		// facem la fel pentru ambele tipuri de diagonale
		
        if(d1[i] > 1)
            k +=  (d1[i] - 1) * d1[i] / 2;
        if(d2[i] > 1)
            k +=  (d2[i] - 1) * d2[i] / 2;
    }
    // daca nu avem doar o singura pereche de nebuni care se ataca intre ei, atunci raspunsul e NU
    if(k != 1)
        p = 0; 
    // daca avem doar o pereche de nebuni care se ataca
    // se poate face o miscare ca sa nu se mai atace doar daca ei nu sunt blocati in colturi
    // verificam la fel pentru ambele tipuri de diagonale
    if(d1[m] == 2 && d2[1] && d2[2 * m - 1])
        p = 0;
    if(d2[m] == 2 && d1[1] && d1[2 * m - 1])
        p = 0;
	// afisam rezultatele
    printf("%d\n", k);
    if(p)
        printf("DA\n");
    else
        printf("NU\n");
}

