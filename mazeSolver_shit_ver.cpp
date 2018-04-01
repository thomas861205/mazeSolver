#include <iostream>
#include <stack>
#include <vector>
#define MAZE_LEN 11
#define MAZE_HEI 9
#define DESTI_X 10
#define DESTI_Y 7

using namespace std;

typedef struct offset{
	int x;
	int y;
} OFFSET;

typedef struct STEP{
	int x;
	int y;
	int dir;
} STEP;

enum DERICTIONS {N, NE, E, SE, S, SW, W, NW};

bool overBorder(int, int);

int main(){
	OFFSET move[8];
	stack<STEP> steps;
	vector< vector<int> > maze(MAZE_LEN, vector<int>(MAZE_HEI, 0));
	vector< vector<bool> > mark(MAZE_LEN, vector<bool>(MAZE_HEI, false));
	bool path = false;

	move[N].x  = 0;  move[N].y  = 1;
	move[NE].x = 1;  move[NE].y = 1;
	move[E].x  = 1;  move[E].y  = 0;
	move[SE].x = 1;  move[SE].y = -1;
	move[S].x  = 0;  move[S].y  = -1;
	move[SW].x = -1; move[SW].y = -1;
	move[W].x  = -1; move[W].y  = 0;
	move[NW].x = -1; move[NW].y = 1;

	for (int i = 0; i < MAZE_HEI; i++){
		for (int j = 0; j < MAZE_LEN; j++)
			cin >> maze.at(j).at(i);
	}

	STEP tmp = {0, 1, E};
	steps.push(tmp);
	mark.at(0).at(1) = true;

	while(!steps.empty()){
		tmp = steps.top();
		steps.pop();
		int i = tmp.x; int j = tmp.y; int d = tmp.dir;
		while(d < 8){
			int g = i + move[d].x; int h = j + move[d].y;
			if((g == DESTI_X) && (h == DESTI_Y)){
				path = true;
				break;
			}
			else if (!overBorder(g, h) && !maze.at(g).at(h) && !mark.at(g).at(h)){
				mark.at(g).at(h) = true;
				tmp.x = i; tmp.y = j; tmp.dir = d + 1;
				steps.push(tmp);
				i = g; j = h; d = N;
			}
			else d++;
		}
		if (path){
			cout << "There's a path." << endl;
			break;
		}
	}
	if (!path) cout << "There's no path." << endl;
	return 0;
}

bool overBorder(int x, int y){
	if (x < 0 || x >= MAZE_LEN || y < 0 || y>=MAZE_HEI) return true;
	else return false;
}