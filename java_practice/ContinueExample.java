import java.util.Scanner;
public class ContinueExample{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);
		
		int num=0,sum=0,i;
		System.out.print("���ڵ��� ������ ���ϱ����� ���ϴ� ���ڸ� �Է��Ͻÿ� ������ ���ϸ� 0���Է�");
		for(i=0;;i++)
		{
			num=scanner.nextInt();
			if(num==0)
				{
					System.out.print("������ "+ sum);
					
					break;
				}
			else if (num<0)
				continue;
		sum+=num;
		}
	scanner.close();	
	}
}