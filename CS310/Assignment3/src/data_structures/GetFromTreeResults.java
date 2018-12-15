package data_structures;

/**
 * This class stores information on
 * the time it takes for a particular 
 * tree to get data from the tree. 
 * @author cwixom (masc0582)
 */
public class GetFromTreeResults {
	/**
	 * The average time to get data
	 * from the tree.
	 * @return
	 */
	public double average(){return _average;}
	private double _average = 0;
	
	/**
	 * The max time to get data from
	 * the tree.	
	 * @return
	 */
	public long max(){return _max;}
	private long _max= 0;
	
	/**
	 * The min time to get data from 
	 * the tree.
	 * @return
	 */
	public long min(){return _min;}
	private long _min= Long.MAX_VALUE;
	
	/**
	 * Increments the average, max and min
	 * time it takes to get data from the
	 * tree.
	 * @param startTime
	 * @param endTime
	 */
	public void add(long startTime, long endTime){
		long difference = endTime - startTime;
		
		if(difference > _max){_max = difference;}
		if(difference < _min){_min = difference;}
		
		_average = (_average + (double)difference) / 2;
	}
}
