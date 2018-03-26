////�ı��ļ�input.txt������Ӣ�ĵ��ʺͷָ������ո񣬻س������У����ɡ���������˵����д����ͳ�Ʋ�ͬ���ʳ��ֵĴ�����Ƶ�ȣ�����ͳ�ƽ��������Ƶ�ȴӸߵ������򣬲�������Ƶ�ȴ���5�ĵ��ʼ���Ƶ��������ļ�output.txt�С��ļ���ʽ��ͼ1��ʾ��
//˵����
//(1)	��������ķָ�������Ϊһ���ָ�����
//(2)	���ʴ�Сд���С�
//(3)	ÿ�����ʵĳ��Ȳ�����20���ַ���
//(4)	���ʵ�����δ֪����ʹ�ö��徲̬������ķ�ʽ��ͳ�ƣ������۳�5�֡�


#include<stdio.h>
#include<Windows.h>

struct wordList{
	char word[21];
	int times;
	struct wordList *next;
}*head;

bool IsDivide(char c){
	//����ַ�c�Ƿָ�������true������ַ�c����ĸ����false
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

	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))//���Ƿָ�������ĸ��
		return false;
	else//�ָ���
		return true;
}

void count(char * w){//ͳ�Ƹõ����Ƿ���ֹ������û���ֹ�������������ֹ���õ��ʵ�Ƶ�ȼ�1
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
				//����õ��ʳ��ֹ�����Ƶ�ȼ�1���ɣ������ӽ��
				p->times++;
				return;
			}
			else{
				p = p->next;
			}
		}

		//�������û���ֹ����򽫸õ��ʼ��뵽��Ƶ�������ͷ���룺
		struct wordList* t = (struct wordList*)malloc(sizeof(struct wordList));
		strcpy(t->word, w);
		t->times = 1;
		t->next = head;
		head = t;

	}
}

void readData(char *p){//��ȡ�ַ����ָ��һ�������ʣ�ͬʱͳ��ÿ�����ʵ�Ƶ��
	head = NULL;
	FILE *f = fopen(p, "r");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		exit(0);
	}
	bool sign = false;
	char tem[21];//��ʱ���浱ǰ��ȡ�ĵ���
	int m = 0;//��ǰ��ȡ���ַ��ڵ����е��±�
	char c = fgetc(f);
	while (!feof(f)){
		if (!IsDivide(c)){//������Ƿָ����ͽ���ĸ������������ȡ��һ���ַ�
			tem[m++] = c;
			c = fgetc(f);
			sign = true;
		}
		else{
			if (sign == true){//�˴�sign==true��ʾ��ȡ��һ����ĸ֮��������һ���ָ�������һ�����ʶ�ȡ����
				tem[m] = '\0';
				count(tem);//ͳ�Ƹõ����Ƿ���ֹ������û���ֹ�������������ֹ���õ��ʵ�Ƶ�ȼ�1

				m = 0;//��ʼ��һ�����ʵĶ�ȡ
				sign = false;
				c = fgetc(f);
			}
			else{
				c = fgetc(f);
			}
		}
	}
	if (sign == true){
		//�������µ����һ�����ʣ��ļ������һ���ַ����Ƿָ��������
		tem[m] = '\0';
		count(tem);
	}
	fclose(f);
}

void sort2(){
	//����ָ��ķ�������������

	//���������������ر��Ӵ��ʱ�����ͨ����������������������������λ�ã�����Ѵ�����ʱ���˷��ڽ�����ݵ��ƶ��ϣ�
	//�����øı�ָ��ָ��ķ������۽��������ж�������ʱ�䶼��һ���ġ�
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

void sort1(){//������Ƶ�ȴӴ�С����
	//���ý���������ݵķ���������������
	//�����������ֻ��word��times��������ģ��С�����Բ��ô˷���
	struct wordList* p = head;
	
	//ѡ������
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
		printf("%s\t%d\n",p->word,p->times);//�����е��ʼ���Ƶ�ȴ�ӡ����Ļ��
		if (p->times > 5){
			//��Ƶ�ȴ���5�ĵ��ʴ�ӡ�������ļ���
			fprintf(f, "%s,%d\n", p->word, p->times);
		}
		p = p->next;
	}
}
void main2016(){
	char path[] = "data//input.txt";
	char path2[] = "data//output.txt";
	readData(path);//��ȡ�ַ����ָ��һ�������ʣ�ͬʱͳ��ÿ�����ʵ�Ƶ��
	sort2();//������Ƶ�ȴӴ�С����
	printData(path2);//��ӡ����
}