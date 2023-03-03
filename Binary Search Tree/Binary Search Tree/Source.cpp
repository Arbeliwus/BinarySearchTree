#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>`
#include<stdlib.h>
#include <string.h>
#define MAX 1000
struct BST//binary search tree
{
	char word[50];
	int count;
	BST* left;
	BST* right;
};
BST* insertleaf(BST*, char*);//���J���l
void inorder(BST*);//���Ǩ��X
int TreeHight(BST*);//��
bool freeTree(BST*);//����G����(Postfix)
int wordcount = 0;//��r�p��
int freecount = 0;
void main()
{
	FILE* fptr = fopen("DesignPattern.txt", "r");
	char temp[MAX];
	BST* root = NULL;
	while (fgets(temp, MAX, fptr))
	{
		char*cutted = strtok(temp, " (,;:\".?)\n\t");
		while (cutted)
		{
			root = insertleaf(root, cutted);
			cutted = strtok(NULL, " (,;: \".?)\t\n");
		}
	}
	fclose(fptr);
	inorder(root);
	printf("All Node:%d\n", wordcount);
	printf("Tree High:%d\n", TreeHight(root));
	freeTree(root);
	printf("free:%d", freecount);

}
BST* insertleaf(BST* root, char* data)
{
	if (root == NULL)//���j�פ����
	{
		root = (BST*)malloc(sizeof(BST));
		strcpy(root->word, data);
		root->right = root->left = NULL;
		root->count = 1;
	}
	else if (strcmp(root->word, data) == 0)//�M��ڬۦP
		root->count++;
	else if (strcmp(root->word, data) > 0)//���ڤj
		root->left = insertleaf(root->left, data);
	else//���ڤp
		root->right = insertleaf(root->right, data);
	return root;
}
void inorder(BST*root)
{
	if (root)//���j�פ����
	{
		inorder(root->left);//�V����V�p
		printf("%-10d %-20s %-d \n", ++wordcount, root->word, root->count);//��ڬ�������
		inorder(root->right);//�V�k��V�j
	}
}
int TreeHight(BST* root)
{
	if (!root) return 0;//���j�פ����
	int left = (!(root->left)) ? 0 : TreeHight(root->left);
	int right = (!(root->right)) ? 0 : TreeHight(root->right);
	int hight = left > right ? left : right;//�𸭬�0:0
	return hight + 1;
}
bool freeTree(BST* root)
{
	if (!root) return 0;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
	freecount++;
}