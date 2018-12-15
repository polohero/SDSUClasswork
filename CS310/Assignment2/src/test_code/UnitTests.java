package test_code;

import ipResolver.*;
import data_structures.*;
import java.util.*;

public class UnitTests {

	private static String _fileName = "C:\\CS310\\Assignment2\\src\\data\\ip_names.txt";
	private static boolean _testsPassed = true;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {

		testIPManagerHash();
		testIPManagerArray();
		testIPManagerLinkedList();
		testHashDictionary();
		testLinkedListDictionary();
		testArrayDictionary();
		testIPAddress();
		logTest(_testsPassed, "Not all tests passed.");
	}
	
	private static void testIPManagerHash(){
		
		IPManager manager = 
				new IPManager(IPManager.HASH, 16);
		testIPManager(manager);
	}
	private static void testIPManagerArray(){
		
		IPManager manager = 
				new IPManager(IPManager.ARRAY, 16);
		testIPManager(manager);
	}
	
	private static void testIPManagerLinkedList(){
		
		IPManager manager = 
				new IPManager(IPManager.LINKED_LIST, 16);
		testIPManager(manager);
	}
	
	private static void testIPManager(IPManager manager){
		int count = 200;
		
		logTest(true == manager.load(_fileName), "Unable to load file.");
		logTest(manager.findName(new IPAddress("130.191.208.70")).equals("psfa-1-mac6.sdsu.edu"),
				"Name was not found.");
		logTest(manager.findIP("psfa-1-mac6.sdsu.edu").equals(new IPAddress("130.191.208.70")),
				"IP was not found.");
		
		logTest(manager.delete(new IPAddress("130.191.208.70")) == true,
				"Deleted IP Successfully");
		logTest(manager.findName(new IPAddress("130.191.208.70")) == null,
				"Name should not be found.");
		logTest(manager.findIP("psfa-1-mac6.sdsu.edu") == null,
				"IP should not be found.");
		logTest(manager.add(new IPAddress("130.191.208.70"), "psfa-1-mac6.sdsu.edu") == true,
				"Added IP Successfully.");
		logTest(manager.findName(new IPAddress("130.191.208.70")).equals("psfa-1-mac6.sdsu.edu"),
				"Name was not found.");
		logTest(manager.findIP("psfa-1-mac6.sdsu.edu").equals(new IPAddress("130.191.208.70")),
				"IP was not found.");
		int i = 0;
		Iterator<String> nameIterator = manager.names();
		while(nameIterator.hasNext()){
			logTest(true, nameIterator.next());
			i++;
		}
		logTest(i == count, "Counts for Names don't match.");
		
		i = 0;
		Iterator<IPAddress> ipIterator = manager.IPs();
		while(ipIterator.hasNext()){
			logTest(true, ipIterator.next().toString());
			i++;
		}
		logTest(i == count, "Counts for IPs don't match.");
		
		nameIterator = manager.names();
		ipIterator = manager.IPs();
		
		while(nameIterator.hasNext()){
			String name = nameIterator.next();
			IPAddress ip = ipIterator.next();
			logTest(manager.findIP(name).equals(ip),
					"IP was not found.");
			logTest(manager.findName(ip).equals(name),
					"Name was not found.");
		}
		
		/*
		 * psfa-1-mac6.sdsu.edu	130.191.208.70
		   etcpasswd.sdsu.edu	130.191.7.111
		   tavo-26-147.sdsu.edu	130.191.26.147
		   ecepc117.sdsu.edu	130.191.163.227
		   dyn-237-75.sdsu.edu	130.191.237.75
		   lovelab-006.sdsu.edu	130.191.137.6
		   lif-sci-n3-mac62.sdsu.edu	130.191.238.127
		 */
		
		manager.printAll();
	}
	
	private static void testIPAddress(){
		String validIPAddress1 = "130.191.238.127";
		String validIPAddress2 = "130.191.224.131";
		String invalidIPAddress = "NOPE";
		IPAddress address = null;
		try{
			address = new IPAddress(invalidIPAddress);
			logTest(false, "Accepted an invalid address.");
		}
		catch(IllegalArgumentException exception){
			logTest(true, exception.getMessage());
		}
		
		address = new IPAddress(validIPAddress1);
		IPAddress address2 = new IPAddress(validIPAddress2);
		IPAddress address11 = new IPAddress(validIPAddress1);
		
		logTest(address.toString().equals(validIPAddress1),
				"IpAddresses were not the same.");
		logTest(address.equals(address11),
				"IpAddress.address11 were not the same.");
		logTest(address.equals(address2) == false,
				"IpAddress.address2 were the same.");
		logTest(address.equals(null) == false,
				"NULL?");
		logTest(address.toString().equals(validIPAddress1),
				"ToString was not the same.");
		
	}
	
	private static void testArrayDictionary(){
		ArrayDictionary<String, String> hash = 
			new ArrayDictionary<String, String>();
		
		testDictionary(hash);
	}
	
	private static void testHashDictionary(){
		HashDictionary<String, String> hash = 
			new HashDictionary<String, String>();
		
		testDictionary(hash);
	}
	
	private static void testLinkedListDictionary(){
		LinkedListDictionary<String, String> hash = 
			new LinkedListDictionary<String, String>();
		
		testDictionary(hash);
	}

