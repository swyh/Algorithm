#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define NULL	0
#define APPLE	1
#define ME		2

int N, K; // ����ũ��, ��� ����

int di[4] = { -1,0,1,0 };
int dj[4] = { 0,1, 0,-1 };

int change_dir(int dir, char C) {
	if (C == 'D') // ������
		return (dir + 1) % 4;
	else // ����
		return (4 + (dir - 1)) % 4;
}

inline int get_v(pair<int, int> p, vector<vector<int>>& v) {
	return v[p.first][p.second];
}

void set_v(pair<int, int> p, int value, vector<vector<int>>& v) {
	v[p.first][p.second] = value;
}

inline pair<int, int> move(pair<int, int> p, int dir) {
	return make_pair(p.first + di[dir], p.second + dj[dir]);
}

bool check(pair<int, int> p) {	// ���� ����
	int i = p.first;
	int j = p.second;

	if (i <= 0 || j <= 0 || i > N || j > N)
		return 0;
	else
		return 1;
}

void print_v(int time, vector<vector<int>>& v) {
	cout << endl;
	cout << time << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> K;

	vector<vector<int>> v(N + 1, vector<int>(N + 1));
	queue<pair<int, char>> cmd;

	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		v[x][y] = APPLE;
	}

	int L;
	cin >> L;

	for (int i = 0; i < L; i++) {
		int X;
		char C;	// X�� �� ����(L ����, D ������)
		cin >> X >> C;
		cmd.push(make_pair(X, C));
	}

	int time = 0;
	int dir = 1;
	pair<int, int> head = make_pair(1, 1);
	queue<pair<int, int>> me;

	set_v(head, ME, v);
	me.push(head);

	while (1) {
		if (!cmd.empty() && cmd.front().first == time) {
			dir = change_dir(dir, cmd.front().second);
			cmd.pop();
		}

		time++;

		pair<int, int> next_head = move(head, dir);


		if (!check(next_head) || get_v(next_head, v) == ME)
			break;

		if (get_v(next_head, v) != APPLE) {
			pair<int, int> tail = me.front();
			me.pop();

			set_v(tail, NULL, v);
		}


		set_v(next_head, ME, v);
		head = next_head;
		me.push(head);

		//print_v(time, v);
	}

	cout << time << "\n";

	return 0;
}