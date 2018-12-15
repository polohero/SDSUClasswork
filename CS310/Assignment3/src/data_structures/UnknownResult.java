package data_structures;

/**
 * The class that contains the 
 * counts for a specific hard drive 
 * brand.
 * @author cwixom (masc0582)
 */
public class UnknownResult {
	
	/**
	 * Gets the name of the brand.
	 * @return
	 */
	public String getBrand(){return _brand;}
	private String _brand;
	
	/**
	 * Gets the count. The number 
	 * of times the brand was evaluated.
	 * @return
	 */
	public int getCount(){return _count;}
	private int _count;
	
	public UnknownResult(String brand){
		_brand = brand;
	}
	
	/**
	 * Increments the count.
	 */
	public void increment(){
		_count++;
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public boolean equals(Object obj){
		if(null == obj){return false;}
		if(false == (obj instanceof UnknownResult)){return false;}
		
		UnknownResult result = (UnknownResult)obj;
		return getBrand().equals(result.getBrand());
	}
}