	private static void testDictionary(DictionaryI<String,String> hash){
		logTest(true, "Empty TOSTRING: " + hash.toString());
		logTest(hash.size() == 0, "Size wasn't 0.");
		logTest(hash.isFull() == false, "Hash was full.");
		logTest(hash.isEmpty() == true, "Hash was not empty.");

		hash.add("cory", "is awesome");
		logTest(true, "Adding cory TOSTRING: " + hash.toString());
		
		logTest(hash.size() == 1, "Size wasn't 1.");
		logTest(hash.getValue("cory").equals("is awesome"), "awesome wasn't the value.");
		logTest(hash.getValue("NOT THERE") == null, "not there is not null.");
		logTest(hash.getKey("is awesome").equals("cory"), "GetKey: cory wasn't the value.");
		
		logTest(hash.delete("cory") == true, "Didn't delete cory");
		logTest(hash.getValue("cory") == null, "cory is not null.");
		logTest(hash.size() == 0, "Size wasn't 0.");
		logTest(true, "Deleted cory TOSTRING: " + hash.toString());
		
		hash.add("cory", "is awesome");
		hash.add("SDSU", "is awesomer");
		logTest(true, "Adding cory and SDSU TOSTRING: " + hash.toString());
		
		logTest(hash.size() == 2, "Size wasn't 2.");
		
		logTest(hash.getValue("cory").equals("is awesome"), "awesome wasn't the value.");
		logTest(hash.getValue("SDSU").equals("is awesomer"), "is awesomer wasn't the value.");
		logTest(hash.getKey("is awesome").equals("cory"), "GetKey: cory wasn't the value.");
		logTest(hash.getKey("is awesomer").equals("SDSU"), "GetKey: SDSU wasn't the value.");
		logTest(hash.getValue("NOT THERE") == null, "not there is not null.");
		
		logTest(true, "FAILED TOSTRING: " + hash.toString());
		logTest(hash.delete("cory") == true, "Didn't delete cory");
		logTest(hash.getValue("cory") == null, "cory is not null.");
		logTest(hash.size() == 1, "Size wasn't 1...");
		logTest(true, "FAILED TOSTRING: " + hash.toString());
		logTest(hash.getValue("SDSU").equals("is awesomer"), "is awesomer wasn't the value.");
		logTest(true, "Deleted SDSU TOSTRING: " + hash.toString());
		logTest(hash.delete("SDSU") == true, "Didn't delete SDSU");
		
		hash.add("cory", "is awesome");
		hash.add("cory", "is awesome");
		hash.add("cory", "is awesome");
		logTest(true, "Deleted cory TOSTRING: " + hash.toString());
		logTest(hash.delete("cory") == true, "Didn't delete cory");
		logTest(hash.delete("cory") == false, "Deleted cory.. not sure how");
		
		hash.add("cory", "is awesome1");
		hash.add("cory", "is awesome2");
		hash.add("cory", "is awesome3");
		hash.add("sdsu1", "is awesome4");
		hash.add("sdsu2", "is awesome5");
		hash.add("sdsu3", "is awesome6");
		
		logTest(true, "TOSTRING: " + hash.toString());
		logTest(hash.delete("sdsu2") == true, "Didn't delete sdsu2");
		logTest(true, "Deleted sdsu2 TOSTRING: " + hash.toString());
		logTest(hash.delete("cory") == true, "Didn't delete cory");
		logTest(true, "Deleted cory TOSTRING: " + hash.toString());
		logTest(hash.delete("sdsu3") == true, "Didn't delete sdsu3");
		logTest(true, "Deleted sdsu3 TOSTRING: " + hash.toString());
		logTest(hash.delete("sdsu1") == true, "Didn't delete sdsu1");
		logTest(true, "TOSTRING: " + hash.toString());
		logTest(hash.size() == 0, "Size was " + hash.size());
		
		int hashCount = 100;
		
		for(int i = 0; i < hashCount; i++){
			logTest(hash.size() == i, "Size was " + hash.size());
			hash.add("key" + i, "value" + i);
		}
		
		logTest(true, "TOSTRING: " + hash.toString());
		int count = 0;
		logTest(hash.size() == hashCount, "Counts don't match");
		
		Iterator<String> values = hash.values();
		while(values.hasNext()){
			values.next();
			count++;
		}
		logTest(count == hashCount, "Counts don't match values.. didn't iterate through all.");
		
		count = 0;
		Iterator<String> keys = hash.keys();
		while(keys.hasNext()){
			keys.next();
			count++;
		}
		logTest(count == hashCount, "Counts don't match keys.. didn't iterate through all.");
		
		for(int i = 0; i < hashCount; i++){
			logTest(hash.getValue("key" + i).equals("value" + i), "key" + i + " didn't find value.");
			logTest(hash.getKey("value" + i).equals("key" + i), "value" + i + " didn't find key.");
			logTest(hash.delete("key" + i) == true, "Didn't delete key" + i);
		}
	}
	
	private static void logTest(boolean result, String errorMessage){
		if(false == result){
			System.out.println("FAILED: " + errorMessage);
			_testsPassed = false;
		}
		else{
			System.out.println("PASSED: " + errorMessage);
		}
	}

}
