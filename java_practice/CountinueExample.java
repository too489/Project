import java.util.scanner;
public class CountinueExample{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);
		
		int num=0,sum=0,i;
		System.out.print("���ڵ��� ������ ���ϱ����� ���ϴ� ���ڸ� �Է��Ͻÿ� ������ ���ϸ� 0���Է�")
		for(i=0;;i++)
		{
			int num=scanner.nextInt();
			if(num==0)
				{
					System.out.print("������ "+ sum);
					scanner.close();
					return 0;
				}
			else if (num<0)
				countinue;
		sum+=num;
		}
		
	}
}