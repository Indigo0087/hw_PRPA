#include <stdio.h>
#include <stdbool.h>

int main(void){
    int a, b = 0, c = 0, tmp;
    bool isBeof = false;

    if (scanf("%i", &a) != 1) { fprintf(stderr, "Error: Chybny vstup!\n"); return 100; }
    if (a < 3 || a > 69) { fprintf(stderr, "Error: Vstup mimo interval!\n"); return 101; }

    if (scanf("%i", &b) != 1) {
        if(scanf("%i", &b) != EOF) { 
            fprintf(stderr, "Error: Chybny vstup!\n"); return 100; 
        } else isBeof = true;
    } else if (b < 3 || b > 69) { fprintf(stderr, "Error: Vstup mimo interval!\n"); return 101; }

    if (isBeof != true){
        if (scanf("%i", &c) != 1) {
            if (scanf("%i", &c) != EOF) { fprintf(stderr, "Error: Chybny vstup!\n"); return 100; }}
        else if (c < 2 || c > 69) { fprintf(stderr, "Error: Vstup mimo interval!\n"); return 101; }
        if (c >= b) { fprintf(stderr, "Error: Neplatna velikost plotu!\n"); return 103; }
    }
    if (a % 2 == 0 && isBeof != true) { fprintf(stderr, "Error: Sirka neni liche cislo!\n"); return 102; }

    tmp = a/2;
    
    if (!isBeof) {
        for (int j = 0; j < a/2; j++)//roof
        {
            for (int i = 0; i < a; i++)
            {
                if (i == tmp + j){ fprintf(stdout, "X"); break; }
                if (i == tmp - j) fprintf(stdout, "X");
                if (i < tmp - j || (i > tmp - j && i < tmp + j)) fprintf(stdout, " ");
            }
            fprintf(stdout, "\n");
        }
    } else b = a;
    for (int i = 0; i < b; i++)//house
    {
        if (i == 0 || i == b-1) {
            for (int k = 0; k < a; k++) fprintf(stdout, "X");
            if (i == b-1) for (int z = 0; z < c; z++) z % 2 == 0 ^ c % 2 == 0 ? fprintf(stdout, "|") : fprintf(stdout, "-");
        }
        else for (int k = 0; k <= a; k++) { //plot
            if (k != a && (a != b || isBeof)){
                k == 0 || k == a-1 ? fprintf(stdout, "X") : fprintf(stdout, " ");
            }
            else if (k != a && a == b) {
                if (k == 0 || k == a-1) fprintf(stdout, "X");
                else {
                    (k + i) % 2 == 0 ? fprintf(stdout, "o") : fprintf(stdout, "*");
                }
            }
            if (k == a){
                if (b - i == c) for (int z = 0; z < c; z++) z % 2 == 0 ^ c % 2 == 0 ? fprintf(stdout, "|") : fprintf(stdout, "-");
                else if (b - i < c) for (int z = 0; z < c; z++) z % 2 == 0 ^ c % 2 == 0 ? fprintf(stdout, "|") : fprintf(stdout, " ");
            }
        }
        
        fprintf(stdout, "\n");
    }

    return 0;
}
