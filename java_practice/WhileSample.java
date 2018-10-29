import java.util.Scanner;
public class WhileSample{
	public static void main(String[] arg){
		Scanner scanner=new Scanner(System.in);
			int count=0,n=0;
			int sum=0;
			double avg;
			System.out.println("정수를 입력하시오. 종료를 원하는 경우 0을 입력");
			while((n=scanner.nextInt()) != 0)
			{
				sum+=n;
				count++;	
			}
			System.out.println("총"+count+"개 입력");
			System.out.println("총 합은 "+sum+"이고 평균은"+(sum/count));
}
}