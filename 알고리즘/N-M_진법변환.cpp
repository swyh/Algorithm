#include <iostream>
#include <string>
#include <cmath>
using namespace std;



//base������ ��ȯ
string func(int n, int base) {
	string t = "0123456789ABCDEF";

	if (n == 0)
		return "";
	else
		return func(n / base, base) + t[n % base];
}

//base���� -> 10������ ��ȯ
int func2(int n, int base) {
	if (n == 0)
		return 0;
	else
		return func2(n / 10, base) * base + (n % 10);
}


int main() {
	int N;
	cin >> N;

	// 3������ 16������ �ٲٱ�!
	int a = func2(N, 3);
	cout << func(a, 16) << endl;

	return 0;
}