import java.util.Scanner;
public class ArrayAccess{
public static void main(String[] args){
	Scanner scanner=new Scanner(System.in);

	int arr[];
	arr=new int[5];
	int max=0;
	System.out.println("제일 큰수를 출력함. 값을 입력하시오");
	for(int i=0;i<5;i++)
	{
		arr[i]=scanner.nextInt();
		if(arr[i]>max)
			max=arr[i];
	}
	System.out.println("제일 큰 수는 "+ max);
	
	scanner.close();
}
}