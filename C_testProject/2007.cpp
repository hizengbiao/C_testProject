//2007���ϻ�������
//��10��1000֮�������������������������浽result.txt�ļ���
//1����������
//2�����ķ���Ҳ���������磺123�ķ�����321��

#include<stdio.h>
#include<math.h>

bool su(int m){
	//int t = sqrt(m*1.0);
	if (m <= 1)
		return false;
	for (int i = 2; i <m; i++){
		if (m%i == 0)
			return false;
	}
	return true;
}

int fan(int m){
	int result = 0;
	while (m != 0){
		result *= 10;
		result += m % 10;
		m /= 10;
	}
	return result;
}
void main2007(){
	char path[] = "d://result.txt";
	FILE *f = fopen(path, "w");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", path);
		return;
	}
	for (int i = 10; i <= 1000; i++){
		int j = fan(i);
		if (su(i) && su(j)){
			printf("%d\t%d\n", i,j);
			fprintf(f, "%d\t", i);
		}
	}
	fclose(f);
}