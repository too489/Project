import java.util.Scanner;
public class Multiple{
	public static void main(String[] args){
		Scanner scanner = new Scanner(System.in);
		
		int n[];
		n = new int[10]; //�迭 ������ 10���� ������ ����ϴ�
		
		System.out.print("���� 10�� �Է� >>");
		
		for(int i=0;i<n.length;i++)//���� 10���� �о�����
		{
			n[i] = scanner.nextInt();
		}

		System.out.print("3�� ��� : ");

/*��� ������ �� �������� 0�� �Ǵ� ���� ����߽��ϴ�*/

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
