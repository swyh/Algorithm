#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 99999999

#define DOWN	0
#define UP		1
#define RIGTH	2
#define LEFT	3

#define RED		5
#define BLUE	6

vector<vector<char>> v;

int di[4] = { 1,-1,0,0 };
int dj[4] = { 0,0,1,-1 };
int N, M;
int min_ = MAX;

bool check(int i, int j) {
	if (i < 0 || j < 0 || i >= N || j >= M)
		return 0;
	else
		return 1;
}

// ������� �κп��� �Ǽ��� ������. 
// �Ǽ��� ���̱� ���ؼ��� �̸� �����غ���
int move(int& dire, pair<int, int>& ball, pair<int, int>& sub, int color) {
	// �̵��� ��
	int ki = ball.first + di[dire];
	int kj = ball.second + dj[dire];
	pair<int, int> move_ = make_pair(ki, kj);

	if (!check(ki, kj))
		return 0;

	// ���� �ٸ� ������ �ִٸ� ���� ������.
	int subBall = 0;
	if (sub == move_) {
		int op_color = (color == RED) ? BLUE : RED;
		subBall = move(dire, sub, ball, op_color);	// ������ ���ۿ� �� ��� ��ȯ�� ����
		if (subBall == BLUE || subBall == RED) {
			sub = make_pair(-1, -1);	// ���� ���ش�.
		}
	}

	if (v[ki][kj] == '.' && sub != move_) {	// move ball
		ball = move_;
		return move(dire, ball, sub, color) + subBall;
	}
	else if (v[ki][kj] == 'O') {	// ������ ã��
		ball = make_pair(-1, -1);
		return color;
	}

	return subBall;
}

void DFS(int dire, int cnt, pair<int, int> red, pair<int, int> blue) {	// ����, Ƚ��
	if (cnt > 10)
		return;

	int result = 0;
	int ki = red.first + di[dire];
	int kj = red.second + dj[dire];
	pair<int, int> move_ = make_pair(ki, kj);

	result += move(dire, blue, red, BLUE);
	result += move(dire, red, blue, RED);

	if (result == RED) {
		min_ = min(min_, cnt);
		return;
	}
	else if (result > RED)
		return;


	if (dire == DOWN || dire == UP) {
		DFS(RIGTH, cnt + 1, red, blue);
		DFS(LEFT, cnt + 1, red, blue);
	}
	else {
		DFS(UP, cnt + 1, red, blue);
		DFS(DOWN, cnt + 1, red, blue);
	}
}

int main() {
	pair<int, int> red;
	pair<int, int> blue;

	cin >> N >> M;
	v.resize(N);

	for (int i = 0; i < N; i++) {
		v[i].resize(M);
		for (int j = 0; j < M; j++) {
			char input;
			cin >> input;
			if (input == 'R') {
				red = make_pair(i, j);
				v[i][j] = '.';
			}
			else if (input == 'B') {
				blue = make_pair(i, j);
				v[i][j] = '.';
			}
			else
				v[i][j] = input;
		}
	}

	for (int i = 0; i < 4; i++)
		DFS(i, 1, red, blue);

	if (min_ == MAX)
		cout << "-1" << endl;
	else
		cout << min_ << endl;
}