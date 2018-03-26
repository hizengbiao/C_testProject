//从网页上下载input.dat文件，里面是用二进制编写的，里面放了一堆int 型的数，每个数占4个字节，每次读取两个，这两个数构成一个坐标。
//（1）规定处于第一象限的数是有效点，（即x>0, y>0的坐标），问这么多点中有效点有多少个？
//（2）现在用户从键盘输入一个坐标和一个数字K，设计算法输出K个离该坐标距离最近的点的坐标和每个坐标到该点的距离，写入到output.txt文件中

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define dataNum 100

int N_input = 0;//本地读入数据的个数

struct nearst{//定义一个点与输入点的距离，将距离从小到大连成一个链表
	int x;
	int y;
	double dis;
	struct nearst* next;
};

void makeData(char *p){
	//生成用二进制编写的一堆int 型的数，每个数占4个字节，每两个数构成一个坐标。
	FILE *f;
	f = fopen(p, "wb");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		return;
	}
	srand((unsigned)time(NULL));
	printf("生成的数据为：\n");
	for (int i = 0; i < dataNum; i++){
		//随机生成dataNUM/2个坐标并保存到本地文件中
		int t = rand() % 100;//随机生成坐标的绝对值范围0-99的数
		int sign = rand() % 2;//随机生成数的正负性，sign为1时为正数，为0时为负数
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
	printf("\n数据生成成功，路径为：%s\n\n\n", p);
	fclose(f);
}

void question1(char *p){
	//（1）规定处于第一象限的数是有效点，（即x>0,y>0的坐标），求这么多点中有效点有多少个
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
		{//在屏幕上打印出有效点并统计
			if (N_input == 1)
			printf("\n有效点：\n");
			if (t[0] > 0 && t[1] > 0){
				printf("%d:	（%d，%d）\n", ++n, t[0], t[1]);
			}
		}
		//if (t[0] > 0 && t[1] > 0){
		//	//有效点统计
		//	n++;
		//}
		fread(t, sizeof(int), 2, f);
	}
	printf("\n有效点一共有%d个\n\n", n);
	fclose(f);
}

double dis(int x1, int y1,int x2,int y2){
	//计算两个点之间的距离
	int x = x2 - x1;
	int y = y2 - y1;
	return sqrt((double)x*x+(double) y*y);
}

void linkInsert(struct nearst *&head,int *t,int &xx,int &yy){
	//将点（xx,yy)与点(t[0],t[1])的距离按从小到大的顺序插入到链表head中
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
	printf("请输入一个坐标和一个数字K：\t");
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
	printf("\n距离最近的%d个坐标点为：\n", k);
	for (int i = 0; i < k; i++){
		if (q == NULL)
			break;
		printf("%d  :  点坐标：(%d,%d)，距离：%.2lf\n", i + 1, q->x, q->y, q->dis);
		fprintf(f,"%d  :  点坐标：(%d,%d)，距离：%.2lf\n", i + 1, q->x, q->y, q->dis);
		q = q->next;
	}
	fclose(f);

	//释放链表空间
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