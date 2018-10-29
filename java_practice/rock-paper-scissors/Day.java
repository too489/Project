import java.util.Scanner;
import java.util.InputMismatchException;
public class Day{
public static void main(String[] args){
	Scanner scanner = new Scanner(System.in);
	
	String D[]={"일","월","화","수","목","금","토"};
	
	System.out.print("정수를 입력하시오 >>");
/* 구간을 총 세 구간으로 나눴습니다.
 num<0, 0<=num<7,7<=num 그에 맞춰 0이하는 탈출문만 줬고 0~6사이는 정상출력 그 뒤의 구간은 7로 나눈 뒤 몫으로 출력했습니다. 
그리고 여기 반복문에 try를 넣어 정수가 아닌 수를 입력할 시 재 입력 받는 명령문을 넣었습니다*/
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
			System.out.println("정수가 아닙니다. 다시 입력하세요!");
			scanner.next();
			//i--;
			continue;
		}
}
			scanner.close();
			System.out.println("프로그램 종료합니다....");
	}
}
