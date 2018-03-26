//2005���ϻ�������
//��1��  ��һ������ʾ�����ɸ������ĺ�
//��2��  һ���ݹ�����ǹ������ѡ������˵�����߲���
//��3��  ͳ��ƪ�����и�Ӣ����ĸ�ĸ�����

#include<stdio.h>
#include<Windows.h>

#define N 100

int chacter[26];


int stack[N];
int top = -1;

void push(int m){
	if (top == N){
		printf("ջ������");
		exit(0);
	}
	stack[++top] = m;
}

int pop(){
	if (top == -1){
		printf("ջ�ѿգ�");
		exit(0);
	}
	return stack[--top];
}

void clearStack(){
	top = -1;
}

bool IsSuShu(int m){
	//int t = sqrt(m*1.0);
	if (m <= 1)
		return false;
	for (int i = 2; i <m; i++){
		if (m%i == 0)
			return false;
	}
	return true;
}

bool resolution(int m){
	if (m == 0)
		return true;
	for (int i = 2; i <= m; i++){
		if (IsSuShu(i)){
			push(i);
			if (resolution(m - i)){
				return true;
			}
			else{
				pop();
				continue;
			}
		}
		else{
			continue;
		}
	}
	return false;
}

void ques1(int m){
	clearStack();
	if (resolution(m)){
		printf("%d = ",m);
		for (int i = 0; i <= top; i++){
			printf("%d ",stack[i]);
			if (i!=top)
				printf("+ ");
			else{
				printf("\n");
			}
		}
	}
	else{
		printf("%d���ֽܷ�����ɸ������ĺ�\n",m);
	}
	
}

void ques2(){
	//��Ŀ��˼����������
}

void ques3(char *p){
	for (int i = 0; i < 26; i++){
		chacter[i] = 0;
	}
	FILE *f = fopen(p, "r");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		return;
	}
	char c = fgetc(f);
	while (!feof(f)){
		if (c >= 'a'&&c <= 'z'){
			chacter[c - 'a']++;
		}
		else if (c >= 'A'&&c <= 'Z'){
			chacter[c - 'A']++;
		}
		else{
			;
		}
		c = fgetc(f);
	}

	for (int i = 0; i < 26; i++){
		printf("��ĸ%c��%c���ֵĴ���Ϊ\t%d\n",'a'+i,'A'+i,chacter[i]);
	}

	fclose(f);
}
void main2005(){

	//��Ŀ1��
	for (int i = 1; i < 100;i++)
		ques1(i);



	//��Ŀ3��
	char path[] = "data//article.txt";
	ques3(path);
}