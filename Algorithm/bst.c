#define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100
#define MaxValue 1000

void printArray(int arr[]);

typedef struct bst {
	int key;  //키 값
	struct bst* left, * right; //왼쪽 자식, 오른쪽 자식
} BST;

int main() {
	BST* node;  //root노드를 가르키고 있는 메모리 주소
	int arr[SIZE];
	int key, idxKey;  //key = 탐색하고자 하는 데이터, idxKey = 탐색 값의 위치
	int i, j;
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

	for (i = 0; i < SIZE; i++) {
		insertBST(node, arr[i]);  //root노드에 i번째 배열 값을 삽입
	}

	//정렬
	printArray(arr);

	return 0;
}

void printArray(int arr[]) {
	int i = 0;

	for (i = 0; i < SIZE; i++) {
		printf("%d  ", arr[i]);
	}
	printf("\n");
}
insertBST(BST* node, int key) {
	if (node == NULL) {  //노드가 비었을 때 노드를 생성하고 키 값을 저장
		BST* newNode = (BST*)malloc(sizeof(BST));  //사용할 메모리 할당

		newNode->key = key;
		newNode->left = NULL;
		newNode->right = NULL;
	}

	if (key < node->key) {  //추가하려는 키가 현재 노드의 키 값보다 작다면 왼쪽 자식으로 추가
		insertBST(node->left, key);
	}
	else {   //추가하려는 키가 현재 노드의 키 값보다 크다면 오른쪽 자식으로 추가
		insertBST(node->right, key);
	}
}