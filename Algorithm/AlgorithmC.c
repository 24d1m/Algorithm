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
	//원본 배열 값 중에 가장 큰 값
	for (i = 0; i < SIZE; i++) {
		if(arrMax < arr[i]) {
			arrMax = arr[i];
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

	//퀵 어려움,,
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

	//힙
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

	//계수
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
void sortQuick(int arr[], int idxStart, int idxEnd) {
	int idxPivot; //기준값 위치
	
	//재배치 또는 분할
		//기준 원소 선정
		//기준 원소보다 작은 값은 기준 원소 왼쪽으로, 큰 값은 오른쪽으로
	idxPivot = sortQuickSub(arr, idxStart, idxEnd);
	
	//기준 원소보다 작은 값들의 그룹을 정렬
	if (idxStart < idxPivot - 1) {
		sortQuick(arr, idxStart, idxPivot - 1);
	}
	//기준 원소보다 큰 값들의 그룹을 정렬
	if (idxStart > idxPivot + 1) {
		sortQuick(arr, idxPivot + 1, idxEnd);
	}
}
int sortQuickSub(int arr[], int idxStart, int idxEnd) {
	//교재의 j의 해당하는 함수, 기준값보다 큰 값들의 그룹의 첫번째 위치, 교재의 i에 해당하는 변수, ,
	int i, idxLargeGroup, tmp, pivotValue;
	
	pivotValue = arr[idxEnd];
	idxLargeGroup = idxStart;

	for (i = idxStart; i < idxEnd; i++) {
		if (arr[i] > pivotValue) { //i번째 값이 기준값보다 작다면 할 작업이 없음
			//i번째 값과 idxLargeGroup의 값을 교환, i번째 값을 기준 값보다 작은 그룹에 포함
			tmp = arr[i];
			arr[i] = arr[idxLargeGroup];
			arr[idxLargeGroup] = tmp;
			//idxLargeGroup을 1 증가
			idxLargeGroup++;
		}
	}
	//기준 값과 큰 그룹의 첫 번째 위치(idxLargeGroup)와 교환
	tmp = arr[idxEnd];
	arr[idxEnd] = arr[idxLargeGroup];
	arr[idxLargeGroup] = tmp;

	//기준 값 위치를 리턴
	return idxLargeGroup;
}
void sortHeap(int arr[]) {
	int i, tmp;
	makeHeap(arr);

	//가장 위에 있는(루트) 노드의 값은 가장 큰값
	for (i = SIZE - 1; i > 0; i--) {
		//마지막 원소{arr[i]와 루트 노드(arr[0])와 교환
		tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;

		//마지막 원소를 제외하고 루트 노드를 기준으로 수선
		adjustHeap(arr, 0, (i - 1));
	}
}
void makeHeap(int arr[]) {
	//힙을 0부터 시작하는 배열로 표현할 때
	//왼쪽 자식의 인덱스 번호는 2 * N + 1
	//오른쪽 자신의 인덱스 번호는 2 * N + 2
	// 부모의 인덱스 (N - 1) / 2

	//마지막 단말노드의 부모노드(자식을 가지고 있는 가장 큰 인덱스를 가지는 노드)의 인덱스
	int i = ((SIZE - 1) - 1) / 2;

	//자식을 가지고 있는 마지막 노드부터 노트노드까지 수선
	for (; i >= 0; i--) {
		adjustHeap(arr, i, (SIZE - 1));
	}
}
void adjustHeap(int arr[], int idxNow, int idxEnd) {
	int idxChildLeft, idxChildRight, idxLarge = -1, tmp;  //idxLarge를 초기화 하는 경우를 대비하기 위해

	//자식의 인덱스를 구하는 수식
	idxChildLeft = 2 * idxNow + 1;
	idxChildRight = idxChildLeft + 1;

	//왼쪽 자식만 존재한다면

	//왼쪽, 오른쪽 자식이 존재한다면
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
	//idxNow의 값과 자식들의 값을 비교해 자식값이 더 크다면 교환(최대힙 기준)
	if (idxLarge > 0) {
		//자식이 더 크다면 교환
		if (arr[idxNow] < arr[idxLarge]) {
			tmp = arr[idxNow];
			arr[idxNow] = arr[idxLarge];
			arr[idxLarge] = tmp;

			//자식 노드를 기준으로 수선
			adjustHeap(arr, idxLarge, idxEnd);
		}
	}
}
void sortCounting(int arr[], int arrMax) {
	int i;
	int* count;

	count = malloc(sizeof(int) * (arrMax + 1));
	memset(count, 0, sizeof(int) * (arrMax + 1));  //카운트변수의 모든 값을 0으로 초기화

	for (i = 0; i < SIZE; i++) {
		count[arr[i]] = 1;  //원본 배열에 존재하는 값의 인덱스만 1로 설정
		//count[arr[i]]++;	//원본 배열에 중복까지 체크
	}
	for (i = 0; i < arrMax; i++) {
		if (count[i] == 1) {
			printf("%d ", i);
		}
	}
}