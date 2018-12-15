package data_structures;

import java.util.Iterator;
import java.lang.Comparable;
import java.util.NoSuchElementException;
import java.util.ConcurrentModificationException;

/** 
 * A Hash implementation of the DitionaryI
 * interface.
 * @author cwixom (masc0582)
 * @param <K> The type for the key of the key/value pair.
 * @param <V> The type for the value of the key/value pair.
*/
public class HashDictionary
	<K extends Comparable<K>, 
	 V extends Comparable<V>>  
	 implements DictionaryI<K,V>{

	/**
	 * Constructor for HashDictionary where 
	 * the capacity is passed.
	 * @param initialCapacity The initial capacity.
	 * @exception IllegalArgumentException if the capacity < 0
	 */
	public HashDictionary(int initialCapacity){
		if(initialCapacity < 0){
				throw new IllegalArgumentException(
						"Capacity must be > 0.");
		}
		
		// The hashing function is optimized for 
		// power of 2, so this will ensure
		// the length is even.
		int initialLength = initialCapacity;
		if((initialLength % 2)!=0){initialLength++;}
				
		initializeArray(initialLength);
		_loadFactor = DEFAULT_LOAD_FACTOR;
		_sizeThreshold = (int)(initialLength * _loadFactor);
	}
	
	/**
	 * Default constructor.
	 */
	public HashDictionary(){
		initializeArray(DEFAULT_INITIAL_CAPACITY);
		_loadFactor = DEFAULT_LOAD_FACTOR;
		_sizeThreshold = (int)(DEFAULT_INITIAL_CAPACITY * _loadFactor);
	}

	/**
	 * Adds a new key/value pair to the hash.
	 * @param key The key for the hash.
	 * @param val The value for the hash.
	 */
	@Override
	public boolean add(K key, V val) {
		if(null == key || null == val){return false;}
		
		// Get the chain that matches this key
		// code, and a new entry to the chain.
		Chain currentChain = getChain(key);
		boolean returnValue = 
			currentChain.add(new ChainEntry<K,V>(key, val));
		
		if(true == returnValue){
			_size++;
			incrementModification();
		}
		
		// Check if we need to resize the array
		// if we do, then resize it.
		if(true == shouldResize()){resize();}
		
		return returnValue;
	}

	/**
	 * Deletes a key/value pair based on the key.
	 * @param key The key for the key/value pair to delete.
	 */
	@Override
	public boolean delete(K key) {
		// Validate we didn't receive nulls.
		if(null == key){return false;}
		
		// Get the chain that matches this key
		// code.
		Chain currentChain = getChain(key);

		boolean deleted = currentChain.delete(key);
		if(true == deleted){
			_size --;
			incrementModification();
		}
		
		return deleted;
	}

	/**
	 * Gets the value for a key/value pair.
	 * @param key The key for the key/value pair.
	 * @exception NullPointerException For null arguments
	 */
	@Override
	public V getValue(K key) {
		if(null == key){return null;}
		
		// Get the chain that matches this key
		// code.
		Chain currentChain = getChain(key);
		ChainEntry<K,V> entry = currentChain.find(key);
		
		// Check if the entry existed. If it is. Return
		// the value.
		return entry == null ? null : entry.getValue();
	}

	/**
	 * Returns the Key for the specified value
	 * @param value The value to search for.
	 */
	@Override
	public K getKey(V value) {
		if(null == value){return null;}
		
		ChainEntryIterator iter = 
			new ChainEntryIterator(_modificationCount);
		
		while(iter.hasNext()){
			ChainEntry<K,V> current = iter.next();
			if(0 == current.getValue().compareTo(value)){
				return current.getKey();
			}
		}
		
		return null;
	}

	/**
	 * Returns the current size of the hash.
	 */
	@Override
	public int size() {
		return _size;
	}

	/**
	 * Returns if the hash is full.
	 */
	@Override
	public boolean isFull() {
		return false;
	}
	
	/**
	 * Returns if the hash is empty.
	 */
	@Override
	public boolean isEmpty() {
		return size() == 0;
	}

	/**
	 * Returns an iterator for all of the keys.
	 */
	@Override
	public Iterator<K> keys() {
		KeyIterator iter = new KeyIterator(_modificationCount);
		return iter;
	}

	/**
	 * Returns an iterator for all of the values.
	 */
	@Override
	public Iterator<V> values() {
		ValueIterator iter = new ValueIterator(_modificationCount);
		return iter;
	}
	
	/**
	 * Returns an iterator for all of the keys.
	 */
	@Override
	public Iterator<K> iterator() {
		KeyIterator iter = new KeyIterator(_modificationCount);
		return iter;
	}
	
	/**
	 * Formats the hash for viewing.
	 */
	@Override
	public String toString(){
		String returnString = "";
		for(Chain chain : _chainArray){
			for(ChainEntry<K,V> entry : chain){
				returnString += entry.toString() + ":";
			}
		}
		
		return returnString;
	}

	/**
	 * Initializes the array.
	 * @param capacity The initial capacity.
	 */
	@SuppressWarnings("unchecked")
	private void initializeArray(int capacity){

		if(capacity == 0){
			capacity = 2;
		}
		
		_chainArray = new HashDictionary.Chain[capacity];
		for(int i = 0; i < capacity; i++){
			_chainArray[i] = new Chain();
		}
	}

	/**
	 * Returns if the hash should resize.
	 * @return
	 */
	private boolean shouldResize(){
		return _size >= _sizeThreshold;
	}
	
	/**
	 * Resizes the array.
	 */
	@SuppressWarnings("unchecked")
	private void resize(){
		int newCapacity = _chainArray.length * RESIZE_MUTIPLIER;
		int previousSize = _chainArray.length - 1;
		Chain[] currentArray = _chainArray;
		_chainArray = new HashDictionary.Chain[newCapacity];
		_sizeThreshold = (int)(newCapacity * _loadFactor);
		_size = 0;
		
		initializeArray(newCapacity);
		
		for(int i =0; i < previousSize + 1; i++){
			Chain currentChain = currentArray[i];
			for(ChainEntry<K,V> chainEntry : currentChain){
				add(chainEntry.getKey(), chainEntry.getValue());
			}
		}
	}
	
	private void incrementModification(){
		_modificationCount++;
		
		if(_modificationCount == Integer.MAX_VALUE){
			_modificationCount = MODIFICATION_START;
		}
	}
	
	/**
	 * Ensure a good hashing, this will force
	 * a more even distribution since the hash 
	 * grows at powers of 2 there is normally
	 * space in the upper regions.
	 * @param h
	 * @return
	 */
    private int hash(int h) {
        h ^= (h >>> 20) ^ (h >>> 12);
        return h ^ (h >>> 7) ^ (h >>> 4);
    }

    private int indexFor(int h, int length) {
        return h & (length-1);
    }
	
    /**
     * Gets the specific chain based on
     * the key passed.
     * @param key
     * @return
     */
	private Chain getChain(K key){
		int hash = hash(key.hashCode());
		return _chainArray[indexFor(hash, _chainArray.length)];
	}
	
    /**
     * The default initial capacity
     */
    private static final int DEFAULT_INITIAL_CAPACITY = 16;
    
    /**
     * The default load factor
     */
    private static final float DEFAULT_LOAD_FACTOR = 0.75f;
    /**
     * The default initial capacity
     */
    private static final int RESIZE_MUTIPLIER = 2;
    /**
     * The default modification start.
     */
    private static final int MODIFICATION_START = 0;
    
	private Chain[] _chainArray;
	private int _size;
	private float _loadFactor;
	private int _sizeThreshold;
	private int _modificationCount = MODIFICATION_START;
    
    /**
     * Iterates through each chain entry in the hash.
     * @author cwixom
     */
    private class ChainEntryIterator implements Iterator<ChainEntry<K,V>>{
    	/**
    	 * Default constructor.
    	 * @param currentModification
    	 */
    	public ChainEntryIterator(int currentModification){
    		_currentIndex = 0;
    		_currentModification = currentModification;
    		_currentChain = findNextChain();
    	}
    	
    	/**
    	 * Returns whether the iterator has a next.
    	 */
		@Override
		public boolean hasNext() {
			if(null == _currentChain || _chainArray.length == 0){
				return false;
			}
			else if(_currentIndex == 
				   (_chainArray.length - 1)){

				return _currentChain.hasNext();
			}
			else if(_currentChain.hasNext()){
				return true;
			}
			
			return isAnotherChain(_currentIndex+1);
		}

    	/**
    	 * Returns the next value of the iterator.
    	 */
		@Override
		public ChainEntry<K,V> next() {
			if(_currentModification != _modificationCount){
				throw new ConcurrentModificationException();
			}
			if(_currentChain.hasNext()){
				return getNext();
			}
			
			_currentIndex++;
			_currentChain = findNextChain();
			
			if(null == _currentChain){
				throw new NoSuchElementException();
			}
			else{
				return getNext();
			}
		}

		@Override
		public void remove() {
			throw new UnsupportedOperationException();
		}
    	
		/**
		 * Gets the next piece of data from the chain.
		 * @return
		 */
		private ChainEntry<K,V> getNext(){
			return _currentChain.next();
		}
		
		/**
		 * Finds the next chain from the current index.
		 * @return
		 */
		private Iterator<ChainEntry<K,V>> findNextChain(){
			for(int i =_currentIndex; i<_chainArray.length; i++){
				_currentChain = _chainArray[i].iterator();
				if(_currentChain.hasNext()){
					return _currentChain;
				}
				_currentIndex++;
			}
			
			return null;
		}
		
		/**
		 * Checks if there is another chain starting
		 * from the current index forward.
		 * @param currentIndex
		 * @return
		 */
		private boolean isAnotherChain(int currentIndex){
			for(int i =currentIndex; i<_chainArray.length; i++){
				Iterator<ChainEntry<K,V>> currentChain = 
						_chainArray[i].iterator();
				if(currentChain.hasNext()){
					return true;
				}
			}
			
			return false;
		}
		
		private int _currentIndex;
		private int _currentModification;
		private Iterator<ChainEntry<K,V>> _currentChain;
    }
    
    /**
     * Iterates through all the values. 
     * This class will wrap the ChainEntryIterator to keep
     * the hash iteration encapsulated in ChainEntryIterator.
     * @author cwixom
     */
    private class ValueIterator implements Iterator<V>{
    	/**
    	 * Default constructor.
    	 * @param currentModification
    	 */
    	public ValueIterator(int currentModification){
    		_chainIterator = new ChainEntryIterator(currentModification);
    	}

    	/**
    	 * Returns if there is a next value.
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
			ChainEntry<K,V> entry = _chainIterator.next();
			return entry == null ? null : entry.getValue();
		}

		/**
		 * Removes from the iterator.
		 */
		@Override
		public void remove() {
			_chainIterator.remove();
		}
		
		private ChainEntryIterator _chainIterator;
    }
    
    /**
     * Iterates through all the keys. 
     * This class will wrap the ChainEntryIterator to keep
     * the hash iteration encapsulated in ChainEntryIterator.
     * @author cwixom
     */
    private class KeyIterator implements Iterator<K>{
    	/**
    	 * Default constructor.
    	 * @param currentModification
    	 */
    	public KeyIterator(int currentModification){
    		_chainIterator = new ChainEntryIterator(currentModification);
    	}
    	/**
    	 * Returns if there is a next value.
    	 */
		@Override
		public boolean hasNext() {
			return _chainIterator.hasNext();
		}
		/**
		 * Returns the next value.
		 */
		@Override
		public K next() {
			ChainEntry<K,V> entry = _chainIterator.next();
			return entry == null ? null : entry.getKey();
		}
		/**
		 * Removes from the iterator.
		 */
		@Override
		public void remove() {
			_chainIterator.remove();
		}
		
		private ChainEntryIterator _chainIterator;
    }
    
    /**
     * A helper class. This is the chain of
     * key/value pairs. It wraps the linked list.
     * @author cwixom
     */
    private class Chain implements Iterable<ChainEntry<K,V>>{
    	/**
    	 * The default constructor.
    	 */
    	public Chain(){
    		_chainList = new LinkedList<ChainEntry<K,V>>();
    	}
    	
    	/**
    	 * Adds a new entry to the linked list.
    	 * @param entry
    	 */
    	public boolean add(ChainEntry<K,V> entry){
    		if(false == _chainList.contains(entry)){
    			_chainList.addFirst(entry);
    			return true;
    		}
    		return false;
    	}

    	/**
    	 * Deletes an entry based on the key passed.
    	 * @param key
    	 * @return
    	 */
    	public boolean delete(K key){
    		ChainEntry<K,V> entry = new ChainEntry<K,V>(key, null);
    		return _chainList.remove(entry) != null;
    	}
    	/**
    	 * Finds an entry based on the key
    	 * passed.
    	 * @param key
    	 * @return
    	 */
    	public ChainEntry<K,V> find(K key){
    		ChainEntry<K,V> entry = new ChainEntry<K,V>(key, null);
    		return _chainList.find(entry);
    	}
    	
    	/**
    	 * The linked list implementation.
    	 */
    	private ListI<ChainEntry<K,V>> _chainList;

    	/**
    	 * Returns an iterator for each entry.
    	 */
		@Override
		public Iterator<ChainEntry<K,V>> iterator() {
			return _chainList.iterator();
		}
    }
  
}
