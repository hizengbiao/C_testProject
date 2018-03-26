/*

Introduction
The project will read flight data from an input file and flight path requests from another input file and output the required information.
Your Task
Your program should determine if a particular destination airport can be reached from a particular originating airport within a particular number of hops.
A hop (leg of a flight) is a flight from one airport to another on the path between an originating and destination airports.
For example, the flight plan from PVG to PEK might be PVG → CAN → PEK. So PVG → CAN would be a hop and CAN → PEK would be a hop.

Input Data Files
Path Input File(PathInput.txt)
This input file will consist of a number of single origination/destination airport pairs (direct flights). The first line of the file will contain an integer representing the total number of pairs in the rest of the file.
6
[PVG, CAN]
[CAN, PEK]
[PVG, CTU]
[CTU, DLC]
[DLC, HAK]
[HAK, LXA]

Path Request File(PathRequest.txt)
This input file will contain a sequence of pairs of origination/destination airports and a max number of hops. The first line of the file will contain an integer representing the number of pairs in the file.
2
[PVG, DLC, 2]
[PVG, LXA, 2]

Output File(Output.txt)
For each pair in the Path Request File, your program should output the pair followed by “YES” or “NO” indicating that it is possible to get from the origination to destination airports within the max number of hops or it is not possible, respectively.
[PVG, DLC, YES]
[PVG, LXA, NO]
Assumptions you can make:
You may make the following simplifying assumptions in your project:
	C/C++ is allowed to be used.
	All airport codes will be 3 letters and will be in all caps
	Origination/destination pairs are unidirectional. To indicate that both directions of flight are possible, two entries would appear in the file. For example, [PVG, PEK] and [PEK, PVG] would have to be present in the file to indicate that one could fly from Shanghai to Beijing and from Beijing to Shanghai.



*/

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

	FILE *f1 = fopen("data\\PathInput.txt", "r");
	FILE *f2 = fopen("data\\PathRequest.txt", "r");
	FILE *f3 = fopen("data\\Output.txt", "w");
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