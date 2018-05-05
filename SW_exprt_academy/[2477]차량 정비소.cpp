#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, K, A, B;

void waitK(int sec, queue<pair<int, int>>& kq, queue<int>& n_wait) {
	while (!kq.empty() && sec == kq.front().first) {	// ����
		int idx = kq.front().second;
		n_wait.push(idx);
		kq.pop();
	}
}

void pushIn(vector<int>& v, queue<int>& wait, vector<pair<int, int>>&  visit, vector<pair<int, int>>& result, bool n_m) {
	if (wait.empty())
		return;

	for (int i = 1; i < v.size(); i++) {
		if (visit[i].first == 0 && visit[i].second == 0) {
			visit[i].first = v[i];
			visit[i].second = wait.front();	//idx

			if (n_m == 0)	// n
				result[wait.front()].first = i;
			else // m
				result[wait.front()].second = i;

			wait.pop();
			if (wait.empty())
				return;
		}
	}
}

void move(vector<pair<int, int>>&  visit, queue<int>& next) {
	for (int i = 1; i < visit.size(); i++) {
		if (visit[i].first == 0 && visit[i].second != 0) {	// �ű� idx ����
			next.push(visit[i].second);
			visit[i].second = 0;
		}
	}
}

void work(vector<pair<int, int>>& visit) {
	for (int i = 1; i < visit.size(); i++) {
		if (visit[i].first > 0)
			visit[i].first--;
	}
}

int foo() {
	int answer = 0;
	cin >> N >> M >> K >> A >> B;
	// ����â�� N, ���� â�� M, �� �� K, ���� ����/����(A,B)

	vector<int> nv(N + 1);
	vector<int> mv(M + 1);
	queue<pair<int, int>> kq;	// ����ȣ �� �����ð�
								//input
	for (int i = 1; i <= N; i++)
		cin >> nv[i];

	for (int i = 1; i <= M; i++)
		cin >> mv[i];

	for (int i = 1; i <= K; i++) {
		int input;
		cin >> input;
		kq.push(make_pair(input, i));
	}

	//start

	int sec = 0;
	queue<int> n_wait;	//���������
	queue<int> m_wait;	//��������
	queue<int> exit;

	vector<pair<int, int>> n_visit(N + 1);	//����ó����(�ð�/idx(����ȣ))
	vector<pair<int, int>> m_visit(M + 1);	//����ó����
	vector<pair<int, int>> result(K + 1);

	while (1) {
		waitK(sec, kq, n_wait);	// kq -> n_wait

		move(n_visit, m_wait);	// n->m_wait
		move(m_visit, exit);	// m->exit

		pushIn(nv, n_wait, n_visit, result, 0);	// n_wait -> n
		move(n_visit, m_wait);	// n->m_wait

		pushIn(mv, m_wait, m_visit, result, 1);	// m_wait -> m
		move(m_visit, exit);			// m->exit

										//cout << sec <<  "exit : " << exit.size() << endl;
		if (exit.size() == K)
			break;

		work(n_visit);
		work(m_visit);

		//for (int i =1; i < n_visit.size(); i++)
		//	cout << n_visit[i].second << " ";
		//cout << endl;
		//for (int i = 1; i < m_visit.size(); i++)
		//	cout << m_visit[i].second << " ";
		//cout << endl;
		sec++;
	}

	for (int i = 1; i <= K; i++) {
		if (A == result[i].first && B == result[i].second)
			answer += i;
	}
	if (answer == 0)
		answer = -1;
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