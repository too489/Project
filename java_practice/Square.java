import java.util.Scanner;

/*import로 스캐너 함수가 어디있는지 명시했습니다*/
public class Square
{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);

/*스캐너함수 선언했습니다*/

		System.out.println("점 (x,y)의 좌표를 입력하세요"); 
		int x=scanner.nextInt();// 둘다 인트값으로 받았습니다
		int y=scanner.nextInt();
		
		if(50<=x && 100>=x && 50<=y && 100>=y)
		System.out.println("점("+x+","+y+")은 (50,50)과 (100,100)의 사각형 내에 있습니다.");
/* 50이상 100이내의 조건식을 만족하면 사각형내에 있다고 적었습니다*/

		else
		System.out.println("점("+x+","+y+")은 (50,50)과 (100,100)의 사각형 내에 없습니다.");
/*위 조건식이 아닐때 출력하게 했습니다*/
	}
}
