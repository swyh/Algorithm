//all shortest path ���ϱ�
//�÷��̵� �ͼ�, ���ͽ�Ʈ�� �˰������� �ذ��� �� �ִ�.
//�÷��̵� �ͼ� : O(n^3), ���ͽ�Ʈ�� : O(nmlogn) -> transpose graph�� �̿��ϸ� O(2mlogn)�� ���� �ذ� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_NUM 999999999

int main() {
	int N, M, X;
	scanf("%d %d %d", &N, &M, &X);

	vector<vector<int>> v(N + 1, vector<int>(N + 1, MAX_NUM));

	for (int i = 0; i < M; i++) {
		int v1, v2, w;
		scanf("%d %d %d", &v1, &v2, &w);
		v[v1][v2] = w;
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (i == j || v[i][k] == MAX_NUM || v[k][j] == MAX_NUM)
					continue;
				if (v[i][k] + v[k][j] < v[i][j])
					v[i][j] = v[i][k] + v[k][j];
			}
		}
	}

	int result = 0;

	for (int i = 1; i <= N; i++) {
		if (v[i][X] == MAX_NUM || v[X][i] == MAX_NUM)
			continue;

		result = max(result, v[i][X] + v[X][i]);
	}

	printf("%d\n", result);

	return 0;
}