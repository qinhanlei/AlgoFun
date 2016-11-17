
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"


int main(int argc, char *argv[]) {
    int num = 0;
    FILE *fout = NULL;
    srand((unsigned)time(NULL));

    while (1) {
        printf("How many random numbers you want generate to \"random_num.txt\": ");
        scanf("%d", &num);
        fout = fopen("random_num.txt", "w");
        if (!fout) {
            puts("create file \"random_num.txt\" failed.");
            return 0;
        }
        while (num--)
            fprintf(fout, "%d ", bigrand());
        fflush(fout);
        fclose(fout);
        puts("done");
        system("pause");
    }

    return 0;
}
