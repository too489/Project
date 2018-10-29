#include<stdio.h>
#include<stdlib.h>
#include<string.h>     
#include<string> 
#include<time.h>
/*
1.Window 10 Pro N
2.i7-8700 CPT@3.20GHz
3.16GB
4.Microsoft Visual Studio Community 2017
버전 15.6.7
VisualStudio.15.Release/15.6.7+27428.2043
Microsoft .NET Framework
버전 4.7.02556
설치된 버전: Community
Visual C++ 2017   00369-60000-00001-AA451
Microsoft Visual C++ 2017
*/
int i, j, k,depth=0;
void printresult(char ** arr, int size);
void initial_arr(char** arr, int size);
bool Result(char **in_arr, char **compare_arr, int size);
void Click_arr(char **arr, int row, int column, int size);
void set(char **in_arr, char **arr, int size);
void findsolution(char **in_arr, char **compare_arr, char *temp, int size, int depth, char** save_arr);
void save_point(int i, int l, char **save_arr);
void Click_arr_result(char **arr, int row, int column, int size, char** save_arr);
void set_result(char **in_arr, char **arr, int size, char** save_arr);
time_t startTime = 0, endTime = 0;//시간을 재주기위해 설정하였습니다
float gap;//시간에 필요한 변수
int main() {
	int size;
	char ** in_arr;
	char ** compare_arr;
	char ** save_arr;
	char * temp;
	int i = 0, j = 0, k = 0;
	startTime = clock();
	scanf("%d", &size);//첫번째 인자값으로 사이즈 뽑습니다

	in_arr = (char**)malloc(sizeof(char*) * size);//입력이 들어오는 배열을 동적 할당받아주었습니다
	for (i = 0; i < size; i++)
		in_arr[i] = (char*)malloc(sizeof(char) * size);
	temp=(char *)malloc(sizeof(char) * size); //제일 위엣줄의 값들을 설정하기 위해 1차원 배열을 할당하였습니다

	printf("Size : %d \n", size);
	for (i = 0; i < size; i++)		   //입력을 리다이렉션하기위해 scanf로 뽑았습니다
	{
		for (j = 0; j < size; j++)
		{
			scanf("%s", &in_arr[i][j]);
		}
	}
	compare_arr = (char**)malloc(sizeof(char*) * size);//임시적으로 계산하여 입력값과 비교하기위해 설정하였습니다
	for (i = 0; i < size; i++)
		compare_arr[i] = (char*)malloc(sizeof(char) * size);

	save_arr = (char**)malloc(sizeof(char*) * size);//최종적인 값을 뽑아주기 위해 저장하는 배열을 만들었습니다
	for (i = 0; i < size; i++)
		save_arr[i] = (char*)malloc(sizeof(char) * size);
	initial_arr(save_arr, size);//#으로 초기화 해주는 함수에 2차원 배열을 넣었습니다
	initial_arr(compare_arr, size);//#으로 초기화 해주는 함수에 2차원 배열을 넣었습니다
	printf("\n입력 배열\n");
	printresult(in_arr, size);//출력하고자 하는 결과물 값을 출력하였습니다

	/*코드 시작점*/
	findsolution(in_arr, compare_arr,temp, size, depth, save_arr);//메인 코드 실행 부분입니다

	printf("결과 값을 구하지 못하였습니다");//결과값에 exit로 종료되게끔 하여 다시 이곳으로 돌아올시 결과값을 구하지 못한것으로 판단 종료하였습니다
	endTime = clock(); //시간을 종료합니다
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);//그 시간들의 갭을 저장합니다
	printf("측정 시간 : %f 초 \n", gap); //프로그램 실행시 걸린 시간을 출력합니다		
}

void findsolution(char **in_arr, char **compare_arr, char *temp, int size, int depth,char** save_arr )
{
	if (size == depth) {

		initial_arr(compare_arr, size);		 //임시로 저장하는 비교값을 #으로 구할때 마다 다시 초기화 하였습니다
		for (int i = 0; i < size; i++) //제일 첫줄의 경우의 가지수를 뽑은걸 해당 배열번호를 누르게끔 하였습니다
			if (temp[i] == 'O')
				Click_arr(compare_arr, 0, i, size);

		set(in_arr, compare_arr, size);//첫줄을 클릭한 값을가지고 밑에 줄을 채우는 함수를 만들었습니다

		if (Result(in_arr, compare_arr, size))//만약 그만들어진 함수가 입력값과 같으면 출력하는 값을 만들었습니다
		{
			printf("\n해답 배열\n"); //각 값을 비교할때마다 값을 넣어주는 배열을 만드는것보다 마지막에 한번더 수행하는게 낫다는 생각이들어 마지막에 다시한번 수행하는 함수를 구현하였습니다.
			initial_arr(compare_arr, size);
			for (int i = 0; i < size; i++)
				if (temp[i] == 'O')
					Click_arr_result(compare_arr, 0, i, size, save_arr);

			set_result(in_arr, compare_arr, size,save_arr);
			printresult(save_arr, size);//최종 어디를누르면 입력값과 같은지를 나타내는 정답인 배열을 출력하였습니다.
			endTime = clock(); //시간을 종료합니다
			gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);//그 시간들의 갭을 저장합니다
			printf("측정 시간 : %f 초 \n", gap);
			exit(0);
		}
	}
	else if(depth<size){
		temp[depth] = 'O';
		findsolution(in_arr, compare_arr,temp, size,depth+1, save_arr);
		temp[depth] = '#';
		findsolution(in_arr, compare_arr,temp, size,depth+1, save_arr);
	}
}

