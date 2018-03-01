//#include <stdio.h>
//#include<windows.h>
//void main(){
//	FILE *fp;
//	fp = fopen("d:\\a.txt","w");
//	if (fp == NULL){
//		printf("the file can not be opened.");
//		exit(1);
//	}
//	else{
//		printf("the file is successely opened.\n");
//	}
//	/*int ch;
//	ch=fgetc(fp);
//	while(ch!=EOF){
//		putchar(ch);
//		ch=fgetc(fp);
//	}*/
//	for(int i=0;i<34;i++){
//		fputc(i,fp);
//	}
//	fclose(fp);
//}



//
//
//#include<stdio.h>
//void main(){
//	FILE *a,*b;
//	a=fopen("c:\\a.txt","r");
//	if(a==NULL){
//		printf("the file a .txt cannot be opened.");
//		return;
//	}
//	b=fopen("c:\\b.txt","w");
//	if(b==NULL){
//		printf("the file b.txt cannot be opened.");
//		return;
//	}
//	int ch;
//	while((ch=fgetc(a))!=EOF){
//		fputc(ch,b);
//		//putchar(ch);
//	}
//	fclose(a);
//	fclose(b);
//}





//
//#include "stdio.h"
//#include "windows.h"	//exit(0);
//#pragma warning(disable:4996)
//void getnum(){
//	int t;
//	FILE *fp;
//	char *add = "d:\\a.txt";
//	if (!(fp = fopen(add, "r"))){
//		printf("the file cannot be opened!\n");
//		return;
//	}
//	printf("get ing...\n");
//	//for (t = 2; t<10; t++){
//	printf("the point now is at %d.\n", ftell(fp));
//	int c = getw(fp);
//	printf("the point now is at %d.\n", ftell(fp));
//	while (!feof(fp)){
//		printf("now the number is:\t %d\n", c);
//		c = getw(fp);
//		printf("the point now is at %d.\n", ftell(fp));
//		//c = putc('h', fp);
//		//printf("%d\n", putw(t,fp));		
//	}
//	//exit(0);
//	printf("the work is done!\n");
//	fclose(fp);
//}
//void putnum(){
//	int t;
//	FILE *fp;
//	char *add = "d:\\a.txt";
//	if (!(fp = fopen(add, "w"))){
//		printf("the file cannot be opened!\n");
//		return;
//	}
//	printf("put ing...\n");
//	for (t = 1; t<9; t++){
//		int c;
//		c = putw(t, fp);
//		//c = putc('h', fp);
//		//printf("%d\n", putw(t,fp));
//		printf("now the number is:\t %d\n", c);
//		printf("the point now is at %d.\n",ftell(fp));
//	}
//	printf("the work is done!\n");
//	fclose(fp);
//}
//void main(){
//	getnum();
//}

#include<stdio.h>

struct test{
	int no;
	char *name;
	int age;
};
void main(){
	FILE *fp;
	fp = fopen("D:\\a.txt", "wb+");
	if (fp == NULL){
		printf("the file can not be opened.");
		return;
	}
	test t1;
	//printf("%d\n",sizeof(test));
	/*printf("please input the no and the age:\t");
	scanf("%d%d", &t1.no, &t1.age);*/
	t1.name = "zengbiao";
	t1.no = 1;
	t1.age = 21;
	printf("\nthe no is %d\t,the name is %s\t,the age is %d,\tthe size of struct is %d.\n", t1.no, t1.name,t1.age,sizeof(test));
	//fwrite(&t1, sizeof(test), 1, fp);
	//fflush(fp);
	test t2;
	fread(&t2, sizeof(test), 1, fp);
	printf("\nthe no is %d\t,the name is %s\t,the age is %d,\tthe size of struct is %d.\n", t2.no, t2.name, t2.age, sizeof(test));
	fclose(fp);
}