import java.util.Scanner;

/*import�� ��ĳ�� �Լ��� ����ִ��� ����߽��ϴ�*/
public class Square
{
	public static void main(String[] arg){
		Scanner scanner = new Scanner(System.in);

/*��ĳ���Լ� �����߽��ϴ�*/

		System.out.println("�� (x,y)�� ��ǥ�� �Է��ϼ���"); 
		int x=scanner.nextInt();// �Ѵ� ��Ʈ������ �޾ҽ��ϴ�
		int y=scanner.nextInt();
		
		if(50<=x && 100>=x && 50<=y && 100>=y)
		System.out.println("��("+x+","+y+")�� (50,50)�� (100,100)�� �簢�� ���� �ֽ��ϴ�.");
/* 50�̻� 100�̳��� ���ǽ��� �����ϸ� �簢������ �ִٰ� �������ϴ�*/

		else
		System.out.println("��("+x+","+y+")�� (50,50)�� (100,100)�� �簢�� ���� �����ϴ�.");
/*�� ���ǽ��� �ƴҶ� ����ϰ� �߽��ϴ�*/
	}
}
