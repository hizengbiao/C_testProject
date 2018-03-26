/*
2008年上机复试题
（1）用IE从FTP上下载org.dat，并保存在D盘的根目录中。
（2）此文件中按文本方式存放了一段其他文章，其中有若干长度小于15的英文单词，单词之间用空格分开，无其他符号。
（3）顺序读取这段文章的不同的单词（大小写敏感），同时在读取的过程中排除所有的单词THE以及变形，即这些单词不能出现在读取的结果中。
（4）将读取的所有单词的首字母转大写后，输出D根目录下new.txt，每个单词一行。
------------------------
那段文字可以点右键打开方式中用记事本打开，内容是：
The constructor is used to initialize the object The destructor is used to delete the Object the calling seqence of constructor is opposite to the calling sequence of destructor
个人感觉今年出题挺有水平的，苏大一个重要的方向就是信息处理，这个应该就是分词技术的基础把，我做的一般，不过听说好象有将近满分的，还当然也有很多兄弟没做出来。
-----------------
正确结果应该是
Constructor
Is
Used
To
Initialize
Object
Destructor
Delete
Object
Calling
Seqence
Of
Opposite
注意有两个Object
因为第一次读取是大小写敏感的，后来又进行了首字母大写转化

*/

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

void main2008(){
	char path1[] = "data//org.dat";
	char path2[] = "data//new.txt";

	pickLetters(path1);
	printLetters(path2);

}