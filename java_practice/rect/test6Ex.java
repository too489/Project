import java.util.Scanner;
/*�������� �־��� �⺻ ������ ���� �������̵��� �����ϵ� �������� �ʹ� �ٸ��Ը��ϰ��� ����ϴ�*/
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

public class test6Ex{
	static String choise(Shape p){
		return p.input();
		}
/*�ϳ��� �����ϸ� �װ��� �Էµǰ� ���ϵǰԲ��Ͽ����ϴ�*/
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int sel,select,num=0,i,count=0;
		/*�迭�� ����� �����ϴ°� ���Ҳ� ���� �����Ͽ����ϴ�*/
		String [] List=new String[10];
		
		/*for(i=0;i<List.length;i++)
			List[i]="NULL";*/
		/*���Ϲ��� �� 4���� ������ ������ �ݺ��ǰ� �Ͽ����ϴ�.*/
		while(true){
		System.out.print("����(1), ����(2), ��� ����(3), ����(4)>>");
		select=sc.nextInt();
		switch(select){
			case 1: /*�ϳ��� �߰��ɶ����� count�� �ö󰡰��Ͽ����ϴ� �׸��� ���õ� ���� ��ü�� ����� �װ��� �迭�� �־����ϴ�*/
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
					if(List[(sel-1)]!=NULL){
						List[(sel-1)]=NULL;
						break;
						}

					else if(List[(sel-1)]==NULL){
						System.out.println("������ �� �����ϴ�");
						break;
						}
					}break;


			case 3: for(i=0;i<count;i++)
					System.out.print(List[i] + " ");
				System.out.println(" ");
				break;
				
			case 4: break; 

		/*
		Line line=new Line();
		paint(line);
		paint(new Shape());
		paint(new Line());
		paint(new Rect());
		paint(new Circle());*/
			}
		if(select==4)
			break;
		}
		//sc.close();
	}

}
