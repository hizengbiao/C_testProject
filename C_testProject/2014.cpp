//����ҳ������input.dat�ļ����������ö����Ʊ�д�ģ��������һ��int �͵�����ÿ����ռ4���ֽڣ�ÿ�ζ�ȡ������������������һ�����ꡣ
//��1���涨���ڵ�һ���޵�������Ч�㣬����x>0, y>0�����꣩������ô�������Ч���ж��ٸ���
//��2�������û��Ӽ�������һ�������һ������K������㷨���K����������������ĵ�������ÿ�����굽�õ�ľ��룬д�뵽output.txt�ļ���

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define dataNum 100

int N_input = 0;//���ض������ݵĸ���

struct nearst{//����һ�����������ľ��룬�������С��������һ������
	int x;
	int y;
	double dis;
	struct nearst* next;
};

void makeData(char *p){
	//�����ö����Ʊ�д��һ��int �͵�����ÿ����ռ4���ֽڣ�ÿ����������һ�����ꡣ
	FILE *f;
	f = fopen(p, "wb");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		return;
	}
	srand((unsigned)time(NULL));
	printf("���ɵ�����Ϊ��\n");
	for (int i = 0; i < dataNum; i++){
		//�������dataNUM/2�����겢���浽�����ļ���
		int t = rand() % 100;//�����������ľ���ֵ��Χ0-99����
		int sign = rand() % 2;//����������������ԣ�signΪ1ʱΪ������Ϊ0ʱΪ����
		if (sign == 1){
			printf("%d\t",t);
			fwrite(&t,4,1,f);
		}
		else{
			t = -t;
			printf("%d\t", t);
			fwrite(&t, 4, 1, f);
		}

	}
	printf("\n�������ɳɹ���·��Ϊ��%s\n\n\n", p);
	fclose(f);
}

void question1(char *p){
	//��1���涨���ڵ�һ���޵�������Ч�㣬����x>0,y>0�����꣩������ô�������Ч���ж��ٸ�
	FILE *f;
	f = fopen(p, "rb");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		return;
	}
	int t[2];
	int n = 0;
	fread(t, sizeof(int), 2, f);
	//int i = 1;
	N_input = 0;
	while (!feof(f)){
		N_input++;
		//printf("%d:	%d	%d\n",i, t[0],t[1]);
		{//����Ļ�ϴ�ӡ����Ч�㲢ͳ��
			if (N_input == 1)
			printf("\n��Ч�㣺\n");
			if (t[0] > 0 && t[1] > 0){
				printf("%d:	��%d��%d��\n", ++n, t[0], t[1]);
			}
		}
		//if (t[0] > 0 && t[1] > 0){
		//	//��Ч��ͳ��
		//	n++;
		//}
		fread(t, sizeof(int), 2, f);
	}
	printf("\n��Ч��һ����%d��\n\n", n);
	fclose(f);
}

double dis(int x1, int y1,int x2,int y2){
	//����������֮��ľ���
	int x = x2 - x1;
	int y = y2 - y1;
	return sqrt((double)x*x+(double) y*y);
}

void linkInsert(struct nearst *&head,int *t,int &xx,int &yy){
	//���㣨xx,yy)���(t[0],t[1])�ľ��밴��С�����˳����뵽����head��
	if (head == NULL){
		head = (struct nearst*)malloc(sizeof(struct nearst));
		head->x = t[0];
		head->y = t[1];
		head->dis = dis(xx,yy,t[0],t[1]);
		head->next = NULL;
		return;
	}
	else{
		struct nearst*tem = (struct nearst*)malloc(sizeof(struct nearst));
		tem->x = t[0];
		tem->y = t[1];
		tem->dis = dis(xx, yy, t[0], t[1]);
		tem->next = NULL;
		struct nearst*q, *p;
		q= head;
		if (tem->dis <= head->dis){
			tem->next = head;
			head = tem;
		}
		else{
			p = q->next;
			while (p){
				if (tem->dis > p->dis){
					q = q->next;
					p = q->next;
					continue;
				}
				else
					break;
			}
			if (!p){
				q->next = tem;
			}
			else{
				tem->next = p;
				q->next = tem;
			}
		}
	}
}

void question2(char *p, char *p2){
	printf("������һ�������һ������K��\t");
	int x, y, k;
	scanf("%d%d%d", &x, &y, &k);
	//printf("\n\n\n%d	%d	%d", x, y, k);
	/*for (int i = 0; i < N_input; i++){

	}*/

	struct nearst *head = NULL;
	FILE *f;
	f = fopen(p, "rb");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		return;
	}
	int t[2];
	fread(t, sizeof(int), 2, f);
	while (!feof(f)){
		linkInsert(head, t,x,y);
		fread(t, sizeof(int), 2, f);
	}	
	fclose(f);

	f = fopen(p2, "w");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p2);
		return;
	}
	struct nearst *q = head;
	printf("\n���������%d�������Ϊ��\n", k);
	for (int i = 0; i < k; i++){
		if (q == NULL)
			break;
		printf("%d  :  �����꣺(%d,%d)�����룺%.2lf\n", i + 1, q->x, q->y, q->dis);
		fprintf(f,"%d  :  �����꣺(%d,%d)�����룺%.2lf\n", i + 1, q->x, q->y, q->dis);
		q = q->next;
	}
	fclose(f);

	//�ͷ�����ռ�
	while (head != NULL){
		q = head;
		head = head->next;
		free(q);
	}
	q = NULL;
}

void main2014(){	
	char path[] = "data//input.dat";
	char path2[] = "data//output.txt";

	makeData(path);
	question1(path);
	question2(path,path2);
}