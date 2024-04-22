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
	//key = 탐색하고자 하는 데이터, idxKey = 탐색 값의 위치
	int arr[SIZE] = {}, key, idxKey;

	//정렬
	qsort(arr, SIZE, sizeof(int), compare);


	idxKey = searchBinary(arr, key);  //이진탐색
	if (idxKey >= 0) {
		printf("%d위치에 %d가 있습니다.\n", idxKey, key);
	}
	else {
		printf("찾고자 하는 데이터가 없습니다.\n");
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
	//idxKey = 키의 인덱스, idxKey = 탐색 실패를 대비하기 위한 초기값
	int idxStart = 0, idxMid, idxEnd = SIZE - 1, idxKey = -1;

	while (idxStart <= idxEnd) {
		//가운데 위치를 구함
		idxMid = (idxStart + idxEnd) / 2;

		//가운데 위치 값과 키 값이 같은지를 비교함
		if (arr[idxMid == key]) {  //같다면 탐색 종료, 가운데 위치를 반환
			idxKey = idxMid;
			break;
		}
		else if (arr[idxMid] > key) {  //키가 가운데 값보다 작다면
			idxEnd = idxMid - 1;
		}
		else {
			idxStart = idxMid + 1;
		}
	}
	return idxKey;
}