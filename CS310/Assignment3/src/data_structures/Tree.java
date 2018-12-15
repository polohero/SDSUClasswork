package data_structures;

/**
 * A generic implementation of a Tree.
 * @author cwixom (masc0582)
 * @param <E> The data the tree will be storing.
 */
public interface Tree<E extends Comparable<E>>{
	/**
	 * Adds a new piece of data to the tree.
	 * It will re-balance on each add to keep
	 * the tree nicely balanced.
	 * @param data The data to add to the tree.
	 * @throws NullPointerException For null data.
	 */
	public void add(E data);
	
	/**
	 * Returns the height of the tree.
	 * @return The height of the tree.
	 */
	public int height();
	
	/**
	 * Clears the tree.
	 */
	public void clear();
	
	/**
	 * Finds data in the tree.
	 * @param data
	 * @return
	 */
	public E find(E data);
	
	/**
	 * Sets the data if it is found in the
	 * tree. If it is not found, it will not
	 * do anything.
	 * @param data
	 */
	public void set(E data);
	
	/**
	 * Returns the next largest item, in order, after
	 * the data passed in. If the data is found, it will
	 * return the data.
	 * @param data
	 * @return
	 */
	public E getCeiling(E data);
	
	/**
	 * Returns the next smallest item
	 * smaller than the item. If the data is found, it will
	 * return the data.
	 * @param data
	 * @return
	 */
	public E getFloor(E data);
}
