
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
#include <queue>
#include <algorithm>
using namespace std;


const int Max = 501;
const char CH_EXTEND = '?';
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
	int step; // g
	double h1, h2, h3; // h1 is important
	Position() {}
	Position(int a, int b):x(a), y(b), step(0), h1(0), h2(0),h3(0) {}
	Position(int a, int b, int c):x(a), y(b), step(c), h1(0), h2(0),h3(0) {}
	bool operator == (const Position &a) const {
		return (x == a.x && y == a.y);
	}
	void heuristic(const Position& p) {
		// Chebyshev
		h1 = max(abs(p.x - x), abs(p.y - y));
		// Euclid
		h2 = sqrt((p.x - x)*(p.x - x)*1.0 + (p.y - y)*(p.y - y));
		// Manhattan
		h3 = abs(p.x - x) + abs(p.y - y);
	}
	bool operator < (const Position &a) const {
		// evaluation function
		double f = step + h1;
		double fa = a.step + a.h1;
		if (f != fa)
			return f > fa;
		// extra guarantee
		if (h2 != a.h2)
			return h2 > a.h2;
		return h3 > a.h3;
	}
};
Position pos_start;
Position pos_goal;


void print_maze() {
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
		puts("");
	}
	printf("\t closed node: '%c' \n", CH_CLOSED);
	printf("\t extend node: '%c' \n", CH_EXTEND);
	printf("\t   path node: '%c' \n", CH_PATH);
	puts("");
}


void delay() {
	int M = 1, N = 10000;
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j);
}


void prepare() {
    memset(closed_set, false, sizeof(closed_set));
	memset(extend_set, false, sizeof(extend_set));
    for (int i = 0; i < maze_row; ++i) {
		for (int j = 0; j < maze_col; ++j) {
            if (maze_map[i][j] == CH_PATH) {
                maze_map[i][j] = ' ';
            }
        }
    }
}


int DFS(Position top) {
    if (top == pos_goal) return top.step;
    closed_set[top.x][top.y] = true;
    print_maze();
    for (int i = 0; i < DIR_NUM; ++i) {
        int tx = top.x + DIR_X[i];
        int ty = top.y + DIR_Y[i];
        if (maze_map[tx][ty] == 'o') continue;
        if (closed_set[tx][ty]) continue;
        dir_pre[tx][ty] = i;
        int ret = DFS(Position(tx, ty, top.step + 1));
        if (ret >= 0) return ret;
        // backtracking
        //closed_set[tx][ty] = false;
    }
    return -1;
}


