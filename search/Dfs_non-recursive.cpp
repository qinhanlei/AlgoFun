
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
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


struct Position {
	int x, y;
	int step;
	Position() {}
	Position(int a, int b):x(a), y(b), step(0) {}
	Position(int a, int b, int c):x(a), y(b), step(c) {}
	bool operator == (const Position &a) const {
		return (x == a.x && y == a.y);
	}
};
Position pos_start, pos_goal;


void DisplayMaze() {
	for (int i = 0; i < maze_row; ++i) {
		for (int j = 0; j < maze_col; ++j) {
			if (closed_set[i][j] && maze_map[i][j] == ' ') {
				printf("%c", CH_CLOSED);
			} else if (extend_set[i][j] && maze_map[i][j] == ' ') {
				printf("%c", CH_EXTEND);
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


void Delay() {
	int M = 1, N = 10000;
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j);
}


int Dfs() {
	stack<Position> open_set;
	memset(closed_set, false, sizeof(closed_set));
	memset(extend_set, false, sizeof(extend_set));

	extend_set[pos_start.x][pos_start.y] = true;
	pos_start.step = 0;
	open_set.push(pos_start);
	while (!open_set.empty()) {
		Position top = open_set.top();
		if (top == pos_goal) return top.step;
		// remove from open set, add to closed set
		open_set.pop();
		closed_set[top.x][top.y] = true;
		//system("cls"); DisplayMaze(); Delay(); //system("pause");
		for (int i = 0; i < DIR_NUM; ++i) {
			int tx = top.x + DIR_X[i];
			int ty = top.y + DIR_Y[i];
			if (extend_set[tx][ty]) continue;
			if (maze_map[tx][ty] == 'o') continue;
			extend_set[tx][ty] = true;
			dir_pre[tx][ty] = i;
			Position tmp(tx, ty, top.step + 1);
			open_set.push(tmp);
		}
	}
	return -1;
}


int main(int argc, char *argv[]) {
	//freopen("map.txt","r",stdin); 
	//freopen("ans.txt","w",stdout);

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
		int result = Dfs();
		clock_t et = clock();
		printf("search cost time: %lfs\n", (double)(et - st)/CLOCKS_PER_SEC);

		if (result == -1) {
			puts("This maze have no solution");
			continue;
		}
		
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
	
	return 0;
}
