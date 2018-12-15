package data_structures;

import java.util.Iterator;
import java.lang.Comparable;

/**
 * A generic linked list. 
 * @author cwixom (masc0582)
 *
 * @param <E> The generic object type the list will work with.
 */
public class LinkedList<E extends Comparable<E>> implements ListI<E>{
	
	/**
	 * The default constructor for the linked list.
	 */
	public LinkedList()
	{
		_size = 0;
		_header = null;
	}
	
	/**
	 * @inheritDoc 
	 * @exception Throws a NullPointerException if the E is null. 
	 */
	@Override
	public void addFirst(E obj) {
		validateInput(obj);
		
		// Check if the header is already.
		// null. If it is we can just set this value
		// to the header.
		if(true == isHeaderNull()){
			_header = new Node<E>(obj, null, null);
			_size = 1;
			return;
		}
		
		// Otherwise, create a temp copy of the header
		// and create a new node as the header.
		Node<E> oldHeader = _header;
		_header = new Node<E>(obj, oldHeader, null);
		oldHeader.setPrevious(_header);
		_size++;
	}

	/**
	 * @inheritDoc 
	 * @exception Throws a NullPointerException if the E input is null. 
	 */
	@Override
	public void addLast(E obj) {
		// If the header is null, we have nothing.
		// the last position = the first position.
		if(true == isHeaderNull()){
			addFirst(obj);
			return;
			}

		Node<E> last = findLastNode();
		
		Node<E> newLast = new Node<E>(obj, null, last);
		
		last.setNext(newLast);
		
		_size++;
	}
	
	/**
	 * @inheritDoc 
	 */
	@Override
	public E remove(E obj){
		if(true == isHeaderNull() || null == obj){return null;}
		
		Node<E> currentObj = _header;
		
		while(null != currentObj){
			if(0 == currentObj.getNodeValue().compareTo(obj)){
				break;
			}
			currentObj = currentObj.getNext();
		}
	
		// If we didn't find anything.
		if(null == currentObj){
			return null;
		}
		// If it's the header.
		else if(null == currentObj.getPrevious()){
			return removeFirst();
		}
		// Else. Somewhere else.
		else{
			E returnObj = currentObj.getNodeValue();
			currentObj.getPrevious().setNext(currentObj.getNext());
			if(null != currentObj.getNext()){
				currentObj.getNext().setPrevious(currentObj.getPrevious());
			}
			_size--;
			return returnObj;
		}
	}

	/**
	 * @inheritDoc 
	 */
	@Override
	public E removeFirst() {
		if(true == isHeaderNull()){return null;}
		
		E firstObject = _header.getNodeValue();
		
		if(null == _header.getNext()){
			_header = null;
		}
		else{
			_header = _header.getNext();
			_header.setPrevious(null);
		}
		
		_size--;
		
		return firstObject;
	}

	/**
	 * @inheritDoc 
	 */
	@Override
	public E removeLast() {
		if(true == isHeaderNull()){return null;}
		
		Node<E> last = findLastNode();
		E lastObj = last.getNodeValue();
		
		// Check if the last node has a previous.
		// If it doesn't, that means it's the last
		// one. Set it to null.
		if(null == last.getPrevious()){
			last = null;
			_header = null;
		}
		// If it does, set the next value of the previous 
		// to null to remove the last from the list.
		else{last.getPrevious().setNext(null);}
		
		_size--;
		return lastObj;
	}

	/**
	 * @inheritDoc 
	 */
	@Override
	public E peekFirst() {
		if(isHeaderNull()){return null;}
		
		return _header.getNodeValue();
	}

	/**
	 * @inheritDoc 
	 */
	@Override
	public E peekLast() {
		if(true == isHeaderNull()){return null;}
		
		Node<E> last = findLastNode();
		
		return last.getNodeValue();
	}

	/**
	 * @inheritDoc 
	 */
	@Override
	public void makeEmpty() {
		_header = null;
		_size = 0;
	}

	/**
	 * @inheritDoc 
	 */
	@Override
	public boolean isEmpty() {return 0 == _size;}

	/**
	 * @inheritDoc 
	 */
	@Override
	public boolean isFull() {
		return false;
	}

	/**
	 * @inheritDoc 
	 */
	@Override
	public int size() {return _size;}

	/**
	 * @inheritDoc 
	 */
	@Override
	public boolean contains(E obj) {
		// First check if the input is null
		// The list does not accept null inputs
		// so if it is, we can rule it out immediately.
		if(true == isENull(obj)){return false;}
		
		// Next iterate through all of the nodes 
		// too see if one equals the input.
		for(E next : this)
		{
			if(0 == next.compareTo(obj)){return true;}
		}

		// Didn't find it.
		return false;
	}
	
	/**
	 * @inheritDoc 
	 */
	@Override
	public E find(E obj) {
		// First check if the input is null
		// The list does not accept null inputs
		// so if it is, we can rule it out immediately.
		if(true == isENull(obj)){return null;}
		
		// Next iterate through all of the nodes 
		// too see if one equals the input.
		for(E next : this)
		{
			if(0 == next.compareTo(obj)){return next;}
		}

		// Didn't find it.
		return null;
	}