int DFS_stack() {
	stack<Position> open_set;
	extend_set[pos_start.x][pos_start.y] = true;
	pos_start.step = 0;
	open_set.push(pos_start);
	while (!open_set.empty()) {
		Position top = open_set.top();
		if (top == pos_goal) return top.step;
		open_set.pop();
		closed_set[top.x][top.y] = true;
		print_maze();
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


int BFS() {
	queue<Position> open_set;
	extend_set[pos_start.x][pos_start.y] = true;
	pos_start.step = 0;
	open_set.push(pos_start);
	while (!open_set.empty()) {
		Position top = open_set.front();
		if (top == pos_goal) return top.step;
		open_set.pop();
		closed_set[top.x][top.y] = true;
		print_maze();
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


int Astar() {
	priority_queue<Position> open_set;
	extend_set[pos_start.x][pos_start.y] = true;
	pos_start.step = 0;
	pos_start.heuristic(pos_goal);
	open_set.push(pos_start);
	while (!open_set.empty()) {
		Position top = open_set.top();
		if (top == pos_goal) return top.step;
		open_set.pop();
		closed_set[top.x][top.y] = true;
		print_maze();
		for (int i = 0; i < DIR_NUM; ++i) {
			int tx = top.x + DIR_X[i];
			int ty = top.y + DIR_Y[i];
			if (extend_set[tx][ty]) continue;
			if (maze_map[tx][ty] == 'o') continue;
			extend_set[tx][ty] = true;
			dir_pre[tx][ty] = i;
			Position tmp(tx, ty, top.step + 1);
			tmp.heuristic(pos_goal);
			open_set.push(tmp);
		}
	}
	return -1;
}


int IDSearch(Position top, int depth) {
    if (top == pos_goal) return top.step;
    closed_set[top.x][top.y] = true;
	print_maze();
    for (int i = 0; i < DIR_NUM; ++i) {
        int tx = top.x + DIR_X[i];
        int ty = top.y + DIR_Y[i];
        if (maze_map[tx][ty] == 'o') continue;
        if (closed_set[tx][ty]) continue;
        Position tmp(tx, ty, top.step + 1);
        tmp.heuristic(pos_goal);
        if (tmp.h1 + tmp.step > depth) continue;
        dir_pre[tx][ty] = i;
        int ret = IDSearch(tmp, depth);
        if (ret >= 0) return ret;
        // closed_set[tx][ty] = false;
    }
    return -1;
}


int IDAstar() {
    pos_start.heuristic(pos_goal);
    for (int depth = pos_start.h1; depth < maze_col * maze_row; ++depth) {
        printf("depth:%d \n", depth);
        memset(closed_set, false, sizeof(closed_set));
        int ret = IDSearch(pos_start, depth);
        if (ret >= 0) return ret;
    }
    return -1;
}


void init_maze_map() {
	puts("Input your map or copy and paste from ./map.txt");
	
	scanf("%d,%d", &maze_col, &maze_row);
	memset(maze_map, 0, sizeof(maze_map));
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
	getchar();
}


int main(int argc, char *argv[]) {
	init_maze_map();
	
    do {
menu:
		puts("");
        puts("=========== Routing Algorithms ===========");
		puts("----------------- DFS --------------");
		puts("    1. Depth-first search, recursive");
    	puts("    2. Depth-first search, stack");
		puts("----------------- BFS ------------------");
		puts("    3. Breadth-first search");
		puts("    4. A* search algorithm");
		puts("    5. Iterative deepening A*");
		puts("-------------------COMMAND--------------------");
		puts("    8. reset maze map");
		puts("    9. exit");
		puts("==============================================");
		printf("    input index number: ");

        char input_str[64] = {0};
input:
		fgets(input_str, sizeof(input_str), stdin);
		int input_len = strlen(input_str) - 1;
		for (int i = 0; i < input_len; ++i) {
			if (input_str[i] < '0' || input_str[i] > '9') {
				puts("input error, please try again.");
				goto input;
			}
		}
        int index = 0;
		sscanf(input_str, "%d", &index);
		printf("\nyour choose index:%d\n", index);
        
        prepare();
        clock_t time_start = clock();
        int result = 0;
        switch (index) {
        case 1:
            result = DFS(pos_start);
            break;
        case 2:
            result = DFS_stack();
            break;
        case 3:
            result = BFS();
            break;
        case 4:
            result = Astar();
            break;
		case 5:
            result = IDAstar();
			break;
		case 8:
			init_maze_map();
			goto menu;
		case 9:
            puts("\nsee you :)\n");
			goto done;
		default:
            puts("input error, please try again.");
            goto input;
		}
        clock_t time_end = clock();

        double cost_time = (double)(time_end - time_start)/CLOCKS_PER_SEC;
		printf("search cost time: %lfs\n", cost_time);
		if (result == -1) {
			puts("This maze have no solution");
			continue;
		}
		
		printf("The path need %d steps \n", result);
		Position tmp = pos_goal;
		while (true) {
			int i = dir_pre[tmp.x][tmp.y];
			tmp.x -= DIR_X[i];
			tmp.y -= DIR_Y[i];
			if (tmp == pos_start) break;
			maze_map[tmp.x][tmp.y] = CH_PATH;
		}
		print_maze();
	} while (true);
	
done:
	return 0;
}
