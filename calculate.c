#include <stdio.h>
long result = 0;
int path[9] = { 0 };	//the path to unlock the phone

void printPath() {

	for (int i = 0; i < 9; i++) {
		if (path[i] == 0) break;
		if (i == 0) {
			printf("path:\t%d  ", path[i]);
			continue;
		}

		printf("-> %d  ", path[i]);
	}
	printf("\n");
}
int isOutOfEdge(int row, int col) {
	return col<0 || row <0 || col>2 || row>2;
}

void moveToNext(int this_num, int depth, int target, int choosed[]);

void nextMove(int num, int row_step, int col_step,int depth, int target, int choosed[]) {
	int can_move = 0;
	int next;
	int t_row = (num - 1) / 3 + row_step;   //-1	-2	-1
	int t_col = (num - 1) % 3 + col_step;	//-1	-1	-2
	next = t_row * 3 + t_col + 1;
	if (!isOutOfEdge(t_row, t_col)) {
		if (choosed[next] == 0) can_move = 1;
		else {
			t_row = t_row + row_step;
			t_col = t_col + col_step;
			next = t_row * 3 + t_col + 1;
			if (!isOutOfEdge(t_row, t_col)) 
				if (choosed[next] == 0)  can_move = 1;
		}
	}	
	if (can_move) {
		choosed[next] = 1;
		moveToNext(next, depth + 1, target, choosed);
		choosed[next] = 0;
	}
}

void moveToNext(int this_num, int depth, int target, int choosed[]) {
	//if (this_num>9 ||this_num<1) return ;
	path[depth - 1] = this_num;
	if (target == depth) {
		result += 1;
		printPath();
		return ;
	}
	//左上	
	nextMove(this_num, -1, -1,depth,target, choosed);
	nextMove(this_num, -2, -1, depth, target, choosed);
	nextMove(this_num, -1, -2, depth, target, choosed);
	//向上
	nextMove(this_num, -1, 0, depth, target, choosed);
	//右上
	nextMove(this_num, -1, +1, depth, target, choosed);
	nextMove(this_num, -2, +1, depth, target, choosed);
	nextMove(this_num, -1, +2, depth, target, choosed);
	//向左移动
	nextMove(this_num, 0, -1, depth, target, choosed);
	//向右移动
	nextMove(this_num, 0, 1, depth, target, choosed);
	//左下
	nextMove(this_num, +2, -1, depth, target, choosed);
	nextMove(this_num, +1, -2, depth, target, choosed);
	nextMove(this_num, +1, -1, depth, target, choosed);
	//向下移动
	nextMove(this_num, +1, 0, depth, target, choosed);
	//右下
	nextMove(this_num, +1, +1, depth, target, choosed);
	nextMove(this_num, +2, +1, depth, target, choosed);
	nextMove(this_num, +1, +2, depth, target, choosed);
	path[depth - 1] = 0;

}

void calculate() {
	int choosed[10] = { 0 };
	int depth;
	for (depth = 4; depth <= 9; depth++) {
		for (int i = 1; i<10; i++) {
				choosed[i] = 1;
				moveToNext(i, 1, depth, choosed);
				choosed[i] = 0;
		}
	}
	printf("\tthere have  %d  result\n", result);
}

void test() {
	int choosed[3][3] = { 0,0,0,
		0,0,0,
		0,0,0 };
	int row = 2, col = 2;
	int n_row = -1, n_col = -1;
	int depth = 3;
	choosed[row][col] = 1;
	/*move(0, 1, depth, choosed);*/
	choosed[row][col] = 0;

	printf("in depth = %d have  %d result\n", depth, result);
}
int main(int argc, char const *argv[])
{
	calculate();
	//test();
	printf("\tpress enter key to exit");
	getchar();
 	return 0;
}
