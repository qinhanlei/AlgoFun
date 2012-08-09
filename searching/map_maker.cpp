
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int Max = 501;

// element of maze
const char MAZE_ELE[] = "  o  o  o ";
char maze_map[Max][Max] = {0};

int main()
{
    srand(time(NULL));
    FILE *fout = fopen("random_map.txt", "w");
    if (fout == NULL) {
        printf("error!\n");
        return 0;
    }

    while (true) {
        printf("Input size of maze (columns, rows): ");
        int N, M;
        scanf("%d %d", &N, &M);
        if (N < 3 || M < 3 || M > 500 || N > 500) break;
        fprintf(fout, "%d,%d\n", N, M);

        memset(maze_map, 0, sizeof(maze_map));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == 0 || j == 0 || i == M - 1 || j == N - 1) {
					// set boundary
                    maze_map[i][j] = 'o';
                } else {
                    int k = rand() % 10;
                    maze_map[i][j] = MAZE_ELE[k];
                }
            }
        }
        maze_map[1][1] = 's';
        maze_map[M-2][N-2] = 'e';

        for (int i = 0; i < M; ++i) {
            fprintf(fout, "%s\n", maze_map[i]);
            printf("%s\n", maze_map[i]);
        }
        puts("\nMaze has made \n");

        fflush(fout);
    }
    fclose(fout);

    return 0;
}

