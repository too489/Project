import java.util.Scanner;
public class change
{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);

		System.out.println("���� �׼��� �Է��Ͻÿ�");

/*���� 5�������� ������ ���� cut���� �������� rest�� �������ְ� cut�� ��� �������� ���� �Լ��� ����Ǵ� �۾��� ���ϰ� �ϱ����� �ٽ� money�� �������־����ϴ�*/

		int money=scanner.nextInt();
		int cut=0,rest=0;
		cut=money/50000;
		rest=money%50000;
		money=rest;
		System.out.print("5������ : "+ cut+ "�� ,");
		
		cut=money/10000; //���ǰ��� �ݺ��Ͽ����ϴ�
		rest=money%10000;
		money=rest;
		System.out.print("1������ : "+cut+"�� ,");
	
		cut=money/1000;
		rest=money%1000;
		money=rest;
		System.out.print("õ���� : "+cut+"�� ,");

		cut=money/500;
		rest=money%500;
		money=rest;
		System.out.print("����� : "+cut+"�� ,");	
	
		cut=money/100;
		rest=money%100;
		money=rest;
		System.out.print("���¥�� : "+cut+"�� ,");

		cut=money/10;
		rest=money%10;
		money=rest;
		System.out.print("�ʿ�¥�� : "+cut+"�� ,");

		
		System.out.print("1��¥�� : "+money+"��");/* ���������� �������� 1��¥���� ������ �־����ϴ�*/
		
	}
}
