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

	//입력값 랜덤 & 중복
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

	//arr배열을 arrTmp에 복사
	memcpy(arrTmp, arr, (sizeof(int) * SIZE));

	//선택
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

	//삽입
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

	//병합
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

	for (i = 0; i < SIZE - 1; i++) {  // n번째 최소값을 찾는 반복
		idxMin = i;  // n번째 최소값을 첫번째 원소값으로 가정
		for (j = i + 1; j < SIZE; j++) {  // n번째 단계의 최소값을 찾는 반복
			if (arr[idxMin] > arr[j]) {  // j번째 값이 지금까지 알고 있는 최소값보다 더 작다면
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
	int idxMid = ((idxStart + idxEnd) / 2);  //전반부와 후반부 배열 구분하는 가운데 위치

	if (idxStart < idxEnd) {
		sortMerge(arr, idxStart, idxMid);  //전반부 배열 정렬(분홍)
		sortMerge(arr, idxMid + 1, idxEnd);  //후반부 배열 정렬(하늘)
		sortMergeSub(arr, idxStart, idxMid, idxEnd);  //전반부와 후반부 배열을 병합하는
	}

	
}
void sortMergeSub(int arr[], int idxStart, int idxMid, int idxEnd) {
	int i, j, k = 0;;  //i: 전반부 배열의 현재 위치, j: 후반부 배열의 현재 위치
	int* tmp = (int*)malloc(sizeof(int) * (idxEnd - idxStart + 1));  //복사할 새로운 공간 생성(사이즈 = idxEnd - idxStart + 1)

	//전반부와 후반부 배열의 현재 위치 값을 비교하여 더 작은 값을 새로운 공간에 복사
	//각 배열의 현재 위치를 첫번째 위치로 설정
	i = idxStart;
	j = idxMid + 1;

	//전반부 끝까지 탐색하거나 후반부 끝까지 탐색할 동안에만
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