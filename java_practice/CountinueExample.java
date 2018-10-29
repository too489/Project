import java.util.scanner;
public class CountinueExample{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);
		
		int num=0,sum=0,i;
		System.out.print("숫자들의 총합을 구하기위해 원하는 숫자를 입력하시오 끝내길 원하면 0을입력")
		for(i=0;;i++)
		{
			int num=scanner.nextInt();
			if(num==0)
				{
					System.out.print("총합은 "+ sum);
					scanner.close();
					return 0;
				}
			else if (num<0)
				countinue;
		sum+=num;
		}
		
	}
}