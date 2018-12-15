package big_numbers;

import java.util.Iterator;

import data_structures.*;

public class UnitTests {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
			checkLinkedList();

	}
	
	private static void checkLinkedList()
	{
		LinkedList<String> stringList = new LinkedList<String>();
		
		logTest(0 == stringList.size(), "Size was incorrect on first call.");
		
		stringList.addFirst("Cory");
		logTest(1 == stringList.size(), "Size was incorrect on size:1 call.");
		logTest(stringList.peekFirst().equals("Cory"), 
				"Cory was not on the top.");
		logTest(stringList.peekLast().equals("Cory"), 
				"Cory was not on the bottom.");
		
		stringList.addFirst("Wixom");
		logTest(2 == stringList.size(), "Size was incorrect on size:2 call.");
		logTest(stringList.peekFirst().equals("Wixom"), 
				"Wixom was not on the top.");
		logTest(stringList.peekLast().equals("Cory"), 
				"Cory was not on the bottom.");
		
		stringList.addLast("Rocks");
		logTest(3 == stringList.size(), "Size was incorrect on size:3 call.");
		logTest(stringList.peekFirst().equals("Wixom"), 
				"Wixom was not on the top.");
		logTest(stringList.peekLast().equals("Rocks"), 
				"Rocks was not on the bottom. " + stringList.peekLast());
		
		logTest(stringList.contains("Rocks"), 
				"Rocks was not in the list. ");
		logTest(stringList.contains("Wixom"), 
				"Wixom was not in the list. ");
		logTest(stringList.contains("Cory"), 
				"Cory was not in the list. ");
		logTest(false == stringList.contains("Nope"), 
				"Nope was in the list. ");
		logTest(false == stringList.contains(null), 
				"Null was in the list. ");
		
		logTest(false == stringList.isEmpty(), 
				"List is empty. ");
		
		stringList.makeEmpty();
		
		logTest(true == stringList.isEmpty(), 
				"List is not empty. ");
		
		logTest(0 == stringList.size(), 
				"Size was not 0. ");
		
		logTest(null == stringList.peekFirst(), 
				"Peek first didn't return null on empty list. ");
		logTest(null == stringList.peekLast(), 
				"Peek first didn't return null on empty list. ");
		
		stringList.addFirst("A");
		stringList.addFirst("B");
		stringList.addFirst("C");
		stringList.addFirst("D");
		
		logTest(4 == stringList.size(), 
				"Size was not 4. ");
		
		String first = stringList.removeFirst();
		
		logTest(first.equals("D"), 
				"D wasn't first. ");
		
		logTest(stringList.peekFirst().equals("C"), 
				"C wasn't first. ");
		logTest(stringList.peekLast().equals("A"), 
				"A wasn't last. ");
		
		Iterator<String> iter = stringList.iterator();
		
		while(iter.hasNext()){
			
			String next = iter.next();
			logTest(true, next);
		}
		
		stringList.addLast("R");
		
		String lastOne = stringList.removeLast();
		
		logTest(lastOne.equals("R"), 
				"R wasn't last. ");
		
		logTest(stringList.peekLast().equals("A"), 
				"A wasn't last. ");
		
		stringList.addLast("Y");
		
		Iterator<String> iter2 = stringList.iterator();
		
		while(iter2.hasNext()){
			
			String next = iter2.next();
			logTest(true, next);
		}
		
		logTest(true, stringList.toString());
	}
	
	private static void logTest(boolean result, String errorMessage){
		if(false == result){
			System.out.println("FAILED: " + errorMessage);
		}
		else{
			System.out.println("PASSED: " + errorMessage);
		}
	}

}
