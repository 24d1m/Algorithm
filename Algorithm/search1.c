#define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 30
#define MaxValue 1000

int compare(const void* arg1, const void* arg2);
int searchBinary(int arr[], int key);

int main() {
	//key = Ž���ϰ��� �ϴ� ������, idxKey = Ž�� ���� ��ġ
	int arr[SIZE] = {}, key, idxKey;

	//����
	qsort(arr, SIZE, sizeof(int), compare);


	idxKey = searchBinary(arr, key);  //����Ž��
	if (idxKey >= 0) {
		printf("%d��ġ�� %d�� �ֽ��ϴ�.\n", idxKey, key);
	}
	else {
		printf("ã���� �ϴ� �����Ͱ� �����ϴ�.\n");
	}

	return 0;
}

int compare(const void* arg1, const void* arg2) {
	if (*(int*)arg1 > *(int*)arg2) {
		return 1;
	}
	else {
		return -1;
	}
}

int searchBinary(int arr[], int key) {
	//idxKey = Ű�� �ε���, idxKey = Ž�� ���и� ����ϱ� ���� �ʱⰪ
	int idxStart = 0, idxMid, idxEnd = SIZE - 1, idxKey = -1;

	while (idxStart <= idxEnd) {
		//��� ��ġ�� ����
		idxMid = (idxStart + idxEnd) / 2;

		//��� ��ġ ���� Ű ���� �������� ����
		if (arr[idxMid == key]) {  //���ٸ� Ž�� ����, ��� ��ġ�� ��ȯ
			idxKey = idxMid;
			break;
		}
		else if (arr[idxMid] > key) {  //Ű�� ��� ������ �۴ٸ�
			idxEnd = idxMid - 1;
		}
		else {
			idxStart = idxMid + 1;
		}
	}
	return idxKey;
}