void printresult(char ** arr,int size)
{
	for (int i = 0; i < size; i++) {
		for (int l = 0; l < size; l++)
		{
			printf("%c ", arr[i][l]);
		}
		printf("\n");
	}
}
//배열을 출력함

void initial_arr(char** arr, int size) {

	for (int i = 0; i < size; i++)
		memset(arr[i], '#', size);
}
//초기화

bool Result(char **in_arr, char **compare_arr, int size)
{
	for (int i = 0; i < size; i++) {
		for (int l = 0; l < size; l++) {
			if (in_arr[i][l] != compare_arr[i][l])
				return false;
		}
	}
	return true;
}
//전체리스트 체크

void save_point(int i,int l,char **save_arr) {
	save_arr[i][l] = 'O';
}
//최종 값을 저장하는 함수

void Click_arr(char **arr, int row, int column, int size) 
{

	if (arr[row][column] == '#')
		arr[row][column] = 'O';
	else
		arr[row][column] = '#';


	if (row > 0) {
		if (arr[row - 1][column] == '#')
			arr[row - 1][column] = 'O';
		else
			arr[row - 1][column] = '#';
	}
	if (row < size-1) {
		//printf("여기는 읽기됨???\n");
		if (arr[row + 1][column] == '#')
			arr[row + 1][column] = 'O';
		else
			arr[row + 1][column] = '#';
	}
	if (column > 0) {
		if (arr[row][column - 1] == '#')
			arr[row][column - 1] = 'O';
		else
			arr[row][column - 1] = '#';
	}
	if (column < size-1) {
		if (arr[row][column + 1] == '#')
			arr[row][column + 1] = 'O';
		else
			arr[row][column + 1] = '#';
	}
}
//버튼을 누르면 십자가로 O으로 바뀌거나 #으로 바뀌는 함수 구현

void set(char **in_arr, char **arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int l = 0; l < size; l++) {
			if (arr[i][l] != in_arr[i][l]) {
				Click_arr(arr, i+1, l, size);
			}
		}
	}
}	  	
//배열들을 검색하고 입력값과 다르다면 하나 밑에행의 버튼을 눌러주는 함수를 적용하여 최종적인 값을 출력하게 하였습니다

void Click_arr_result(char **arr, int row, int column, int size,char** save_arr)
{
	save_point(row, column, save_arr);
	if (arr[row][column] == '#')
		arr[row][column] = 'O';
	else
		arr[row][column] = '#';


	if (row > 0) {
		if (arr[row - 1][column] == '#')
			arr[row - 1][column] = 'O';
		else
			arr[row - 1][column] = '#';
	}
	if (row < size - 1) {
		//printf("여기는 읽기됨???\n");
		if (arr[row + 1][column] == '#')
			arr[row + 1][column] = 'O';
		else
			arr[row + 1][column] = '#';
	}
	if (column > 0) {
		if (arr[row][column - 1] == '#')
			arr[row][column - 1] = 'O';
		else
			arr[row][column - 1] = '#';
	}
	if (column < size - 1) {
		if (arr[row][column + 1] == '#')
			arr[row][column + 1] = 'O';
		else
			arr[row][column + 1] = '#';
	}
}
//결과값을 출력하기위해 저장하는 배열인 인자값을 하나 더주고 함수를 만들었습니다
void set_result(char **in_arr, char **arr, int size, char** save_arr) {
	for (int i = 0; i < size - 1; i++) {
		for (int l = 0; l < size; l++) {
			if (arr[i][l] != in_arr[i][l]) {
				Click_arr_result(arr, i + 1, l, size, save_arr);
			}
		}
	}
}
//결과값을 출력하기위해 저장하는 배열인 인자값을 하나 더주고 함수를 만들었습니다
