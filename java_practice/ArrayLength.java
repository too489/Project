import java.util.Scanner;
public class ArrayLength{
public static void main(String[] args){
	Scanner scanner=new Scanner(System.in);

	int arr[];
	arr=new int[5];
	int sum=0;
	System.out.println("5숫자를 입력하면 평균값 출력");
	for(int i=0;i<arr.length;i++)
	{
		arr[i]=scanner.nextInt();	
		sum+=arr[i];
	}

	
	System.out.println("파일들의 합"+sum);
	System.out.println("평균값은?"+(double)(sum/(arr.length)));
	scanner.close();
}
}