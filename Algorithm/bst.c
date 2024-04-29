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
	int key;  //Ű ��
	struct bst* left, * right; //���� �ڽ�, ������ �ڽ�
} BST;

int main() {
	BST* node;  //root��带 ����Ű�� �ִ� �޸� �ּ�
	int arr[SIZE];
	int key, idxKey;  //key = Ž���ϰ��� �ϴ� ������, idxKey = Ž�� ���� ��ġ
	int i, j;
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

	for (i = 0; i < SIZE; i++) {
		insertBST(node, arr[i]);  //root��忡 i��° �迭 ���� ����
	}

	//����
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
	if (node == NULL) {  //��尡 ����� �� ��带 �����ϰ� Ű ���� ����
		BST* newNode = (BST*)malloc(sizeof(BST));  //����� �޸� �Ҵ�

		newNode->key = key;
		newNode->left = NULL;
		newNode->right = NULL;
	}

	if (key < node->key) {  //�߰��Ϸ��� Ű�� ���� ����� Ű ������ �۴ٸ� ���� �ڽ����� �߰�
		insertBST(node->left, key);
	}
	else {   //�߰��Ϸ��� Ű�� ���� ����� Ű ������ ũ�ٸ� ������ �ڽ����� �߰�
		insertBST(node->right, key);
	}
}