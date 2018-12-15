package data_structures;

/**
 * A helper class that will store a key/value pair.
 * @author cwixom (masc0582)
 *
 * @param <K> The key data type
 * @param <V> The value data type.
 */
public class ChainEntry
	<K extends Comparable<K>, 
	 V extends Comparable<V>> 
	implements Comparable<ChainEntry<K,V>>{

	/**
	 * Constructor to create a new ChainEntry.
	 * @param key The key for the ChainEntry
	 * @param val The value for the ChainEntry.
	 */
	public ChainEntry(K key, V val){
		setKey(key);
		setValue(val);
	}

	/**
	 * Gets the key for the chained entry
	 */
	public K getKey(){return _key;}
	/**
	 * Sets the key for the chained entry.
	 */
	public void setKey(K key){_key = key;}
	
	/**
	 * Gets the value for the chained entry.
	 */
	public V getValue(){return _value;}
	/**
	 * Sets the value for the chained entry.
	 */
	public void setValue(V val){_value = val;}
	
	/**
	 * Compares to another ChainEntry
	 * @param arg0 The chain entry to compare to.
	 */
	@Override
	public int compareTo(ChainEntry<K,V> arg0) {
		if(null == arg0){return -1;}
	
		return getKey().compareTo(arg0.getKey());
	}
	
	/**
	 * {@inheritDoc}
	 */
	@SuppressWarnings("unchecked")
	@Override
	public boolean equals(Object obj){
		if(null == obj){
			return false;
		}
		else if(false == (obj instanceof ChainEntry<?,?>)){
			return false;
		}
		
		return compareTo((ChainEntry<K,V>)obj) == 0;
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString(){
		return getKey() + "\t" + getValue();
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public int hashCode(){
	    return (getKey()==null   ? 0 : getKey().hashCode()) ^
	           (getValue()==null ? 0 : getValue().hashCode());
	}
	
	private K _key;
	private V _value;
}