	/**
	 * @inheritDoc 
	 */
	@Override
	public Iterator<E> iterator() {
		return new NodeIterator<E>(_header);
	}
	
	/**
	 * @inheritDoc 
	 */
	@Override
	public String toString(){
		String returnString = "";
		
		for(E next : this)
		{
			returnString += next.toString() + ": ";
		}

		return returnString;
	}
	
	/**
	 * Loops through the list, and finds the last node.
	 * @return The last node in the list.
	 */
	private Node<E> findLastNode(){
		// Check if the header is null. If the header
		// is null, there is nothing in the list. Return null.
		if(true == isHeaderNull()){return null;}
		
		// Start from the header.
		Node<E> last = _header;
		
		// Loop until we get to the end.
		while(null != last.getNext()){
			last = last.getNext();
		}
		
		return last;
	}
	
	/**
	 * Helper method that will check if an E object is null
	 * Used because it provides cleaner reading of the code.
	 * @param obj The generic object to check.
	 * @return True if the 
	 */
	private boolean isENull(E obj){
		return null == obj;
	}
	
	/**
	 * Validates if the input E is valid. If it isn't, it will
	 * throw an exception.
	 * @exception NullPointerException
	 * @param obj
	 */
	private void validateInput(E obj){
		if(true == isENull(obj)){
			throw new NullPointerException(
					"Object E was passed in as NULL. " +
					"This Linkedlist will not accept " + 
					"null as a value. Check the caling " +
					"code for coding errors."
				    );
		}
	}
	
	/**
	 * Checks if the header is null.
	 * @return
	 */
	private boolean isHeaderNull(){return null == _header;}

	private Node<E> _header;
	private int _size;
	
	/**
	 * The NodeIterator is the iterator that will help looping
	 * through all of the Nodes.
	 * @author cwixom
	 *
	 * @param <E>
	 */
	private class NodeIterator<T> implements Iterator<T>{

		/**
		 * The constructor for the NodeIterator
		 * @param current the starting point.
		 */
		public NodeIterator(Node<T> current){_current = current;}
		
		/**
		 * @inheritDoc 
		 */
		@Override
		public boolean hasNext() {
			// Check if current is null.
			if(null == _current){return false;}
			
			// We must have a next.
			return true;
		}

		/**
		 * @inheritDoc 
		 */
		@Override
		public T next() {
			// Check if current or next is null. 
			if(null == _current){return null;}
			
			T val = _current.getNodeValue();
			
			_current = _current.getNext();
			
			return val;
		}
		

		/**
		 * @exception Throws an UnsupportedOperationException
		 */
		@Override
		public void remove() {
			throw new UnsupportedOperationException();
		}
		
		private Node<T> _current;
	}
	
	/**
	 * The Node class represents a single node or element in the linked list.
	 * 
	 * @author cwixom
	 *
	 * @param <E> The generic object that represents the value of the Node
	 */
	private class Node<T>{
		/**
		 * The constructor for a Node.
		 * @param nodeValue The current generic value of the Node
		 * @param _next The next Node
		 * @param previous The previous Node.
		 */
		public Node(T nodeValue, Node<T> next, Node<T> previous){
			setNodeValue(nodeValue);
			setNext(next);
			setPrevious(previous);
		}
		
		/**
		 * Gets the node value of the current Node object.
		 * @return The node value
		 */
		public T getNodeValue(){return _nodeValue;}
		/**
		 * Sets the node value of the current Node object.
		 * @param nodeValue
		 */
		public void setNodeValue(T nodeValue){_nodeValue = nodeValue;}
		
		/**
		 * Gets the next Node for the Node.
		 * @return
		 */
		public Node<T> getNext(){return _next;}
		/**
		 * Sets the next Node for the Node.
		 * @param next
		 */
		public void setNext(Node<T> next){_next = next;}
		
		/**
		 * Gets the next Node for the Node.
		 * @return
		 */
		public Node<T> getPrevious(){return _previous;}
		/**
		 * Sets the next Node for the Node.
		 * @param next
		 */
		public void setPrevious(Node<T> previous){_previous = previous;}
		
		/**
		 * @inheritDoc 
		 */
		@Override
		public String toString(){
			String returnString = "";
			
			if(null == _nodeValue){
				returnString = "Value: NULL, ";
			}
			else{
				returnString = "Value: " + _nodeValue + ", ";
			}
			
			if(null == _next){
				returnString += "Next: NULL, ";
			}
			else{
				if(null == _next.getNodeValue()){
					returnString += "Next: NULL, ";
				}
				else{
					returnString += "Next: " + _next.getNodeValue().toString();
				}
			}
			
			if(null == _previous){
				returnString += "Previous: NULL, ";
			}
			else{
				if(null == _previous.getNodeValue()){
					returnString += "Previous: NULL, ";
				}
				else{
					returnString += "Previous: " + _previous.getNodeValue().toString();
				}
			}
			
			return returnString;
		}
		
		private T _nodeValue;
		private Node<T> _next;
		private Node<T> _previous;
	} 
}