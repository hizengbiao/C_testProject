//2006年上机复试题
//找出100到1000内的不含9的素数，存到result文件中。

#include<stdio.h>

bool suShu(int m){
	//int t = sqrt(m*1.0);
	if (m <= 1)
		return false;
	for (int i = 2; i <m; i++){
		if (m%i == 0)
			return false;
	}
	return true;
}

bool IsInclude9(int m){
	int t;
	while (m != 0){
		t = m % 10;
		if (t == 9)
			return true;
		m /= 10;
	}
	return false;
}

void main2006(){
	char path[] = "d://result.txt";
	FILE *f = fopen(path, "w");
	if (f == NULL){
		printf("\n\nthe file %s can not be opened.\n\n", path);
		return;
	}

	for (int i = 100; i <= 1000; i++){
		if (IsInclude9(i))
			continue;
		if (!suShu(i))
			continue;
		printf("%d\t", i);
		fprintf(f,"%d\t", i);
	}
	fclose(f);
}