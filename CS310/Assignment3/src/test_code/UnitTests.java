package test_code;

import data_structures.*;

public class UnitTests {

	private static boolean _testsPassed = true;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		BalancedTree<Integer> balancedTree = new BalancedTree<Integer>();
		testTree(balancedTree);
		//RedBlackTree<Integer> rbTree = new RedBlackTree<Integer>();
		//testRedBlackTree(rbTree);
		logTest(_testsPassed, "Not all tests passed.");
	}
	
	private static void testRedBlackTree(RedBlackTree<Integer> tree){
		tree.add(8);
		tree.add(4);
		tree.add(12);
		tree.add(2);
		tree.add(6);
		tree.add(9);
		tree.add(14);
		tree.add(1);
		tree.add(3);
		tree.add(8);
		tree.add(10);
		
		logTest(tree.find(8) == 8, "8 was not found.");
		logTest(tree.find(12) == 12, "12 was not found.");
		logTest(tree.find(10) == 10, "10 was not found.");
	}
	
	private static void testTree(BalancedTree<Integer> tree){
		logTest(0 == tree.height(), "Height was not 0.");
		tree.add(8);
		logTest(1 == tree.height(), "Height was not 1.");
		tree.add(4);
		logTest(2 == tree.height(), "Height was not 2.");
		tree.add(12);
		tree.add(2);
		logTest(3 == tree.height(), "Height was not 3.");
		tree.add(6);
		tree.add(9);
		tree.add(14);
		tree.add(0);
		logTest(4 == tree.height(), "Height was not 4.");
		tree.add(3);
		logTest(4 == tree.height(), "Height was not 4.");
		tree.add(8);
		tree.add(10);
		
		logTest(
			tree.toString().equals("[[[[{} 0 {}] 2 [{} 3 {}]] 4 [[{} 6 {}] 8 {}]] 8 [[[{} 9 {}] 10 {}] 12 [{} 14 {}]]]"),
			"tree is not correct." + tree.toString());
		
		
		logTest(tree.getCeiling(5) == 6, "getCeiling didn't work: " + tree.getCeiling(5));
		logTest(tree.getCeiling(13) == 14, "getCeiling didn't work: " + tree.getCeiling(13));
		logTest(tree.getCeiling(2) == 2, "getCeiling didn't work: " + tree.getCeiling(2));
		logTest(tree.getCeiling(11) == 12, "getCeiling didn't work: " + tree.getCeiling(11));
		logTest(tree.getCeiling(1) == 2, "getCeiling didn't work: " + tree.getCeiling(1));
		
		
		logTest(tree.getFloor(5) == 4, "getFloor didn't work: " + tree.getFloor(5));
		logTest(tree.getFloor(13) == 12, "getFloor didn't work: " + tree.getFloor(13));
		logTest(tree.getFloor(13) == 12, "getFloor didn't work: " + tree.getFloor(13));
		logTest(tree.getFloor(1) == 0, "getFloor didn't work: " + tree.getFloor(0));
		logTest(tree.getFloor(11) == 10, "getFloor didn't work: " + tree.getFloor(11));
		//logTest(tree.inOrderSuccessor(12) == 14, "Inorder successor didn't work: " + tree.inOrderSuccessor(12));
		//logTest(tree.inOrderSuccessor(9) == 10, "Inorder successor didn't work: " + tree.inOrderSuccessor(9));
		//logTest(tree.inOrderSuccessor(2) == 3, "Inorder successor didn't work: " + tree.inOrderSuccessor(2));
		
		//logTest(tree.inOrderPredecessor(4) == 2, "inOrderPredecessor didn't work: " + tree.inOrderPredecessor(4));
		//logTest(tree.inOrderPredecessor(12) == 9, "inOrderPredecessor didn't work: " + tree.inOrderPredecessor(12));
		//logTest(tree.inOrderPredecessor(9) == 8, "inOrderPredecessor didn't work: " + tree.inOrderPredecessor(9));
		//logTest(tree.inOrderPredecessor(2) == 1, "inOrderPredecessor didn't work: " + tree.inOrderPredecessor(2));
		
		tree.clear();
		
		tree.add(8);
		tree.add(4);
		tree.add(2);
		logTest(tree.toString().equals("[[{} 2 {}] 4 [{} 8 {}]]"), "right rotation. " + tree.toString());
		tree.clear();
		
		tree.add(8);
		tree.add(10);
		tree.add(12);
		logTest(tree.toString().equals("[[{} 8 {}] 10 [{} 12 {}]]"), "left rotation. " + tree.toString());
		tree.clear();
		
		tree.add(43);
		tree.add(18);
		tree.add(22);
		logTest(tree.toString().equals("[[{} 18 {}] 22 [{} 43 {}]]"), "left right rotation. " + tree.toString());
		tree.clear();
		
		tree.add(43);
		tree.add(50);
		tree.add(47);
		logTest(tree.toString().equals("[[{} 43 {}] 47 [{} 50 {}]]"), "right left rotation. " + tree.toString());
		tree.clear();
		
		tree.add(8);
		tree.add(4);
		tree.add(12);
		tree.add(2);
		tree.add(6);
		tree.add(9);
		tree.add(14);
		tree.add(1);
		tree.add(3);
		tree.add(8);
		tree.add(10);
		
		logTest(true, tree.toString());
		
		logTest(tree.find(8) == 8, "8 was not found.");
		logTest(tree.find(12) == 12, "12 was not found.");
		logTest(tree.find(10) == 10, "10 was not found.");
		
		tree.clear();
		tree.add(43);
		tree.add(18);
		tree.add(22);
		logTest(true, tree.toString());
		tree.add(9);
		logTest(true, tree.toString());
		tree.add(21);
		logTest(true, tree.toString());
		tree.add(6);
		logTest(true, tree.toString());
		tree.add(8);
		logTest(true, tree.toString());
		tree.add(20);
		logTest(true, tree.toString());
		tree.add(63);
		logTest(true, tree.toString());
		tree.add(50);
		logTest(true, tree.toString());
		logTest(true, "START");
		tree.add(62);
		logTest(true, tree.toString());
		tree.add(51);
		logTest(true, tree.toString());
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
