#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//#define Max 100

int patNum=0;
int reqNum=0;

struct pat{
	char ori[4];
	char dest[4];
};
pat* pats;
struct req{
	char ori[4];
	char dest[4];
	int hops;
};
req* reqs;

struct result{
	int hops;
	char YN[4];
};
result* results;

void showData(){
	printf("\nPathInput.txt:\n%d", patNum);
	for (int i = 0; i < patNum; i++){
		printf("\n[%s, %s]", pats[i].ori, pats[i].dest);
	}
	printf("\n");
}

void readData(FILE *f){
	fscanf(f, "%d", &patNum);
	//patNum = fgetc(f) - '0';
	//printf("%d", patNum);
	pats = (pat*)malloc(sizeof(pat)*patNum);
	for (int i = 0; i < patNum; i++){
		fgetc(f); fgetc(f);
		for (int j = 0; j < 3; j++){
			pats[i].ori[j]=fgetc(f);
		}
		pats[i].ori[3] = '\0';
		fgetc(f); fgetc(f);
		fgets(pats[i].dest, 4, f);
		pats[i].dest[3] = '\0';
		fgetc(f);
	}

	showData();
}

void showReq(){
	printf("\nPathRequest.txt:\n%d", reqNum);
	for (int i = 0; i < reqNum; i++){
		printf("\n[%s, %s, %d]", reqs[i].ori, reqs[i].dest,reqs[i].hops);
	}
	printf("\n");
}

void readResq(FILE *f){
	//reqNum = fgetc(f) - '0';
	fscanf(f, "%d", &reqNum);
	//printf("%d", patNum);
	reqs = (req*)malloc(sizeof(req)*reqNum);
	for (int i = 0; i < reqNum; i++){
		fgetc(f); fgetc(f);
		for (int j = 0; j < 3; j++){
			reqs[i].ori[j] = fgetc(f);
		}
		reqs[i].ori[3] = '\0';
		fgetc(f); fgetc(f);
		//fgets(reqs[i].dest, 4, f);
		fread(reqs[i].dest, 3, 1, f);
		reqs[i].dest[3] = '\0';
		fgetc(f); fgetc(f);
		fscanf(f, "%d", &reqs[i].hops);
		//reqs[i].hops = fgetc(f) - '0';
		fgetc(f);
	}
	showReq();
}


bool judg(char* ori ,char *dest,int nowHops,int& maxHops){
	if (nowHops == maxHops){
		if (strcmp(ori, dest) == 0)
			return true;
		else
			return false;
	}

	for (int i = 0; i < patNum; i++){
		if (strcmp(ori, pats[i].ori) == 0){
			if (judg(pats[i].dest, dest, nowHops + 1, maxHops) == true)
				return true;
		}
	}
	return false;


	//int result;
	//if (strcmp(ori, dest) == 0)
	//	return 0;
	//for (int i = 0; i < patNum; i++){
	//	if (strcmp(ori, pats[i].ori) == 0){
	//		result = judg(pats[i].dest, dest);
	//		if(result == -1)
	//			return -1;
	//		else
	//			return result+1;
	//	}
	//}
	//return -1;
}

void deal(){
	results = (result*)malloc(sizeof(result)*reqNum);
	for (int i = 0; i < reqNum; i++){
		//results[i].hops = Max;
		if (judg(reqs[i].ori, reqs[i].dest,0,reqs[i].hops) == true){
			strcpy(results[i].YN, "YES");
		}
		else{
			strcpy(results[i].YN, "NO");
		}
	}
}

void outPut(FILE *f){
	fprintf(f, "%d\n", reqNum);
	for (int i = 0; i < reqNum; i++){
		fprintf(f, "[%s, %s, %s]\n",reqs[i].ori,reqs[i].dest,results[i].YN);

	}
}

void main11(){
	FILE *f1 = fopen("D:\\PathInput.txt", "r");
	FILE *f2 = fopen("D:\\PathRequest.txt", "r");
	FILE *f3 = fopen("D:\\Output.txt", "w");
	if (f1 == NULL || f2 == NULL || f3 == NULL){
		printf("the file can not be opened.");
		return;
	}

	readData(f1);
	readResq(f2);

	deal();
	outPut(f3);

	fclose(f1);
	fclose(f2);
	fclose(f3);
}