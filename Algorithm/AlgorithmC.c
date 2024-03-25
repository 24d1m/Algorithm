#define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 50000
#define MaxValue 100000


void printArray(int arr[]);
void sortSelection(int arr[]);
void sortInsert(int arr[]);
void sortMerge(int arr[], int idxStart, int idxEnd);
void sortMergeSub(int arr[], int idxStart, int idxMid, int idxEnd);

int main() {
	int arr[SIZE] = { 0 };
	int arrTmp[SIZE] = { 0 };
	int i, j;
	float executeTime;
	time_t startTime, endTime;
	unsigned int input;

	//�Է°� ���� & �ߺ�
	for (i = 0; i < SIZE; i++) {
		rand_s(&input);
		arr[i] = input % MaxValue;
		for (j = 0; j < i; j++) {
			if (arr[i] == arr[j]) {
				i--;
				break;
			}
		}
	}

	//arr�迭�� arrTmp�� ����
	memcpy(arrTmp, arr, (sizeof(int) * SIZE));

	//����
	printf("$$$ Selecetion  $$$\n");
	//printf("Before: ");
	//printArray(arr);
	startTime = clock();
	sortSelection(arr);
	endTime = clock();
	executeTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	//printf("After: ");
	//printArray(arr);
	printf("Execute time: %f\n", executeTime);

	//����
	memcpy(arr, arrTmp, (sizeof(int) * SIZE));
	printf("\n\n$$$ Insert  $$$\n");
	//printf("Before: ");
	//printArray(arr);
	startTime = clock();
	sortInsert(arr);
	endTime = clock();
	executeTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	//printf("After: ");
	//printArray(arr);
	printf("Execute time: %f\n", executeTime);

	//����
	memcpy(arr, arrTmp, (sizeof(int) * SIZE));
	printf("\n\n$$$ Merge  $$$\n");
	//printf("Before: ");
	//printArray(arr);
	startTime = clock();
	sortMerge(arr, 0, SIZE - 1);
	endTime = clock();
	executeTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	//printf("After: ");
	//printArray(arr);
	printf("Execute time: %f\n", executeTime);

	return 0;
}

void printArray(int arr[]) {
	int i = 0;
	for (i = 0; i < SIZE; i++) {
		printf("%d  ", arr[i]);
	}
	printf("\n");
}
void sortSelection(int arr[]) {
	int i, j, idxMin, tmp;

	for (i = 0; i < SIZE - 1; i++) {  // n��° �ּҰ��� ã�� �ݺ�
		idxMin = i;  // n��° �ּҰ��� ù��° ���Ұ����� ����
		for (j = i + 1; j < SIZE; j++) {  // n��° �ܰ��� �ּҰ��� ã�� �ݺ�
			if (arr[idxMin] > arr[j]) {  // j��° ���� ���ݱ��� �˰� �ִ� �ּҰ����� �� �۴ٸ�
				idxMin = j;
			}
			tmp = arr[i];
			arr[i] = arr[idxMin];
			arr[idxMin] = tmp;
		}
	}
}
void sortInsert(int arr[]) {
	int i, j, k, tmp;

	for (i = 1; i < SIZE; i++) {
		for (j = 0; j < i; j++) {
			if (arr[i] < arr[j]) {
				tmp = arr[i];
				for (k = i; k > j; k--) {
					arr[k] = arr[k - 1];
				}
				arr[j] = tmp;
				break;
			}
		}
	}
}
void sortMerge(int arr[], int idxStart, int idxEnd) {
	int idxMid = ((idxStart + idxEnd) / 2);  //���ݺο� �Ĺݺ� �迭 �����ϴ� ��� ��ġ

	if (idxStart < idxEnd) {
		sortMerge(arr, idxStart, idxMid);  //���ݺ� �迭 ����(��ȫ)
		sortMerge(arr, idxMid + 1, idxEnd);  //�Ĺݺ� �迭 ����(�ϴ�)
		sortMergeSub(arr, idxStart, idxMid, idxEnd);  //���ݺο� �Ĺݺ� �迭�� �����ϴ�
	}

	
}
void sortMergeSub(int arr[], int idxStart, int idxMid, int idxEnd) {
	int i, j, k = 0;;  //i: ���ݺ� �迭�� ���� ��ġ, j: �Ĺݺ� �迭�� ���� ��ġ
	int* tmp = (int*)malloc(sizeof(int) * (idxEnd - idxStart + 1));  //������ ���ο� ���� ����(������ = idxEnd - idxStart + 1)

	//���ݺο� �Ĺݺ� �迭�� ���� ��ġ ���� ���Ͽ� �� ���� ���� ���ο� ������ ����
	//�� �迭�� ���� ��ġ�� ù��° ��ġ�� ����
	i = idxStart;
	j = idxMid + 1;

	//���ݺ� ������ Ž���ϰų� �Ĺݺ� ������ Ž���� ���ȿ���
	for (; i < idxMid && j < idxEnd;) {
		if (arr[i] > arr[j])
			tmp[k++] = arr[j++];
		else
			tmp[k++] = arr[i++];
	}

	while (i <= idxMid) {
		tmp[k++] = arr[i++];
	}
	while (j <= idxEnd) {
		tmp[k++] = arr[j++];
	}

	memcpy(arr+idxStart, tmp, sizeof(int) * (idxEnd - idxStart + 1));
	free(tmp);
}