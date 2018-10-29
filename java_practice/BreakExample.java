import java.util.Scanner;
public class BreakExample{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);
		
		int i;
		System.out.println("exit을 입력하면 종료됩니다. 아닌경우 계속 숫자입력 가능");
		String text;
		for(i=0;;i++)
		{
			text=scanner.next();
			if (text.equals("exit"))
				break;
		}
	System.out.println("종료합니다...");

	scanner.close();
}
}