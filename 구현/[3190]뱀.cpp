#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define FREE	0
#define APPLE	1
#define SNAKE	2

#define UP		0
#define RIGHT	1
#define DOWN	2
#define LEFT	3

int di[4] = { -1,0,1,0 };
int dj[4] = { 0,1,0,-1 };


vector<vector<int>> v;	// map
queue <pair<int, char>> direction;	// ������ȯ
queue<pair<int, int>> snake;	// ���� ��ġ index�� �������
int currentDir = RIGHT;// ���� ����
int sec = 0;


bool check(int i, int j, int N) {	// ���� ���� �ٵ��ƴ��� Ȯ��
	if (i < 1 || j < 1 || i > N || j > N)
		return 1;
	else
		return 0;
}

void move(int N) {
	while (++sec) {
		// ���� �̵��� ��ġ
		int move_i = snake.back().first + di[currentDir];
		int move_j = snake.back().second + dj[currentDir];

		// �� �ڽ��� �����ų�, ���� ������� ����
		if (check(move_i, move_j, N) || v[move_i][move_j] == SNAKE) {
			break;
		}

		if (v[move_i][move_j] != APPLE) {	// ����� ������ ���� ����
			int tail_i = snake.front().first;
			int tail_j = snake.front().second;
			v[tail_i][tail_j] = FREE;
			snake.pop();
		}

		// �̵��� ���� �� queue�� �ִ´�.
		snake.push(make_pair(move_i, move_j));
		v[move_i][move_j] = SNAKE;

		// ������ �ٲ۴�.
		if (!direction.empty()) {
			int dir_time = direction.front().first;

			if (dir_time == sec) {	// ���⺯��
				int dir = direction.front().second;
				direction.pop();

				if (dir == 'L') {	// ��������
					currentDir = (currentDir - 1) < 0 ? 3 : (currentDir - 1);
				}
				else {	// ����������
					currentDir = (currentDir + 1) % 4;
				}
			}
		}
	}
}

int main() {
	int N, K;	// map�� size, K���� ����� �־�����.
	cin >> N >> K;

	v.resize(N + 1);	// 0�� index�� ������� �ʴ´�.
	for (int i = 1; i <= N; i++)
		v[i].resize(N + 1);
	v[1][1] = SNAKE;

	while (K--) {
		int i, j;
		cin >> i >> j;
		v[i][j] = APPLE;
	}

	int L;	// ���� ��ȯ�� ����
	cin >> L;

	while (L--) {
		int X;	// �� ���Ŀ� ������ȯ�� �� ������?
		char C;	// L : ����, D : ������
		cin >> X >> C;
		direction.push(make_pair(X, C));
	}

	snake.push(make_pair(1, 1));	//1,1���� ����;
	move(N);

	cout << sec << endl;
}