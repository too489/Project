package Hw1;
import java.io.IOException;
import java.util.*;
import java.util.Map.Entry;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.Reducer.Context;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;


public class Most_Call_People_Reducer extends Reducer<Text,LongWritable, Text, LongWritable>{
		private LongWritable result = new LongWritable();
		public Map<String ,Integer> map = new HashMap<String, Integer>();
		public void reduce(Text key,Iterable<LongWritable> values,Context context)throws IOException, InterruptedException{
			int sum = 0;
			for(LongWritable val : values) {
				sum+=val.get();
			}
//			result.set(sum);
			//context.write(key,result);
			map.put(key.toString(),sum);
			
		}	
		public void cleanup(Context context) throws IOException, InterruptedException {
			
			sortMap(map,context);
			
		}
		
		public void sortMap (Map<String,Integer> unsortMap , Context context) throws IOException, InterruptedException{
			Map<String, Integer> hashmap = new HashMap<String,Integer>();
			int count = 0;
			List<Map.Entry<String,Integer>> list = new LinkedList<Map.Entry<String,Integer>>(unsortMap.entrySet());
			Collections.sort(list, new Comparator<Map.Entry<String,Integer>>(){
				public int compare (Map.Entry<String,Integer> o1, Map.Entry<String,Integer> o2) {
					return o2.getValue().compareTo(o1.getValue());
				}
			});
			for(Map.Entry<String,Integer> entry : list) {
				if(count>4)
					break;
				context.write(new Text(entry.getKey()), new LongWritable(entry.getValue()));
				hashmap.put(Run_test.Most_Peo[count]=entry.getKey(),entry.getValue());count++;
			}
			
		}
}
