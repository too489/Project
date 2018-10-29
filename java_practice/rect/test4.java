class Point{
	private int x,y;
	public Point(int x, int y){ this.x=x; this.y=y;}
	public int getX(){return x;}
	public int getY(){return y;}
	protected void move(int x, int y){this.x=x; this.y=y;}
	public void superShow(){System.out.print("("+x+","+y+")");}
	}
class ColorPoint extends Point{

	private	String Color;
	/*객체를 생성하는 생성자를 만든 후 거기에다 입력들어오는 값을 받아서 color로 넣어주었습니다*/
	ColorPoint(int x,int y,String Color)
	{
		super(x,y);
		this.Color=Color;
	}
	/*여기선 super의 포인터를 변경해주는 값을 넣었습니다*/
	public void setPoint(int x, int y){super.move(x,y);}
	/*여기선 색을 바꾸는 함수를 생성하였습니다*/
	public void setColor(String Color){this.Color=Color;}
	public void show(){ System.out.print(Color+"색으로"); super.superShow();}
	/*여기서 show를 보여줄때 super에 있는 show도 같이 불러주어 같이출력되게 하였습니다*/

}

public class test4{
	public static void main(String[] args){
		ColorPoint cp = new ColorPoint(5,5,"YELLOW");
		cp.setPoint(10,20);
		cp.setColor("GREEN");
		cp.show();

	}
}