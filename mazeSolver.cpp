#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#define MAZE_LENGTH 11 //x
#define MAZE_HEIGHT 9  //y

using namespace std;

enum Directions {N, NE, E, SE, S, SW, W, NW}; // 0 ~ 7

struct offset{
	int _x;
	int _y;
};

typedef struct step{
	int x; 
	int y;
	int dir;
} STEP;

void initMove(struct offset *);
bool checkBorder(int, int);

int main(){
	struct offset move[8];
	stack<STEP> steps;
	vector< vector<int> > row(MAZE_LENGTH, vector<int>(MAZE_HEIGHT, 0)); // maze
	vector< vector<bool> > mark(MAZE_LENGTH, vector<bool>(MAZE_HEIGHT, false));
	int dest_x = 10;
	int dest_y = 7;
	bool has_path = false;

	initMove(move);

	for (int i = 0; i < MAZE_HEIGHT; i++){
		for (int j = 0; j < MAZE_LENGTH; j++)
			cin >> row.at(j).at(i);
	}

	// for (int i = 0; i < MAZE_HEIGHT; i++){
	// 	for (int j = 0; j < MAZE_LENGTH; j++){
	// 		if (!row.at(j).at(i)) cout << row.at(j).at(i);
	// 		else cout << " ";
	// 	}
	// 	cout << endl;
	// }

	STEP tmp = {0, 1, E};
	steps.push(tmp);
	mark.at(0).at(1) = true;

	while (!steps.empty()){
		tmp = steps.top();
		steps.pop();
		int i = tmp.x; int j = tmp.y; int d = tmp.dir;
		cout << endl << "(" << i << "," << j << ")->" << d << endl;
		while (d < 8){

			int g = i + move[d]._x;
			int h = j + move[d]._y;
			cout << "(" << g << "," << h << "):" << row.at(g).at(h) << endl;

			if (g == dest_x && h == dest_y){
				has_path = true;
				break;
			}
			else if (checkBorder(g, h) && !row.at(g).at(h) && !mark.at(g).at(h)){
				mark.at(g).at(h) = true;

				tmp.x = i; tmp.y = j; tmp.dir = d + 1;
				steps.push(tmp);

				i = g; j = h; d = N;
			}
			else
				d++;
		}
		if (has_path){
			cout << "There's a path." << endl;
			break;
		}
	}
	if (!has_path) cout << "There's no path." << endl;
	return 0;
}

void initMove(struct offset * move){
	move[N]._x  = 0;  move[N]._y  = 1;
	move[NE]._x = 1;  move[NE]._y = 1;
	move[E]._x  = 1;  move[E]._y  = 0;
	move[SE]._x = 1;  move[SE]._y = -1;
	move[S]._x  = 0;  move[S]._y  = -1;
	move[SW]._x = -1; move[SW]._y = -1;
	move[W]._x  = -1; move[W]._y  = 0;
	move[NW]._x = -1; move[NW]._y = 1;
}

bool checkBorder(int x, int y){
	if (x >= MAZE_LENGTH || x < 0 || y >= MAZE_HEIGHT || y < 0)
		return false;
	else return true;
}