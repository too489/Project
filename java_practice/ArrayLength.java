import java.util.Scanner;
public class ArrayLength{
public static void main(String[] args){
	Scanner scanner=new Scanner(System.in);

	int arr[];
	arr=new int[5];
	int sum=0;
	System.out.println("5���ڸ� �Է��ϸ� ��հ� ���");
	for(int i=0;i<arr.length;i++)
	{
		arr[i]=scanner.nextInt();	
		sum+=arr[i];
	}

	
	System.out.println("���ϵ��� ��"+sum);
	System.out.println("��հ���?"+(double)(sum/(arr.length)));
	scanner.close();
}
}