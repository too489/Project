interface AdderInterface{
	int add(int x,int y);
	int add(int n);
	}

class MyAdder implements AdderInterface //인터페이스를 구현하는 class를 MyAdder로 정하였습니다
{
	public int add(int x,int y){return x+y;}
	public int add(int n){
	int sum=0;

	for(int i=1;i<=n;i++){sum+=i;} //for문을 이용하여 n까지의 정수합을 리턴하였습니다
	return sum;
	}
}

public class test2{
	public static void main(String[] args){
		MyAdder adder = new MyAdder();
		System.out.println(adder.add(5,10));
		System.out.println(adder.add(10));
	}
}