package data_structures;

/**
 * An implementation of an AVL tree.
 * @author cwixom (masc0582)
 * @param <E> The data the tree will be storing.
 */
public class BalancedTree
	<E extends Comparable<E>>
	implements Tree<E>{
	
	/**
	 * The root node of the tree.
	 */
	private TreeNode<E> _root;
	
	/**
	 * Default constructor
	 */
	public BalancedTree(){}
	
	/**
	 * {@inheritDoc}
	 */
	public int height(){
		return null == _root ? 0 : _root.height();
	}

	/**
	 * {@inheritDoc}
	 */
	public void add(E data){
		// If the data is null throw it out
		// we don't like null data.
		if(null == data){
			throw new NullPointerException("Data cannot be null.");
		}
		TreeNode<E> newNode = new TreeNode<E>(data);
		if(null == _root){
			_root = newNode;
			return;
		}
		addNode(_root, newNode);
		_root = rebalance(_root);
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public E find(E data){
		if(null == data){return null;}
		
		TreeNode<E> dataNode = 
			find(_root, new TreeNode<E>(data));
		
		if(null != dataNode){
			return dataNode._data;
		}
		return null;
	}
	
	/**
	 * Returns a string representation
	 * of the tree.
	 */
	@Override
	public String toString(){
		return _root == null ? "" : _root.toString();
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public void clear(){
		_root = null;
	}
	
	/**
	 * Finds the Tree node that matches
	 * the data node passed in.
	 * @param node
	 * @param dataNode
	 * @return
	 */
	private TreeNode<E> find(
		TreeNode<E> node,
		TreeNode<E> dataNode){
		if(null == node){return null;}
		
		if(dataNode.compareTo(node) < 0){
			return find(node._leftChild, dataNode);
		}
		else if(dataNode.compareTo(node) > 0){
			return find(node._rightChild, dataNode);
		}
		return node;
	}
	
	/**
	 * Adds a new node in the subtree of
	 * the current node.
	 * @param currentNode
	 * @param newNode
	 */
	private void addNode(
		TreeNode<E> currentNode,
		TreeNode<E> newNode){
		
		// If the new node is > than the current node
		// then put the new node on the right
		// side.
		if(newNode.compareTo(currentNode) > 0){
			// Check if our right node is null.
			// if it is. Set the right now with the 
			// current node.
			if(null == currentNode._rightChild){
				currentNode._rightChild = newNode;
			}
			// Otherwise continue traversing the
			// tree to find the next one.
			else{
				addNode(currentNode._rightChild, newNode);
				currentNode._rightChild = rebalance(currentNode._rightChild);
			}
		}
		// If the new node <= the current node
		// put it on the left side.
		else{
			// If the left child is null, we
			// know this is where is goes. Place it.
			if(null == currentNode._leftChild){
				currentNode._leftChild = newNode;
			}
			// Otherwise continue traversing the
			// tree to find the next one.
			else{
				addNode(currentNode._leftChild, newNode);
				currentNode._leftChild = rebalance(currentNode._leftChild);
			}
		}
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public void set(E data){
		E found = find(data);
		if(null != found){
			found = data;
		}
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public E getCeiling(E data){
		if(data == null){
			return null;
		}
		
		TreeNode<E> dataNode = 
				new TreeNode<E>(data);
		
		TreeNode<E> ceilingNode = 
			getCeiling(_root, dataNode, _root, false);
		
		return null == ceilingNode ? null : ceilingNode._data;
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public E getFloor(E data){
		if(data == null){
			return null;
		}
		
		TreeNode<E> dataNode = 
				new TreeNode<E>(data);
		
		TreeNode<E> floorNode = 
			getFloor(_root, dataNode, _root, false);
		
		return null == floorNode ? null : floorNode._data;
	}
	
	private TreeNode<E> getCeiling(
		TreeNode<E> node,
		TreeNode<E> dataNode,
		TreeNode<E> previousNode,
		boolean wasLeft){
		if(null == node){return null;}
		
		if(dataNode.compareTo(node) < 0){
			if(null == node._leftChild){
				return node;
			}
			return getCeiling(node._leftChild, dataNode, node, true);
		}
		else if(dataNode.compareTo(node) > 0){
			if(null == node._rightChild){
				if(true == wasLeft){
					return previousNode;
				}
				return node;
			}
			return getCeiling(node._rightChild, dataNode, node, false);
		}
		return node;
	}
	
	private TreeNode<E> getFloor(
			TreeNode<E> node,
			TreeNode<E> dataNode,
			TreeNode<E> previousNode,
			boolean wasRight){
			if(null == node){return null;}

			if(dataNode.compareTo(node) > 0){

				if(null == node._rightChild){
					return node;
				}
				return getFloor(node._rightChild, dataNode,node, true);
			}
			else if(dataNode.compareTo(node) < 0){
				if(null == node._leftChild){
					if(wasRight){
						return previousNode;
					}
					return node;
				}
				return getFloor(node._leftChild, dataNode,node, false);
			}
			return node;
		}
	
	private TreeNode<E> leftMost(TreeNode<E> node){
		if(null == node){return null;}
		if(null == node._leftChild){return node;}
		return leftMost(node._leftChild);
	}
	
	private TreeNode<E> rightMost(TreeNode<E> node){
		if(null == node){return null;}
		if(null == node._rightChild){return node;}
		return rightMost(node._rightChild);
	}
	
	/**
	 * Re-balances the tree from the node.
	 * @param node
	 */
	private TreeNode<E> rebalance(TreeNode<E> node){
		if(null == node){return null;}
		
		TreeNode<E> leftChild = node._leftChild;
		TreeNode<E> rightChild = node._rightChild;
		
		// Check if the left side is unbalanced.
		if(height(leftChild) - height(rightChild) > 1){
			// Check how to fix the unbalance.
			// If unbalance in to the left of the child
			// we only need to right rotate, if the
			// unbalance is to the right of the child,
			// we need to do a left right rotate.
			if(leftChildHeight(leftChild) < rightChildHeight(leftChild)){
				return leftRightRotate(node);
			}
			else{
				return rightRotate(node);
			}
		}
		// Check if the right side is unbalanced.
		if(height(rightChild ) - height(leftChild) > 1){
			// Check how to fix the unbalance.
			// If unbalance in to the right of the child
			// we only need to left rotate, if the
			// unbalance is to the left of the child,
			// we need to do a right left rotate.
			if(leftChildHeight(rightChild) > rightChildHeight(rightChild)){
				return rightLeftRotate(node);
			}
			else{
				return leftRotate(node);
			}
		}

		return node;
	} 
	
	/**
	 * Gets the height of the node. If
	 * the node is null, returns 0.
	 * @param node
	 * @return
	 */
	private int height(TreeNode<E> node){
		return null == node ? -1 : node.height();
	}
	
	/**
	 * Gets the height of the right child of the node. 
	 * If the node is null, returns 0.
	 * @param node
	 * @return
	 */
	private int rightChildHeight(TreeNode<E> node){
		if(null == node){return 0;}
		
		return height(node._rightChild);
	}
	
	/**
	 * Gets the height of the left child of the node. 
	 * If the node is null, returns 0.
	 * @param node
	 * @return
	 */
	private int leftChildHeight(TreeNode<E> node){
		if(null == node){return 0;}
		
		return height(node._leftChild);
	}
	
	/**
	 * Right rotates the specified node.
	 * @param node The node to rotate
	 * @return the new node.
	 */
	private TreeNode<E> rightRotate(TreeNode<E> node){
		TreeNode<E> tempNode = node._leftChild;
		node._leftChild = tempNode._rightChild;
		tempNode._rightChild = node;
		return tempNode;
	}
	
	/**
	 * Left rotates the specified node.
	 * @param node The node to rotate
	 * @return the new node.
	 */
	private TreeNode<E> leftRotate(TreeNode<E> node){
		TreeNode<E> tempNode = node._rightChild;
		node._rightChild = tempNode._leftChild;
		tempNode._leftChild = node;
		return tempNode;
	}
	
	/**
	 * Left right rotates the tree 
	 * node passed in.
	 * @param node
	 * @return
	 */
	private TreeNode<E> leftRightRotate(TreeNode<E> node){
		node._leftChild = leftRotate(node._leftChild);
		return rightRotate(node);
	}
	
	/**
	 * Left right rotates the tree 
	 * node passed in.
	 * @param node
	 * @return
	 */
	private TreeNode<E> rightLeftRotate(TreeNode<E> node){
		node._rightChild = rightRotate(node._rightChild);
		return leftRotate(node);
	}
	
	/**
	 * Helper class that stores the 
	 * tree node information.
	 * @author cwixom (masc0582)
	 *
	 * @param <K>
	 */
	private class TreeNode
		<K extends Comparable<K>> 
		implements Comparable<TreeNode<K>>{
		
		K _data;
		TreeNode<K> _leftChild;
		TreeNode<K> _rightChild;
		
		/**
		 * Constructor with only data.
		 * @param data
		 */
		public TreeNode(K data){
			_data = data;
		}
		
		/**
		 * Returns the height of the node
		 * by recursively calling each 
		 * child to find the height.
		 * @return
		 */
		public int height(){
			int leftHeight = null == _leftChild ? 0 :  _leftChild.height();
			int rightHeight = null == _rightChild ? 0 :  _rightChild.height();
			
			return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
		}

		/**
		 * Compares one tree node to another
		 * based on the data.
		 * @param node The node to compare to.
		 * @return
		 */
		@Override
		public int compareTo(TreeNode<K> node) {
			if(null == node){return -1;}
			return _data.compareTo(node._data);
		}
		
		/**
		 * Returns a string for the
		 * node.
		 */
		@Override
		public String toString(){
			String returnString = "";
			returnString += "[";
			returnString += 
				null == _leftChild ? 
						"{} " : 
						_leftChild.toString() + " ";
			returnString += _data + " ";
			returnString += 
				null == _rightChild ? 
						"{}]" : 
						_rightChild.toString() + "]";
			
			return returnString;
		}
	}

}
