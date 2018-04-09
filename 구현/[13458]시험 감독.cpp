#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	//input
	int N; // �������� ����
	cin >> N;

	vector<int> v; // �� ���� �������� ���� ����
	int A; // �� ���� �������� ��
	for (int i = 0; i < N; i++) {
		cin >> A;
		v.push_back(A);
	}

	int B, C;	// �Ѱ�����, �ΰ������� ������ �� �ִ� ������ ��
	cin >> B >> C;


	//request output : �ʿ��� ������ ���� �ּҰ�
	long long cnt = N;	// N���� �游ŭ �Ѱ������� ���� �ʿ�
	for (int i = 0; i < N; i++) {
		v[i] -= B;	// �Ѱ������� �����ϴ� �����ڸ� ����,
		if (v[i] <= 0)	// 0���� �۰ų� ���ٸ� ���� �� �˻����� �Ѿ
			continue;
		cnt += ceil(((double)v[i] / (double)C)); // �ʿ��� �ΰ����� ���ϰ� ����
	}

	cout << cnt << endl;	//��� ���
}