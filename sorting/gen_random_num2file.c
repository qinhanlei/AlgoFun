
#include <stdio.h>

#include "common.h"

int main(int argc, char *argv[])
{
    int num = 0;
    FILE *fout = fopen("random_num.txt", "w");
    if (!fout) {
        puts("create file \"random_num.txt\" failed.");
        return 0;
    }
    srand((unsigned)time(NULL));

    printf("Input how many random numbers you want: ");
    scanf("%d", &num);
    while (num--) {
        fprintf(fout, "%d ", bigrand());
    }
    fflush(fout);
    puts("done");
    system("pause");

    return 0;
}
