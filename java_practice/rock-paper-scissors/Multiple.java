import java.util.Scanner;
public class Multiple{
	public static void main(String[] args){
		Scanner scanner = new Scanner(System.in);
		
		int n[];
		n = new int[10]; //배열 선언후 10개의 공간을 줬습니다
		
		System.out.print("정수 10개 입력 >>");
		
		for(int i=0;i<n.length;i++)//정수 10개를 읽었구요
		{
			n[i] = scanner.nextInt();
		}

		System.out.print("3의 배수 : ");

/*목과 나눴을 때 나머지가 0이 되는 수를 출력했습니다*/

		for(int i=0;i<n.length;i++)
		{
			if(n[i]%3==0)
			{
				System.out.print(n[i] );
				if(i!=(n.length-1))
					System.out.print(", ");
			}
		}
	}
