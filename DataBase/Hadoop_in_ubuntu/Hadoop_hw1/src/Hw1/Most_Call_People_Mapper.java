package Hw1;
import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;


public class Most_Call_People_Mapper extends Mapper<LongWritable, Text, Text, LongWritable>{
	private Text Text = new Text();
	private final static LongWritable one=new LongWritable(1);
	
	public void map(LongWritable key, Text value ,Context context) throws IOException, InterruptedException{
		String st = value.toString();//value값을 받아와서 자바에서 쓸수있는 string 으로 변	
		String[] splits = st.split(" ");
		String[] Time = splits[2].split(":");//시 분으로 나누
		if(Integer.parseInt(Time[0])>5) {
			//		System.out.println("????????????????실행안되니??");
			//시간이 6보다 크그냥 지나가
		}else
		{
			Text.set(splits[0]);
			context.write(Text,one);
		}
	}
}
