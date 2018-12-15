package ipResolver;

import java.util.Iterator; 
import java.io.FileReader;
import java.io.BufferedReader;

import data_structures.DictionaryI;
import data_structures.HashDictionary;
import data_structures.ArrayDictionary;
import data_structures.LinkedListDictionary;

/**
 * The IPManager is responsible for interacting 
 * with the dictionary implementations to 
 * add, delete, change, and search the 
 * dictionaries
 * @author cwixom (masc0582)
 */
public class IPManager {
 
	private DictionaryI<IPAddress, String> _dictionary;
	
	public static final String ARRAY = "array";
	public static final String LINKED_LIST = "linkedlist";
	public static final String HASH = "hash";
	
	private static final String TAB_REGEX = "\t";

     /**
      * Constructor, the type of dictionary to 
      * use (hash, linkedlist, array)
      * and the initial size of the 
      * supporting dictionary
      * @param dictionaryType The type of dictionary to use.
      * @param initialSize The initial size of the dictionary.
      * @exception IllegalArgumentException
      * For invalid arguments.
      */
        public IPManager(String dictionaryType, int initialSize){
        	_dictionary = 
        		createDictionary(
        			dictionaryType,
        			initialSize);
        }
    
        /**
         * Loads the text file with the given 
         * fileName parameter, and creates a dictionary
         * in memory. The data file consists of
         * key:value pairs, one per line, 
         * separated by tabs. Returns false if there
         * were any errors loading the file.
         * @param fileName The file to load the IPAddresses
         * from.
         */
        public boolean load(String fileName){
        	// Check for an invalid argument.
        	if(null == fileName ||
        	   fileName.equals("")){
        		return false;
        	}
        	
        	// Try to read in the file, if there are
        	// any errors. Return a false.
        	try 
        	{
        	    BufferedReader in = 
        	    	new BufferedReader(
        	    		new FileReader(fileName));
        	    
        	    String line = null;
        	    while ((line = in.readLine()) != null) {
        	        String[] values = line.split(TAB_REGEX);
        	        // Only take good lines. Bad data
        	        // will be ignore.
        	        if(values.length >= 2){
        	        	String name = values[0];
        	        	IPAddress ip = 
        	        		new IPAddress(values[1]);
        	        	add(ip, name);
        	        }
        	    }
        	    in.close();
        	} 
        	catch(Exception exception){
        		return false;
        	}
        	
        	return true;
        }

     /**
      *  Insert a new pair into the dictionary.  
      *  Returns true if the insertion succeeds, 
      *  false if the max capacity has been
      *  reached, or the IP is a duplicate
      * @param IP The IP Address
      * @param name The DNS Name
      * @return
      */
        public boolean add(IPAddress IP, String name){
        	// Check for nulls.
        	if(null == IP || 
        	   null == name){
        		return false;
        	}
        	
        	return _dictionary.add(IP, name);
        }
        
        /**
         * Removes the pair identified by 
         * the IP from the dictionary.
         * Returns true if found and 
         * removed, otherwise false
         * @param IP The IP Address to remove.
         * @return
         */
        public boolean delete(IPAddress IP){
        	// Check nulls.
        	if(null == IP){
        		return false;
        	}
        	
        	return _dictionary.delete(IP);
        }
        
        /**
         * Returns the canonical name 
         * associated with the given IP
         * @param IP The IP Address to 
         * lookup the DNS Name for.
         * @return
         */
        public String findName(IPAddress IP){
        	// Check nulls.
        	if(null == IP){
        		return null;
        	}
        	
        	return _dictionary.getValue(IP);
        }
        
        /**
         * Returns the IP, given the name.
         * @param name
         * @return
         */
        public IPAddress findIP(String name){
        	if(null == name){
        		return null;
        	}
        	
        	return _dictionary.getKey(name);
        }
     
        /**
         * Returns an Iterator of the IPs 
         * currently in the dictionary
         * @return
         */
        public Iterator<IPAddress> IPs(){
        	return _dictionary.iterator();
        }
        
        /**
         * Returns an Iterator of the 
         * names currently in the dictionary
         * The order must be the same 
         * as the IPs Iterator
         * @return
         */
        public Iterator<String> names(){
        	return _dictionary.values();
        }

        /**
         * Print the IP addresses and canonical names for
         * all of the pairs in the dictionary within the given range
         * inclusive.
         */
        public void printAll(){
        	System.out.println(_dictionary.toString());
        }
        
        /**
         * Performs a switch/case on the name to find
         * the correct dictionary.
         * @param name The name of the dictionary.
         * @param initialSize The initial size.
         * @return
         */
        private DictionaryI<IPAddress, String> createDictionary(
        		String name,
        		int initialSize){
        	if(name == null){
        		throw new IllegalArgumentException(
        			"DictionaryType cannot be null.");
        	}
        	else if(name.equals(ARRAY)){
        		return new ArrayDictionary
        				<IPAddress, String>(initialSize);
        	}
        	else if(name.equals(LINKED_LIST)){
        		return new LinkedListDictionary
        				<IPAddress, String>();
        	}
        	else if(name.equals(HASH)){
        		return new HashDictionary
        				<IPAddress, String>(initialSize);
        	}
        	
    		throw new IllegalArgumentException(
        			"Unknown DictionaryType: " + name);
        }
}