#define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 30
#define MaxValue 1000

void printArray(int arr[]);
void sortSelection(int arr[]);
void sortInsert(int arr[]);
void sortMerge(int arr[], int idxStart, int idxEnd);
void sortMergeSub(int arr[], int idxStart, int idxMid, int idxEnd);
void sortQuick(int arr[], int idxStart, int idxEnd);
int sortQuickSub(int arr[], int idxStart, int idxEnd);
void sortHeap(int arr[]);
void makeHeap(int arr[]);
void adjustHeap(int arr[], int idxNow, int idxEnd);
void sortCounting(int arr[], int arrMax);

int main() {
	int arr[SIZE] = { 0 }, arrTmp[SIZE] = { 0 };
	int arrMax = -1;
	int i, j;
	unsigned int input;
	float executeTime;
	time_t startTime, endTime;

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
	//���� �迭 �� �߿� ���� ū ��
	for (i = 0; i < SIZE; i++) {
		if(arrMax < arr[i]) {
			arrMax = arr[i];
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

	//�� �����,,
	memcpy(arr, arrTmp, (sizeof(int) * SIZE));
	printf("\n\n$$$ Quick  $$$\n");
	//printf("Before: ");
	//printArray(arr);
	startTime = clock();
	sortQuick(arr, 0, SIZE);
	endTime = clock();
	executeTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	//printf("After: ");
	//printArray(arr);
	printf("Execute time: %f\n", executeTime);

	//��
	memcpy(arr, arrTmp, (sizeof(int) * SIZE));
	printf("\n\n$$$ Heap  $$$\n");
	//printf("Before: ");
	//printArray(arr);
	startTime = clock();
	sortHeap(arr);
	endTime = clock();
	executeTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	//printf("After: ");
	//printArray(arr);
	printf("Execute time: %f\n", executeTime);

	//���
	memcpy(arr, arrTmp, (sizeof(int) * SIZE));
	printf("\n\n$$$ Counting $$$\n");
	//printf("Before: ");
	//printArray(arr);
	startTime = clock();
	sortCounting(arr, arrMax);
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
	int i, j;
	int idxMin, tmp;

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
void sortQuick(int arr[], int idxStart, int idxEnd) {
	int idxPivot; //���ذ� ��ġ
	
	//���ġ �Ǵ� ����
		//���� ���� ����
		//���� ���Һ��� ���� ���� ���� ���� ��������, ū ���� ����������
	idxPivot = sortQuickSub(arr, idxStart, idxEnd);
	
	//���� ���Һ��� ���� ������ �׷��� ����
	if (idxStart < idxPivot - 1) {
		sortQuick(arr, idxStart, idxPivot - 1);
	}
	//���� ���Һ��� ū ������ �׷��� ����
	if (idxStart > idxPivot + 1) {
		sortQuick(arr, idxPivot + 1, idxEnd);
	}
}
int sortQuickSub(int arr[], int idxStart, int idxEnd) {
	//������ j�� �ش��ϴ� �Լ�, ���ذ����� ū ������ �׷��� ù��° ��ġ, ������ i�� �ش��ϴ� ����, ,
	int i, idxLargeGroup, tmp, pivotValue;
	
	pivotValue = arr[idxEnd];
	idxLargeGroup = idxStart;

	for (i = idxStart; i < idxEnd; i++) {
		if (arr[i] > pivotValue) { //i��° ���� ���ذ����� �۴ٸ� �� �۾��� ����
			//i��° ���� idxLargeGroup�� ���� ��ȯ, i��° ���� ���� ������ ���� �׷쿡 ����
			tmp = arr[i];
			arr[i] = arr[idxLargeGroup];
			arr[idxLargeGroup] = tmp;
			//idxLargeGroup�� 1 ����
			idxLargeGroup++;
		}
	}
	//���� ���� ū �׷��� ù ��° ��ġ(idxLargeGroup)�� ��ȯ
	tmp = arr[idxEnd];
	arr[idxEnd] = arr[idxLargeGroup];
	arr[idxLargeGroup] = tmp;

	//���� �� ��ġ�� ����
	return idxLargeGroup;
}
void sortHeap(int arr[]) {
	int i, tmp;
	makeHeap(arr);

	//���� ���� �ִ�(��Ʈ) ����� ���� ���� ū��
	for (i = SIZE - 1; i > 0; i--) {
		//������ ����{arr[i]�� ��Ʈ ���(arr[0])�� ��ȯ
		tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;

		//������ ���Ҹ� �����ϰ� ��Ʈ ��带 �������� ����
		adjustHeap(arr, 0, (i - 1));
	}
}
void makeHeap(int arr[]) {
	//���� 0���� �����ϴ� �迭�� ǥ���� ��
	//���� �ڽ��� �ε��� ��ȣ�� 2 * N + 1
	//������ �ڽ��� �ε��� ��ȣ�� 2 * N + 2
	// �θ��� �ε��� (N - 1) / 2

	//������ �ܸ������ �θ���(�ڽ��� ������ �ִ� ���� ū �ε����� ������ ���)�� �ε���
	int i = ((SIZE - 1) - 1) / 2;

	//�ڽ��� ������ �ִ� ������ ������ ��Ʈ������ ����
	for (; i >= 0; i--) {
		adjustHeap(arr, i, (SIZE - 1));
	}
}
void adjustHeap(int arr[], int idxNow, int idxEnd) {
	int idxChildLeft, idxChildRight, idxLarge = -1, tmp;  //idxLarge�� �ʱ�ȭ �ϴ� ��츦 ����ϱ� ����

	//�ڽ��� �ε����� ���ϴ� ����
	idxChildLeft = 2 * idxNow + 1;
	idxChildRight = idxChildLeft + 1;

	//���� �ڽĸ� �����Ѵٸ�

	//����, ������ �ڽ��� �����Ѵٸ�
	if (idxChildRight <= idxEnd) {
		if (arr[idxChildLeft] > arr[idxChildRight]) {
			idxLarge = idxChildLeft;
		}
		else {
			idxLarge = idxChildRight;
		}
	}
	else if (idxChildLeft <= idxEnd) {
		idxLarge = idxChildLeft;
	}
	//idxNow�� ���� �ڽĵ��� ���� ���� �ڽİ��� �� ũ�ٸ� ��ȯ(�ִ��� ����)
	if (idxLarge > 0) {
		//�ڽ��� �� ũ�ٸ� ��ȯ
		if (arr[idxNow] < arr[idxLarge]) {
			tmp = arr[idxNow];
			arr[idxNow] = arr[idxLarge];
			arr[idxLarge] = tmp;

			//�ڽ� ��带 �������� ����
			adjustHeap(arr, idxLarge, idxEnd);
		}
	}
}
void sortCounting(int arr[], int arrMax) {
	int i;
	int* count;

	count = malloc(sizeof(int) * (arrMax + 1));
	memset(count, 0, sizeof(int) * (arrMax + 1));  //ī��Ʈ������ ��� ���� 0���� �ʱ�ȭ

	for (i = 0; i < SIZE; i++) {
		count[arr[i]] = 1;  //���� �迭�� �����ϴ� ���� �ε����� 1�� ����
		//count[arr[i]]++;	//���� �迭�� �ߺ����� üũ
	}
	for (i = 0; i < arrMax; i++) {
		if (count[i] == 1) {
			printf("%d ", i);
		}
	}
}