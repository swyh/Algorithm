#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> v;
int cnt = 0;
int N, M;

int dn[4] = { 3, 0, 1, 2 };
int di[4] = { -1, 0, 1, 0 };	//��, ������, �Ʒ�, �������� ��������
int dj[4] = { 0, 1, 0, -1 };

bool check(int i, int j) {
	if (i >= N || j >= M || i < 0 || j < 0)
		return 0;
	else
		return 1;
}

void clear(int i, int j, int d) {
	if (check(i, j) && v[i][j] == 0) {
		int T = 4, dt = d;
		cnt++;
		v[i][j] = 2; // ���� ��ġ�� û���Ѵ�.

		while (T--) {
			clear(i + di[d], j + dj[d], dt);// ���� Ž��
			dt = dn[d];	// ȸ��
		}
	}
}


int main() {

	cin >> N >> M;

	int r, c, d;	//��, �� ���� ([r][c])
	cin >> r >> c >> d;

	v.resize(N);
	for (int i = 0; i < N; i++) {
		v[i].resize(M);
		for (int j = 0; j < M; j++) {
			cin >> v[i][j];
		}
	}

	clear(r, c, d);
	cout << cnt << endl;

}