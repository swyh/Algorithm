#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<pair<int, int>>> v;
vector<bool> visit;
int max_val = 0, max_i = 0;

void dfs(int i, int cost_sum) {
	visit[i] = 1;
	for (int j = 0; j < v[i].size(); j++) {
		int next = v[i][j].first;
		int cost = v[i][j].second;
		if (!visit[next])
			dfs(next, cost_sum + cost);
	}

	if (cost_sum > max_val) {
		max_val = cost_sum;
		max_i = i;
	}
}

int main() {
	ios::sync_with_stdio(false);

	int N;
	cin >> N;

	v.resize(N + 1);
	visit.resize(N + 1);
	for (int i = 0; i < N; i++) {
		int num, vertex, cost;
		cin >> num;

		while (1) {
			cin >> vertex;
			if (vertex == -1)
				break;
			cin >> cost;

			v[num].push_back(make_pair(vertex, cost));
		}
	}

	dfs(1, 0);

	for (int i = 0; i < visit.size(); i++)
		visit[i] = 0;

	dfs(max_i, 0);

	cout << max_val << endl;

	return 0;
}