import java.util.Scanner;

public class RockPaperScissors{
public static void main(String[] avgs){
	Scanner scanner= new Scanner(System.in);

	String rpc[]={"����","��","����"};
	String u;
/* ����� �Է��� ���̶�� �ǹ̿��� ����ڰ� �Է��ϴ� ������ u�� ��� ������ڸ� ���� ������������ �⺻ �迭 ���� �̸��� rpc��� ���߽��ϴ�*/
	
	System.out.println("��ǻ�Ϳ� ���� ���� �� ������ �մϴ�.");
	System.out.println("���� ���� ��!");
	int n;
	
/*���⼱ �������� �̿��Ͽ� �� ��� �� ��� �� ��� �����Ͽ��� �����Լ��� å�� �ִ� ���� �����Ͽ� �������ϴ�*/
	while(true){
		u=scanner.next();
		n =(int)(Math.random()*3);
		System.out.println("���� ���� ��!");
		if(u.equals("�׸�")){
			System.out.println("������ �����մϴ�...");
			break;
			}
		else
			System.out.println("�ٽ�!");
		
		if(rpc[n].equals("����")){
			if(u.equals("����")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " �����ϴ�");
				}
			else if(u.equals("����")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " ����ڰ� �̰���ϴ�.");
				}
			else if(u.equals("��")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " ��ǻ�Ͱ� �̰���ϴ�.");
				}
				continue;
			}
		else if(rpc[n].equals("����")){
			if(u.equals("����")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " �����ϴ�");
				}
			else if(u.equals("��")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " ����ڰ� �̰���ϴ�.");
				}
			else if(u.equals("����")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " ��ǻ�Ͱ� �̰���ϴ�.");
				}
				continue;
			}
			
		else if(rpc[n].equals("��")){
			if(u.equals("��")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " �����ϴ�");
				}
			else if(u.equals("����")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " ����ڰ� �̰���ϴ�.");
				}
			else if(u.equals("����")){
				System.out.println(" ����� = "+u+", ��ǻ�� = "+rpc[n]+ " ��ǻ�Ͱ� �̰���ϴ�.");
				}
				continue;
			}
		
		
		}
	scanner.close();
	
	}
}
