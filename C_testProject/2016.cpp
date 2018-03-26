////文本文件input.txt由若干英文单词和分隔符（空格，回车，换行）构成。根据如下说明编写程序统计不同单词出现的次数（频度）。将统计结果按出现频度从高到低排序，并将出现频度大于5的单词及其频度输出到文件output.txt中。文件格式如图1所示。
//说明：
//(1)	多个连续的分隔符被视为一个分隔符。
//(2)	单词大小写敏感。
//(3)	每个单词的长度不超过20个字符。
//(4)	单词的数量未知。如使用定义静态大数组的方式来统计，将被扣除5分。


#include<stdio.h>
#include<Windows.h>

struct wordList{
	char word[21];
	int times;
	struct wordList *next;
}*head;

bool IsDivide(char c){
	//如果字符c是分隔符返回true，如果字符c是字母返回false
	//...

	/*if (c == ' ' || c == '\n')
		return true;
	else
		return false;*/


	//switch (c){
	//case ' ':
	//case '\n':
	//case '.':
	//case ',':
	//case '?':
	//	return true; break;
	//default:
	//	return false; break;
	//}

	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))//不是分隔符（字母）
		return false;
	else//分隔符
		return true;
}

void count(char * w){//统计该单词是否出现过，如果没出现过则加入链表，出现过则该单词的频度加1
	if (head == NULL){
		struct wordList* t = (struct wordList*)malloc(sizeof(struct wordList));
		strcpy(t->word, w);
		t->times = 1;
		t->next = NULL;
		head = t;
	}
	else{
		struct wordList* p = head;
		while (p != NULL){
			if (!strcmp(p->word, w)){
				//如果该单词出现过，则频度加1即可，不增加结点
				p->times++;
				return;
			}
			else{
				p = p->next;
			}
		}

		//如果单词没出现过，则将该单词加入到词频表里，采用头插入：
		struct wordList* t = (struct wordList*)malloc(sizeof(struct wordList));
		strcpy(t->word, w);
		t->times = 1;
		t->next = head;
		head = t;

	}
}

void readData(char *p){//读取字符并分割成一个个单词，同时统计每个单词的频度
	head = NULL;
	FILE *f = fopen(p, "r");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		exit(0);
	}
	bool sign = false;
	char tem[21];//临时保存当前读取的单词
	int m = 0;//当前读取的字符在单词中的下标
	char c = fgetc(f);
	while (!feof(f)){
		if (!IsDivide(c)){//如果不是分隔符就将字母储存起来并读取下一个字符
			tem[m++] = c;
			c = fgetc(f);
			sign = true;
		}
		else{
			if (sign == true){//此处sign==true表示读取了一个字母之后遇到了一个分隔符，上一个单词读取结束
				tem[m] = '\0';
				count(tem);//统计该单词是否出现过，如果没出现过则加入链表，出现过则该单词的频度加1

				m = 0;//开始下一个单词的读取
				sign = false;
				c = fgetc(f);
			}
			else{
				c = fgetc(f);
			}
		}
	}
	if (sign == true){
		//处理文章的最后一个单词，文件中最后一个字符不是分隔符的情况
		tem[m] = '\0';
		count(tem);
	}
	fclose(f);
}

void sort2(){
	//采用指针的方法对链表排序

	//当单个结点的数据特别庞大的时候，如果通过交换结点的数据来交换两个结点的位置，将会把大量的时间浪费在结点数据的移动上，
	//而采用改变指针指向的方法无论结点的数据有多大，排序的时间都是一样的。
	struct wordList* p = head;
	if (head == NULL)
		return;
	bool start = true;
	while (p->next){		
		if (start==true){
			start = false;
			struct wordList* q = head;
			p = q->next;
			if (p->times > q->times){
				q->next = p->next;
				p->next = q;
				head = p;
				q = p;
			}
			q = q->next;

			while (q->next){
				if (q->next->times > head->times){
					struct wordList* t = q->next;
					p = head->next;
					head->next = t->next;
					t->next = p;
					q->next = head;					
					head = t;
				}
				q = q->next;
			}
			p = head;
		}
		else{
			struct wordList* q = p->next;
			while (q->next){
				if (q->next->times > p->next->times){
					struct wordList* t = q->next;
					q->next = p->next;
					p->next = t;
					struct wordList* t2 = t->next;
					t->next = q->next->next;
					q->next->next = t2;
				}
				q = q->next;
			}
			p = p->next;
		}
		
	}

}

void sort1(){//按单词频度从大到小排序
	//采用交换结点数据的方法来对链表排序
	//本题结点的数据只有word和times两个，规模较小，可以采用此方法
	struct wordList* p = head;
	
	//选择排序：
	while (p){
		struct wordList* t = p->next;
		while (t){
			if (t->times > p->times){
				char w[21];
				strcpy(w, t->word);
				strcpy(t->word, p->word);
				strcpy(p->word, w);

				int ti = t->times;
				t->times = p->times;
				p->times = ti;
			}
			t = t->next;
		}
		p = p->next;
	}
}

void printData(char *path2){
	FILE *f = fopen(path2, "w");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", path2);
		exit(0);
	}

	struct wordList* p = head;
	while (p != NULL){
		printf("%s\t%d\n",p->word,p->times);//将所有单词及其频度打印到屏幕上
		if (p->times > 5){
			//将频度大于5的单词打印到本地文件里
			fprintf(f, "%s,%d\n", p->word, p->times);
		}
		p = p->next;
	}
}
void main2016(){
	char path[] = "data//input.txt";
	char path2[] = "data//output.txt";
	readData(path);//读取字符并分割成一个个单词，同时统计每个单词的频度
	sort2();//按单词频度从大到小排序
	printData(path2);//打印数据
}