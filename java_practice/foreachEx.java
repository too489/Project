public class foreachEx{
public static void main(String[] args){

	int arr[]={1,2,3,4,5};	
	int sum=0;

	for(int k:arr)
	{
		System.out.print(k+ " ");
		sum+=k;
	}
		System.out.println(" �� ���� "+sum);

	String f[]={"����","�ٳ���","���̴�","������","�̰Ź���"};
	
	for(String s : f)
		System.out.print("���� "+ s + " " );
}}