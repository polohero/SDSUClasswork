package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.ConcurrentModificationException;

/**
 * An array based implementation of the
 * DictionaryI interface.
 * @author cwixom (masc0582)
 *
 * @param <K> The type for the key of the key/value pair.
 * @param <V> The type for the value of the key/value pair.
 */
public class ArrayDictionary 
	<K extends Comparable<K>, 
	 V extends Comparable<V>>  
	implements DictionaryI<K,V> {

	/**
	 * Constructor for HashDictionary where 
	 * the capacity is passed.
	 * @param initialCapacity The initial capacity.
	 * @exception IllegalArgumentException if the capacity < 0
	 */
	public ArrayDictionary(int initialCapacity){
		// Check that we have an initial capacity > 0.
		if(initialCapacity < 0){
			throw new IllegalArgumentException(
				"Capacity must be > 0.");
		}
		// If they give us a 0, we'l just allocate
		// 1.
		if(initialCapacity == 0){
			initialCapacity = 1;
		}
		initializeArray(initialCapacity);
		_loadFactor = DEFAULT_LOAD_FACTOR;
		_sizeThreshold = (int)(initialCapacity * _loadFactor);
	}
	
	/**
	 * Default constructor.
	 */
	public ArrayDictionary(){
		initializeArray(DEFAULT_INITIAL_CAPACITY);
		_loadFactor = DEFAULT_LOAD_FACTOR;
		_sizeThreshold = (int)(DEFAULT_INITIAL_CAPACITY * _loadFactor);
	}

	/**
	 * Adds a new key/value pair to the array.
	 * @param key The key for the key/value pair.
	 * @param value The value for the key/value pair.
	 */
	@Override
	public boolean add(K key, V value) {
		// Check for nulls first.
		if(null == key || null == value){return false;}
		
		// Check if we need to resize.
		// This will ensure the list is always at a 
		// capacity to handle an new entry.
		if(shouldResize()){
			resize();
		}
		
		// Check if the value already exists.
		// If the value doesn't exit, it should
		// not allow a duplicate.
		V gottenValue = getValue(key);
		if(null == gottenValue){
			ChainEntry<K,V> entry = 
				new ChainEntry<K,V>(key, value);
			_array[_size] = entry;
			_size++;
			incrementModification();
			return true;
		}
		
		return false;
	}

	/**
	 * Deletes a key/value pair from the list
	 * @param key The key to delete.
	 */
	@Override
	public boolean delete(K key) {
		// Check for a null value.
		if(null == key){return false;}

		// Create a temp variable that's used 
		// to compare.
		ChainEntry<K,V> chainEntry = new ChainEntry<K,V>(key, null);
		
		// Create a new array. 
		@SuppressWarnings("unchecked")
		ChainEntry<K,V>[] newArray = 
				(ChainEntry<K,V>[])new ChainEntry[_array.length];
		int index = 0;
		boolean found = false;
		
		for(int i = 0; i < _size; i++){
			ChainEntry<K,V> currentChainEntry = _array[i];
			if(0 != currentChainEntry.compareTo(chainEntry)){
				newArray[index] = currentChainEntry;
				index++;
			}
			else{
				found = true;
			}
			
		}
		
		// If the object was found then 
		// change the size, and increment
		// the modification.
		if(true == found){
			_size--;
			incrementModification();
			_array = newArray;
		}
		
		return found;
	}

	/**
	 * Finds the value based on the key
	 * provided
	 * @param key The key to search for.
	 */
	@Override
	public V getValue(K key) {
		// Check for a null value.
		if(null == key){return null;}
		
		// Create a temp variable that's used 
		// to compare.
		ChainEntry<K,V> chainEntry =
			new ChainEntry<K,V>(key, null);
		
		// Loop through and find the key that
		// matches.
		for(ChainEntry<K,V> entry : _array){
			if(0 == chainEntry.compareTo(entry)){
				chainEntry.setValue(entry.getValue());
			}
		}
		
		return chainEntry.getValue();
	}

	/**
	 * Finds the key based on the value provided
	 * @param value The value to search for.
	 */
	@Override
	public K getKey(V value) {
		// Check for a null value.
		if(null == value){return null;}
		
		K key = null;
		
		// Loop through and find the key that
		// matches.
		for(int i = 0; i< _size; i++){
			ChainEntry<K,V> entry = _array[i];
			V val = entry.getValue();
			if(0 == val.compareTo(value)){
				key = entry.getKey();
				break;
			}
		}
		
		return key;
	}

	/**
	 * Returns the size of the collection.
	 */
	@Override
	public int size() {
		return _size;
	}

	/**
	 * Returns if the collection is full.
	 */
	@Override
	public boolean isFull() {
		return false;
	}
	
	/**
	 * @inheritDoc
	 */
	@Override
	public String toString(){
		String returnString = "";
		for(int i = 0; i < _size; i++){
			ChainEntry<K,V> entry = _array[i];
			returnString += entry.toString() + "\n";
		}
		return returnString;
	}

	/**
	 * Returns if the collection is empty.
	 */
	@Override
	public boolean isEmpty() {
		return _size == 0;
	}

	/**
	 * Returns an iterator to loop through all
	 * the keys.
	 */
	@Override
	public Iterator<K> keys() {
		ChainEntryIterator chainEntryIter = 
				new ChainEntryIterator(_modificationCount);
		KeyIterator iter = 
				new KeyIterator(chainEntryIter);
		return iter;
	}

	/**
	 * Returns an iterator to loop through all
	 * the values.
	 */
	@Override
	public Iterator<V> values() {
		ChainEntryIterator chainEntryIter = 
			new ChainEntryIterator(_modificationCount);
		ValueIterator iter = 
			new ValueIterator(chainEntryIter);
		return iter;
	}
	
	/**
	 * Returns an iterator to loop through all
	 * the keys.
	 */
	@Override
	public Iterator<K> iterator() {
		ChainEntryIterator chainEntryIter = 
				new ChainEntryIterator(_modificationCount);
		KeyIterator iter = 
				new KeyIterator(chainEntryIter);
		return iter;
	}
	
	@SuppressWarnings("unchecked")
	private void initializeArray(int initialCapacity){
		_array = (ChainEntry<K,V>[])new ChainEntry[initialCapacity];
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
	 * Returns if the hash should resize.
	 * @return
	 */
	private boolean shouldResize(){
		return _size + 1 >= _sizeThreshold;
	}
	
	/**
	 * Resizes the array.
	 */
	@SuppressWarnings("unchecked")
	private void resize(){
		int newCapacity = _array.length * RESIZE_MUTIPLIER;
		ChainEntry<K,V>[] currentArray = _array;
		_array = (ChainEntry<K,V>[])new ChainEntry[newCapacity];
		_sizeThreshold = (int)(newCapacity * _loadFactor);
		
		for(int i = 0; i < _size; i++){
			_array[i] = currentArray[i];
		}
	}
	
    /**
     * The default modification start.
     */
    private static final int MODIFICATION_START = 0;
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
    
    private int _modificationCount = MODIFICATION_START;
    private ChainEntry<K,V>[] _array;
	private int _size = 0;
	private float _loadFactor;
	private int _sizeThreshold;
	
	/**
	 * An iterator over every value in the Array.
	 * It wraps the ChainEntryIterator class.
	 * @author cwixom
	 */
	private class ValueIterator implements Iterator<V>{
		public ValueIterator(ChainEntryIterator iter){
			_iter = iter;
		}
		@Override
		public boolean hasNext() {
			return _iter.hasNext();
		}

		@Override
		public V next() {
			ChainEntry<K,V> entry = _iter.next();
			return entry.getValue();
		}

		@Override
		public void remove() {
			_iter.remove();
			
		}
		private ChainEntryIterator _iter;
	}
	
	/**
	 * An iterator over every key in the Array.
	 * It wraps the ChainEntryIterator class.
	 * @author cwixom
	 */
	private class KeyIterator implements Iterator<K>{
		public KeyIterator(ChainEntryIterator iter){
			_iter = iter;
		}
		@Override
		public boolean hasNext() {
			return _iter.hasNext();
		}

		@Override
		public K next() {
			ChainEntry<K,V> entry = _iter.next();
			return entry.getKey();
		}

		@Override
		public void remove() {
			_iter.remove();
			
		}
		private ChainEntryIterator _iter;
	}
	
	/**
	 * An iterator for every ChainEntry in the 
	 * Hash. This allows for either Key and Value
	 * iterators to use the same logic, then
	 * just specify the return value.
	 * @author cwixom
	 */
	private class ChainEntryIterator implements Iterator<ChainEntry<K,V>>{
		public ChainEntryIterator(int currentModification){
			_currentModification = currentModification;
		}
		@Override
		public boolean hasNext() {
			return _currentIndex < _size;
		}

		@Override
		public ChainEntry<K,V> next() {
			if(_currentModification != _modificationCount){
				throw new ConcurrentModificationException();
			}
			
			if(_currentIndex >= _size){
				throw new NoSuchElementException();
			}
			
			ChainEntry<K,V> obj = _array[_currentIndex];
			_currentIndex++;
			return obj;
		}

		@Override
		public void remove() {
			throw new UnsupportedOperationException();
			
		}
		private int _currentModification;
		private int _currentIndex = 0;
	}
}
