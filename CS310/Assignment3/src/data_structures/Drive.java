package data_structures;

/**
 * Contains the brand and mtbf of a
 * particular hard drive.
 * @author cwixom (masc0582)
 */
public final class Drive implements Comparable<Drive>{
	/**
	 * The mtbf of the hard drive.
	 */
	private Double _mtbf;
	/**
	 * Gets the MTBF of the Drive.
	 * @return
	 */
	public Double getMtbf(){return _mtbf;}
	
	public void setMtbf(Double mtbf){_mtbf = mtbf;}
	
	public void setBrand(String brand){_brand = brand;}
	
	/**
	 * The brand name for the drive data.
	 */
	private String _brand;
	/**
	 * Gets the Brand of the Drive.
	 * @return
	 */
	public String getBrand(){return _brand;}
	
	public Drive(String brand, Double mtbf){
		if(null == brand || null == mtbf){
			throw new NullPointerException(
				"Brand or MTBF cannot be NULL.");
		}
		_brand = brand;
		_mtbf = mtbf;
	}

	/**
	 * Compares to drives.
	 * @param arg0
	 * @return
	 */
	@Override
	public int compareTo(Drive otherDrive) {
		if(null == otherDrive){return -1;}

		return getMtbf().compareTo(otherDrive.getMtbf());
	}
	
	/**
	 * Compares if the 2 drives are the same
	 * based on the brand.
	 */
	@Override
	public boolean equals(Object obj){
		if(null == obj){return false;}
		else if(false == (obj instanceof Drive)){
			return false;
		}
		
		Drive otherDrive = (Drive)obj;
		return getBrand().equals(otherDrive.getBrand());
	}
	
	/**
	 * Returns the String of the Drive.
	 */
	@Override
	public String toString(){
		return getBrand();
	}
	
	/**
	 * Returns the hash code of the 
	 * Drive.
	 */
	@Override
	public int hashCode(){
	    return (getBrand()==null  ? 0 : getBrand().hashCode()) ^
	            (getMtbf()==null ? 0 : getMtbf().hashCode());
	}
}
