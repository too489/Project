import java.util.Scanner;
public class ScannerEx {
	public static void main(String args[]){
	System.out.println("�̸�, ����, ����, ü��, ���ſ��θ� ��ĭ���� �и��Ͽ� �Է��ϼ���");

	Scanner scanner=new Scanner(System.in);
	String name = scanner.next();
	System.out.println("��� �̸��� "+name+"�Դϴ�.");
	String city = scanner.next();
	System.out.println("����� ��� ���ô� " + name + "�Դϴ�.");
	int age=scanner.nextInt();
	System.out.println("����� ���̴�" + age + "�� �Դϴ�.");
	double weight = scanner.nextDouble();
	System.out.println("����� ü����" + weight + "kg�Դϴ�.");
	boolean single = scanner.nextBoolean();
	System.out.println("����� ���� ���δ�" + single + "�Դϴ�.");

	scanner.close();
	}
}