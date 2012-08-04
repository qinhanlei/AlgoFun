#include <stdio.h>

#include "common.h"

int main(int argc, char *argv[])
{
    FILE *fout = fopen("random_num.txt", "w");
    int num = 0;

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
