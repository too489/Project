import java.util.Scanner;

public class RockPaperScissors{
public static void main(String[] avgs){
	Scanner scanner= new Scanner(System.in);

	String rpc[]={"바위","보","가위"};
	String u;
/* 당신이 입력할 값이라는 의미에서 사용자가 입력하는 변수를 u로 잡고 영어약자를 따와 가위바위보의 기본 배열 값의 이름을 rpc라고 정했습니다*/
	
	System.out.println("컴퓨터와 가위 바위 보 게임을 합니다.");
	System.out.println("가위 바위 보!");
	int n;
	
/*여기선 이퀄값을 이용하여 한 경우 한 경우 다 적어서 적용하였고 랜덤함수는 책에 있는 것을 참조하여 적었습니다*/
	while(true){
		u=scanner.next();
		n =(int)(Math.random()*3);
		System.out.println("가위 바위 보!");
		if(u.equals("그만")){
			System.out.println("게임을 종료합니다...");
			break;
			}
		else
			System.out.println("다시!");
		
		if(rpc[n].equals("가위")){
			if(u.equals("가위")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 비겼습니다");
				}
			else if(u.equals("바위")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 사용자가 이겼습니다.");
				}
			else if(u.equals("보")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 컴퓨터가 이겼습니다.");
				}
				continue;
			}
		else if(rpc[n].equals("바위")){
			if(u.equals("바위")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 비겼습니다");
				}
			else if(u.equals("보")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 사용자가 이겼습니다.");
				}
			else if(u.equals("가위")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 컴퓨터가 이겼습니다.");
				}
				continue;
			}
			
		else if(rpc[n].equals("보")){
			if(u.equals("보")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 비겼습니다");
				}
			else if(u.equals("가위")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 사용자가 이겼습니다.");
				}
			else if(u.equals("바위")){
				System.out.println(" 사용자 = "+u+", 컴퓨터 = "+rpc[n]+ " 컴퓨터가 이겼습니다.");
				}
				continue;
			}
		
		
		}
	scanner.close();
	
	}
}
