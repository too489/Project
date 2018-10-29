import java.util.Scanner;
public class change
{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);

		System.out.println("돈의 액수를 입력하시오");

/*먼저 5만원으로 나눠서 몫을 cut으로 나머지를 rest로 지정해주고 cut은 출력 나머지는 다음 함수를 수행되는 작업을 편하게 하기위해 다시 money로 지정해주었습니다*/

		int money=scanner.nextInt();
		int cut=0,rest=0;
		cut=money/50000;
		rest=money%50000;
		money=rest;
		System.out.print("5만원권 : "+ cut+ "개 ,");
		
		cut=money/10000; //위의것을 반복하였습니다
		rest=money%10000;
		money=rest;
		System.out.print("1만원권 : "+cut+"개 ,");
	
		cut=money/1000;
		rest=money%1000;
		money=rest;
		System.out.print("천원권 : "+cut+"개 ,");

		cut=money/500;
		rest=money%500;
		money=rest;
		System.out.print("오백권 : "+cut+"개 ,");	
	
		cut=money/100;
		rest=money%100;
		money=rest;
		System.out.print("백원짜리 : "+cut+"개 ,");

		cut=money/10;
		rest=money%10;
		money=rest;
		System.out.print("십원짜리 : "+cut+"개 ,");

		
		System.out.print("1원짜리 : "+money+"개");/* 최종적으로 나머지를 1원짜리의 갯수로 넣었습니다*/
		
	}
}
