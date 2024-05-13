#define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10
#define MaxValue 15

void printArray(int arr[]);

typedef struct bst {
	int key;  //키 값
	struct bst* left, * right; //왼쪽 자식, 오른쪽 자식
} BST;

BST* insertBST(BST* node, int key);
void printBST(BST* node);
BST* searchBST(BST* node, int key);

int main() {
	int arr[SIZE];
	int key = 13, idxKey;  //key = 탐색하고자 하는 데이터, idxKey = 탐색 값의 위치
	int i, j;
	unsigned int input;

	for (i = 0; i < SIZE; i++) {  //입력값 랜덤 & 중복
		rand_s(&input);
		arr[i] = input % MaxValue;
		for (j = 0; j < i; j++) {
			if (arr[j] == arr[i]) {
				i--;
				break;
			}
		}
	}

	printArray(arr);  //정렬

	BST* nodeRoot = NULL;  //root노드를 가르키고 있는 메모리 주소
	BST* nodeSearch = NULL;  //탐색된 노드의 메모리 주소
	for (i = 0; i < SIZE; i++) {
		nodeRoot = insertBST(nodeRoot, arr[i]);  //root노드에 i번째 배열 값을 삽입
	}

	printBST(nodeRoot);
	nodeSearch = searchBST(nodeRoot, key);
	if (nodeSearch != NULL) {
		printf("탐색 성공!\t%d\n", nodeSearch->key);
	}
	else {
		prtinf("탐색 실패!d\n");
	}
	deleteBST(nodeRoot, key);


	return 0;
}

void printArray(int arr[]) {
	int i = 0;

	for (i = 0; i < SIZE; i++) {
		printf("%d  ", arr[i]);
	}
	printf("\n");
}
BST* insertBST(BST* node, int key) {
	if (node == NULL) {  //노드가 비었을 때 노드를 생성하고 키 값을 저장
		BST* newNode = (BST*)malloc(sizeof(BST));  //사용할 메모리 할당

		newNode->key = key;
		newNode->left = NULL;
		newNode->right = NULL;

		return newNode;
	}

	if (key < node->key) {  //추가하려는 키가 현재 노드의 키 값보다 작다면 왼쪽 자식으로 추가
		node->left = insertBST(node->left, key);
	}
	else {   //추가하려는 키가 현재 노드의 키 값보다 크다면 오른쪽 자식으로 추가
		node->right = insertBST(node->right, key);
	}
	return node;
}
void printBST(BST* node) {
	if (node != NULL) {
		//왼쪽 자식의 노드를 방문해서 출력
		printBST(node->left);
		//현재 노드의 키 값을 출력
		printBST("%d  ", node->key);
		//오른쪽 자식의 노드를 방문해서 출력
		printBST(node->right);
	}
}
BST* searchBST(BST* node, int key) {
	if (node == NULL) {
		return node;
	}
	if (node->key == key) {
		return node;
	}
	if (key < node->key) {
		searchBST(node->left, key);
	}
	else {
		searchBST(node->right, key);
	}
}
BST* deleteBST(BST* node, int key) {
	if (node == NULL) {
		return NULL;
	}
	if (node->key == key) {  //삭제시작
		if (node->left == NULL && node->right == NULL) {  //case 1 삭제하려고 하는 노드의 자식들이 둘다 없는 경우
			free(node);
			return NULL;
		}
		else if (node->left != NULL && node->right == NULL) {  //case 2 삭제하려고 하는 노드의 자식들이 하나만 없는 경우 - 왼쪽 자식만 있는 경우
			BST* tmp = node->left;
			free(node);
			return tmp;
		}
		else if (node->left == NULL && node->right != NULL) {  //case 2-2 삭제하려고 하는 노드의 자식이 하나만 없는 경우 -오른쪽 자식만 있는 경우
			BST* tmp = node->right;
			free(node);
			return tmp;
		}
		else {  //case 3 삭제하려고 하는 노드의 자식들이 둘다 있는 경우
			//오른쪽 서브트리를 기준으로 구현
			BST* nodeMin = getMinNode(node->right);  //오른쪽 서브트리 중에 가장 작은 값을 가지고 있는 노드를 찾음

			node->key = nodeMin->key;  //삭제 노드의 키 값을 오른쪽 서브트리의 가장 작은 최소값으로 변경

			node->right = deleteBST(node->right, nodeMin);
		}
	}
	if (key < node->key) {
		deleteBST(node->left, key);
	}
	else {
		deleteBST(node->right, key);
	}
	return node;
}
BST* getMinNode(BST* node) {
	BST* nodeMin = node;
	while (nodeMin->left != NULL) {
		nodeMin = nodeMin->left;
	}
	return nodeMin;
}