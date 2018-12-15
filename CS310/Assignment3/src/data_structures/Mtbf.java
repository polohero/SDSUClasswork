package data_structures;

import java.lang.Math;
import java.io.FileReader;
import java.io.BufferedReader;

/**
 * A class that will load known and unknown
 * data sets in order to make decisions about
 * what hard drive brand is expected based
 * on the data.
 * @author cwixom (masc0582)
 */
public class Mtbf {

	/**
	 * The type of Tree data structure that is 
	 * used. The options are "balancedtree" and 
	 * "redblacktree".
	 */
	private String _dataStructureType;
	/**
	 * The Tree variable that is used to 
	 * store the data.
	 */
	private Tree<Drive> _tree;
	/**
	 * The "known" filename. That is 
	 * loaded into the tree.
	 */
	private String _knownFileName;
	/**
	 * The unknown data that will need
	 * to be identified.
	 */
	private String _unknownFileName;
	
	/**
	 * Stores the results from the addition
	 * of elements to the tree.
	 */
	private LoadResults _loadResults = 
		new LoadResults();
	/**
	 * Stores the results from getting
	 * data from the tree.
	 */
	private GetFromTreeResults _getResults = 
		new GetFromTreeResults();
	
	/**
	 * Default value for the known filename
	 * files;
	 */
	private static final String KNOWN_FILENAME = 
		"C:\\CS310\\Assignment3\\src\\data\\mtbf.txt";
	/**
	 * Default value for the unknown filename
	 * files;
	 */
	private static final String UNKNOWN_FILENAME = 
		"C:\\CS310\\Assignment3\\src\\data\\unknown_mtbf.txt";
	
	private static final int NUMBER_OF_KNOWN_TO_USE = 1000;
	
	/**
	 * The entry point into the MTBF 
	 * application. NOTE: The requirements
	 * did not specify how the data with the
	 * percentages was supposed to be returned.
	 * So, my instance Mtbf.run() will return an object,
	 * but calling the static main will output
	 * to the console. You can modify the static
	 * final variables to change where the filename 
	 * is looking, or pass in the values via the
	 * arguments.
	 * @param args
	 */
	public static void main(String[] args) {
		// Check if there are any arguments.
		// If there are 3, it will specify what
		// type of data structure to use,
		// as well as what files.
		if(args.length == 3){
			try{
				runOnce(
					args[0], 
					args[1], 
					args[2], 
					NUMBER_OF_KNOWN_TO_USE);
			}
			catch(Exception exception){
				exception.printStackTrace();
			}
		}
		// If there are 4 arguments. The 4th one
		// should be the number of known to
		// use in a batch.
		else if(args.length == 4){
			try{
				runOnce(
					args[0], 
					args[1], 
					args[2], 
					Integer.parseInt(args[3]));
			}
			catch(Exception exception){
				exception.printStackTrace();
			}
		}
		// Else just run against the default 
		// values.
		else if(args.length == 0){
			runOnce(
				"balancedtree", 
				KNOWN_FILENAME, 
				UNKNOWN_FILENAME, 
				NUMBER_OF_KNOWN_TO_USE);
			runOnce(
				"redblacktree", 
				KNOWN_FILENAME, 
				UNKNOWN_FILENAME, 
				NUMBER_OF_KNOWN_TO_USE);
		}
	}
	
	/**
	 * Runs a single instance of the 
	 * MTBF process.
	 * @param dataStructure
	 * @param knownFile
	 * @param unknownFile
	 * @param numberOfKnown
	 */
	private static void runOnce(
		String dataStructure,
		String knownFile,
		String unknownFile,
		int numberOfKnown){
		
		Mtbf mtbf = 
			new Mtbf(
				dataStructure, 
				knownFile, 
				unknownFile);
		
		UnknownResults results = 
			mtbf.run(numberOfKnown);
		
		System.out.println(results.getResultsReport());
	}

	/**
	 * C-Tor.
	 * @param dataStructureType
	 * @param knownFileName
	 * @param unknownFileName
	 */
	public Mtbf(String dataStructureType,
				String knownFileName,
				String unknownFileName){
		validateString(dataStructureType,"dataStructureType");
		validateString(knownFileName,"knownFileName");
		validateString(unknownFileName,"unknownFileName");
		_dataStructureType = dataStructureType;
		getTree(_dataStructureType);
		_knownFileName = knownFileName;
		_unknownFileName = unknownFileName;
	}
	
