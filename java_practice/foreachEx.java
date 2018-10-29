public class foreachEx{
public static void main(String[] args){

	int arr[]={1,2,3,4,5};	
	int sum=0;

	for(int k:arr)
	{
		System.out.print(k+ " ");
		sum+=k;
	}
		System.out.println(" 총 합은 "+sum);

	String f[]={"딸기","바나나","사이다","누렁이","이거뭐야"};
	
	for(String s : f)
		System.out.print("시작 "+ s + " " );
}}