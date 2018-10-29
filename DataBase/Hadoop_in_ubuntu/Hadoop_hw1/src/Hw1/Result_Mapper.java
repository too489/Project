package Hw1;

import java.io.IOException;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.WritableComparable;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;

public class Result_Mapper extends MapReduceBase
    implements Mapper<LongWritable , Text ,Text ,LongWritable >{
	private Text Loc = new Text();
	private LongWritable Peo=new LongWritable();
	@Override
	public void map(LongWritable key, Text value, OutputCollector<Text, LongWritable> output, Reporter reporter)
			throws IOException {

		String st = value.toString();//value값을 받아와서 자바에서 쓸수있는 string 으로 변	
		String[] splits = st.split(" ");
		String[] Time = splits[2].split(":");//시 분으로 나누

		if(Integer.parseInt(Time[0])>5) {
			//시간이 6보다 크그냥 지나가
		}else
		{
				if(Run_test.Most_Loc[0].equals(splits[3])||Run_test.Most_Loc[1].equals(splits[3])||Run_test.Most_Loc[2].equals(splits[3])||Run_test.Most_Loc[3].equals(splits[3])) {
				Loc.set(splits[3]);
				Peo.set(new Long(splits[0]));

				output.collect(Loc, Peo);
			}
		}
		
	}
}


