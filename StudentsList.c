#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define LEN 25

struct Node {
	char name[LEN];
	int age;
	struct Node *next;
};
typedef struct Node SNode;
typedef struct Node *SList;

void Insert(SList *L);
void Delete(SList *L,char a[]);
void Merge(SList *L1, SList *L2);
void ReadLine(char *a, int n);
void ShowList(SList L);

int main(void)
{
	int i,n;
	char a[LEN];
	SList L1 = (SList)malloc(sizeof(SNode));
	L1->next = NULL;
	SList L2 = (SList)malloc(sizeof(SNode));
	L2->next = NULL;
	for (;;) {
		printf("选择操作对象（1.表1 2.表2 3.合并）：");
		scanf_s("%d", &n);
		if (n == 1) {
			printf("\n输入你的选择（1.插入2.删除3.合并）：");
			scanf_s("%d", &i);
			switch (i) {
			case 1:
				Insert(&L1);
				ShowList(L1);
				break;
			case 2:
				printf("输入要删除的学生学号：");
				ReadLine(a, LEN);
				Delete(&L1, a);
				ShowList(L1);
				break;
			default:
				printf("输入操作不合法！");
				break;
			}
		}
		else if (n == 2) {
			printf("\n输入你的选择（1.插入2.删除3.合并）：");
			scanf_s("%d", &i);
			switch (i) {
			case 1:
				Insert(&L2);
				ShowList(L2);
				break;
			case 2:
				printf("输入要删除的学生学号：");
				ReadLine(a, LEN);
				Delete(&L2, a);
				ShowList(L2);
				break;
			default:
				printf("输入操作不合法！");
				break;
			}
		}
		else if (n == 3) {
			Merge(&L1, &L2);
			ShowList(L1);
			system("pause");
			return 0;
		}
		else {
			printf("输入值不合法！");
			exit(0);
		}
	}
	return 0;
}


void Insert(SList *L)
{
	SNode *p = (SNode *)malloc(sizeof(SNode));
	SNode *q = (*L)->next;
	SNode *pre = *L;
	if (p == NULL) {
		printf("ERROR:no space...");
		exit(0);
	}
	printf("PLS enter the name:");
	ReadLine(p->name, LEN);
	for (;q!=NULL;) {
		if (strcmp(q->name, p->name) == 0) {
			printf("ERROR:repeated name...");
			exit(0);
		}
		q = q->next;
	}
	printf("PLS enter the age:");
	scanf_s("%d", &p->age);

	q = (*L)->next;
	for (;q != NULL&&p->age < q->age;) {
		pre = q;
		q = q->next;
		}
	p->next = q;
	pre->next = p;
	
}

void Delete(SList *L,char a[])
{
	SNode *p = (*L)->next;
	SNode *pre = (*L);
	for (;p != NULL;) {
		if (strcmp(p->name, a) == 0)
			break;
		pre = p;
		p = p->next;
	}
	if (p == NULL) {
		printf("ERROR:fail to find the name...");
		exit(0);
	}
	else {
		pre->next = p->next;
		free(p);
	}
}

void Merge(SList *L1, SList *L2)
{
	SNode *pa = (*L1)->next;
	SNode *pb = (*L2)->next;
	SList pc = (*L1);
	while (pa != NULL&&pb != NULL) {
		if (pa->age > pb->age) {
			pc->next = pa;
			pa = pa->next;
			pc = pc->next;
		}
		else if (pa->age == pb->age) {
			pc->next = pa;
			pa->next = pb;
			pa = pa->next;
			pb = pb->next;
			pc = pc->next;
		}
		else {
			pc->next = pb;
			pb = pb->next;
			pc = pc->next;
		}
	}
	if (pa == NULL) {
		pc->next = pb;
	}
	else pc->next = pa;
	free(*L2);
}

void ReadLine(char *a, int n)
{
	char ch;
	int i=0;
	while (isspace(ch = getchar()))
		;
	while (ch != '\n'&&ch != EOF) {
		if (i < n)
			a[i++] = ch;
		ch = getchar();
	}
	a[i] = '\0';
}

void ShowList(SList L)
{
	SNode *p = L->next;
	printf("年龄     学号\n");
	while (p) {
		printf("%-10d", p->age);
		puts(p->name);
		p = p->next;
	}
}
