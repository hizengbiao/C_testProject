//2005年上机复试题
//第1道  把一个数表示成若干个素数的和
//第2道  一个递归程序，是关于如何选择机器人的最佳走步的
//第3道  统计篇文章中各英文字母的个数，

#include<stdio.h>

int chacter[26];

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

void ques1(int m){
	bool sign = false;
	for (int i = 2; i < m; i++){
		if (IsSuShu(i)){
			int b = m - i;
			if (IsSuShu(b)){
				sign = true;
				printf("%d = %d + %d \n", m, i, b);
				break;
			}
			else{
				continue;
			}
		}
		else{
			continue;
		}
	}
	if (sign == false){
		printf("%d不能分解\n",m);
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
void main(){

	//题目1：
	for (int i = 50; i < 100;i++)
		ques1(i);



	//题目3：
	/*char path[] = "d://article.txt";
	ques3(path);*/
}