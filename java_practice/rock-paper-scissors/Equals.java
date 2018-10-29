import java.util.Scanner;

public class Equals{
	public static void main(String[] avgs){
		Scanner scanner=new Scanner(System.in);
		String eng[]={"student","love","java","happy","future"};
		String kor[]={"학생","사랑","자바","행복한","미래"};
		String in;
		String exit ="exit";
		String EXIT="EXIT";
		/*탈출명령어가 대문자 소문자 둘 다 있어야 할꺼 같아 이렇게 줬습니다*/
		while(true)
		{
			System.out.println("영어 단어를 입력하세요>>");
			in=scanner.next();
			

			if(in.equals(eng[0]))	
				System.out.println(kor[0]);
			else if(in.equals(eng[1]))
				System.out.println(kor[1]);
			else if(in.equals(eng[2]))
				System.out.println(kor[2]);
			else if(in.equals(eng[3]))
				System.out.println(kor[3]);
			else if(in.equals(eng[4]))
				System.out.println(kor[4]);
			else if(exit.equals(in))
				break;
			else if(EXIT.equals(in))
				break;
			else
				System.out.println("그런 영어단어 없습니다");
				
			}
/*하나 하나 이퀄함수를 이용하여 비교하여 값을 출력하는 와일문을 만들었고 나머지는 그런영어단어 없다는 것으로 디폴트값을 설정 하였습니다*/
		scanner.close();
	}
}
