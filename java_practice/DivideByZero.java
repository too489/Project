import java.util.Scanner;
public class DivideByZero{
	public static void main(String[] args){
		Scanner scanner=new Scanner(System.in);
		int dividend;
		int divisor;

		System.out.print("�������� �Է��Ͻÿ�: ");
		dividend=scanner.nextInt();
		System.out.print("�������� �Է��Ͻÿ� :");
		divisor=scanner.nextInt();

		System.out.print(dividend+"�� "+divisor+"�� ������ ���� " +dividend/divisor+"�Դϴ�.");
		}
}		
		