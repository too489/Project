import java.util.Scanner;
/*�������� �־��� �Ͱ� ����ϰ� ����� ��ü�� �����Ҷ� ���ϰ��� ������� string���� �����ϵ��� �Ͽ����ϴ�*/
class Shape{
	public String input(){
		return "Shape";
		}
	}
class Line extends Shape{
	public String input(){
		return "Line";
		}
	}
class Rect extends Shape{
	public String input(){
		return "Rect";
		}
	}
class Circle extends Shape{
	public String input(){
		return "Circle";
		}
	}

public class test6{
	static String choise(Shape p){
		return p.input();
		}/*���⼭ ���ϰ��� choise�ȿ� ���� ���� ���ϰ����� ����Ͽ� �ٷ� ����ǰ� �Ͽ����ϴ�*/
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int sel,select,num=0,i,count=0;
		String [] List=new String[10];
		/*NULL�̶�� ���ڷ� �迭��ü�� �����Ͽ����ϴ�*/
		for(i=0;i<List.length;i++)
			List[i]="NULL";
		while(true){
		System.out.print("����(1), ����(2), ��� ����(3), ����(4)>>");
		select=sc.nextInt();
		switch(select){/*���� ó�� �޴°� select��� �ΰ� ���� 4�������� ���α׷��� ����ǰ� ��������ϴ�*/
			case 1: 
				{
					System.out.print("���� ���� Line(1), Rect(2), Circle(3)>>");
					sel=sc.nextInt();
					switch(sel){

					case 1: List[count]=choise(new Line()); count++;break;

					case 2: List[count]=choise(new Rect());count++;break;

					case 3: List[count]=choise(new Circle());count++;break;
										
				}	
					
				}break;
						
			case 2: {
					System.out.print("������ ������ ��ġ >>");
					sel=sc.nextInt();
					if(List[(sel-1)]!="NULL"){
						List[(sel-1)]="NULL";
						break;
						}

					else if(List[(sel-1)]=="NULL"){
						System.out.println("������ �� �����ϴ�");
						break;
						}
					}break;


			case 3: for(i=0;i<count;i++)
					System.out.print(List[i] + " ");
				System.out.println(" ");
				break;
				
			case 4: break; 


			}
		if(select==4)
			break;
		}
		sc.close();
	}

}
