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
���� 15.6.7
VisualStudio.15.Release/15.6.7+27428.2043
Microsoft .NET Framework
���� 4.7.02556
��ġ�� ����: Community
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
time_t startTime = 0, endTime = 0;//�ð��� ���ֱ����� �����Ͽ����ϴ�
float gap;//�ð��� �ʿ��� ����
int main() {
	int size;
	char ** in_arr;
	char ** compare_arr;
	char ** save_arr;
	char * temp;
	int i = 0, j = 0, k = 0;
	startTime = clock();
	scanf("%d", &size);//ù��° ���ڰ����� ������ �̽��ϴ�

	in_arr = (char**)malloc(sizeof(char*) * size);//�Է��� ������ �迭�� ���� �Ҵ�޾��־����ϴ�
	for (i = 0; i < size; i++)
		in_arr[i] = (char*)malloc(sizeof(char) * size);
	temp=(char *)malloc(sizeof(char) * size); //���� �������� ������ �����ϱ� ���� 1���� �迭�� �Ҵ��Ͽ����ϴ�

	printf("Size : %d \n", size);
	for (i = 0; i < size; i++)		   //�Է��� �����̷����ϱ����� scanf�� �̾ҽ��ϴ�
	{
		for (j = 0; j < size; j++)
		{
			scanf("%s", &in_arr[i][j]);
		}
	}
	compare_arr = (char**)malloc(sizeof(char*) * size);//�ӽ������� ����Ͽ� �Է°��� ���ϱ����� �����Ͽ����ϴ�
	for (i = 0; i < size; i++)
		compare_arr[i] = (char*)malloc(sizeof(char) * size);

	save_arr = (char**)malloc(sizeof(char*) * size);//�������� ���� �̾��ֱ� ���� �����ϴ� �迭�� ��������ϴ�
	for (i = 0; i < size; i++)
		save_arr[i] = (char*)malloc(sizeof(char) * size);
	initial_arr(save_arr, size);//#���� �ʱ�ȭ ���ִ� �Լ��� 2���� �迭�� �־����ϴ�
	initial_arr(compare_arr, size);//#���� �ʱ�ȭ ���ִ� �Լ��� 2���� �迭�� �־����ϴ�
	printf("\n�Է� �迭\n");
	printresult(in_arr, size);//����ϰ��� �ϴ� ����� ���� ����Ͽ����ϴ�

	/*�ڵ� ������*/
	findsolution(in_arr, compare_arr,temp, size, depth, save_arr);//���� �ڵ� ���� �κ��Դϴ�

	printf("��� ���� ������ ���Ͽ����ϴ�");//������� exit�� ����ǰԲ� �Ͽ� �ٽ� �̰����� ���ƿý� ������� ������ ���Ѱ����� �Ǵ� �����Ͽ����ϴ�
	endTime = clock(); //�ð��� �����մϴ�
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);//�� �ð����� ���� �����մϴ�
	printf("���� �ð� : %f �� \n", gap); //���α׷� ����� �ɸ� �ð��� ����մϴ�		
}

void findsolution(char **in_arr, char **compare_arr, char *temp, int size, int depth,char** save_arr )
{
	if (size == depth) {

		initial_arr(compare_arr, size);		 //�ӽ÷� �����ϴ� �񱳰��� #���� ���Ҷ� ���� �ٽ� �ʱ�ȭ �Ͽ����ϴ�
		for (int i = 0; i < size; i++) //���� ù���� ����� �������� ������ �ش� �迭��ȣ�� �����Բ� �Ͽ����ϴ�
			if (temp[i] == 'O')
				Click_arr(compare_arr, 0, i, size);

		set(in_arr, compare_arr, size);//ù���� Ŭ���� ���������� �ؿ� ���� ä��� �Լ��� ��������ϴ�

		if (Result(in_arr, compare_arr, size))//���� �׸������ �Լ��� �Է°��� ������ ����ϴ� ���� ��������ϴ�
		{
			printf("\n�ش� �迭\n"); //�� ���� ���Ҷ����� ���� �־��ִ� �迭�� ����°ͺ��� �������� �ѹ��� �����ϴ°� ���ٴ� �����̵�� �������� �ٽ��ѹ� �����ϴ� �Լ��� �����Ͽ����ϴ�.
			initial_arr(compare_arr, size);
			for (int i = 0; i < size; i++)
				if (temp[i] == 'O')
					Click_arr_result(compare_arr, 0, i, size, save_arr);

			set_result(in_arr, compare_arr, size,save_arr);
			printresult(save_arr, size);//���� ��𸦴����� �Է°��� �������� ��Ÿ���� ������ �迭�� ����Ͽ����ϴ�.
			endTime = clock(); //�ð��� �����մϴ�
			gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);//�� �ð����� ���� �����մϴ�
			printf("���� �ð� : %f �� \n", gap);
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
//�迭�� �����

void initial_arr(char** arr, int size) {

	for (int i = 0; i < size; i++)
		memset(arr[i], '#', size);
}
//�ʱ�ȭ

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
//��ü����Ʈ üũ

void save_point(int i,int l,char **save_arr) {
	save_arr[i][l] = 'O';
}
//���� ���� �����ϴ� �Լ�

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
		//printf("����� �б��???\n");
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
//��ư�� ������ ���ڰ��� O���� �ٲ�ų� #���� �ٲ�� �Լ� ����

void set(char **in_arr, char **arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int l = 0; l < size; l++) {
			if (arr[i][l] != in_arr[i][l]) {
				Click_arr(arr, i+1, l, size);
			}
		}
	}
}	  	
//�迭���� �˻��ϰ� �Է°��� �ٸ��ٸ� �ϳ� �ؿ����� ��ư�� �����ִ� �Լ��� �����Ͽ� �������� ���� ����ϰ� �Ͽ����ϴ�

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
		//printf("����� �б��???\n");
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
//������� ����ϱ����� �����ϴ� �迭�� ���ڰ��� �ϳ� ���ְ� �Լ��� ��������ϴ�
void set_result(char **in_arr, char **arr, int size, char** save_arr) {
	for (int i = 0; i < size - 1; i++) {
		for (int l = 0; l < size; l++) {
			if (arr[i][l] != in_arr[i][l]) {
				Click_arr_result(arr, i + 1, l, size, save_arr);
			}
		}
	}
}
//������� ����ϱ����� �����ϴ� �迭�� ���ڰ��� �ϳ� ���ְ� �Լ��� ��������ϴ�
