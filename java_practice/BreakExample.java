import java.util.Scanner;
public class BreakExample{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);
		
		int i;
		System.out.println("exit�� �Է��ϸ� ����˴ϴ�. �ƴѰ�� ��� �����Է� ����");
		String text;
		for(i=0;;i++)
		{
			text=scanner.next();
			if (text.equals("exit"))
				break;
		}
	System.out.println("�����մϴ�...");

	scanner.close();
}
}