import java.util.Scanner;

public class Equals{
	public static void main(String[] avgs){
		Scanner scanner=new Scanner(System.in);
		String eng[]={"student","love","java","happy","future"};
		String kor[]={"�л�","���","�ڹ�","�ູ��","�̷�"};
		String in;
		String exit ="exit";
		String EXIT="EXIT";
		/*Ż���ɾ �빮�� �ҹ��� �� �� �־�� �Ҳ� ���� �̷��� ����ϴ�*/
		while(true)
		{
			System.out.println("���� �ܾ �Է��ϼ���>>");
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
				System.out.println("�׷� ����ܾ� �����ϴ�");
				
			}
/*�ϳ� �ϳ� �����Լ��� �̿��Ͽ� ���Ͽ� ���� ����ϴ� ���Ϲ��� ������� �������� �׷�����ܾ� ���ٴ� ������ ����Ʈ���� ���� �Ͽ����ϴ�*/
		scanner.close();
	}
}
