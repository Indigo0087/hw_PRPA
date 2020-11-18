#include <stdio.h>
#include <string.h>

int offPos[2] = {0, 0};

char rotate(char *src, int offset){
    if ((*src >= 65 && *src < 90) || (*src >= 97 && *src < 122)) 
        *src += 1;
    else if (*src == 122) *src = *src - 57;
    else if (*src == 90) *src = *src + 7;
    return *src;
}

void shift(const char *src, char *dst, int offset) {
    // printf("|%02i:| ", offset-1);
    for (int i = 0; i < strlen(src)-1; i++){
        dst[i] = rotate((dst+i), offset);
        // printf("%c", dst[i]);
    }
}

int compare(const char *str1, const char *str2){
    int result = 0;
    char dst[strlen(str1)];
    strcpy(dst, str1);

    for (int j = 1; j < 53; j++){
        shift(str1, dst, j+1);
        for (int i = 0; i < strlen(str1); i++){
            if (dst[i] == str2[i]){
                result++;
            }
        }
        result > offPos[0] ? offPos[0] = result, offPos[1] = j : 0;
        // printf(" | ~ | lol | %i correct\n", result);
        result = 0;
    }
    return result;
}

void print(char *fin, int q){
    for (int j = 0; j < offPos[1]; j++)
        for (int i = 0; i < q; i++)
            rotate(fin+i, offPos[1]);
    fprintf(stdout, "%s", fin);
    fprintf(stdout, "\n");
}

int main(void){
    int q;
    scanf("%i\n", &q);
    char src[q], src1[q], dst[q];

    for (int i = 0; i < q; i++) {
        if (scanf("%c", &src[i]) == 1)
            if (!(src[i] >= 65 && src[i] <= 90) && !(src[i] >= 97 && src[i] <= 122)) {
                if (src[i] == '\n' && i < q){
                    fprintf(stderr, "Error: Chybna delka vstupu!");
                    return 101;
                }
                fprintf(stderr, "Error: Chybny vstup!");
                return 100;
            }
    }

    src[q] = '\0';
    scanf("\n");

    for (int i = 0; i < q; i++) {
        if (scanf("%c", &src1[i]) == 1)
            if (!(src1[i] >= 65 && src1[i] <= 90) && !(src1[i] >= 97 && src1[i] <= 122)) {
                if (src1[i] == '\n' && i < q){
                    fprintf(stderr, "Error: Chybna delka vstupu!");
                    return 101;
                }
                fprintf(stderr, "Error: Chybny vstup!");
                return 100;
            }
    }

    strcpy(dst, src);
    compare(src, src1);
    print(dst, q);


    return 0;
}
