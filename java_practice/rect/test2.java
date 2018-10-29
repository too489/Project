interface AdderInterface{
	int add(int x,int y);
	int add(int n);
	}

class MyAdder implements AdderInterface //�������̽��� �����ϴ� class�� MyAdder�� ���Ͽ����ϴ�
{
	public int add(int x,int y){return x+y;}
	public int add(int n){
	int sum=0;

	for(int i=1;i<=n;i++){sum+=i;} //for���� �̿��Ͽ� n������ �������� �����Ͽ����ϴ�
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