import java.util.Scanner;
public class DivideByZero{
	public static void main(String[] args){
		Scanner scanner=new Scanner(System.in);
		int dividend;
		int divisor;

		System.out.print("나뉨수를 입력하시오: ");
		dividend=scanner.nextInt();
		System.out.print("나눗수를 입력하시오 :");
		divisor=scanner.nextInt();
		try{

		System.out.print(dividend+"를 "+divisor+"로 나누면 몫은 " +dividend/divisor+"입니다.");
}
		catch(ArithmeticException e){
			System.out.println("0으로 나눌 수 없습니다!");
		}
		finally{scanner.close();}
		}
}		
		