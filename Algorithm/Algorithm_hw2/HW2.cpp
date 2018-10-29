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
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
																		   
int main() {
	int **arr;	//2차원 배열을 설정하여 더블포인터를 만들었습니다
	int *arr_sum; //2차원배열들의 각 행들에 열들을 더하는것들을 또 그행들의 최대 합을 구하기위해 1차원배열을 만들었습니다
	time_t startTime = 0, endTime = 0;//시간을 재주기위해 설정하였습니다
	float gap;//시간에 필요한 변수
	int Total_Size,i = 0, j = 0, k = 0, temp_sum = 0, max_sum = 0, min_sum = 0, min_s_i = 0, min_s_j = 0, min_e_i = 0, min_e_j = 0, max_s_i = 0, max_s_j = 0, max_e_i = 0, max_e_j = 0, s_p = 0, e_p=0;
	//여기서 min_s_j에서 s는 start이고 j는 열을 나타낸것입니다 그리고 s_p는 임시로 스타트포인트를 저장할 변수이고 e_p는 end포인트를 저장할 변수입니다
	startTime = clock();//시간 측정을 시작하였습니다
	scanf("%d", &Total_Size);// 리다이렉션으로 text파일을 집어 넣을꺼기 때문에 scanf로 받아왔습니다
	printf("%d*%d 크기 측정 시작 \n", Total_Size, Total_Size);//시작 멘트입니다

	arr = (int**)malloc(sizeof(int*) * Total_Size);//위에서 설정한 더블포인터들의 값들을 총 [Total_Size][Total_Size] 사이즈로 초기화 시켜줍니다
	for (i = 0; i < Total_Size; i++)
		arr[i] = (int*)malloc(sizeof(int) * Total_Size);

	arr_sum = (int*)malloc(sizeof(int) * Total_Size); //포인터를 Total_Size값으로 초기화 하여 주었습니다
	
	for (i = 0; i < Total_Size; i++)
	{
		for (j = 0; j < Total_Size; j++)
		{
			scanf("%d", &arr[i][j]); // 파일 리다이렉션으로 불로언 text파일들을 2차원배열에 다 넣어줬습니다
		}
	}

	for (k = 0; k < Total_Size; k++)	   //배열이 있으면 왼쪽의 시작단위 ,한마디로 해당값의 제일 왼쪽을 담당합니다
	{
		memset(arr_sum, 0, sizeof(int)*Total_Size);
	for (j = k; j < Total_Size; j++) {	   //배열이 있으면 오른쪽을 담당 j에 해당하는 수가있으면 그건 j-i인 열의 갯수일것입니다 현재 탐색하고있는 행을뜻합니다
			for (i = 0; i < Total_Size; i++)
				arr_sum[i] += arr[i][j];//각 해당하는 행들의 열들을 하나씩 더해서 1차원 배열에 정렬합니다
			temp_sum = 0;//아래의 함수가 빠져나오면 sum은 임시변수기 때문에 필요가 없어 리셋을 해줍니다
			for (i = 0; i < Total_Size; i++) {
				if (arr_sum[i] < temp_sum + arr_sum[i]) {
					temp_sum += arr_sum[i];	//제일 중요한 부분으로서 n3으로 갈수있는 핵심적인 열쇠를 들고있다고 할수있는 알고리즘입니다 . 각 arr_sum으로 각 행들의 열의 합을 더한 값을 가지고 배열을 만들어 그 배열내에서 최대 부분합을 구합니다
											//만약 현재 [][][][][][][][][] 이렇게 1차원 배열이 있다고 쳤을때 기존에 있던값과 새로운 값을 더하였을때 값이 커졌다면 temp_sum이라는 배열에 저장하여
											//temp_sum이 최종으로 나오면 그값들을 max_sum과 비교하여 max_sum으로 지정하는 역활을 합니다
					e_p = i;
				}
				else
				{
					temp_sum = arr_sum[i];// 이값은 만약 현재 행렬비해 그 해당 행렬과 그 전행렬의 합이 더 작다면 아마 그전행렬들의 합은 음수일것입니다 그리하여 그전값들은 버리고 현재값을 설정하여 줍니다 
					s_p=i;
				}
				if (temp_sum > max_sum) {// 이건 임시로 저장된 temp_sum이 현재 저장되어있는 최대값 보다 높았을때 설정하여 주는 조건문입니다.
					max_sum = temp_sum;
					max_s_i = s_p; //현재 실행중인 루프문중 임시로 저장한 s_p를 수들의 합이 최대인 사각형의 왼쪽 행부분을 가르키게 설정합니다
					max_s_j = k; //현재 실행중인 루프문의k번째 열을 설정하여 줍니다. 제일 왼쪽으로서 수들의 합이 최대인 사각형의 제일 왼쪽 열부분을 가르키게됩니다
					max_e_i = e_p; //현재 실행중인 임시로 저장한 e_p를 수들의 합이 최대인 사각형의 오른쪽 행부분을 가르키게 설정합니다
					max_e_j = j; //현재 실행중인 루프문의j번째 열을 설정하여 줍니다. 제일 오른쪽으로서 수들의 합이 최대인 사각형의 제일 왼쪽 열부분을 가르키게됩니다
				}
			}
							   
			for (i = 0; i < Total_Size; i++) {	 //수들의 합이 최소인 사각형을 구합니다
				if (arr_sum[i] > temp_sum + arr_sum[i]) {
					temp_sum += arr_sum[i];
					//제일 중요한 부분으로서 n3으로 갈수있는 핵심적인 열쇠를 들고있다고 할수있는 알고리즘입니다 . 각 arr_sum으로 각 행들의 열의 합을 더한 값을 가지고 배열을 만들어 그 배열내에서 최대 부분합을 구합니다
					//만약 현재 [][][][][][][][][] 이렇게 1차원 배열이 있다고 쳤을때 기존에 있던값과 새로운 값을 더하였을때 값이 작아졌다면 temp_sum이라는 배열에 저장하여
					//temp_sum이 최종으로 나오면 그값들을 min_sum과 비교하여 min_sum으로 지정하는 역활을 합니다
					e_p = i;
				}
				else
				{
					temp_sum = arr_sum[i]; ;// 이값은 만약 현재 행렬비해 그 해당 행렬과 그 전행렬의 합이 더 크다면 아마 그 전 행렬들의 합은 음수가 아닐것입니다 그리하여 그 전 값들은 버리고 현재값을 설정하여 줍니다 
					s_p = i;
				}
				if (temp_sum < min_sum) {			// 이건 임시로 저장된 temp_sum이 현재 저장되어있는 최소값 보다 낮았을때  설정하여 주는 조건문입니다.
					min_sum = temp_sum;
					min_s_i = s_p;		//현재 실행중인 루프문중 임시로 저장한 s_p를 수들의 합이 최소인 사각형의 왼쪽 행부분을 가르키게 설정합니다
					min_s_j = k;	   //현재 실행중인 루프문의k번째 열을 설정하여 줍니다. 제일 왼쪽으로서 수들의 합이 최소인 사각형의 제일 왼쪽 열부분을 가르키게됩니다
					min_e_i = e_p;	    //현재 실행중인 임시로 저장한 e_p를 수들의 합이 최소인 사각형의 오른쪽 행부분을 가르키게 설정합니다
					min_e_j = j;		//현재 실행중인 루프문의j번째 열을 설정하여 줍니다. 제일 오른쪽으로서 수들의 합이 최소인 사각형의 제일 왼쪽 열부분을 가르키게됩니다
				}
			}
		}
	}
	
//	cout << "최대 큰수 결과 " << max_sum << endl<<"start 좌표 : ("<<max_s_i<<","<<max_s_j<<") ," << "end 좌표 : (" << max_e_i << "," << max_e_j << ")" <<endl;
	printf("최소 값 사각형 결과 : %d  \n", max_sum);
	printf("최대 값 사각형 시작 블록 위치 : (%d , %d)\n최대 값 사각형 시작 블록 위치 : (%d , %d)\n", max_s_i, max_s_j, max_e_i, max_e_j);

	//cout << "최대 작은 수 결과 " << min_sum << endl<<"start 좌표 : (" << min_s_i << "," << min_s_j << ") ," << "end 좌표 : (" << min_e_i << "," << min_e_j << ")" << endl;
	printf("최소 값 사각형 결과 : %d  \n", min_sum);
	printf("최소 값 사각형 시작 블록 위치 : (%d , %d)\n최소 값 사각형 시작 블록 위치 : (%d , %d)\n", min_s_i, min_s_j, min_e_i, min_e_j);

	endTime = clock(); //시간을 종료합니다
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);//그 시간들의 갭을 저장합니다
	printf("측정 시간 : %f 초 \n", gap); //프로그램 실행시 걸린 시간을 출력합니다												  
	free(arr);
	free(arr_sum);

	
}