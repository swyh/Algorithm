#include <stdio.h>
#include <stdlib.h>

void FIFO(int* input, int* frame, int input_size, int frame_size);
void OPT(int* input, int* frame, int input_size, int frame_size);
void LRU(int* input, int* frame, int input_size, int frame_size);
void Second_Chance(int* input, int* frame, int input_size, int frame_size);

int main(int argc, char* argv[]) {
	
	int frame_size = atoi(argv[1]);
	int* frame = malloc(sizeof(int)*frame_size);

	for (int i = 0; i < frame_size; i++) {
		frame[i] = -1;
	}

	FILE *fp;
	fp = fopen("Dataset","r");
	int input_size = 0;
	int input[1000];
	int num;
	while (1) {
		fscanf(fp, "%d", &input[input_size++]);
		if (feof(fp)) break;
	}
	input_size--;
		
	fclose(fp);
	
	printf("Select Page Replacement\n");
	printf("1. FIFO\n");
	printf("2. OPT\n");
	printf("3. LRU\n");
	printf("4. Second-Chance\n");
	
	char c;
	scanf("%c", &c);
	if (c == '$') {
		int select;
		scanf("%d", &select);

		switch (select)
		{
		case 1:
			printf("FIFO");
			FIFO(input, frame, input_size, frame_size);
			break;
		case 2:
			printf("OPT");
			OPT(input, frame, input_size, frame_size);
			break;
		case 3:
			printf("LRU");
			LRU(input, frame, input_size, frame_size);
			break;
		case 4:
			printf("Second-Chance");
			Second_Chance(input, frame, input_size, frame_size);
			break;
		default:
			break;
		}
	}
	free(frame);
	return 0;
}

void FIFO(int* input, int* frame, int input_size, int frame_size) {
	int point = 0;	// page fault �� frame���� swap �� ��ȣ
	int fault_size = 0; // page fault�� �߻��� Ƚ���̴�.

	for (int i = 0; i < input_size; i++) {
		printf("\n");
		int page_fault = 1;	// page_fault�� �Ͼ������ ���� ����
		printf("Number : %d", input[i]);

		for (int j = 0; j < frame_size; j++) {	//page fault�� �߻��ϴ��� Ȯ��
			if (input[i] == frame[j]){	// ���� �� page fault �߻� X
				page_fault = 0;
				break;
			}
		}
		if (page_fault == 0) continue;
		// page fault�� �߻����� �ʾ����� ���� input ���� �޵��� continue

		frame[point%frame_size] = input[i];
		// page fault�� �߻����� �� frame�� �� �ٲ����
		point++;
		// ���� page fault�� �߻����� �� ��ü�� frame ������ ����Ų��.

		for (int j = 0; j < frame_size; j++) { // frame ���
			printf("     %d", frame[j]);
		}
		fault_size++;	// page fault Ƚ���� ����
	}
	printf("\n");
	printf("page_fault : %d\n", fault_size);
}


void OPT(int* input, int* frame, int input_size, int frame_size) {
	int point = 0;	// page-fault �� frame���� swap �� ��ȣ
	int* check = malloc(sizeof(int)*frame_size);	
	// �� frame �� �������� page fualt�� �Ͼ ��ȣ�� ã�� ���� �迭

	int fault_size = 0;

	for (int i = 0; i < input_size; i++) {
		printf("\n");
		int page_fault = 1;
		printf("Number : %d", input[i]);

		for (int j = 0; j < frame_size; j++) {	// page fault�� �߻��ϴ��� Ȯ��
			if (input[i] == frame[j]) {
				page_fault = 0;
				break;
			}
		}
		if (page_fault == 0) continue;	// page_fault�� �Ͼ�� �ʾ����� ��� ����
		
		if (frame[frame_size - 1] != -1) {	// frame�� ����á�� ��
			for (int i = 0; i < frame_size; i++)	//check �迭 0���� �ʱ�ȭ
				check[i] = 0;
			int check_size = 0;
			for (int j = i; j < input_size; j++) {
				// ���� �������κ��� ������ input ������ ���ϱ� ���� for��
				for (int k = 0; k < frame_size; k++) {
					// frame�� ��� ���� �б� ���� for��
					if (check_size == frame_size - 1) break;
					if (input[j] == frame[k] && check[k] == 0) { // check �迭�� �̿��Ͽ�, 
						check[k] = 1;
						check_size++;
// �ֱ� input ������ frame�� �����ϸ� �ش� frame�� �ش�Ǵ� check�� 1�� �ٲ۴�.
// check_size�� frame ������ 1 ���� �� �����ϰ� �Ǿ�, ���� ���߿� page fualt �߻��ϴ� ���� ��ü��.
					}
				}
			}

			for (int k = 0; k < frame_size; k++) {
				if (check[k] == 0) {	// ���帶������ page fualt �Ǵ� ���� ��ü�ϱ� ����.
					point = k;
					break;
				}
			}
		}
			frame[point] = input[i];	// page fault�� �߻����� �� frame�� �� �ٲ����
		
			if (frame[frame_size - 1] == -1)	point++;

		for (int j = 0; j < frame_size; j++) { // frame ���
			printf("     %d", frame[j]);
		}
		fault_size++;
	}
	printf("\n");
	printf("page_fault : %d\n", fault_size);
	free(check);
}

