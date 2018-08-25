
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

const char CH_START = 's';
const char CH_END = 'e';
const char CH_WALL = 'o';

const int DIR_NUM = 8;
const int DIR_X[] = {-1, 1,  0, 0, -1, -1, 1, 1};
const int DIR_Y[] = { 0, 0, -1, 1,  1, -1, 1,-1};


int _maze_col;
int _maze_row;
char _maze_map[Max][Max];

bool _closed[Max][Max];
bool _extend[Max][Max];
// preceding direction
int _dir_pre[Max][Max];


struct Position {
	int x, y;
	int step; // g
	double h1, h2, h3; // h1 is important
	Position() {}
	Position(int a, int b):x(a), y(b), step(0), h1(0), h2(0),h3(0) {}
	Position(int a, int b, int c):x(a), y(b), step(c), h1(0), h2(0),h3(0) {}
	bool operator == (const Position& a) const {
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
	bool operator < (const Position& a) const {
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
Position _pstart;
Position _pgoal;


void print_maze() {
	for (int i = 0; i < _maze_row; ++i) {
		for (int j = 0; j < _maze_col; ++j) {
			if (_closed[i][j] && _maze_map[i][j] == ' ') {
				printf("%c", CH_CLOSED);
			} else if (_extend[i][j] && _maze_map[i][j] == ' ') {
				printf("%c", CH_EXTEND);
			} else {
				printf("%c", _maze_map[i][j]);
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
	memset(_closed, false, sizeof(_closed));
	memset(_extend, false, sizeof(_extend));
	for (int i = 0; i < _maze_row; ++i) {
		for (int j = 0; j < _maze_col; ++j) {
			if (_maze_map[i][j] == CH_PATH) {
				_maze_map[i][j] = ' ';
			}
		}
	}
}


inline bool valid_position(int row, int col) {
	if (_maze_map[row][col] == CH_WALL) {
		return false;
	}
	if (_closed[row][col]) {
		return false;
	}
	if (_extend[row][col]) {
		return false;
	}
	return true;
}


int DFS(Position top) {
	if (top == _pgoal) {
		return top.step;
	}
	
	_closed[top.x][top.y] = true;
	print_maze();
	for (int i = 0; i < DIR_NUM; ++i) {
		int tx = top.x + DIR_X[i];
		int ty = top.y + DIR_Y[i];
		if (!valid_position(tx, ty)) {
			continue;
		}
		_dir_pre[tx][ty] = i;
		int ret = DFS(Position(tx, ty, top.step + 1));
		if (ret >= 0) {
			return ret;
		}
		// backtracking
		_closed[tx][ty] = false;
	}
	
	return -1;
}


int DFS_stack() {
	stack<Position> open_set;
	_extend[_pstart.x][_pstart.y] = true;
	_pstart.step = 0;
	
	open_set.push(_pstart);
	while (!open_set.empty()) {
		Position top = open_set.top();
		if (top == _pgoal) {
			return top.step;
		}
		open_set.pop();
		_closed[top.x][top.y] = true;
		print_maze();
		for (int i = 0; i < DIR_NUM; ++i) {
			int tx = top.x + DIR_X[i];
			int ty = top.y + DIR_Y[i];
			if (!valid_position(tx, ty)) {
				continue;
			}
			_extend[tx][ty] = true;
			_dir_pre[tx][ty] = i;
			Position tmp(tx, ty, top.step + 1);
			open_set.push(tmp);
		}
	}
	
	return -1;
}


int BFS() {
	queue<Position> open_set;
	_extend[_pstart.x][_pstart.y] = true;
	_pstart.step = 0;
	
	open_set.push(_pstart);
	while (!open_set.empty()) {
		Position top = open_set.front();
		if (top == _pgoal) {
			return top.step;
		}
		open_set.pop();
		_closed[top.x][top.y] = true;
		print_maze();
		for (int i = 0; i < DIR_NUM; ++i) {
			int tx = top.x + DIR_X[i];
			int ty = top.y + DIR_Y[i];
			if (!valid_position(tx, ty)) {
				continue;
			}
			_extend[tx][ty] = true;
			_dir_pre[tx][ty] = i;
			Position tmp(tx, ty, top.step + 1);
			open_set.push(tmp);
		}
	}
	
	return -1;
}


int Astar() {
	priority_queue<Position> open_set;
	
	_extend[_pstart.x][_pstart.y] = true;
	_pstart.step = 0;
	_pstart.heuristic(_pgoal);
	
	open_set.push(_pstart);
	while (!open_set.empty()) {
		Position top = open_set.top();
		if (top == _pgoal) {
			return top.step;
		}
		open_set.pop();
		_closed[top.x][top.y] = true;
		print_maze();
		for (int i = 0; i < DIR_NUM; ++i) {
			int tx = top.x + DIR_X[i];
			int ty = top.y + DIR_Y[i];
			if (!valid_position(tx, ty)) {
				continue;
			}
			_extend[tx][ty] = true;
			_dir_pre[tx][ty] = i;
			Position tmp(tx, ty, top.step + 1);
			tmp.heuristic(_pgoal);
			open_set.push(tmp);
		}
	}
	
	return -1;
}


int IDSearch(Position top, int depth) {
	if (top == _pgoal) {
		return top.step;
	}
	
	_closed[top.x][top.y] = true;
	print_maze();
	for (int i = 0; i < DIR_NUM; ++i) {
		int tx = top.x + DIR_X[i];
		int ty = top.y + DIR_Y[i];
		if (!valid_position(tx, ty)) {
			continue;
		}
		Position tmp(tx, ty, top.step + 1);
		tmp.heuristic(_pgoal);
		if (tmp.h1 + tmp.step > depth) {
			continue;
		}
		_dir_pre[tx][ty] = i;
		int ret = IDSearch(tmp, depth);
		if (ret >= 0) {
			return ret;
		}
		// _closed[tx][ty] = false;
	}
	
	return -1;
}


int IDAstar() {
	_pstart.heuristic(_pgoal);
	for (int depth = _pstart.h1; depth < _maze_col * _maze_row; ++depth) {
		printf("depth:%d \n", depth);
		memset(_closed, false, sizeof(_closed));
		int ret = IDSearch(_pstart, depth);
		if (ret >= 0) return ret;
	}
	return -1;
}


void init_maze_map() {
	static char filename[] = "./map.txt";
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("open file '%s' error!\n", filename);
		exit(-1);
	}
	
	fscanf(fp, "%d,%d", &_maze_col, &_maze_row);
	memset(_maze_map, 0, sizeof(_maze_map));
	for (int i = 0; i < _maze_row; ++i) {
		fgetc(fp);
		for (int j = 0; j < _maze_col; ++j) {
			fscanf(fp, "%c", &_maze_map[i][j]);
			if (_maze_map[i][j] == CH_START) {
				_pstart.x = i;
				_pstart.y = j;
			} else if (_maze_map[i][j] == CH_END) {
				_pgoal.x = i;
				_pgoal.y = j;
			}
		}
	}
	printf("\nThis is initial maze map from: '%s'\n", filename);
	print_maze();
}


void reset_maze_map() {
	puts("Input your map or copy and paste from ./map.txt");
	scanf("%d,%d", &_maze_col, &_maze_row);
	memset(_maze_map, 0, sizeof(_maze_map));
	for (int i = 0; i < _maze_row; ++i) {
		getchar();
		for (int j = 0; j < _maze_col; ++j) {
			scanf("%c", &_maze_map[i][j]);
			if (_maze_map[i][j] == CH_START) {
				_pstart.x = i;
				_pstart.y = j;
			} else if (_maze_map[i][j] == CH_END) {
				_pgoal.x = i;
				_pgoal.y = j;
			}
		}
	}
	getchar();
}


int main(int argc, char* argv[]) {
	init_maze_map();
	
	do {
menu:
		puts("");
		puts("=========== Pathfinding Algorithms ===========");
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
			result = DFS(_pstart);
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
			reset_maze_map();
			goto menu;
		case 9:
			puts("\nsee you :)\n");
			goto over;
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
		Position tmp = _pgoal;
		while (true) {
			int i = _dir_pre[tmp.x][tmp.y];
			tmp.x -= DIR_X[i];
			tmp.y -= DIR_Y[i];
			if (tmp == _pstart) break;
			_maze_map[tmp.x][tmp.y] = CH_PATH;
		}
		print_maze();
	} while (true);
	
over:
	return 0;
}
