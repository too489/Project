import java.util.Scanner;
public class Clap
{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);

		System.out.print("1~99������ ������ �Է��ϼ��� >> ");
		int num=scanner.nextInt();
		int cut=0,rest=0;
		cut=num/10; 
/* 10�ڸ��� �����ϱ����ؼ� 10���� ������ ������ ������ ���� ���߽��ϴ�*/
		rest=num%10; 
/* ������ ���� 1�� �ڸ� ���� �־�����ϴ�*/

		if(cut%3==0 && rest%3==0)
		System.out.print("�ڼ� ¦¦"); 
/* ��� �������� 3���� �������� �Ѵ� �������� 0�� �ǰԵǸ� �ڼ��� �ι�ģ�ٰ� ���؇J���ϴ�*/

		else if(cut%3==0||rest%3==0)
		System.out.print("�ڼ� ¦"); 
/*��� �������� 3���� �������� �������� �ϳ��� 3�� ����� ������ �ѹ� �ڼ��� ģ�ٰ� �س����ϴ�*/

		else if(cut%3!=0&&rest%3!=0)
		System.out.print("�ڼ�����");
/*�ٸ� ������ �ڼ��������� �߽��ϴ�*/
		
	}
}