void LRU(int* input, int* frame, int input_size, int frame_size) {
	int point = 0;	// page-fault �� frame���� swap �� ��ȣ
	int* time = malloc(sizeof(int)*frame_size);	
	// �� frame�� time ���� �����ϱ� ���� �迭
	int fault_size = 0;

	for (int i = 0; i < input_size; i++) {	// (���⼭ i�� time ������ ����)
		printf("\n");
		int page_fault = 1;
		printf("Number : %d", input[i]);

		for (int j = 0; j < frame_size; j++) {	// page fault�� �߻��ϴ��� Ȯ��
			if (input[i] == frame[j]) {
				time[j] = i;
				page_fault = 0;
				break;
			}
		}
		if (page_fault == 0)	continue;	// page_fault�� �Ͼ�� �ʾ����� ��� ����

		if (frame[frame_size - 1] != -1) {	// frame�� ����á�� ��
			int idx = 0;
			for (int j = 0; j < frame_size; j++) {
				// frame �߿��� ���� ������, time ���� ���� frame�� ã�´�.
				if (time[idx] > time[j]){	// �� frame �߿��� time ���� ���� ���� ���� idx�� ����
					idx = j;
				}
			}
			point = idx;
		}

		frame[point] = input[i];	// page fault�� �߻����� �� frame�� �� �ٲ����
		time[point] = i;			// ���� ���� ������ �ð��� i�� ��

		if (frame[frame_size - 1] == -1) {	// frame�� �������� �ʾҴٸ�(������ frame�� ����� ���)
			point++;
		}

		for (int j = 0; j < frame_size; j++) { // frame ���
			printf("     %d", frame[j]);
		}
		fault_size++;
	}
	printf("\n");
	printf("page_fault : %d\n", fault_size);
	free(time);
}

void Second_Chance(int* input, int* frame, int input_size, int frame_size) {
	int point = 0;	// page-fault �� frame���� swap �� ��ȣ
	int* ref_bit = malloc(sizeof(int)*frame_size);// �� frame�� ���� ��Ʈ�� ����(0�� �� ����, 1�̸� 0���� �ٲٱ� ����)
	int position = 0;	// ref_bit �迭���� 0,1�� �˻��ϴ� ����
	int fault_size = 0;

	for (int i = 0; i < frame_size; i++)	// 0���� �ʱ�ȭ
		ref_bit[i] = 0;

	for (int i = 0; i < input_size; i++) {
		printf("\n");
		int page_fault = 1;
		printf("Number : %d", input[i]);

		for (int j = 0; j < frame_size; j++) {	// page fault�� �߻��ϴ��� Ȯ��
			if (input[i] == frame[j]) {
				ref_bit[j] = 1;	// frame�� ������Ʈ�� 1�� ����
				page_fault = 0;
				break;
			}
		}
		if (page_fault == 0)	continue;	// page_fault�� �Ͼ�� �ʾ����� ��� ����
		
		if (frame[frame_size - 1] != -1) {	// frame�� ����á�� ��
			int j = 0;	// j�� frame_size�� �ɶ����� �ݺ�
			while(frame_size + 1 > j){	// frame�� �ѹ��� ����.
				if (position == frame_size) position = 0;// position�� frame_size�� �������� frame�� ó������ Ȯ��
				if (ref_bit[position] == 0) {
					// ���� ��Ʈ�� 0�̸� ���� ���� page�� �ڸ��� point�� �ش� position���� �����Ѵ�.
					point = position;
					position++;	// ���� ������Ʈ �˻簡 �̷������� position �������� �˻��ϵ��� ������Ŵ.
					break;
				}
				else	// ������Ʈ�� 1�̸� 0���� �ٲ۴�.
					ref_bit[position] = 0;
				position++;	// frame�� ���� �ڸ��� �˻��ϱ����� ������Ŵ
				j++;
			}
		}

		frame[point] = input[i];	// page fault�� �߻����� �� frame�� �� �ٲ����
		ref_bit[point] = 1;	// ���� ���� frame�� ������Ʈ�� 1�� �ٲ۴�.
		
		if (frame[frame_size - 1] == -1) {
			point++;
		}

		for (int j = 0; j < frame_size; j++) { // frame ���
			printf("     %d", frame[j]);
		}
		fault_size++;
	}
	printf("\n");
	printf("page_fault : %d\n", fault_size);
	free(ref_bit);
}