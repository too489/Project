import java.util.Scanner;
public class Clap
{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);

		System.out.print("1~99사이의 정수를 입력하세요 >> ");
		int num=scanner.nextInt();
		int cut=0,rest=0;
		cut=num/10; 
/* 10자리를 구분하기위해서 10으로 나누고 나머지 버리고 몫을 구했습니다*/
		rest=num%10; 
/* 나머지 값을 1의 자리 수로 넣어놨습니다*/

		if(cut%3==0 && rest%3==0)
		System.out.print("박수 짝짝"); 
/* 몫과 나머지가 3으로 나눴을떄 둘다 나머지가 0이 되게되면 박수를 두번친다고 정해놧습니다*/

		else if(cut%3==0||rest%3==0)
		System.out.print("박수 짝"); 
/*몫과 나머지를 3으로 나눴을때 나머지가 하나라도 3의 배수가 있으면 한번 박수를 친다고 해놨습니다*/

		else if(cut%3!=0&&rest%3!=0)
		System.out.print("박수없음");
/*다른 값들은 박수없음으로 했습니다*/
		
	}
}