#define _CRT_SECURE_NO_WARNINGS    // strtok ���� ���� ���� ������ ���� ����
#include <iostream>
#include <string>
using namespace std;

int main()
{
	char s1[30];  // ũ�Ⱑ 30�� char�� �迭�� �����ϰ� ���ڿ� �Ҵ�
	scanf("%s", s1);

	char *ptr = strtok(s1, "-");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (ptr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		printf("%s\n", ptr);          // �ڸ� ���ڿ� ���
		ptr = strtok(NULL, "-");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}

	return 0;
}