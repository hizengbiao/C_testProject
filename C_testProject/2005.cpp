//2005���ϻ�������
//��1��  ��һ������ʾ�����ɸ������ĺ�
//��2��  һ���ݹ�����ǹ������ѡ������˵�����߲���
//��3��  ͳ��ƪ�����и�Ӣ����ĸ�ĸ�����

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
		printf("%d���ֽܷ�\n",m);
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
void main(){

	//��Ŀ1��
	for (int i = 50; i < 100;i++)
		ques1(i);



	//��Ŀ3��
	/*char path[] = "d://article.txt";
	ques3(path);*/
}