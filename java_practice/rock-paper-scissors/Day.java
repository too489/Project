import java.util.Scanner;
import java.util.InputMismatchException;
public class Day{
public static void main(String[] args){
	Scanner scanner = new Scanner(System.in);
	
	String D[]={"��","��","ȭ","��","��","��","��"};
	
	System.out.print("������ �Է��Ͻÿ� >>");
/* ������ �� �� �������� �������ϴ�.
 num<0, 0<=num<7,7<=num �׿� ���� 0���ϴ� Ż�⹮�� ��� 0~6���̴� ������� �� ���� ������ 7�� ���� �� ������ ����߽��ϴ�. 
�׸��� ���� �ݺ����� try�� �־� ������ �ƴ� ���� �Է��� �� �� �Է� �޴� ��ɹ��� �־����ϴ�*/
	while(true){
	try
	{
		int num=scanner.nextInt();
	
	if (num<7&&num>=0)
		{
			System.out.println(D[num]);
			break;
		}
	else if (num>=7)
		{
		 System.out.println(D[num%7]);
			break;
		}
	else if (num<0)
		 break;
}
	catch(InputMismatchException e) 
		{
			System.out.println("������ �ƴմϴ�. �ٽ� �Է��ϼ���!");
			scanner.next();
			//i--;
			continue;
		}
}
			scanner.close();
			System.out.println("���α׷� �����մϴ�....");
	}
}
