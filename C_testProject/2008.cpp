#include <stdio.h>
#include<ctype.h>
#include<string.h>


int N = 0;//合法的单词数量
char letters[1000][15];

bool IsIlleagl(int n){
	//检查第n+1个单词是否合法
	char t[4];
	for (int i = 0; i < 3; i++){
		t[i] = toupper(letters[n][i]);
	}
	t[3] = '\0';
	if (!strcmp("THE", t))//如果此单词是the的变形，返回false
		return false;


	for (int i = 0; i < n; i++){
		if (!strcmp(letters[i], letters[n]))//此单词出现过
			return false;
	}
	return true;
}

void pickLetters(char *p){
	FILE *f = fopen(p, "r");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		return;
	}
	char c;
	int i = 0;//第i+1个单词
	int j = 0;//第i+1个单词的第j+1个字母
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
				//可能的情况有：
				//1.文章的开头是空格
				//2.一个单词后有连续多个空格，读到第二个及以上的空格时的情况
				c = fgetc(f);
			}
			else{
				letters[i++][j] = '\0';//上一个单词提取完成

				if(!IsIlleagl(i-1))//筛选是否是the的变形及出现过的单词，如果是则跳过
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

void printLetters(char *p){
	FILE *f = fopen(p, "w");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		return;
	}
	for (int i = 0; i < N; i++){
		letters[i][0] = toupper(letters[i][0]);//将读取的所有单词的首字母转大写
		//printf("%s\n", letters[i]);
		fprintf(f, "%s\n", letters[i]); //输出D根目录下new.txt，每个单词一行
	}

	fclose(f);
}

void main2007(){
	char path1[] = "d://org.dat";
	char path2[] = "d://new.txt";

	pickLetters(path1);
	printLetters(path2);

}