	/**
	 * Runs the MTBF calculations.
	 * @param numberOfKnownAtATime
	 * @return
	 */
	public UnknownResults run(int numberOfKnownAtATime){
		
		// Sets the return variable.
		UnknownResults results = 
			new UnknownResults(_dataStructureType);
		
		int count = 0;
		int totalCount = 0;
		
		try 
    	{
    	    BufferedReader in = 
    	    	new BufferedReader(
    	    		new FileReader(_unknownFileName));
    	    
    	    String line = null;
    	    
    	    // Load all the known data
    	    // into the tree.
    	    loadKnown(totalCount, totalCount+numberOfKnownAtATime);
    	    
    	    // Loop through each line in the
    	    // unknown data.
    	    while ((line = in.readLine()) != null) {
    	    	if(count == numberOfKnownAtATime){
    	    		loadKnown(totalCount, totalCount+numberOfKnownAtATime);
    	    		count = 0;
    	    	}
	    		String[] values = line.split("\t");
	    		// Only take good lines. Bad data
	    		// will be ignore.
	    		if(values.length >= 2){
	    			Drive drive = 
	    				new Drive(
	    					values[0], 
	    					Double.parseDouble(values[1]));
	    			
	    			// Get the ceiling and floor, and use
	    			// that to determine what
	    			// brand the hard drive is.
	    			long startTime = System.nanoTime();
	    			Drive ceiling = _tree.getCeiling(drive);
	    			long endTime = System.nanoTime();
	    			Drive floor = _tree.getFloor(drive);
	    			long endTime2 = System.nanoTime();
	    			_getResults.add(startTime, endTime);
	    			_getResults.add(endTime, endTime2);
	    			
	    			UnknownResult result = 
	    				getResult(
	    					drive, 
	    					ceiling, 
	    					floor);
	    			
	    			// Now that we know what brand
	    			// it is. Set it, and set it 
	    			// in the tree so the data is 
	    			// updated.
	    			drive.setBrand(result.getBrand());
	    			startTime = System.nanoTime();
	    			_tree.set(drive);
	    			endTime = System.nanoTime();
	    			_getResults.add(startTime, endTime);
	    			
	    			// Increment the count of the results.
	    			results.increment(result);
	    		}
	    		
	    		count++;
	    		totalCount++;
    	    }
    	    in.close();
    	} 
    	catch(Exception exception){
    		throw new RuntimeException(exception);
    	}
		
		results.addLoadResults(_loadResults);
		results.addGetResults(_getResults);
		
		return results;
	}
	
	/**
	 * Based on the ceiling, and floor
	 * determine the type of the 
	 * drive.
	 * @param drive
	 * @param ceiling
	 * @param floor
	 * @return
	 */
	private UnknownResult getResult(
		Drive drive,
		Drive ceiling,
		Drive floor){
		UnknownResult result = null;
		
		// If there is no ceiling or floor
		// we have nothing to compare against
		// so let it be set as unknown.
		if(null == ceiling && null == floor){
			result = new UnknownResult("unknown");
		}
		else{
			// If there is only a ceiling
			// use the floor.
			if(null == ceiling){
				result = 
	    			new UnknownResult(
	    				floor.getBrand());
			}
			// If there is only a floor
			// use the ceiling.
			else if(null == floor) {
				result = 
		    		new UnknownResult(
		    			ceiling.getBrand());
			}
			// Otherwise, use the
			// data that is closer to the
			// original drive to determine
			// the brand.
			else{
				result = 
					new UnknownResult(
						findClosest(
							ceiling, 
							floor, 
							drive).getBrand()
							);
			}
		}
		
		return result;
	}
	
	/**
	 * Finds the Drive that is 
	 * closer to the original data passed in.
	 * @param ceiling
	 * @param floor
	 * @param data
	 * @return
	 */
	private Drive findClosest(
		Drive ceiling, 
		Drive floor, 
		Drive data){
		if(Math.abs(data.getMtbf() - ceiling.getMtbf()) < 
		   Math.abs(data.getMtbf() - floor.getMtbf())){
			return ceiling;
		}
	    return floor;
	}
	
	/**
	 * Loads the known data 
	 * into the tree based on the
	 * indexes passed in.
	 * @param start
	 * @param end
	 */
	private void loadKnown(int start, int end){

    	try 
    	{
    		_tree.clear();
    		
    	    BufferedReader in = 
    	    	new BufferedReader(
    	    		new FileReader(_knownFileName));
    	    
    	    int count = 0;
    	    
    	    String line = null;

    	    while ((line = in.readLine()) != null) {
 
    	    	if(count >= start && count <= end){
    	    		String[] values = line.split("\t");
    	    		// Only take good lines. Bad data
    	    		// will be ignore.
    	    		if(values.length >= 2){
    	    			Drive drive = new Drive(values[0], Double.parseDouble(values[1]));
    	    			long startTime = System.nanoTime();
    	    			_tree.add(drive);
    	    			long endTime = System.nanoTime();
    	    			_loadResults.add(startTime, endTime);
    	    		}
    	    	}
    	    	else if (count > end){
    	    		break;
    	    	}
    	    	count++;
    	    }
    	    in.close();
    	} 
    	catch(Exception exception){
    		throw new RuntimeException(exception);
    	}
	}
	
	/**
	 * Validates a string is
	 * valid.
	 * @param stringToValidate
	 * @param name
	 */
	private void validateString(
			String stringToValidate,
			String name){
		if(null == stringToValidate){
			throw new NullPointerException(
					name + " is NULL.");
		}
		if(stringToValidate.equals("")){
			throw new NullPointerException(
					name + " is Empty.");
		}
	}
	
	/**
	 * Creates the tree based on the
	 * data structure type variable.
	 * @param dataStructureType
	 */
	private void getTree(String dataStructureType){
		if(dataStructureType.equals("balancedtree")){
			_tree = new BalancedTree<Drive>();
		}
		else if(dataStructureType.equals("redblacktree")){
			_tree = new RedBlackTree<Drive>();
		}
		else{
			throw new IllegalArgumentException(
					"Unknown dataStructureType " + dataStructureType);
		}
	}
}
