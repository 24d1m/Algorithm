#define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 30
#define MaxValue 100


void printArray(int arr[]);
void sortSelection(int arr[]);
void sortInsert(int arr[]);

int main() {
	int arr[SIZE] = { 0 };
	int arrTmp[SIZE] = { 0 };
	int i, j;
	float executeTime;
	time_t startTime, endTime;
	unsigned int input;

	printf("test555");

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
	printf("$$$ Selecetion  $$$\nBefore: ");
	printArray(arr);
	startTime = clock();
	sortSelection(arr);
	endTime = clock();
	executeTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	printf("After: ");
	printArray(arr);
	printf("Execute time: %f\n", executeTime);

	//삽입
	memcpy(arr, arrTmp, (sizeof(int) * SIZE));
	printf("\n\n$$$ Insert  $$$\nBefore: ");
	printArray(arr);
	startTime = clock();
	sortInsert(arr);
	endTime = clock();
	executeTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	printf("After: ");
	printArray(arr);
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

	for (i = 0; i < SIZE - 1; i++) {	// n번째 최소값을 찾는 반복
		idxMin = i;	// n번째 최소값을 첫번째 원소값으로 가정
		for (j = i + 1; j < SIZE; j++) {	// n번째 단계의 최소값을 찾는 반복
			if (arr[idxMin] > arr[j]) {	// j번째 값이 지금까지 알고 있는 최소값보다 더 작다면
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