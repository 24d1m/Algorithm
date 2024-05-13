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
	int key;  //Ű ��
	struct bst* left, * right; //���� �ڽ�, ������ �ڽ�
} BST;

BST* insertBST(BST* node, int key);
void printBST(BST* node);
BST* searchBST(BST* node, int key);

int main() {
	int arr[SIZE];
	int key = 13, idxKey;  //key = Ž���ϰ��� �ϴ� ������, idxKey = Ž�� ���� ��ġ
	int i, j;
	unsigned int input;

	for (i = 0; i < SIZE; i++) {  //�Է°� ���� & �ߺ�
		rand_s(&input);
		arr[i] = input % MaxValue;
		for (j = 0; j < i; j++) {
			if (arr[j] == arr[i]) {
				i--;
				break;
			}
		}
	}

	printArray(arr);  //����

	BST* nodeRoot = NULL;  //root��带 ����Ű�� �ִ� �޸� �ּ�
	BST* nodeSearch = NULL;  //Ž���� ����� �޸� �ּ�
	for (i = 0; i < SIZE; i++) {
		nodeRoot = insertBST(nodeRoot, arr[i]);  //root��忡 i��° �迭 ���� ����
	}

	printBST(nodeRoot);
	nodeSearch = searchBST(nodeRoot, key);
	if (nodeSearch != NULL) {
		printf("Ž�� ����!\t%d\n", nodeSearch->key);
	}
	else {
		prtinf("Ž�� ����!d\n");
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
	if (node == NULL) {  //��尡 ����� �� ��带 �����ϰ� Ű ���� ����
		BST* newNode = (BST*)malloc(sizeof(BST));  //����� �޸� �Ҵ�

		newNode->key = key;
		newNode->left = NULL;
		newNode->right = NULL;

		return newNode;
	}

	if (key < node->key) {  //�߰��Ϸ��� Ű�� ���� ����� Ű ������ �۴ٸ� ���� �ڽ����� �߰�
		node->left = insertBST(node->left, key);
	}
	else {   //�߰��Ϸ��� Ű�� ���� ����� Ű ������ ũ�ٸ� ������ �ڽ����� �߰�
		node->right = insertBST(node->right, key);
	}
	return node;
}
void printBST(BST* node) {
	if (node != NULL) {
		//���� �ڽ��� ��带 �湮�ؼ� ���
		printBST(node->left);
		//���� ����� Ű ���� ���
		printBST("%d  ", node->key);
		//������ �ڽ��� ��带 �湮�ؼ� ���
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
	if (node->key == key) {  //��������
		if (node->left == NULL && node->right == NULL) {  //case 1 �����Ϸ��� �ϴ� ����� �ڽĵ��� �Ѵ� ���� ���
			free(node);
			return NULL;
		}
		else if (node->left != NULL && node->right == NULL) {  //case 2 �����Ϸ��� �ϴ� ����� �ڽĵ��� �ϳ��� ���� ��� - ���� �ڽĸ� �ִ� ���
			BST* tmp = node->left;
			free(node);
			return tmp;
		}
		else if (node->left == NULL && node->right != NULL) {  //case 2-2 �����Ϸ��� �ϴ� ����� �ڽ��� �ϳ��� ���� ��� -������ �ڽĸ� �ִ� ���
			BST* tmp = node->right;
			free(node);
			return tmp;
		}
		else {  //case 3 �����Ϸ��� �ϴ� ����� �ڽĵ��� �Ѵ� �ִ� ���
			//������ ����Ʈ���� �������� ����
			BST* nodeMin = getMinNode(node->right);  //������ ����Ʈ�� �߿� ���� ���� ���� ������ �ִ� ��带 ã��

			node->key = nodeMin->key;  //���� ����� Ű ���� ������ ����Ʈ���� ���� ���� �ּҰ����� ����

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