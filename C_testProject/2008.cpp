#include <stdio.h>
#include<ctype.h>
#include<string.h>


int N = 0;
char letters[1000][15];

bool IsIlleagl(int n){
	//����n+1�������Ƿ�Ϸ�
	char t[3];
	for (int i = 0; i < 3; i++){
		t[i] = toupper(letters[n][i]);
	}
	if (!strcmp("THE", t))
		return false;
	for (int i = 0; i < n; i++){

	}
}

void pickLetters(char *p){
	FILE *f = fopen(p, "r");
	char c;
	int i = 0;
	int j = 0;
	bool sign = false;//����ո�ı�־
	c = fgetc(f);
	while (!feof(f)){
		if (c != ' '){
			letters[i][j++] = c;
			sign = true;
			c = fgetc(f);
		}
		else{
			if (sign == false){
				//�����˿ո񣬼�������һ���ַ�
				//1.���µĿ�ͷ�ǿո�
				//2.һ�����ʺ�����������ո񣬶����ڶ��������ϵĿո�ʱ�����
				c = fgetc(f);
			}
			else{
				letters[i++][j] = '\0';

				if(!IsIlleagl(i-1,j));//ɸѡ�Ƿ���the�ı��μ����ֹ��ĵ��ʣ������������
					i--;

				j = 0;//��ʼ������һ������
				sign = false;
				c = fgetc(f);
			}
		}
	}
	N = i;
	if (N!=0)
		letters[i-1][j] = '\0';
	fclose(f);
}

void printLetters(){
	for (int i = 0; i < N; i++){
		printf("%s\n", letters[i]);
	}
}

void main(){
	char path1[] = "d://org.dat";
	char path2[] = "d://new.txt";

	pickLetters(path1);
	printLetters();

}