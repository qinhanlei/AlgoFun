
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

//#include <queue>
#include <algorithm>
using namespace std;

const int Max = 501;

const char CH_EXTEND = ',';
const char CH_CLOSED = '.';
const char CH_PATH = '*';

int maze_col;
int maze_row;
char maze_map[Max][Max];

bool closed_set[Max][Max];
bool extend_set[Max][Max];
// preceding direction
int dir_pre[Max][Max];

const int DIR_NUM = 8;
const int DIR_X[] = {-1, 1,  0, 0, -1, -1, 1, 1};
const int DIR_Y[] = { 0, 0, -1, 1,  1, -1, 1,-1};
// negative direction index
//const int NEG_DIR[] = {1, 0, 3, 2, 7, 6, 5, 4};

struct Position {
	int x, y;
	int step; // g
	double h1, h2, h3; // h1 is important
	Position() {}
	Position(int a, int b):x(a), y(b), step(0), h1(0), h2(0),h3(0) {}
	Position(int a, int b, int c):x(a), y(b), step(c), h1(0), h2(0),h3(0) {}
	bool operator == (const Position &a) const {
		return (x == a.x && y == a.y);
	}
	void Heuristic(const Position& p) {
		h1 = max(abs(p.x - x), abs(p.y - y)); // Chebyshev
		h2 = sqrt((p.x - x)*(p.x - x)*1.0 + (p.y - y)*(p.y - y)); // Euclid
		h3 = abs(p.x - x) + abs(p.y - y); // Manhattan
	}
};
Position pos_start, pos_goal;

void DisplayMaze()
{
	for (int i = 0; i < maze_row; ++i) {
		for (int j = 0; j < maze_col; ++j) {
			if (closed_set[i][j] && maze_map[i][j] == ' ') {
				printf("%c", CH_CLOSED);
//			} else if (extend_set[i][j] && maze_map[i][j] == ' ') {
//				printf("%c", CH_EXTEND);
			} else {
				printf("%c", maze_map[i][j]);
			}
		}
		if (i == 0) {
			printf("\t closed node sign: %c ", CH_CLOSED);
		} else if (i == 1) {
			printf("\t extend node sign: %c ", CH_EXTEND);
		} else if (i == 2) {
			printf("\t   path node sign: %c ", CH_PATH);
		}
		puts("");
	}
	puts("");
}

void Delay()
{
	int M = 1, N = 10000;
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j);
}

int search(Position top, int depth)
{
    if (top == pos_goal) return top.step;
    closed_set[top.x][top.y] = true;
    //system("cls"); DisplayMaze(); Delay(); //system("pause");
    for (int i = 0; i < DIR_NUM; ++i) {
        int tx = top.x + DIR_X[i];
        int ty = top.y + DIR_Y[i];
        if (maze_map[tx][ty] == 'o') continue;
        if (closed_set[tx][ty]) continue;
        Position tmp(tx, ty, top.step + 1);
        tmp.Heuristic(pos_goal);
        if (tmp.h1 + tmp.step > depth) continue;
        dir_pre[tx][ty] = i;
        int ret = search(tmp, depth);
        if (ret >= 0) return ret;
        //closed_set[tx][ty] = false;
    }
    return -1;
}

int IDAstar()
{
    pos_start.Heuristic(pos_goal);
    for (int depth = pos_start.h1; depth < maze_col * maze_row; ++depth) {
        printf("depth:%d \n", depth);
        memset(closed_set, false, sizeof(closed_set));
        int ret = search(pos_start, depth);
        if (ret >= 0) return ret;
    }
    return -1;
}

int main ()
{
	//freopen("map.txt","r",stdin); freopen("ans.txt","w",stdout);

	while (scanf("%d,%d", &maze_col, &maze_row) != EOF) {
		memset(maze_map, 0, sizeof(maze_map));
		// read in maze map
		for (int i = 0; i < maze_row; ++i) {
			getchar();
			for (int j = 0; j < maze_col; ++j) {
				scanf("%c", &maze_map[i][j]);
				if (maze_map[i][j] == 's') {
					pos_start.x = i;
					pos_start.y = j;
				} else if (maze_map[i][j] == 'e') {
					pos_goal.x = i;
					pos_goal.y = j;
				}
			}
		}

		clock_t st = clock();
		// search
		int result = IDAstar();
		clock_t et = clock();
		printf("search cost time: %lfs\n", (double)(et - st)/CLOCKS_PER_SEC);

		if (result == -1) {
			puts("This maze is no solution");
			continue;
		} else {
			printf("The path need %d steps \n", result);
			Position tmp = pos_goal;
			// get path
			while (true) {
				int i = dir_pre[tmp.x][tmp.y];
				tmp.x -= DIR_X[i];
				tmp.y -= DIR_Y[i];
				if (tmp == pos_start) break;
				maze_map[tmp.x][tmp.y] = CH_PATH;
			}
			DisplayMaze();
		}
	}
	return 0;
}
