package data_structures;

import java.util.TreeSet;
import java.util.SortedSet;

/**
 * An implementation of a Red Black Tree tree.
 * @author cwixom (masc0582)
 * @param <E> The data the tree will be storing.
 */
public class RedBlackTree
	<E extends Comparable<E>> 
	implements Tree<E>{

	private TreeSet<E> _tree;
	
	/**
	 * The default constructor for the
	 * Red Black Tree.
	 */
	public RedBlackTree(){
		_tree = new TreeSet<E>();
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public void add(E data) {
		_tree.add(data);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public int height() {
		return _tree.size();
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public E find(E data) {
		if(null ==  data){return null;}
		SortedSet<E> set =_tree.tailSet(data);
		if(null == set || set.size() == 0){
			return null;
		}
		return set.first();
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public void clear() {
		_tree.clear();
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public void set(E data) {
		@SuppressWarnings("unused")
		E realData = find(data);
		realData = data;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public E getCeiling(E data) {
		return _tree.ceiling(data);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public E getFloor(E data) {
		return _tree.floor(data);
	}
}
