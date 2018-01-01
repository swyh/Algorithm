//#include <iostream>
//#include <vector>
//#include <queue>
//#include <functional>
//using namespace std;
//
//vector <vector<pair<int, int>>> arr;	// �׷����� ����� �Բ� �����Ѵ�.
//vector<bool> visit;
//priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;	// (���, �ڷᱸ��, ����)
//// greater : ��������?
//void func(int n);
//int result = 0;
//
//int main() {
//	int v, e;
//	cin >> v >> e;
//
//	arr.resize(v + 1);
//	visit.resize(v + 1);
//	for (int i = 0; i < e; i++) {
//		int v1, v2, cost;
//		cin >> v1 >> v2 >> cost;
//		arr[v1].push_back(make_pair(cost, v2));
//		arr[v2].push_back(make_pair(cost, v1));
//	}
//	func(1);
//	cout << result << endl;
//
//}
//
//void func(int n) { // Ǫ�� �˰���
//	visit[n] = 1;
//	for (int i = 0; i < arr[n].size(); i++) {
//		pq.push(arr[n][i]);
//	}
//
//	while (!pq.empty()) {
//		if (visit[pq.top().second] == 0) {
//			result += pq.top().first;
//			func(pq.top().second);
//		}
//		else
//			pq.pop();
//	}
//}

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

vector<vector<pair<int, int>>> arr;
vector<bool> visit;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int cnt = 0;

void func(int i) {
	visit[i] = 1;
	for (int j = 0; j < arr[i].size(); j++)
		pq.push(arr[i][j]);

	while (!pq.empty()) {
		int cost = pq.top().first;
		int dest = pq.top().second;
		pq.pop();

		if (visit[dest] == 0) {
			visit[dest] = 1;
			cnt += cost;
			for (int j = 0; j < arr[dest].size(); j++) {
				if (visit[arr[dest][j].second] == 0)
					pq.push(arr[dest][j]);
			}
		}
	}

}

int main() {
	int v, e;
	cin >> v >> e;	// v : vertex�� ��, e : edge�� ��

	arr.resize(v + 1);
	visit.resize(v + 1);

	for (int i = 0; i < e; i++) {
		int a, b, c;	// a, b vertex ������ cost
		cin >> a >> b >> c;

		arr[a].push_back(make_pair(c, b));
		arr[b].push_back(make_pair(c, a));
	}

	func(1);	// ���� �˰���
	cout << cnt << endl;

}