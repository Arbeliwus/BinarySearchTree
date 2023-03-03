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
BST* insertleaf(BST*, char*);//插入葉子
void inorder(BST*);//中序走訪
int TreeHight(BST*);//樹高
bool freeTree(BST*);//釋放二元樹(Postfix)
int wordcount = 0;//單字計算
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
	if (root == NULL)//遞迴終止條件
	{
		root = (BST*)malloc(sizeof(BST));
		strcpy(root->word, data);
		root->right = root->left = NULL;
		root->count = 1;
	}
	else if (strcmp(root->word, data) == 0)//和樹根相同
		root->count++;
	else if (strcmp(root->word, data) > 0)//比樹根大
		root->left = insertleaf(root->left, data);
	else//比樹根小
		root->right = insertleaf(root->right, data);
	return root;
}
void inorder(BST*root)
{
	if (root)//遞迴終止條件
	{
		inorder(root->left);//越左邊越小
		printf("%-10d %-20s %-d \n", ++wordcount, root->word, root->count);//樹根為中間值
		inorder(root->right);//越右邊越大
	}
}
int TreeHight(BST* root)
{
	if (!root) return 0;//遞迴終止條件
	int left = (!(root->left)) ? 0 : TreeHight(root->left);
	int right = (!(root->right)) ? 0 : TreeHight(root->right);
	int hight = left > right ? left : right;//樹葉為0:0
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