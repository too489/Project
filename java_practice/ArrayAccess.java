import java.util.Scanner;
public class ArrayAccess{
public static void main(String[] args){
	Scanner scanner=new Scanner(System.in);

	int arr[];
	arr=new int[5];
	int max=0;
	System.out.println("���� ū���� �����. ���� �Է��Ͻÿ�");
	for(int i=0;i<5;i++)
	{
		arr[i]=scanner.nextInt();
		if(arr[i]>max)
			max=arr[i];
	}
	System.out.println("���� ū ���� "+ max);
	
	scanner.close();
}
}