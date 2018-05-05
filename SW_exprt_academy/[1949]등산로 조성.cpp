#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
int max_cnt = 0;

int di[4] = { 1,-1, 0,0 };
int dj[4] = { 0,0,1,-1 };

bool check(int i, int j) {
	if (i < 0 || j < 0 || i >= N || j >= N)
		return 0;
	else
		return 1;
}

void DFS(int i, int j, bool have_k, int cnt, vector<vector<int>> v, vector<vector<bool>>& visit) {
	visit[i][j] = 1;

	for (int k = 0; k < 4; k++) {
		int ki = i + di[k];
		int kj = j + dj[k];

		if (check(ki, kj) && !visit[ki][kj]) {	// ������ ����� �ʰ�, �湮���� �ʾ��� ��
			if (v[ki][kj] < v[i][j])	// �� ���� �� �����δ�.
				DFS(ki, kj, have_k, cnt + 1, v, visit);
			else if (have_k) {
				for (int l = 1; l <= K; l++) {
					if (v[ki][kj] - l < v[i][j]) {	// (���� ���츮�� ũ�ų� ���� ��) K�� ���� �� �� �۴ٸ�
						v[ki][kj] -= l;
						DFS(ki, kj, 0, cnt + 1, v, visit);
						v[ki][kj] += l;
					}
				}
			}

		}

	}

	visit[i][j] = 0;
	max_cnt = max(max_cnt, cnt);
}

int foo() {
	cin >> N >> K;

	int answer = 0;

	int max_ = 0;
	vector<vector<int>> v(N);
	vector<vector<bool>> visit(N);


	//input
	for (int i = 0; i < N; i++) {
		v[i].resize(N);
		visit[i].resize(N);
		for (int j = 0; j < N; j++) {
			cin >> v[i][j];
			max_ = max(max_, v[i][j]);	// �ִ밪 ã�´�.
		}
	}

	//�� ���츮������ DFS ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (max_ == v[i][j])
				DFS(i, j, 1, 1, v, visit);
		}
	}

	answer = max_cnt;
	max_cnt = 0;
	return answer;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << " " << foo() << endl;
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}