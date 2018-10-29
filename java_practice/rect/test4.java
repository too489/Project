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
	/*��ü�� �����ϴ� �����ڸ� ���� �� �ű⿡�� �Էµ����� ���� �޾Ƽ� color�� �־��־����ϴ�*/
	ColorPoint(int x,int y,String Color)
	{
		super(x,y);
		this.Color=Color;
	}
	/*���⼱ super�� �����͸� �������ִ� ���� �־����ϴ�*/
	public void setPoint(int x, int y){super.move(x,y);}
	/*���⼱ ���� �ٲٴ� �Լ��� �����Ͽ����ϴ�*/
	public void setColor(String Color){this.Color=Color;}
	public void show(){ System.out.print(Color+"������"); super.superShow();}
	/*���⼭ show�� �����ٶ� super�� �ִ� show�� ���� �ҷ��־� ������µǰ� �Ͽ����ϴ�*/

}

public class test4{
	public static void main(String[] args){
		ColorPoint cp = new ColorPoint(5,5,"YELLOW");
		cp.setPoint(10,20);
		cp.setColor("GREEN");
		cp.show();

	}
}