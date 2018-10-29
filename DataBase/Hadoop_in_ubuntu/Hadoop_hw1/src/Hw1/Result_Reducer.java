package Hw1;


import java.io.IOException;
import java.util.*;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.WritableComparable;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reducer;
import org.apache.hadoop.mapred.Reporter;



public class Result_Reducer <K extends WritableComparable, V extends Writable> 
extends MapReduceBase implements Reducer<Text, LongWritable, Text, Text> {
		private Text result_key = new Text();
		private Text result_value = new Text();
		public Map<String ,List> map = new HashMap<String, List>();
		
		@Override
		public void reduce(Text key, Iterator<LongWritable> values, OutputCollector<Text, Text> output, Reporter reporter)
				throws IOException {
			
			ArrayList list=new ArrayList();
			while(values.hasNext()) {
				list.add(Integer.parseInt(values.next().toString()));
			}
			Collections.sort(list,new Comparator<Integer>() {
				public int compare(Integer o1, Integer o2) {
					return o1.compareTo(o2);
				}
			});
			Run_test.array_key.add(key.toString());
			Run_test.array_value.add(list.toString());
			
			output.collect(key,new Text(list.toString()));
			String k=key.toString();
			MongoDB_conf db = new MongoDB_conf(k,list);
			//map.put(key.toString(),list);
		}
		public void cleanup(OutputCollector<Text,Text> output,Reporter reporter) throws IOException, InterruptedException {
			sort_value(map,output);
		}
		public void sort_value(Map<String,List> unsortMap,OutputCollector<Text,Text> output) throws IOException {
			List<Map.Entry<String , List>> list= new LinkedList<Map.Entry<String,List>>(unsortMap.entrySet());
			for(Map.Entry<String,List> entry : list) {
				output.collect(new Text(entry.getKey()), new Text(entry.getValue().toString()));			
		}
			

//					
//		public void cleanup(OutputCollector<Text,List> output,Reporter reporter) throws IOException, InterruptedException {
//
//			sort_value(map,output);
//						
//		}
//		public void sort_value(Map<String,List> unsortMap,OutputCollector<Text,LongWritable> output) throws IOException {
//			List<Map.Entry<String , List>> list= new LinkedList<Map.Entry<String,List>>(unsortMap.entrySet());
//			for(Map.Entry<String,List> entry : list) {
//				System.out.println("????????????????실행안되니??");
//				output.collect(new Text(entry.getKey()), (entry.getValue()));			
//		}
////		
//		public void sortMap (Map<String,String> unsortMap,OutputCollector<Text,Text> output ) throws IOException, InterruptedException{
//			Map<String, String> hashmap = new HashMap<String,String>();
//			List<Map.Entry<String,String>> list = new LinkedList<Map.Entry<String,String>>(unsortMap.entrySet());
//			Collections.sort(list, new Comparator<Map.Entry<String,Integer>>(){
//				public int compare (Map.Entry<String,Integer> o1, Map.Entry<String,Integer> o2) {
//					return o2.getValue().compareTo(o1.getValue());
//				}
//			});
//			for(Map.Entry<String,Integer> entry : list) {
//				Run_test.Most_Loc[count]=entry.getKey();
//				context.write(new Text(entry.getKey()), new LongWritable(entry.getValue()));
//				hashmap.put(entry.getKey(),entry.getValue());count++;
			//}
			
		}
		


}


