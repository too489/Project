import java.util.Scanner;
public class WhileSample{
	public static void main(String[] arg){
		Scanner scanner=new Scanner(System.in);
			int count=0,n=0;
			int sum=0;
			double avg;
			System.out.println("������ �Է��Ͻÿ�. ���Ḧ ���ϴ� ��� 0�� �Է�");
			while((n=scanner.nextInt()) != 0)
			{
				sum+=n;
				count++;	
			}
			System.out.println("��"+count+"�� �Է�");
			System.out.println("�� ���� "+sum+"�̰� �����"+(sum/count));
}
}