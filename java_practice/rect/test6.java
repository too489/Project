import java.util.Scanner;
/*문제에서 주어진 것과 비슷하게 만들어 객체를 생성할때 리턴값을 각모양의 string값을 리턴하도록 하였습니다*/
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
		}/*여기서 리턴값을 choise안에 들어온 값을 리턴값으로 출력하여 바로 저장되게 하였습니다*/
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int sel,select,num=0,i,count=0;
		String [] List=new String[10];
		/*NULL이라는 문자로 배열전체를 셋팅하였습니다*/
		for(i=0;i<List.length;i++)
			List[i]="NULL";
		while(true){
		System.out.print("삽입(1), 삭제(2), 모두 보기(3), 종료(4)>>");
		select=sc.nextInt();
		switch(select){/*제일 처음 받는걸 select라고 두고 만약 4가나오면 프로그램이 종료되게 만들었습니다*/
			case 1: 
				{
					System.out.print("도형 종류 Line(1), Rect(2), Circle(3)>>");
					sel=sc.nextInt();
					switch(sel){

					case 1: List[count]=choise(new Line()); count++;break;

					case 2: List[count]=choise(new Rect());count++;break;

					case 3: List[count]=choise(new Circle());count++;break;
										
				}	
					
				}break;
						
			case 2: {
					System.out.print("삭제할 도형의 위치 >>");
					sel=sc.nextInt();
					if(List[(sel-1)]!="NULL"){
						List[(sel-1)]="NULL";
						break;
						}

					else if(List[(sel-1)]=="NULL"){
						System.out.println("삭제할 수 없습니다");
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
