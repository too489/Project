import java.util.Scanner;
/*문제에서 주어진 기본 예제와 같이 오버라이딩을 설정하되 문제에서 와는 다르게리턴값을 줬습니다*/
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
/*하나를 선택하면 그것이 입력되게 리턴되게끔하였습니다*/
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int sel,select,num=0,i,count=0;
		/*배열을 만들어 저장하는게 편할꺼 같아 저장하였습니다*/
		String [] List=new String[10];
		
		/*for(i=0;i<List.length;i++)
			List[i]="NULL";*/
		/*와일문을 줘 4번을 누르기 전까지 반복되게 하였습니다.*/
		while(true){
		System.out.print("삽입(1), 삭제(2), 모두 보기(3), 종료(4)>>");
		select=sc.nextInt();
		switch(select){
			case 1: /*하나가 추가될때마다 count가 올라가게하였습니다 그리고 선택된 것을 객체를 만들어 그것을 배열에 넣었습니다*/
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
					if(List[(sel-1)]!=NULL){
						List[(sel-1)]=NULL;
						break;
						}

					else if(List[(sel-1)]==NULL){
						System.out.println("삭제할 수 없습니다");
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
