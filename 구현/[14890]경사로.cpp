#include <iostream>
#include <vector>
using namespace std;

int N, L;	// map�� ũ��, ������ ũ��

bool check(int i) {
	if (i < 0 || i >= N)
		return 0;
	else
		return 1;
}

bool low(int arr[], int visit[], int i) {	// ������ �� ��ο� ���θ� ����
	for (int j = i; j < i + L; j++) {
		if (!check(j) || visit[j] == 1)
			return 0;
	}
	for (int j = i; j < i + L; j++)
		visit[j] = 1;
	return 1;
}

bool high(int arr[], int visit[], int i) {	// �ڿ� ���� ���� �ڸ��� �ִ��� Ȯ��
	for (int j = i; j > i - L; j--) {
		if (!check(j) || visit[j] == 1)
			return 0;
	}
	for (int j = i; j > i - L; j--)
		visit[j] = 1;
	return 1;
}

bool move(int arr[]) {
	int* visit = new int[N];
	for (int i = 0; i < N; i++)
		visit[i] = 0;

	for (int i = 0; i < N - 1; i++) {
		//���鼭 �� ���� ��, ���� �� ������
		//���� ���� �� �ִ� �� Ȯ�� => yes : �Ѿ, no : false
		if (arr[i] == arr[i + 1])	// �Ѿ
			continue;
		else if (arr[i] == arr[i + 1] - 1) {	// ��簡 1ĭ ����
			if (high(arr, visit, i) == false)
				return 0;
		}
		else if (arr[i] == arr[i + 1] + 1) { // ��簡 ��ĭ ����
			if (low(arr, visit, i + 1) == false)
				return 0;
		}
		else
			return 0;
	}
	return 1;
}

int main() {

	cin >> N >> L;

	vector<vector<int>> v;
	v.resize(N);

	for (int i = 0; i < N; i++) {
		v[i].resize(N);
		for (int j = 0; j < N; j++) {
			cin >> v[i][j];
		}
	}

	int cnt = 0;

	//������
	for (int i = 0; i < N; i++) {
		int* arr = new int[N];
		for (int j = 0; j < N; j++) {
			arr[j] = v[i][j];
		}
		cnt += move(arr);
	}

	//������
	for (int i = 0; i < N; i++) {
		int* arr = new int[N];
		for (int j = 0; j < N; j++) {
			arr[j] = v[j][i];
		}
		cnt += move(arr);
	}
	cout << cnt << endl;
}

//Ʋ�ȴ� ���� : ���� �ϳ��� ��ĭ�� �ø� �� �ִٴ� �� ����
// ���� : �Ű��������� int arr[]�� �����ͷ� �����Ͽ� �������� ������ ��