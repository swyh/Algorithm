#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int w, h;
int di[4] = { 1, -1, 0, 0 };
int dj[4] = { 0, 0, 1, -1 };

//vector�� ����Ѵ�.
void print(vector<vector<char>>& v) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			cout << v[i][j];
		cout << endl;
	}
}

//vector�� �߸��� index�� �����ϴ��� Ȯ���ϴ� �Լ�
bool check(int i, int j) {
	if (i < 0 || j < 0 || i >= h || j >= w)
		return 0;
	else
		return 1;
}

int BFS(vector<vector<char>>& v, vector<pair<int, int>>& fire, pair<int, int> start) {
	queue<pair<int, int>> q[2];			// ������� ��ġ�ε����� ����
	queue<pair<int, int>> q_fire[2];	// ���� ��ġ�ε����� ����
										// queue�� 2���� �����Ͽ� 0,1 �ε����� �����ư��� ���� �̵��� ��ġ�ε����� �����Ѵ�.
	bool idx = 0;	// queue�� 0,1 �����ư��� ����ϱ� ���� ����
	int sec = 0;


	q[idx].push(start);
	for (int i = 0; i < fire.size(); i++)
		q_fire[idx].push(fire[i]);


	while (1) {
		//1�ʰ� �������� �ǹ�(��ĭ�� �̵�)
		sec++;

		//����� �̵�
		while (!q[idx].empty()) {
			int fi = q[idx].front().first;
			int fj = q[idx].front().second;
			q[idx].pop();

			// ���� �Űܺپ��� ���
			if (v[fi][fj] == '*')
				continue;

			// ������������ �̵��� �� �ִ��� Ȯ��
			for (int k = 0; k < 4; k++) {
				int ki = fi + di[k];
				int kj = fj + dj[k];

				//����̰� �̵��� �� �ִ� ��ġ
				if (check(ki, kj) && v[ki][kj] == '.') {
					v[ki][kj] = '@';
					q[!idx].push(make_pair(ki, kj));
				}
				else if (!check(ki, kj))	// ����̰� �ܺη� Ż��
					return sec;
			}
		}

		if (q[!idx].empty())	// �� �̻� �� ���� ������
			return 0;

		//���� �̵�
		while (!q_fire[idx].empty()) {
			int fi = q_fire[idx].front().first;
			int fj = q_fire[idx].front().second;
			q_fire[idx].pop();

			// ������������ �̵��� �� �ִ��� Ȯ��
			for (int k = 0; k < 4; k++) {
				int ki = fi + di[k];
				int kj = fj + dj[k];

				//���� �̵��� �� �ִ� ��ġ
				if (check(ki, kj) && (v[ki][kj] == '.' || v[ki][kj] == '@')) {
					v[ki][kj] = '*';
					q_fire[!idx].push(make_pair(ki, kj));
				}
			}
		}

		//index�� �����´�.
		idx = !idx;
	}
}


int main() {
	int T;
	cin >> T;

	while (T--) {
		cin >> w >> h;
		cin.ignore();

		vector<vector<char>> v(h);

		//fire�� start ������ �ε����� �����ϴ� ���Ϳ� ����
		vector<pair<int, int>> fire;
		pair<int, int> start;

		for (int i = 0; i < h; i++) {
			string s;
			getline(cin, s);

			//get and store input
			for (int j = 0; j < s.size(); j++) {
				v[i].push_back(s[j]);
				if (s[j] == '*') //it's fire
					fire.push_back(make_pair(i, j));
				else if (s[j] == '@')
					start = make_pair(i, j);
			}
		}

		int result = BFS(v, fire, start);

		if (result)
			cout << result << endl;
		else
			cout << "IMPOSSIBLE" << endl; \
	}
}