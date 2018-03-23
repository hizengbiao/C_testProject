#include <stdio.h>
#include<ctype.h>
#include<string.h>


int N = 0;
char letters[1000][15];

bool IsIlleagl(int n){
	//检查第n+1个单词是否合法
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
	bool sign = false;//处理空格的标志
	c = fgetc(f);
	while (!feof(f)){
		if (c != ' '){
			letters[i][j++] = c;
			sign = true;
			c = fgetc(f);
		}
		else{
			if (sign == false){
				//跳过此空格，继续读下一个字符
				//1.文章的开头是空格
				//2.一个单词后有连续多个空格，读到第二个及以上的空格时的情况
				c = fgetc(f);
			}
			else{
				letters[i++][j] = '\0';

				if(!IsIlleagl(i-1,j));//筛选是否是the的变形及出现过的单词，如果是则跳过
					i--;

				j = 0;//开始处理下一个单词
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