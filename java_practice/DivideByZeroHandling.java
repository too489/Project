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
		try{

		System.out.print(dividend+"�� "+divisor+"�� ������ ���� " +dividend/divisor+"�Դϴ�.");
}
		catch(ArithmeticException e){
			System.out.println("0���� ���� �� �����ϴ�!");
		}
		finally{scanner.close();}
		}
}		
		