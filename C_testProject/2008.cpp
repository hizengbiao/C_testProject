/*
2008���ϻ�������
��1����IE��FTP������org.dat����������D�̵ĸ�Ŀ¼�С�
��2�����ļ��а��ı���ʽ�����һ���������£����������ɳ���С��15��Ӣ�ĵ��ʣ�����֮���ÿո�ֿ������������š�
��3��˳���ȡ������µĲ�ͬ�ĵ��ʣ���Сд���У���ͬʱ�ڶ�ȡ�Ĺ������ų����еĵ���THE�Լ����Σ�����Щ���ʲ��ܳ����ڶ�ȡ�Ľ���С�
��4������ȡ�����е��ʵ�����ĸת��д�����D��Ŀ¼��new.txt��ÿ������һ�С�
------------------------
�Ƕ����ֿ��Ե��Ҽ��򿪷�ʽ���ü��±��򿪣������ǣ�
The constructor is used to initialize the object The destructor is used to delete the Object the calling seqence of constructor is opposite to the calling sequence of destructor
���˸о��������ͦ��ˮƽ�ģ��մ�һ����Ҫ�ķ��������Ϣ�������Ӧ�þ��Ƿִʼ����Ļ����ѣ�������һ�㣬������˵�����н������ֵģ�����ȻҲ�кܶ��ֵ�û��������
-----------------
��ȷ���Ӧ����
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
ע��������Object
��Ϊ��һ�ζ�ȡ�Ǵ�Сд���еģ������ֽ���������ĸ��дת��

*/

#include <stdio.h>
#include<ctype.h>
#include<string.h>


int N = 0;//�Ϸ��ĵ�������
char letters[1000][15];

bool IsIlleagl(int n){
	//����n+1�������Ƿ�Ϸ�
	char t[4];
	for (int i = 0; i < 3; i++){
		t[i] = toupper(letters[n][i]);
	}
	t[3] = '\0';
	if (!strcmp("THE", t))//����˵�����the�ı��Σ�����false
		return false;


	for (int i = 0; i < n; i++){
		if (!strcmp(letters[i], letters[n]))//�˵��ʳ��ֹ�
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
	int i = 0;//��i+1������
	int j = 0;//��i+1�����ʵĵ�j+1����ĸ
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
				//���ܵ�����У�
				//1.���µĿ�ͷ�ǿո�
				//2.һ�����ʺ�����������ո񣬶����ڶ��������ϵĿո�ʱ�����
				c = fgetc(f);
			}
			else{
				letters[i++][j] = '\0';//��һ��������ȡ���

				if(!IsIlleagl(i-1))//ɸѡ�Ƿ���the�ı��μ����ֹ��ĵ��ʣ������������
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

void printLetters(char *p){
	FILE *f = fopen(p, "w");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", p);
		return;
	}
	for (int i = 0; i < N; i++){
		letters[i][0] = toupper(letters[i][0]);//����ȡ�����е��ʵ�����ĸת��д
		//printf("%s\n", letters[i]);
		fprintf(f, "%s\n", letters[i]); //���D��Ŀ¼��new.txt��ÿ������һ��
	}

	fclose(f);
}

void main2008(){
	char path1[] = "data//org.dat";
	char path2[] = "data//new.txt";

	pickLetters(path1);
	printLetters(path2);

}