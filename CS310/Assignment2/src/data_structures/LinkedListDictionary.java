package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.ConcurrentModificationException;

/**
 * A LinkedList implementation of the
 * DitionaryI interface.
 * @author cwixom (masc0582)
 *
 * @param <K> The type for the key of the key/value pair.
 * @param <V> The type for the value of the key/value pair.
 */
public class LinkedListDictionary	
	<K extends Comparable<K>, 
	 V extends Comparable<V>>  
	implements DictionaryI<K,V> {

	/**
	 * Default Constructor.
	 */
	public LinkedListDictionary(){
		_linkedList = new LinkedList<ChainEntry<K,V>>();
	}

	/**
	 * Adds a value to the Dictionary
	 * @param key The key for the key/value pair.
	 * @param value The value for the key/value pair.
	 */
	@Override
	public boolean add(K key, V value) {
		// Check if nulls were passed.
		if(null == key || null == value){return false;}
		
		// Created the variable to be added to the list.
		ChainEntry<K,V> entry = new ChainEntry<K,V>(key, value);
		
		// If it's not in the list add it.
		// Also keep track of the modifications
		// so iterators don't mess up.
		if(false == _linkedList.contains(entry)){
			_linkedList.addFirst(entry);
			incrementModification();
			return true;
		}
		
		return false;
	}

	/**
	 * Deletes a key/value pair based on the key.
	 * @param key The key for the key/value pair.
	 */
	@Override
	public boolean delete(K key) {
		// Check if a null value was passed.
		if(null == key){return false;}
		
		// Set a temp variable used for 
		// the search.
		ChainEntry<K,V> entry = new ChainEntry<K,V>(key, null);
		ChainEntry<K,V> returnEntry =
			_linkedList.remove(entry);
		
		// If we successfully deleted it
		// increment the modification.
		if(null != returnEntry){
			incrementModification();
			return true;
		}
		
		return false;
	}

	/**
	 * Gets the value for a specfic key
	 * @param key The key to search for.
	 */
	@Override
	public V getValue(K key) {
		// Check if there was a null passed.
		if(null == key){return null;}
		
		// Create a temp variable to search the list.
		ChainEntry<K,V> entry = 
				new ChainEntry<K,V>(key, null);
		ChainEntry<K,V> returnEntry =
				_linkedList.find(entry);
		
		return returnEntry == null ? null : returnEntry.getValue();
	}

	/**
	 * Finds a key in the list, based on the value.
	 * @param value The value to seach for.
	 */
	@Override
	public K getKey(V value) {
		// Check for nulls.
		if(null == value){return null;}
		
		// Loop through the list to find if the
		// value is present.
		for(ChainEntry<K,V> entry : _linkedList){
			if(0 == entry.getValue().compareTo(value)){
				return entry.getKey();
			}
		}
		
		return null;
	}

	/**
	 * Returns the size of the list.
	 */
	@Override
	public int size() {
		return _linkedList.size();
	}

	@Override
	public boolean isFull() {
		return _linkedList.isFull();
	}

	/**
	 * Returns if the list is empty.
	 */
	@Override
	public boolean isEmpty() {
		return _linkedList.isEmpty();
	}

	/**
	 * Returns an iterator for all of the keys.
	 */
	@Override
	public Iterator<K> keys() {
		KeyIterator iter = new KeyIterator(
				_linkedList.iterator(),
				_modificationCount);
		return iter;
	}

	/**
	 * Returns an iterator for all of the values.
	 */
	@Override
	public Iterator<V> values() {
		ValueIterator iter = new ValueIterator(
				_linkedList.iterator(),
				_modificationCount);
		return iter;
	}
	
	/**
	 * Returns an iterator for all of the keys.
	 */
	@Override
	public Iterator<K> iterator() {
		KeyIterator iter = new KeyIterator(
				_linkedList.iterator(),
				_modificationCount);
		return iter;
	}
	
	/**
	 * Formats the list in a string.
	 */
	@Override
	public String toString(){
		String returnString = "";
		for(ChainEntry<K,V> entry : _linkedList){
			returnString+= entry.toString() + "|";
		}
		return returnString;
	}
	
	/**
	 * Increments the modification count.
	 */
	private void incrementModification(){
		_modificationCount++;
		
		if(_modificationCount == Integer.MAX_VALUE){
			_modificationCount = MODIFICATION_START;
		}
	}
	
	
    /**
     * The default modification start.
     */
    private static final int MODIFICATION_START = 0;
    
    private int _modificationCount = MODIFICATION_START;
	private LinkedList<ChainEntry<K,V>> _linkedList;

	
	/**
	 * Iterates throughout the values. It uses
	 * the built in LinkedList iterator.
	 * @author cwixom
	 */
	private class ValueIterator implements Iterator<V>{

		/**
		 * Constructor.
		 * @param iterator The ChainEntry iterator.
		 * @param modificationCount The current count of modifications.
		 */
		public ValueIterator(
				Iterator<ChainEntry<K,V>> iterator,
				int modificationCount){
			_chainIterator = iterator;
			_currentModification = modificationCount;
		}
		/**
		 * Returns whether it has next.
		 */
		@Override
		public boolean hasNext() {
			return _chainIterator.hasNext();
		}
		/**
		 * Returns the next value.
		 */
		@Override
		public V next() {
			if(_currentModification != _modificationCount)
				throw new ConcurrentModificationException();
				
			ChainEntry<K,V> currentEntry = 
				_chainIterator.next();
			
			if(null == currentEntry){
				throw new NoSuchElementException();
			}
			return currentEntry.getValue();
		}

		/**
		 * Removes the value.
		 */
		@Override
		public void remove() {
			_chainIterator.remove();			
		}
		private Iterator<ChainEntry<K,V>> _chainIterator;
		private int _currentModification;
	}

	/**
	 * Iterates throughout the keys. It uses
	 * the built in LinkedList iterator.
	 * @author cwixom
	 */
	private class KeyIterator implements Iterator<K>{

		/**
		 * Constructor.
		 * @param iterator The ChainEntry iterator.
		 * @param modificationCount The current count of modifications.
		 */
		public KeyIterator(
				Iterator<ChainEntry<K,V>> iterator,
				int modificationCount){
			_chainIterator = iterator;
			_currentModification = modificationCount;
		}
		/**
		 * Returns whether there is a next.
		 */
		@Override
		public boolean hasNext() {
			return _chainIterator.hasNext();
		}

		/**
		 * Returns the next key.
		 */
		@Override
		public K next() {
			if(_currentModification != _modificationCount)
				throw new ConcurrentModificationException();
				
			ChainEntry<K,V> currentEntry = 
				_chainIterator.next();
			
			if(null == currentEntry){
				throw new NoSuchElementException();
			}
			return currentEntry.getKey();
		}

		/**
		 * Removes the record.
		 */
		@Override
		public void remove() {
			_chainIterator.remove();			
		}
		private Iterator<ChainEntry<K,V>> _chainIterator;
		private int _currentModification;
	}

}
