package data_structures;

/**
 * This class stores information on
 * the time it takes for a particular 
 * tree to add data. 
 * @author cwixom (masc0582)
 */
public class LoadResults {
	/**
	 * The average time it takes to 
	 * add a new element to the 
	 * tree.
	 * @return
	 */
	public double average(){return _averageAdd;}
	private double _averageAdd = 0;
	
	/**
	 * The max time it takes to add
	 * a new element to the tree.
	 * @return
	 */
	public long max(){return _maxAdd;}
	private long _maxAdd= 0;
	
	/**
	 * The min time it takes to add
	 * a new element to the tree.
	 * @return
	 */
	public long min(){return _minAdd;}
	private long _minAdd= Long.MAX_VALUE;
	
	/**
	 * Increments the average, max and min
	 * times it takes to add elements to
	 * the tree.
	 * @param startTime
	 * @param endTime
	 */
	public void add(long startTime, long endTime){
		long difference = endTime - startTime;
		
		if(difference > _maxAdd){_maxAdd = difference;}
		if(difference < _minAdd){_minAdd = difference;}
		
		_averageAdd = (_averageAdd + (double)difference) / 2;
	}
}
