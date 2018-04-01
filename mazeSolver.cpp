#include <iostream>
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
namespace my{
	struct offset move[8];
}

typedef struct step{
	int x; 
	int y;
	int dir;
} STEP;

void initMove(struct offset *);
void initMaze(vector< vector<int> > &, int, int); // height, length
bool checkBorder(int, int); // x, y
void mazeSolver(vector< vector<int> > &);

int main(){
	vector< vector<int> > row(MAZE_LENGTH, vector<int>(MAZE_HEIGHT, 0)); // maze

	initMove(my::move);
	initMaze(row, MAZE_HEIGHT, MAZE_LENGTH);
	mazeSolver(row);
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

void initMaze(vector< vector<int> > &row, int height, int length){
	for (int i = 0; i < height; i++){
		for (int j = 0; j < length; j++)
			cin >> row.at(j).at(i);
	}
}

bool checkBorder(int x, int y){
	if (x >= MAZE_LENGTH || x < 0 || y >= MAZE_HEIGHT || y < 0)
		return false;
	else return true;
}

void mazeSolver(vector< vector<int> > &row){
	stack<STEP> steps;
	vector< vector<bool> > mark(MAZE_LENGTH, vector<bool>(MAZE_HEIGHT, false));
	int dest_x = 10;
	int dest_y = 7;

	STEP tmp = {0, 1, E};
	steps.push(tmp);
	mark.at(0).at(1) = true;

	while (!steps.empty()){
		tmp = steps.top();
		steps.pop();
		int i = tmp.x; int j = tmp.y; int d = tmp.dir;
		while (d < 8){

			int g = i + my::move[d]._x;
			int h = j + my::move[d]._y;

			if (g == dest_x && h == dest_y){
				cout << "There's a path." << endl;
				return;
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
	}
	cout << "There's no path." << endl;
}