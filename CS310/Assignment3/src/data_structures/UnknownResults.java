package data_structures;

/**
 * The class that contains all
 * results of running the MTBF.
 * @author cwixom (masc0582)
 */
public class UnknownResults {
	
	/**
	 * The type of data structure that was used.
	 */
	private String _dataStructure;
	
	/**
	 * The results array.
	 */
	private UnknownResult[] _results;
	
	/**
	 * The total count of
	 * Drives that were categorized.
	 */
	private int _total = 0;
	
	/**
	 * The total count of brands
	 * that were categorized.
	 */
	private int _count;
	
	private LoadResults _loadResults;
	private GetFromTreeResults _getResults;

	/**
	 * C-Tor
	 */
	public UnknownResults(
		String dataStructure){
		_results = new UnknownResult[5];
		_count = 0;
		_dataStructure = dataStructure;
	}
	
	public void addLoadResults(LoadResults loadResults){
		_loadResults = loadResults;
	}
	
	public void addGetResults(GetFromTreeResults getResults){
		_getResults = getResults;
	}
	
	/**
	 * Increments the count on a specific
	 * brand. If the brand doesn't exist
	 * it will add it new to the array.
	 * @param result
	 */
	public void increment(UnknownResult result){
		UnknownResult addResult = null;
		
		for(int i = 0; i < _count; i++){
			UnknownResult compareResult = _results[i];
			if(compareResult.equals(result)){
				addResult = compareResult;
			}
		}
		
		if(null != addResult){
			addResult.increment();
			_total++;
		}
		else{
			_results[_count] = result;
			_count++;
			_total++;
			if(_count + 2 > _results.length){
				resize();
			}
		}
	}
	
	/**
	 * Returns a string reporting
	 * the results.
	 * @return
	 */
	public String getResultsReport(){
		String returnString = "";
		returnString += "Data Structure: " + _dataStructure + "\n";
		returnString += "Total Drives: " + _total + "\n";
		returnString += "Add Results: " + "\t" + 
					    "Average: " + _loadResults.average() + "\t" +
					    "Max: " + _loadResults.max() + "\t" +
					    "Min: " + _loadResults.min();
		returnString += "\n";
		returnString += "Get Results: " + "\t" + 
			    "Average: " + _getResults.average() + "\t" +
			    "Max: " + _getResults.max() + "\t" +
			    "Min: " + _getResults.min();
						
		returnString += "\n";
		
		for(int i = 0; i < _count; i++){
			UnknownResult result = _results[i];
			returnString += "Brand: " + result.getBrand();
			returnString += "\t";
			int count = result.getCount();
			returnString += "Count: " + count;
			returnString += "\t";
			returnString += "Percentage: " + 
							(double)(100 * 
							((double)count / (double)_total));
			returnString += "\t";
			returnString += "\n";
		}
		
		return returnString;
	}
	
	/**
	 * Resizes the array if it gets too big.
	 */
	private void resize(){
		UnknownResult[] results = new UnknownResult[_count * 2];
		for(int i = 0; i < _count; i++){
			results[i] = _results[i];
		}
		
		_results = results;
	}

}
