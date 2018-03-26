//2005年上机复试题
//第1道  把一个数表示成若干个素数的和
//第2道  一个递归程序，是关于如何选择机器人的最佳走步的
//第3道  统计篇文章中各英文字母的个数，

#include<stdio.h>
#include<Windows.h>

#define N 100

int chacter[26];


int stack[N];
int top = -1;

void push(int m){
	if (top == N){
		printf("栈已满！");
		exit(0);
	}
	stack[++top] = m;
}

int pop(){
	if (top == -1){
		printf("栈已空！");
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
		printf("%d不能分解成若干个质数的和\n",m);
	}
	
}

void ques2(){
	//题目意思不懂。。。
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
		printf("字母%c或%c出现的次数为\t%d\n",'a'+i,'A'+i,chacter[i]);
	}

	fclose(f);
}
void main2005(){

	//题目1：
	for (int i = 1; i < 100;i++)
		ques1(i);



	//题目3：
	char path[] = "data//article.txt";
	ques3(path);
}