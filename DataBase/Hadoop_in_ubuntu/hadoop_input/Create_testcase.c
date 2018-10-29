#include <stdio.h>
#include<stdlib.h>

int main(){

	char c[]="QWERTPOIOUASDFKLJHGHZXCOVIUFYQWKLJEHRFYA";

	int id,p,loc,h,m;
	FILE *f;
	f=fopen("hadoop_input.txt","w");
	
	for(int i =0;i<3000;i++){
		id=rand()%130;
		p=rand()%100;
		loc=c[rand()%20];
		h=(rand()%24)+1;
		m=(rand()%60)+1;
		fprintf(f,"%d 01012341234 %d:%d %c\n",id,h,m,loc);
//	printf("id : %d , p : %d , loc %c, h %d, m %d \n",id,p,loc,h,m);
	}
	fclose(f);
}
