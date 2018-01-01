//#include <iostream>
//#include <stack>
//#include <vector>
//using namespace std;
//
//vector<vector<int>> v;
//vector<bool> visit;
//stack<int> s;
//
//void DFS(int n) {	// DFS�� �̿��� ��� : ������ ������. �׷��� �ƿ����꿧��?�� ������ queue�� �ִ´�.
//	//�׷� ������� �ǰ���??~
//	visit[n] = 1;
//
//	for (int i = 0; i < v[n].size(); i++) {
//		int k = v[n][i];
//		if (visit[k] == 0)
//			DFS(k);
//	}
//	s.push(n);
//}
//// �������Ŀ��� 2���� ����� �ִ�. 1.DFS, 2.topo,,?�� ��¼��
//// �̰� DFS�� �̿��� ���!
//int main() {
//	int N, M;	// N : �ο�, M :Ű�� �� Ƚ��
//	cin >> N >> M;
//
//	v.resize(N + 1);
//	visit.resize(N + 1);
//	for (int i = 0; i < M; i++) {
//		int A, B;
//		cin >> A >> B;
//		v[A].push_back(B);	// A�� B �տ� �ִ�
//	}
//
//	for (int i = 1; i <= N; i++) {	// ��ȸ�Ѵ�.
//		if (visit[i] == 0)
//			DFS(i);
//	}
//	while (!s.empty()) {
//		cout << s.top() << " ";
//		s.pop();
//	}
//	cout << endl;
//	return 0;
//}


//2017-12-15 update... queue�� �̿��Ͽ� ��Ȯ�ϰ�
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<vector<int>> v;
vector<bool> visit;
stack<int> s;

void DFS(int n) {	// DFS�� �̿��� ��� : ������ ������. �׷��� �ƿ����꿧��?�� ������ queue�� �ִ´�.
					//�׷� ������� �ǰ���??~
	visit[n] = 1;

	for (int i = 0; i < v[n].size(); i++) {
		int k = v[n][i];
		if (visit[k] == 0)
			DFS(k);
	}
	s.push(n);
}
// �������Ŀ��� 2���� ����� �ִ�. 1.DFS, 2.topo,,?�� ��¼��
// �̰� DFS�� �̿��� ���!
int main() {
	int N, M;	// N : �ο�, M :Ű�� �� Ƚ��
	cin >> N >> M;

	v.resize(N + 1);
	visit.resize(N + 1);
	for (int i = 0; i < M; i++) {
		int A, B;
		cin >> A >> B;
		v[A].push_back(B);	// A�� B �տ� �ִ�
	}

	for (int i = 1; i <= N; i++) {	// ��ȸ�Ѵ�.
		if (visit[i] == 0)
			DFS(i);
	}
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
	return 0;
}