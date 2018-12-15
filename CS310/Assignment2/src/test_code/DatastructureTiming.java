package test_code;
import data_structures.*;

import java.math.*;
import java.util.ArrayList;

public class DatastructureTiming {


	public static void main(String[] args) {
		
		int count = 100000;
			System.out.println("Hash:");
			ArrayList<Timing> hash = timeHash(count, count);
			System.out.println("Add:" + hash.get(0));
			System.out.println("Get:" + hash.get(1));
			System.out.println("Delete:" + hash.get(2));
			System.out.println("");
			
			ArrayList<Timing> linked = timeLinked(count, count);
			System.out.println("LinkedList:");
			System.out.println("Add:" + linked.get(0));
			System.out.println("Get:" + linked.get(1));
			System.out.println("Delete:" + linked.get(2));
			
			ArrayList<Timing> array = timeArray(count, count);
			System.out.println("Array:");
			System.out.println("Add:" + array.get(0));
			System.out.println("Get:" + array.get(1));
			System.out.println("Delete:" + array.get(2));
		}
	
	private static ArrayList<Timing> timeHash(int countItems, int countIterations){
		HashDictionary<String, String> hash = 
			new HashDictionary<String,String>(2);
		
		return time(hash, countItems, countIterations);
	}
	
	private static ArrayList<Timing> timeLinked(int countItems, int countIterations){
		LinkedListDictionary<String, String> hash = 
			new LinkedListDictionary<String,String>();
		
		return time(hash, countItems, countIterations);
	}
	
	private static ArrayList<Timing> timeArray(int countItems, int countIterations){
		ArrayDictionary<String, String> hash = 
			new ArrayDictionary<String,String>(2);
		
		return time(hash, countItems, countIterations);
	}
	
	private static ArrayList<Timing> time(DictionaryI<String,String> hash, int countItems, int countIterations){
		ArrayList<Long> getTimes = 
			new ArrayList<Long>(countIterations);
		ArrayList<Long> addTimes = 
				new ArrayList<Long>(countIterations);
		ArrayList<Long> deleteTimes = 
				new ArrayList<Long>(countIterations);
		
		ArrayList<Timing> returnList = 
				new ArrayList<Timing>(3);

		long startClock = System.currentTimeMillis()/1000;
		for(int i = 0; i < countItems; i++){
			long start = System.nanoTime();
			hash.add("key" + i, "val" + i);
			long stop = System.nanoTime();
			addTimes.add(stop - start);
		}
		long stopClock = System.currentTimeMillis()/1000;
		System.out.println("Add Took: " + (stopClock - startClock));
		
		returnList.add(calculateTiming(addTimes));
		
		startClock = System.currentTimeMillis()/1000;
		for(int i = 0; i < countItems; i++){
			long start = System.nanoTime();
			hash.getValue("key" + i);
			long stop = System.nanoTime();
			getTimes.add(stop - start);
		}
		stopClock = System.currentTimeMillis()/1000;
		System.out.println("Get Took: " + (stopClock - startClock));
		
		returnList.add(calculateTiming(getTimes));
		
		startClock = System.currentTimeMillis()/1000;
		for(int i = 0; i < countItems; i++){
			long start = System.nanoTime();
			hash.delete("key" + i);
			long stop = System.nanoTime();
			deleteTimes.add(stop - start);
		}
		stopClock = System.currentTimeMillis()/1000;
		System.out.println("Delete Took: " + (stopClock - startClock));
		
		returnList.add(calculateTiming(deleteTimes));
		
		return returnList;
	}
	
	private static Timing calculateTiming(ArrayList<Long> times){
		
		Timing time = new Timing();
		
		long sum = 0;
		
		for(Long singleTime : times){
			if(singleTime > time.max){
				time.max = singleTime;
			}
			if(singleTime < time.min){
				time.min = singleTime;
			}
			sum += singleTime;
		}
		
		time.average = sum / times.size();
		time.stdDev = (long) Math.sqrt(sum / (times.size() - 1)); 
		time.iterations = times.size();

		return time;
	}
	

}
